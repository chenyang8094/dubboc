//
// Created by 云海 on 2017/4/13.
//

#include "AbstractChannelHandlerDelegate.h"

namespace DUBBOC {
    namespace REMOTING {
        shared_ptr<IChannelHandler> AbstractChannelHandlerDelegate::getHandler() {
            if (std::dynamic_pointer_cast<IChannelHandlerDelegate>(handler)) {
                return std::dynamic_pointer_cast<IChannelHandlerDelegate>(handler)->getHandler();
            }
            return handler;
        }

        void AbstractChannelHandlerDelegate::connected(shared_ptr<IChannel> channel) {
            handler->connected(channel);
        }

        void AbstractChannelHandlerDelegate::disconnected(shared_ptr<IChannel> channel) {
            handler->disconnected(channel);
        }

        void AbstractChannelHandlerDelegate::sent(shared_ptr<IChannel> channel, const folly::dynamic &message) {
            handler->sent(channel,message);
        }

        void AbstractChannelHandlerDelegate::received(shared_ptr<IChannel> channel, const folly::dynamic &message) {
            handler->received(channel,message);
        }

        void AbstractChannelHandlerDelegate::caught(shared_ptr<IChannel> channel, std::exception_ptr exception) {
            handler->caught(channel,exception);
        }
    }
}