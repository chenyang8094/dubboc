//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_HEADEREXCHANGECHANNEL_H
#define DUBBOC_HEADEREXCHANGECHANNEL_H

#include <remoting/dubboc_remoting_api/exchange/IExchangeChannel.h>
#include <memory>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;


        class HeaderExchangeChannel : public IExchangeChannel, public enable_shared_from_this<HeaderExchangeChannel> {
        public:
            explicit HeaderExchangeChannel(shared_ptr<IChannel> channel) {
                if (channel == nullptr) {
                    throw std::invalid_argument("channel is null.");
                }
                this->channel = channel;
            }

        public:

            static shared_ptr<HeaderExchangeChannel> getOrAddChannel(shared_ptr<IChannel> ch);

            static void removeChannelIfDisconnected(shared_ptr<IChannel> ch);

            shared_ptr<IResponseFuture> request(const folly::dynamic &request) override;

            shared_ptr<IResponseFuture> request(const folly::dynamic &request, uint32_t timeout) override;

            shared_ptr<IExchangeHandler> getExchangeHandler() override;

            void close(uint32_t timeout) override;

            folly::SocketAddress getRemoteAddress() override;

            bool isConnected() override;

            bool hasAttribute(const std::string &key) override;

            boost::any getAttribute(const std::string &key) override;

            void setAttribute(const std::string &key, const boost::any &value) override;

            void removeAttribute(const std::string &key) override;

            shared_ptr<URL> getUrl() override;

            shared_ptr<IChannelHandler> getChannelHandler() override;

            folly::SocketAddress getLocalAddress() override;

            void send(const folly::dynamic &message) override;

            void send(const folly::dynamic &message, bool sent) override;

            void close() override;

            bool isClosed() override;

        private:
            shared_ptr<IChannel> channel{nullptr};
            volatile bool closed{false};
            static const std::string CHANNEL_KEY;
        };
    }
}
#endif //DUBBOC_HEADEREXCHANGECHANNEL_H
