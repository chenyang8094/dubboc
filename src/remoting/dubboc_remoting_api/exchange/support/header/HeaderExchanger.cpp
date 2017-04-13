//
// Created by 云海 on 2017/4/13.
//

#include <remoting/dubboc_remoting_api/Transporters.h>
#include <remoting/dubboc_remoting_api/transport/DecodeHandler.h>
#include "HeaderExchanger.h"
#include "HeaderExchangeClient.h"
#include "HeaderExchangeServer.h"
#include "HeaderExchangeHandler.h"

namespace DUBBOC {
    namespace REMOTING {
        shared_ptr<IExchangeServer>
        HeaderExchanger::bind(shared_ptr<URL> url, shared_ptr<IExchangeHandler> handler) {
            list<shared_ptr<IChannelHandler>> handlers;
            handlers.push_back(make_shared<DecodeHandler>(make_shared<HeaderExchangeHandler>(handler)));
            return make_shared<HeaderExchangeServer>(Transporters::connect(url,handlers));
        }

        shared_ptr<IExchangeClient>
        HeaderExchanger::connect(shared_ptr<URL> url, shared_ptr<IExchangeHandler> handler) {
            list<shared_ptr<IChannelHandler>> handlers;
            handlers.push_back(make_shared<DecodeHandler>(make_shared<HeaderExchangeHandler>(handler)));
            return make_shared<HeaderExchangeClient>(Transporters::bind(url, handlers));
        }
    }
}