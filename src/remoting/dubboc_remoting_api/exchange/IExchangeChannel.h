//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_EXCHANGECHANNEL_H
#define DUBBOC_EXCHANGECHANNEL_H

#include <remoting/dubboc_remoting_api/IChannel.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class IResponseFuture;

        class IExchangeHandler;

        class IExchangeChannel : public IChannel {
        public:
            IExchangeChannel() = default;

            virtual ~IExchangeChannel() {}

        public:
            /**
             * send request.
             *
             * @param request
             * @return response future
             * @throws RemotingException
             */
            virtual shared_ptr<IResponseFuture> request(const folly::dynamic &request) = 0;

            /**
             * send request.
             *
             * @param request
             * @param timeout
             * @return response future
             * @throws RemotingException
             */
            virtual shared_ptr<IResponseFuture> request(const folly::dynamic &request, uint32_t timeout) = 0;

            /**
             * get message handler.
             *
             * @return message handler
             */
            virtual shared_ptr<IExchangeHandler> getExchangeHandler() = 0;

            /**
             * graceful close.
             *
             * @param timeout
             */
//            virtual void close(uint32_t timeout) = 0;
        };
    }
}
#endif //DUBBOC_EXCHANGECHANNEL_H
