//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_HEADEREXCHANGESERVER_H
#define DUBBOC_HEADEREXCHANGESERVER_H

#include <remoting/dubboc_remoting_api/exchange/IExchangeServer.h>

namespace DUBBOC {
    namespace REMOTING {
        class HeaderExchangeServer : public IExchangeServer {
        public:
            explicit HeaderExchangeServer(std::shared_ptr<IServer> server){

            }


        };
    }
}
#endif //DUBBOC_HEADEREXCHANGESERVER_H
