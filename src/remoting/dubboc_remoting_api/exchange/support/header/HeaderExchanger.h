//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_HEADEREXCHANGER_H
#define DUBBOC_HEADEREXCHANGER_H

#include <remoting/dubboc_remoting_api/exchange/IExchanger.h>

/**
 * DefaultMessenger
 *
 * @author william.liangf
 */
namespace DUBBOC {
    namespace REMOTING {
        class HeaderExchanger : public IExchanger {
        public:
            shared_ptr<IExchangeServer> bind(shared_ptr<URL> url, shared_ptr<IExchangeHandler> handler) override;

            shared_ptr<IExchangeClient> connect(shared_ptr<URL> url, shared_ptr<IExchangeHandler> handler) override;

        };
    }
}
#endif //DUBBOC_HEADEREXCHANGER_H
