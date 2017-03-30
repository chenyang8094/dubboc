//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_ICHANNELHANDLER_H
#define DUBBOC_ICHANNELHANDLER_H

#include <iostream>
#include <folly/dynamic.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class IChannel;
        class IChannelHandler {
        public:
            virtual ~IChannelHandler() {}

        public:
            /**
             * on channel connected.
             *
             * @param channel channel.
             */
            virtual void connected(shared_ptr<IChannel> channel) = 0;

            /**
             * on channel disconnected.
             *
             * @param channel channel.
             */
            virtual void disconnected(shared_ptr<IChannel> channel) = 0;

            /**
             * on message sent.
             *
             * @param channel channel.
             * @param message message.
             */
            virtual void sent(shared_ptr<IChannel> channel, const folly::dynamic &message) = 0;

            /**
             * on message received.
             *
             * @param channel channel.
             * @param message message.
             */
            virtual void received(shared_ptr<IChannel> channel, const folly::dynamic &message) = 0;

            /**
             * on exception caught.
             *
             * @param channel channel.
             * @param exception exception.
             */
            virtual void caught(shared_ptr<IChannel> channel, const std::exception &exception) = 0;
        };
    }
}
#endif //DUBBOC_ICHANNELHANDLER_H
