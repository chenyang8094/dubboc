//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_HEADEREXCHANGEHANDLER_H
#define DUBBOC_HEADEREXCHANGEHANDLER_H

#include <remoting/dubboc_remoting_api/transport/IChannelHandlerDelegate.h>
#include <remoting/dubboc_remoting_api/exchange/IExchangeHandler.h>

namespace DUBBOC {
    namespace REMOTING {
        class HeaderExchangeHandler : public IChannelHandlerDelegate {
        public:
            explicit HeaderExchangeHandler(std::shared_ptr<IExchangeHandler> handler) {

            }

        };
    }
}
#endif //DUBBOC_HEADEREXCHANGEHANDLER_H
