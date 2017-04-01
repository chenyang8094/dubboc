//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_ABSTRACTPEER_H
#define DUBBOC_ABSTRACTPEER_H

#include <remoting/dubboc_remoting_api/IEndpoint.h>
#include <remoting/dubboc_remoting_api/IChannelHandler.h>
#include "IChannelHandlerDelegate.h"

namespace DUBBOC {
    namespace REMOTING {
        class AbstractPeer : virtual public IEndpoint, public IChannelHandler {
        public:
            explicit AbstractPeer(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) {

            }

            virtual void send(const folly::dynamic &message) override {
                send(message, url->getParameter(Constants::SENT_KEY, false));
            }

            virtual void send(const folly::dynamic &message, bool sent) override {
               throw std::runtime_error("invoke abstract method.");
            }

            virtual void close() override {
                closed = true;
            }

            virtual void close(uint32_t timeout) override {
                close();
            }

            virtual shared_ptr<URL> getUrl() override {
                return url;
            }

            virtual void setUrl(shared_ptr<URL> url) {
                if (url == nullptr) {
                    throw std::invalid_argument("url == null");
                }
                this->url = url;
            }

            virtual shared_ptr<IChannelHandler> getChannelHandler() override {
                if (std::dynamic_pointer_cast<IChannelHandlerDelegate>(handler)) {
                    return (std::dynamic_pointer_cast<IChannelHandlerDelegate>(handler))->getHandler();
                } else {
                    return handler;
                }
            }

            /**
             * 返回最终的handler，可能已被wrap,需要区别于getChannelHandler
             * @return ChannelHandler
             */
            virtual shared_ptr<IChannelHandler> getDelegateHandler() {
                return handler;
            }

            virtual bool isClosed() override {
                return closed;
            }

            virtual void connected(shared_ptr<IChannel> ch) override {
                if (closed) {
                    return;
                }
                handler->connected(ch);
            }

            virtual void disconnected(shared_ptr<IChannel> ch) override {
                handler->disconnected(ch);
            }

            virtual void sent(shared_ptr<IChannel> ch, const folly::dynamic &msg) override {
                if (closed) {
                    return;
                }
                handler->sent(ch, msg);
            }

            virtual void received(shared_ptr<IChannel> ch, const folly::dynamic &msg) override {
                if (closed) {
                    return;
                }
                handler->received(ch, msg);
            }

            virtual void caught(shared_ptr<IChannel> ch, const std::exception &ex) override {
                handler->caught(ch, ex);
            }

        private:
            shared_ptr<IChannelHandler> handler{nullptr};
            shared_ptr<URL> url{nullptr};
            bool closed;
        };
    }
}
#endif //DUBBOC_ABSTRACTPEER_H
