//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_WANGLECHANNEL_H
#define DUBBOC_WANGLECHANNEL_H

#include <remoting/dubboc_remoting_api/transport/AbstractChannel.h>
//#include <wangle/channel/EventBaseHandler.h>
#include <wangle/channel/Pipeline.h>
#include <chrono>

namespace DUBBOC {
    namespace REMOTING {
        using DubbocPipeline = wangle::Pipeline<folly::IOBufQueue &, const folly::dynamic &>;

        class WangleChannel : public AbstractChannel, public std::enable_shared_from_this<WangleChannel> {
        public:
            WangleChannel(shared_ptr<DubbocPipeline> channel, shared_ptr<URL> url,
                          shared_ptr<IChannelHandler> handler) : AbstractChannel(url, handler) {
                if (channel == nullptr) {
                    throw std::invalid_argument("wangle channel is null;");
                }
                this->channel = channel;
            }

            static shared_ptr<WangleChannel> getOrAddChannel(shared_ptr<DubbocPipeline> ch, shared_ptr<URL> url,
                                                             shared_ptr<IChannelHandler> handler) {
                if (ch == nullptr) {
                    return nullptr;
                }
                // 根据Netty的channel映射dubbo自己的channel
                rwSpinLock.lock_shared();
                auto iter = channelMap.find(ch);
                if (iter != channelMap.end()) {
                    rwSpinLock.unlock_shared();
                    return iter->second;
                }
                rwSpinLock.unlock_shared();

                // 没有的话就新建一个
                auto wc = make_shared<WangleChannel>(ch, url, handler);
                // 如果channel是已经连接的，就加入映射
                if (ch->getTransport()->connecting()) {
                    rwSpinLock.lock();
                    auto iter = channelMap.find(ch);
                    if (iter != channelMap.end()) {
                        rwSpinLock.unlock();
                        return iter->second;
                    }
                    channelMap[ch] = wc;
                    rwSpinLock.unlock();
                }
                return wc;
            }

            static void removeChannelIfDisconnected(shared_ptr<DubbocPipeline> ch) {
                // 如果channel已经关闭连接，则移除映射
                if (ch != nullptr && !ch->getTransport()->connecting()) {
                    rwSpinLock.lock();
                    channelMap.erase(ch);
                    rwSpinLock.unlock();
                }
            }

            folly::SocketAddress getLocalAddress() override {
                folly::SocketAddress local_address;
                channel->getTransport()->getLocalAddress(&local_address);
                return local_address;
            }

            folly::SocketAddress getRemoteAddress() override {
                folly::SocketAddress remote_address;
                channel->getTransport()->getPeerAddress(&remote_address);
                return remote_address;
            }

            bool isConnected() override {
                return channel->getTransport()->connecting();
            }

            void send(const folly::dynamic &message, bool sent) override {
                // 如果关闭就抛异常
                AbstractChannel::send(message, sent);

                bool success = true;
                int timeout = 0;
                try {
                    // Request
                    auto future = channel->write(message);
                    // 如果已发送完成
                    if (sent) {
                        timeout = getUrl()->getPositiveParameter(Constants::TIMEOUT_KEY, Constants::DEFAULT_TIMEOUT);
                        // 等待超时时间
                        future.then([&success] {
                            success = true;
                            return;
                        }).onError([](std::runtime_error &e) {
                            throw e;
                        }).wait(timeout * 1ms);
                    }

                } catch (const std::exception &e) {
                    throw e;
                }
            }

            void close() override {
                try {
                    AbstractChannel::close();
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }
                try {
                    removeChannelIfDisconnected(channel);
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }
                try {
                    attributes.erase(attributes.begin(), attributes.end());
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }
                try {
                    LOG(INFO) << "Close wangle channel ";
                    channel->close();
                } catch (const std::exception &e) {
                    LOG(WARNING) << e.what();
                }
            }

            bool hasAttribute(const string &key) override {
                folly::RWSpinLock::ReadHolder readHolder(attr_rwSpinLock);
                return attributes.get_ptr(key) != nullptr;
            }

            folly::dynamic getAttribute(const string &key) override {
                folly::RWSpinLock::ReadHolder readHolder(attr_rwSpinLock);
                if (attributes.get_ptr(key)) {
                    return attributes[key];
                }
                return nullptr;
            }

            void setAttribute(const string &key, const folly::dynamic &value) override {
                folly::RWSpinLock::WriteHolder writeHolder(attr_rwSpinLock);
                if (value.isNull()) {
                    attributes.erase(key);
                } else {
                    attributes[key] = value;
                }
            }

            void removeAttribute(const string &key) override {
                folly::RWSpinLock::WriteHolder writeHolder(attr_rwSpinLock);
                attributes.erase(key);
            }

        private:
            shared_ptr<DubbocPipeline> channel;
            folly::dynamic attributes{folly::dynamic::object()};
            folly::RWSpinLock attr_rwSpinLock;
            static unordered_map<shared_ptr<DubbocPipeline>, shared_ptr<WangleChannel>> channelMap;
            static folly::RWSpinLock rwSpinLock;
        };
    }
}
#endif //DUBBOC_WANGLECHANNEL_H
