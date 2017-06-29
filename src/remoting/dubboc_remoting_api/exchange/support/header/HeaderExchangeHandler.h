//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_HEADEREXCHANGEHANDLER_H
#define DUBBOC_HEADEREXCHANGEHANDLER_H

#include <remoting/dubboc_remoting_api/transport/IChannelHandlerDelegate.h>
#include <remoting/dubboc_remoting_api/exchange/IExchangeHandler.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class Request;

        class Response;

        class HeaderExchangeHandler : public IChannelHandlerDelegate {
        public:
            explicit HeaderExchangeHandler(std::shared_ptr<IExchangeHandler> handler) {
                if (handler == nullptr) {
                    throw std::invalid_argument("handler == null");
                }
                this->handler = handler;
            }

        public:
            virtual void handlerEvent(shared_ptr<IChannel> channel, shared_ptr<Request> req);

            virtual shared_ptr<Response> handleRequest(shared_ptr<IExchangeChannel> channel, shared_ptr<Request> req);

            static void handleResponse(shared_ptr<IChannel> channel, shared_ptr<Response> response);

            shared_ptr<IChannelHandler> getHandler() override {
                return nullptr;
            }

            void connected(shared_ptr<IChannel> channel) override;

            void disconnected(shared_ptr<IChannel> channel) override;

            void sent(shared_ptr<IChannel> channel, const folly::dynamic &message) override;

            void received(shared_ptr<IChannel> channel, const folly::dynamic &message) override;

            void caught(shared_ptr<IChannel> channel, std::exception_ptr exception) override;

        public:
            static string KEY_READ_TIMESTAMP;
            static string KEY_WRITE_TIMESTAMP;
            // 这些handler里面都会有其他的handler，本handler把自己的事情处理完成之后，就会调用自己包装的handler的对应方法，形成链式处理
            shared_ptr<IExchangeHandler> handler{nullptr};

        };
    }
}
#endif //DUBBOC_HEADEREXCHANGEHANDLER_H
