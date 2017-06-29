//
// Created by 云海 on 2017/4/13.
//

#include "HeaderExchangeClient.h"

namespace DUBBOC {
    namespace REMOTING {

        shared_ptr<folly::ManualExecutor> HeaderExchangeClient::scheduled{nullptr};

        shared_ptr<IResponseFuture> HeaderExchangeClient::request(const folly::dynamic &request) {
            return this->channel->request(request);
        }

        shared_ptr<IResponseFuture>
        HeaderExchangeClient::request(const folly::dynamic &request, uint32_t timeout) {
            return this->channel->request(request, timeout);
        }

        shared_ptr<IExchangeHandler> HeaderExchangeClient::getExchangeHandler() {
            return this->channel->getExchangeHandler();
        }

        void HeaderExchangeClient::close(uint32_t timeout) {
            doClose();
            this->channel->close(timeout);
        }

        void HeaderExchangeClient::reconnect() {
            this->client->reconnect();
        }

        folly::SocketAddress HeaderExchangeClient::getRemoteAddress() {
            return this->channel->getRemoteAddress();
        }

        bool HeaderExchangeClient::isConnected() {
            return this->channel->isConnected();
        }

        bool HeaderExchangeClient::hasAttribute(const std::string &key) {
            return this->channel->hasAttribute(key);
        }

        boost::any HeaderExchangeClient::getAttribute(const std::string &key) {
            return this->channel->getAttribute(key);
        }

        void HeaderExchangeClient::setAttribute(const std::string &key, const boost::any &value) {
            this->channel->setAttribute(key, value);
        }

        void HeaderExchangeClient::removeAttribute(const std::string &key) {
            this->channel->removeAttribute(key);
        }

        shared_ptr<URL> HeaderExchangeClient::getUrl() {
            return this->channel->getUrl();
        }

        shared_ptr<IChannelHandler> HeaderExchangeClient::getChannelHandler() {
            return this->channel->getChannelHandler();
        }

        folly::SocketAddress HeaderExchangeClient::getLocalAddress() {
            return this->channel->getLocalAddress();
        }

        void HeaderExchangeClient::send(const folly::dynamic &message) {
            this->channel->send(message);
        }

        void HeaderExchangeClient::send(const folly::dynamic &message, bool sent) {
            this->channel->send(message, sent);
        }

        void HeaderExchangeClient::close() {
            doClose();
            this->channel->close();
        }

        bool HeaderExchangeClient::isClosed() {
            return this->channel->isClosed();
        }

        void HeaderExchangeClient::reset(shared_ptr<URL> url) {
            this->client->reset(url);
        }
    }
}