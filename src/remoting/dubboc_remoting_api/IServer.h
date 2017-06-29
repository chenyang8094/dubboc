//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_ISERVER_H
#define DUBBOC_ISERVER_H

#include "IEndpoint.h"
#include <common/IResetable.h>

namespace DUBBOC {
    namespace REMOTING {
        using  namespace DUBBOC::COMMON;

        class IChannel;

        class IServer : virtual public IEndpoint, public IResetable {
        public:
            /**
             * is bound.
             *
             * @return bound
             */
            virtual bool isBound() = 0;

            /**
             * get channels.
             *
             * @return channels
             */
            virtual std::shared_ptr<std::list<std::shared_ptr<IChannel>>> getChannels() = 0;


            /**
             * get channel.
             *
             * @param remoteAddress
             * @return channel
             */
            virtual std::shared_ptr<IChannel> getChannel(const folly::SocketAddress &remoteAddress) = 0;
        };
    }
}
#endif //DUBBOC_ISERVER_H
