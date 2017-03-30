//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_DEFAULTFUTURE_H
#define DUBBOC_DEFAULTFUTURE_H

#include <remoting/dubboc_remoting_api/exchange/IResponseFuture.h>
#include <remoting/dubboc_remoting_api/IChannel.h>
#include <remoting/dubboc_remoting_api/exchange/Response.h>
#include <remoting/dubboc_remoting_api/exchange/Request.h>
#include <unordered_map>
#include <remoting/dubboc_remoting_api/TimeoutException.h>
#include <iomanip>


namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class DefaultFuture : public IResponseFuture, public enable_shared_from_this<DefaultFuture> {
        public:
            explicit DefaultFuture(shared_ptr<IChannel> channel, shared_ptr<Request> request, uint32_t timeout) {
                this->channel = channel;
                this->request = request;
                this->timeout = timeout;
                this->id = request->getMId();
                this->timeout = timeout > 0 ? timeout : channel->getUrl()->getPositiveParameter(Constants::TIMEOUT_KEY,
                                                                                                Constants::DEFAULT_TIMEOUT);
                futures_rwlock.lock();
                FUTURES[this->id] = shared_from_this();
                futures_rwlock.unlock();
                channels_rwlock.lock();
                CHANNELS[this->id] = channel;
                channels_rwlock.unlock();
                if (!daemon_thread_flag.test_and_set(std::memory_order_acquire)) {
                    thread daemon([]() {

                    });
                    daemon.detach();
                }

            }

        public:
            folly::dynamic get() override {
                return get(timeout);
            }

            folly::dynamic get(uint32_t timeoutInMillis) override {
                if (timeout == 0) {
                    timeout = Constants::DEFAULT_TIMEOUT;
                }
                if (!isDone()) {
                    auto start = std::chrono::system_clock::now();
                    std::lock_guard<std::recursive_mutex> lck(reentrant_lock);
                    try {
                        while (!isDone()) {
                            std::unique_lock<std::mutex> lk(done_lock);
                            done.wait_for(lk, timeout * 1ms);
                            if (isDone() || std::chrono::duration_cast<std::chrono::microseconds>(
                                    std::chrono::system_clock::now() - start).count() > timeout) {
                                break;
                            }
                        }
                    } catch (const std::exception &e) {
                        throw;
                    }
                    if (!isDone()) {
                        throw TimeoutException(issent.time_since_epoch().count() > 0, channel,
                                               getTimeoutMessage(false));
                    }
                }
                return returnFromResponse();
            }

            void setCallback(shared_ptr<IResponseCallback> callback) override {
                if (isDone()) {
                    invokeCallback(callback);
                } else {
                    bool isdone = false;
                    std::lock_guard<std::recursive_mutex> lck(reentrant_lock);
                    if (!isDone()) {
                        this->callback = callback;
                    } else {
                        isdone = true;
                    }
                    if (isdone) {
                        invokeCallback(callback);
                    }
                }
            }

            void cancel() {
                auto errorResult = make_shared<Response>(id);
                errorResult->setMErrorMsg("request future has been canceled.");
                response = errorResult;
                futures_rwlock.lock();
                FUTURES.erase(id);
                futures_rwlock.unlock();
                channels_rwlock.lock();
                CHANNELS.erase(id);
                channels_rwlock.unlock();
            }

            bool isDone() override {
                return response != nullptr;
            }

        private:
            folly::dynamic const &returnFromResponse() {
                if (response == nullptr) {
                    throw std::invalid_argument("response cannot be null");
                }

                if (response->getMStatus() == Response::OK) {
                    return response->getMResult();
                }

                if (response->getMStatus() == Response::CLIENT_TIMEOUT ||
                    response->getMStatus() == Response::SERVER_TIMEOUT) {
                    throw TimeoutException(response->getMStatus() == Response::SERVER_TIMEOUT, channel,
                                           response->getMErrorMsg());
                }
                throw RemotingException(channel, response->getMErrorMsg());
            }

            void doSent() {
                // 只是记录发送时间
                issent = std::chrono::system_clock::now();
            }

            void invokeCallback(shared_ptr<IResponseCallback> c) {
                auto callbackCopy = c;
                if (callbackCopy == nullptr) {
                    throw std::invalid_argument("callback cannot be null.");
                }
                c = nullptr;
                auto res = response;
                if (res->getMStatus() == Response::OK) {
                    try {
                        callbackCopy->done(res->getMResult());
                    } catch (const std::exception &e) {
                        LOG(ERROR) << "callback invoke error .reasult:" + folly::toJson(res->getMResult()) + ",url:" +
                                      channel->getUrl()->toFullString() << e.what();
                    }
                } else if (res->getMStatus() == Response::CLIENT_TIMEOUT ||
                           res->getMStatus() == Response::SERVER_TIMEOUT) {
                    try {
                        TimeoutException te(res->getMStatus() == Response::SERVER_TIMEOUT, channel,
                                            res->getMErrorMsg());
                        callbackCopy->caught(te);
                    } catch (const std::exception &e) {
                        LOG(ERROR) << "callback invoke error ,url:" + channel->getUrl()->toFullString() << e.what();
                    }
                } else {
                    try {
                        std::runtime_error re(res->getMErrorMsg());
                        callbackCopy->caught(re);
                    } catch (const std::exception &e) {
                        LOG(ERROR) << "callback invoke error ,url:" + channel->getUrl()->toFullString() << e.what();
                    }
                }
            }

            static shared_ptr<DefaultFuture> getFuture(long id) {
                folly::RWSpinLock::ReadHolder readHolder(futures_rwlock);
                auto iter = FUTURES.find(id);
                if (iter != FUTURES.end()) {
                    return iter->second;
                }
                return nullptr;
            }

            static bool hasFuture(shared_ptr<IChannel> channel) {
                folly::RWSpinLock::ReadHolder readHolder(channels_rwlock);
                for (auto &it:CHANNELS) {
                    if (it.second == channel) {
                        return true;
                    }
                }
                return false;
            }

            static void sent(shared_ptr<IChannel> channel, shared_ptr<Request> request) {
                folly::RWSpinLock::ReadHolder readHolder(futures_rwlock);
                auto iter = FUTURES.find(request->getMId());
                if (iter != FUTURES.end()) {
                    iter->second->doSent();
                }
            }

            static void received(shared_ptr<IChannel> channel, shared_ptr<Response> response) {
                try {
                    // 根据请求ID移除映射（响应id和请求id一致对应）
                    folly::RWSpinLock::WriteHolder writeHolder(futures_rwlock);
                    auto iter = FUTURES.find(response->getMId());
                    shared_ptr<DefaultFuture> future = nullptr;
                    if (iter != FUTURES.end()) {
                        future = iter->second;
                        FUTURES.erase(iter);
                    }

                    if (future != nullptr) {
                        // 调用future的doReceived
                        future->doReceived(response);
                    } else {
                        auto now = std::chrono::system_clock::now();
                        auto now_t = chrono::system_clock::to_time_t(now);

                        LOG(WARNING) << "The timeout response finally returned at "
                                     << std::put_time(std::localtime(&now_t), "%Y-%m-%d %H.%M.%S")
                                     << ", response " << response->toString()
                                     << (channel == nullptr ? "" :
                                         std::string(", channel: ") + channel->getLocalAddress().getAddressStr()
                                         + " -> " + channel->getRemoteAddress().getAddressStr());
                    }
                } catch (...) {
                    FUTURES.erase(response->getMId());
                }
            }

            void doReceived(shared_ptr<Response> res) {
                std::lock_guard<std::recursive_mutex> lck(reentrant_lock);

                // 设置响应体
                response = res;
                // 向条件变量发送信号。唤醒等待线程
                done.notify_one();

                // 如果为future设置了回调
                if (callback != nullptr) {
                    invokeCallback(callback);
                }
            }

            string getTimeoutMessage(bool scan) {
                auto startTimestampTime_t = chrono::system_clock::to_time_t(start);
                auto nowTimestamp = std::chrono::system_clock::now();
                auto nowTimestampTime_t = chrono::system_clock::to_time_t(nowTimestamp);
                std::ostringstream os;
                os << (issent.time_since_epoch().count() > 0
                       ? "Waiting server-side response timeout" : "Sending request timeout in client-side");
                os << (scan ? " by scan timer" : "");
                os << ". start time: ";
                os << std::put_time(std::localtime(&nowTimestampTime_t), "%Y-%m-%d %H.%M.%S");
                os << ", end time: ";
                os << std::put_time(std::localtime(&nowTimestampTime_t), "%Y-%m-%d %H.%M.%S");
                os << ",";
                os << (issent.time_since_epoch().count() > 0 ? (
                        std::string(" client elapsed: ") +
                        to_string(
                                std::chrono::duration_cast<std::chrono::microseconds>(
                                        issent - start).count()) +
                        " ms, server elapsed: " +
                        to_string(std::chrono::duration_cast<std::chrono::microseconds>(
                                nowTimestamp - issent).count())) :
                       (std::string(" elapsed: ") +
                        to_string(
                                std::chrono::duration_cast<std::chrono::microseconds>(nowTimestamp - start).count())));
                os << " ms, timeout: ";
                os << timeout << " ms, request: " << request->toString() << ", channel: "
                   << channel->getLocalAddress().getAddressStr();
                os << " -> " << channel->getRemoteAddress().getAddressStr();

                return os.str();
            }

            std::chrono::system_clock::time_point const &getStartTimestamp() {
                return start;
            }

            uint32_t getTimeout() {
                return timeout;
            }

            long getId() {
                return id;
            }

            bool isSent() {
                return issent.time_since_epoch().count() > 0;
            }

            shared_ptr<IChannel> getChannel() {
                return channel;
            }

            static void RemotingInvocationTimeoutScan() {
                while (true) {
                    try {
                        for (auto &it: FUTURES) {
                            if (it.second == nullptr || it.second->isDone()) {
                                continue;
                            }
                            auto future = it.second;
                            auto now = std::chrono::system_clock::now();
                            if (std::chrono::duration_cast<std::chrono::microseconds>(
                                    now - future->getStartTimestamp()).count() > future->getTimeout()) {
                                auto timeoutResponse = make_shared<Response>(future->getId());
                                timeoutResponse->setMStatus(
                                        future->isSent() ? Response::SERVER_TIMEOUT : Response::CLIENT_TIMEOUT);

                                DefaultFuture::received(future->getChannel(), timeoutResponse);
                            }
                        }
                        std::this_thread::sleep_for(30 * 1ms);
                    } catch (const std::exception &e) {
                        LOG(ERROR) << "Exception when scan the timeout invocation of remoting." << e.what();
                    }
                }
            }

        private:
            long id{0};
            shared_ptr<IChannel> channel{nullptr};
            shared_ptr<Request> request{nullptr};
            shared_ptr<Response> response{nullptr};
            shared_ptr<IResponseCallback> callback{nullptr};
            uint32_t timeout{0};
            std::condition_variable done;
            std::mutex done_lock;
            std::chrono::system_clock::time_point start{std::chrono::system_clock::now()};
            std::chrono::system_clock::time_point issent;
            static unordered_map<long, shared_ptr<IChannel>> CHANNELS;
            static unordered_map<long, shared_ptr<DefaultFuture>> FUTURES;
            static folly::RWSpinLock channels_rwlock;
            static folly::RWSpinLock futures_rwlock;
            static std::atomic_flag daemon_thread_flag;
            std::recursive_mutex reentrant_lock;
        };
    }
}
#endif //DUBBOC_DEFAULTFUTURE_H
