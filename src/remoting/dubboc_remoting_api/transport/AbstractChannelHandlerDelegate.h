//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_ABSTRACTCHANNELHANDLERDELEGATE_H
#define DUBBOC_ABSTRACTCHANNELHANDLERDELEGATE_H

#include "IChannelHandlerDelegate.h"
#include <memory>
#include <cassert>


namespace DUBBOC {
    namespace REMOTING {
        using namespace std;


        class AbstractChannelHandlerDelegate : public IChannelHandlerDelegate {
        public:
            explicit AbstractChannelHandlerDelegate(shared_ptr<IChannelHandler> handler) {
                assert(handler != nullptr);
                this->handler = handler;
            }

        public:
            shared_ptr<IChannelHandler> getHandler() override ;

            void connected(shared_ptr<IChannel> channel) override ;

            void disconnected(shared_ptr<IChannel> channel) override ;

            void sent(shared_ptr<IChannel> channel, const folly::dynamic &message) override ;

            void received(shared_ptr<IChannel> channel, const folly::dynamic &message) override ;

            void caught(shared_ptr<IChannel> channel, std::exception_ptr exception) override ;

        protected:
            shared_ptr<IChannelHandler> handler{nullptr};
        };
    }
}

#endif //DUBBOC_ABSTRACTCHANNELHANDLERDELEGATE_H
