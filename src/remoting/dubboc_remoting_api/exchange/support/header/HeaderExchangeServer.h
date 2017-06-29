//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_HEADEREXCHANGESERVER_H
#define DUBBOC_HEADEREXCHANGESERVER_H


#include <remoting/dubboc_remoting_api/exchange/IExchangeServer.h>
#include <list>
#include <remoting/dubboc_remoting_api/RemotingException.h>
#include <folly/json.h>
#include <folly/futures/ManualExecutor.h>
#include <remoting/dubboc_remoting_api/exchange/support/DefaultFuture.h>
#include "HeaderExchangeChannel.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class HeaderExchangeServer : public IExchangeServer {
        public:
            explicit HeaderExchangeServer(std::shared_ptr<IServer> server) {
                if (server == nullptr) {
                    throw std::invalid_argument("server == null");
                }
                this->server = server;
                this->heartbeat = server->getUrl()->getParameter(Constants::HEARTBEAT_KEY, (int) 0);
                this->heartbeatTimeout = server->getUrl()->getParameter(Constants::HEARTBEAT_TIMEOUT_KEY,
                                                                        heartbeat * 3);
                if (heartbeatTimeout < heartbeat * 2) {
                    throw std::invalid_argument("heartbeatTimeout < heartbeatInterval * 2");
                }
                startHeatbeatTimer();
            }


        public:
            shared_ptr<IServer> getServer() {
                return server;
            }

            shared_ptr<list<shared_ptr<IExchangeChannel>>> getExchangeChannels() override {
                auto exchangeChannels = make_shared<list<shared_ptr<IExchangeChannel>>>();
                auto channels = server->getChannels();
                if (channels != nullptr && (channels->size() > 0)) {
                    for (auto &channel: *channels) {
                        exchangeChannels->push_back(HeaderExchangeChannel::getOrAddChannel(channel));
                    }
                }
                return exchangeChannels;
            }

            shared_ptr<IExchangeChannel> getExchangeChannel(const folly::SocketAddress &remoteAddress) override {
                auto channel = server->getChannel(remoteAddress);
                return HeaderExchangeChannel::getOrAddChannel(channel);;
            }

            bool isBound() override {
                return server->isBound();
            }

            shared_ptr<list<shared_ptr<IChannel>>> getChannels() override {
//                auto channels = make_shared<>
//                return getExchangeChannels();
                return nullptr;
            }

            shared_ptr<IChannel> getChannel(const folly::SocketAddress &remoteAddress) override {
                return getExchangeChannel(remoteAddress);
            }


            shared_ptr<URL> getUrl() override {
                return server->getUrl();
            }

            shared_ptr<IChannelHandler> getChannelHandler() override {
                return server->getChannelHandler();
            }

            void reset(shared_ptr<URL> url) override {
                server->reset(url);
                try {
                    if (url->hasParameter(Constants::HEARTBEAT_KEY)
                        || url->hasParameter(Constants::HEARTBEAT_TIMEOUT_KEY)) {
                        int h = url->getParameter(Constants::HEARTBEAT_KEY, heartbeat);
                        int t = url->getParameter(Constants::HEARTBEAT_TIMEOUT_KEY, h * 3);
                        if (t < h * 2) {
                            throw std::runtime_error("heartbeatTimeout < heartbeatInterval * 2");
                        }
                        if (h != heartbeat || t != heartbeatTimeout) {
                            heartbeat = h;
                            heartbeatTimeout = t;
                            startHeatbeatTimer();
                        }
                    }
                } catch (const std::exception &e) {
                    LOG(ERROR) << e.what();
                }
            }

            folly::SocketAddress getLocalAddress() override {
                return server->getLocalAddress();
            }

            void send(const folly::dynamic &message) override {
                if (this->closed) {
                    throw RemotingException(this->getLocalAddress(), folly::SocketAddress(),
                                            string("Failed to send message ") + folly::toJson(message) +
                                            ", cause: The server " + this->getLocalAddress().getAddressStr() +
                                            " is closed!");
                }
                server->send(message);
            }

            void send(const folly::dynamic &message, bool sent) override {
                if (this->closed) {
                    throw RemotingException(this->getLocalAddress(), folly::SocketAddress(),
                                            string("Failed to send message ") + folly::toJson(message) +
                                            ", cause: The server " + this->getLocalAddress().getAddressStr() +
                                            " is closed!");
                }

                server->send(message, sent);
            }

            void close() override {
                doClose();
                server->close();
            }

            void close(uint32_t timeout) override {
                if (timeout > 0) {
                    long max = (long) timeout;
                    long start = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch()).count();

                    if (getUrl()->getParameter(Constants::CHANNEL_SEND_READONLYEVENT_KEY, false)) {
                        sendChannelReadOnlyEvent();
                    }
                    while (this->isRunning() && std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::system_clock::now().time_since_epoch()).count() - start < max) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                }
                doClose();
                server->close(timeout);
            }

            bool isClosed() override {
                return this->server->isClosed();
            }

        private:
            void doClose() {
                if (closed) {
                    return;
                }
                closed = true;
                stopHeartbeatTimer();

            }

            void startHeatbeatTimer() {

            }

            void stopHeartbeatTimer() {

            }

            void sendChannelReadOnlyEvent() {

            }

            bool isRunning() {
                auto channels = getChannels();
                for (auto & channel : *channels) {
                    if (DefaultFuture::hasFuture(channel)) {
                        return true;
                    }
                }
                return false;
            }

        private:
            shared_ptr<folly::ManualExecutor> scheduled{make_shared<folly::ManualExecutor>()};
            shared_ptr<IServer> server{nullptr};
            volatile bool closed{false};
            int heartbeat{0};
            int heartbeatTimeout{0};
        };
    }
}
#endif //DUBBOC_HEADEREXCHANGESERVER_H
