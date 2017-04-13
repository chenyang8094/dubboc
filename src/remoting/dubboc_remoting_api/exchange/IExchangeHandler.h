//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_EXCHANGEHANDLER_H
#define DUBBOC_EXCHANGEHANDLER_H

#include <remoting/dubboc_remoting_api/IChannelHandler.h>
#include <remoting/dubboc_remoting_api/telnet/ITelnetHandler.h>
#include <memory>

namespace DUBBOC {
    namespace REMOTING {
        class IExchangeChannel;

        class IExchangeHandler : public IChannelHandler, public ITelnetHandler {
        public:
            IExchangeHandler() = default;

            virtual ~IExchangeHandler() {}

        public:
            /**
             * reply.
             *
             * @param channel
             * @param request
             * @return response
             * @throws RemotingException
             */
            virtual folly::dynamic reply(std::shared_ptr<IExchangeChannel> channel, const folly::dynamic &request) = 0;
        };
    }
}
#endif //DUBBOC_EXCHANGEHANDLER_H
