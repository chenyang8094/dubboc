//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_ABSTRACTCLIENT_H
#define DUBBOC_ABSTRACTCLIENT_H

#include <folly/futures/Future.h>
#include <folly/futures/InlineExecutor.h>
#include <folly/futures/ManualExecutor.h>
#include <folly/futures/QueuedImmediateExecutor.h>
#include <folly/futures/ScheduledExecutor.h>
#include <folly/Baton.h>
#include <remoting/dubboc_remoting_api/IClient.h>
#include <remoting/dubboc_remoting_api/RemotingException.h>
#include <remoting/dubboc_remoting_api/transport/dispatcher/ChannelHandlers.h>
#include <folly/Executor.h>
#include "AbstractEndpoint.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class AbstractClient : public AbstractEndpoint, public IClient {
        public:
            AbstractClient(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) : AbstractEndpoint(url, handler) {
                send_reconnect = url->getParameter(Constants::SEND_RECONNECT_KEY, false);
                shutdown_timeout = url->getParameter(Constants::SHUTDOWN_TIMEOUT_KEY,
                                                     Constants::DEFAULT_SHUTDOWN_TIMEOUT);
                //默认重连间隔2s，1800表示1小时warning一次.
                reconnect_warning_period = url->getParameter(string("reconnect.waring.period"), 1800);

                try {
                    // 调用工厂方法，具体实现比如netty，创建Client的时候都是自动打开端口
                    doOpen();
                } catch (const std::exception &t) {
                    close();
                    throw RemotingException(url->toInetSocketAddress(), folly::SocketAddress(),
                                            string("Failed to start ") + "AbstractClient" + " " +
                                            NetUtils::getLocalAddress()->str()
                                            + " connect to the server " + getRemoteAddress().getAddressStr() +
                                            ", cause: " + t.what());
                }

                try {
                    // connect.
                    connect();//会调用doConnect工厂方法进行连接
                    LOG(INFO) << "Start " << "AbstractClient" << " " << NetUtils::getLocalAddress()->str()
                              << " connect to the server " << getRemoteAddress().getAddressStr();
                } catch (const RemotingException &t) {
                    if (url->getParameter(Constants::CHECK_KEY, true)) {
                        close();
                        throw t;
                    } else {
                        LOG(WARNING) << "Failed to start " << "AbstractClient" << " "
                                     << NetUtils::getLocalAddress()->str()
                                     << " connect to the server " << getRemoteAddress().getAddressStr() <<
                                     " (check == false, ignore and retry later!), cause: " << t.what();
                    }
                } catch (const std::exception &t) {
                    close();
                    throw RemotingException(url->toInetSocketAddress(), folly::SocketAddress(),
                                            string("Failed to start ") + "AbstractClient" + " " +
                                            NetUtils::getLocalAddress()->str()
                                            + " connect to the server " + getRemoteAddress().getAddressStr() +
                                            ", cause: " +
                                            t.what());
                }
                // 获取执行线程池
                executor = std::make_shared<folly::ManualExecutor>();
                reconnectExecutorService = std::make_shared<folly::ManualExecutor>();
            }


        protected:
            static shared_ptr<IChannelHandler>
            wrapChannelHandler(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) {
//                url = ExecutorUtil.setThreadName(url, CLIENT_THREAD_POOL_NAME);
                url = url->addParameterIfAbsent(Constants::THREADPOOL_KEY, Constants::DEFAULT_CLIENT_THREADPOOL);
                return ChannelHandlers::wrap(handler, url);
            }

            virtual void connect() {
                std::lock_guard<std::recursive_mutex> lck(reentrant_lock);
                try {
                    if (isConnected()) {
                        return;
                    }
                    initConnectStatusCheckCommand();
                    doConnect();// 工厂方法
                    if (!isConnected()) {
//                            throw RemotingException(this, "Failed connect to server " + getRemoteAddress() + " from " + getClass().getSimpleName() + " "
//                                                              + NetUtils.getLocalHost() + " using dubbo version " + Version.getVersion()
//                                                              + ", cause: Connect wait timeout: " + getTimeout() + "ms.");
                    } else {

//                                logger.info("Successed connect to server " + getRemoteAddress() + " from " + getClass().getSimpleName() + " "
//                                            + NetUtils.getLocalHost() + " using dubbo version " + Version.getVersion()
//                                            + ", channel is " + this.getChannel());

                    }
                    reconnect_count.store(0);
                    reconnect_error_log_flag.clear();
                } catch (const RemotingException &e) {
                    throw e;
                } catch (const std::exception &e) {
//                    throw new RemotingException(this, "Failed connect to server " + getRemoteAddress() + " from " +
//                                                      getClass().getSimpleName() + " "
//                                                      + NetUtils.getLocalHost() + " using dubbo version " +
//                                                      Version.getVersion()
//                                                      + ", cause: " + e.getMessage(), e);
                }

            }

        private:
            static int getReconnectParam(shared_ptr<URL> url) {
                int reconnect;
                string param = url->getParameter(Constants::RECONNECT_KEY);
                if (param.empty() || boost::algorithm::iequals("true", param)) {
                    reconnect = Constants::DEFAULT_RECONNECT_PERIOD;
                } else if (boost::algorithm::iequals("false", param)) {
                    reconnect = 0;
                } else {
                    try {
                        reconnect = stoi(param);
                    } catch (const std::exception &e) {
                        throw std::invalid_argument(
                                string("reconnect param must be nonnegative integer or false/true. input is:") + param);
                    }
                    if (reconnect < 0) {
                        throw std::invalid_argument(
                                string("reconnect param must be nonnegative integer or false/true. input is:") + param);
                    }
                }
                return reconnect;
            }

            void destroyConnectStatusCheckCommand() {
                if (reconnectExecutorService) {
                    reconnectExecutorService->clear();
                }
            }

            void initConnectStatusCheckCommand() {
                //reconnect=false to close reconnect
                int reconnect = getReconnectParam(getUrl());
                if (reconnect > 0 && reconnectExecutorService != nullptr) {
                    auto connectStatusCheckCommand = [this]{
                        try {
                            if (!isConnected()) {
                                connect();
                            } else {
                                lastConnectedTime = std::chrono::system_clock::now();
                            }
                        } catch (const std::exception &t) {
                            string errorMsg =
                                    string("client reconnect to ") + getUrl()->getAddress() + " find error . url: " +
                                    getUrl()->toFullString();
                            // wait registry sync provider list
                            auto now = std::chrono::system_clock::now();
                            if (std::chrono::duration_cast<std::chrono::microseconds>(
                                    now - lastConnectedTime).count() > shutdown_timeout) {

                                if (!reconnect_error_log_flag.test_and_set(std::memory_order_acquire)) {
                                    LOG(ERROR) << errorMsg;
                                    return;
                                }
                            }
                            if (reconnect_count++ % reconnect_warning_period == 0) {
                                LOG(WARNING) << errorMsg;
                            }
                        }
                    };


                    reconnectExecutorService->schedule(std::move(connectStatusCheckCommand), reconnect * 1ms);
                    reconnectExecutorService->run();

                }
            }

        public:
            folly::SocketAddress getConnectAddress() {
                return folly::SocketAddress(NetUtils::filterLocalHost(getUrl()->getHost()), getUrl()->getPort());
            }

            virtual folly::SocketAddress getRemoteAddress() override {
                auto channel = getChannel();
                if (channel == nullptr)
                    return getUrl()->toInetSocketAddress();
                return channel->getRemoteAddress();
            }

            virtual folly::SocketAddress getLocalAddress() override {
                auto channel = getChannel();
                if (channel == nullptr)
                    return folly::SocketAddress(NetUtils::getLocalHost(), 0);
                return channel->getLocalAddress();
            }

            bool isConnected() override {
                auto channel = getChannel();//getChannel()为工厂方法，由具体实现，比如netty,返回的为dubbo的Channel
                if (channel == nullptr)
                    return false;
                return channel->isConnected();
            }

            folly::dynamic getAttribute(const string &key) override {
                auto channel = getChannel();
                if (channel == nullptr)
                    return nullptr;
                return channel->getAttribute(key);
            }

            void setAttribute(const string &key, const folly::dynamic &value) override {
                auto channel = getChannel();
                if (channel == nullptr)
                    return;
                channel->setAttribute(key, value);
            }

            void removeAttribute(const string &key) override {
                auto channel = getChannel();
                if (channel == nullptr)
                    return;
                channel->removeAttribute(key);
            }

            bool hasAttribute(const string &key) override {
                auto channel = getChannel();
                if (channel == nullptr)
                    return false;
                return channel->hasAttribute(key);
            }

            virtual void send(const folly::dynamic &message, bool sent) override {
                if (send_reconnect && !isConnected()) {
                    connect();
                }
                auto channel = getChannel();
                //TODO getChannel返回的状态是否包含null需要改进
                if (channel == nullptr || !channel->isConnected()) {
//                        throw new RemotingException(this, "message can not send, because channel is closed . url:" + getUrl());
                }
                channel->send(message, sent);
            }

            virtual void disconnect() {
                std::lock_guard<std::recursive_mutex> lck(reentrant_lock);

                destroyConnectStatusCheckCommand();
                try {
                    auto channel = getChannel();
                    if (channel != nullptr) {
                        channel->close();
                    }
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }
                try {
                    doDisConnect();
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }

            }

            virtual void reconnect() override {
                disconnect();
                connect();
            }

            virtual void close() override {
                try {
                    if (executor != nullptr) {
//                        ExecutorUtil.shutdownNow(executor, 100);
                    }
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }
                try {
                    AbstractEndpoint::close();
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }
                try {
                    disconnect();
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }
                try {
                    doClose();
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }
            }

            virtual void close(uint32_t timeout) override {
//                ExecutorUtil.gracefulShutdown(executor ,timeout);
                close();
            }

        protected:
            /****************************具体的有不同的客户端实现*****************************/
            /**
             * Open client.
             *
             * @throws Throwable
             */
            virtual void doOpen() {
                throw std::runtime_error("invoke abstract method.");
            };

            /**
             * Close client.
             *
             * @throws Throwable
             */
            virtual void doClose() {
                throw std::runtime_error("invoke abstract method.");
            }

            /**
             * Connect to server.
             *
             * @throws Throwable
             */
            virtual void doConnect() {
                throw std::runtime_error("invoke abstract method.");
            }

            /**
             * disConnect to server.
             *
             * @throws Throwable
             */
            virtual void doDisConnect() {
                throw std::runtime_error("invoke abstract method.");
            }

            /**
             * Get the connected channel.
             *
             * @return channel
             */

            virtual shared_ptr<IChannel> getChannel() {
                throw std::runtime_error("invoke abstract method.");
            }

        private:
            bool send_reconnect{false};
            long shutdown_timeout{0};
            int reconnect_warning_period{0};
            std::shared_ptr<folly::ManualExecutor> executor{nullptr};
            std::shared_ptr<folly::ManualExecutor> reconnectExecutorService{nullptr};
            std::recursive_mutex reentrant_lock;
            std::atomic_uint reconnect_count{0};
            std::atomic_flag reconnect_error_log_flag = ATOMIC_FLAG_INIT;
            std::chrono::system_clock::time_point lastConnectedTime{std::chrono::system_clock::now()};
        };
    }
}
#endif //DUBBOC_ABSTRACTCLIENT_H
