//
// Created by 云海 on 2017/4/13.
//

#include <remoting/dubboc_remoting_api/RemotingException.h>
#include <folly/json.h>
#include <remoting/dubboc_remoting_api/exchange/Request.h>
#include <remoting/dubboc_remoting_api/exchange/support/DefaultFuture.h>
#include "HeaderExchangeChannel.h"

namespace DUBBOC {
    namespace REMOTING {

        shared_ptr<IResponseFuture> HeaderExchangeChannel::request(const folly::dynamic &request) {
            return this->request(request, channel->getUrl()->getPositiveParameter(Constants::TIMEOUT_KEY,
                                                                                  Constants::DEFAULT_TIMEOUT));
        }

        shared_ptr<IResponseFuture>
        HeaderExchangeChannel::request(const folly::dynamic &request, uint32_t timeout) {
            if (this->closed) {
                throw RemotingException(this->getLocalAddress(), folly::SocketAddress(),
                                        std::string("Failed to send request ") + folly::toJson(request) +
                                        ", cause: The channel is closed!");
            }

            auto request_wrapper = std::make_shared<Request>();
            request_wrapper->setMVersion("2.0.0");
            request_wrapper->setMTwoWay(true);
            request_wrapper->setMData(request);

            std::shared_ptr<DefaultFuture> future = std::make_shared<DefaultFuture>(channel, request_wrapper, timeout);

            try {
                channel->send(request_wrapper->GetDynamic());
            } catch (const std::exception &e) {
                future->cancel();
                throw e;
            }
            return future;
        }

        shared_ptr<IExchangeHandler> HeaderExchangeChannel::getExchangeHandler() {
            return nullptr;
        }

        // graceful close
        void HeaderExchangeChannel::close(uint32_t timeout) {
            if (closed) {
                return;
            }
            closed = true;
            if (timeout > 0) {
                auto start = std::chrono::system_clock::now();
                while (DefaultFuture::hasFuture(shared_from_this()) &&
                       std::chrono::duration_cast<std::chrono::microseconds>(
                               std::chrono::system_clock::now() - start).count() < timeout) {
                    std::this_thread::sleep_for(std::chrono::microseconds(10));
                }
            }
            close();
        }

        folly::SocketAddress HeaderExchangeChannel::getRemoteAddress() {
            return this->channel->getRemoteAddress();
        }

        bool HeaderExchangeChannel::isConnected() {
            return this->channel->isConnected();
        }

        bool HeaderExchangeChannel::hasAttribute(const std::string &key) {
            return this->channel->hasAttribute(key);
        }

        folly::dynamic HeaderExchangeChannel::getAttribute(const std::string &key) {
            return this->channel->getAttribute(key);
        }

        void HeaderExchangeChannel::setAttribute(const std::string &key, const folly::dynamic &value) {
            this->channel->setAttribute(key, value);
        }

        void HeaderExchangeChannel::removeAttribute(const std::string &key) {
            this->channel->removeAttribute(key);
        }

        shared_ptr<URL> HeaderExchangeChannel::getUrl() {
            return this->channel->getUrl();
        }

        shared_ptr<IChannelHandler> HeaderExchangeChannel::getChannelHandler() {
            return this->channel->getChannelHandler();
        }

        folly::SocketAddress HeaderExchangeChannel::getLocalAddress() {
            return this->channel->getLocalAddress();
        }

        void HeaderExchangeChannel::send(const folly::dynamic &message) {
            send(message, this->getUrl()->getParameter(Constants::SENT_KEY, false));
        }

        void HeaderExchangeChannel::send(const folly::dynamic &message, bool sent) {
            if (this->closed) {
                throw RemotingException(this->getLocalAddress(), folly::SocketAddress(),
                                        std::string("Failed to send request ") + folly::toJson(message) +
                                        ", cause: The channel is closed!");
            }

            if (message.isObject() && message.get_ptr("@type") && (message.get_ptr("@type")->asString() == "Request"
                                                                   || message.get_ptr("@type")->asString() ==
                                                                      "Response")) {
                channel->send(message);
            } else if (message.isString()) {
                channel->send(message);
            } else {
                Request request;
                request.setMVersion("2.0.0");
                request.setMTwoWay(false);
                request.setMData(message);
                channel->send(request.GetDynamic(), sent);// 发送请求
            }
        }

        void HeaderExchangeChannel::close() {
            try {
                channel->close();
            } catch (const std::exception &e) {
                LOG(WARNING) << e.what();
            }
        }

        bool HeaderExchangeChannel::isClosed() {
            return closed;
        }
    }
}