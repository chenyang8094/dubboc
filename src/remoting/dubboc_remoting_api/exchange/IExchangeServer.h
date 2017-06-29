//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_IEXCHANGESERVER_H
#define DUBBOC_IEXCHANGESERVER_H

#include <list>
#include <memory>
#include <remoting/dubboc_remoting_api/IServer.h>

namespace DUBBOC {
    namespace REMOTING {

        using namespace std;

        class IExchangeChannel;

        class IExchangeServer : public IServer {
        public:
            IExchangeServer() = default;

            virtual ~IExchangeServer() {}

        public:
            /**
             * get channels.
             *
             * @return channels
             */
            virtual shared_ptr<list<shared_ptr<IExchangeChannel>>> getExchangeChannels() = 0;

            /**
             * get channel.
             *
             * @param remoteAddress
             * @return channel
             */
            virtual shared_ptr<IExchangeChannel> getExchangeChannel(const folly::SocketAddress &remoteAddress) = 0;

        };
    }
}
#endif //DUBBOC_IEXCHANGESERVER_H
