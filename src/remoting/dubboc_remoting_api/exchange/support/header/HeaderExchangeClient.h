//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_HEADEREXCHANGECLIENT_H
#define DUBBOC_HEADEREXCHANGECLIENT_H

#include <remoting/dubboc_remoting_api/exchange/IExchangeClient.h>
#include "HeaderExchangeChannel.h"
#include <folly/futures/ManualExecutor.h>
#include <list>

namespace DUBBOC {
    namespace REMOTING {


        class HeaderExchangeClient : public IExchangeClient, public std::enable_shared_from_this<HeaderExchangeClient> {
        public:
            explicit HeaderExchangeClient(std::shared_ptr<IClient> client) {
                if (client == nullptr) {
                    throw std::invalid_argument("client is null.");
                }

                this->client = client;
                this->channel = std::make_shared<HeaderExchangeChannel>(client);
                std::string dubboc = client->getUrl()->getParameter(Constants::DUBBOC_VERSION_KEY);
                this->heartbeat = client->getUrl()->getParameter(Constants::HEARTBEAT_KEY, !dubboc.empty() &&
                                                                                           boost::algorithm::starts_with(
                                                                                                   dubboc, "1.0.")
                                                                                           ? Constants::DEFAULT_HEARTBEAT
                                                                                           : 0);
                this->heartbeatTimeout = client->getUrl()->getParameter(Constants::HEARTBEAT_TIMEOUT_KEY,
                                                                        (int) (heartbeat * 3));
                if (heartbeatTimeout < heartbeat * 2) {
                    throw std::invalid_argument("heartbeatTimeout < heartbeatInterval * 2");
                }

                scheduled = std::make_shared<folly::ManualExecutor>();

                startHeatbeatTimer();
            }

            virtual ~HeaderExchangeClient() {}


        public:
            shared_ptr<IResponseFuture> request(const folly::dynamic &request) override;

            shared_ptr<IResponseFuture> request(const folly::dynamic &request, uint32_t timeout) override;

            shared_ptr<IExchangeHandler> getExchangeHandler() override;

            void close(uint32_t timeout) override;

            void reconnect() override;

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
            void startHeatbeatTimer() {
                thread_local std::list<std::shared_ptr<IChannel>> providers;

//                providers.push_back(shared_from_this());
                stopHeartbeatTimer();
                if (heartbeat > 0) {
                    scheduled->schedule([] {
                        auto now = std::chrono::system_clock::now();
                        for (auto &channel :providers) {

                        }

                    }, std::chrono::microseconds(heartbeatTimeout));
                }

            }

            void stopHeartbeatTimer() {
                scheduled->clear();
            }

            void doClose() {
                stopHeartbeatTimer();
            }


        private:
            static shared_ptr<folly::ManualExecutor> scheduled;
            int heartbeat{0};
            int heartbeatTimeout{0};
            std::shared_ptr<IClient> client{nullptr};
            std::shared_ptr<IExchangeChannel> channel{nullptr};
        };
    }
}
#endif //DUBBOC_HEADEREXCHANGECLIENT_H
