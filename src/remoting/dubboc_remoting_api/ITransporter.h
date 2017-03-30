//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_ITRANSPORTER_H
#define DUBBOC_ITRANSPORTER_H

#include <memory>
#include <common/URL.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class IServer;

        class IClient;

        class IChannelHandler;

        class ITransporter {
        public:
            ITransporter() = default;

            virtual ~ITransporter() {}

        public:
            /**
               * Bind a server.
               *
               * @see com.alibaba.dubbo.remoting.Transporters#bind(URL, Receiver, ChannelHandler)
               * @param url server url
               * @param handler
               * @return server
               * @throws RemotingException
               *
               * 作为服务端，注意bind之后返回的是一个Server，而参数是要监听的url和其对应的dubbo handler
               */
            virtual shared_ptr<IServer> bind(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) = 0;

            /**
             * Connect to a server.
             *
             * @see com.alibaba.dubbo.remoting.Transporters#connect(URL, Receiver, ChannelListener)
             * @param url server url
             * @param handler
             * @return client
             * @throws RemotingException
             *
             * 作为客户端，注意connect之后返回的是一个Client，其参数为要连接的url和对应的dubbo hanlder
             */
            virtual shared_ptr<IClient> connect(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) = 0;
        };
    }
}
#endif //DUBBOC_ITRANSPORTER_H
