//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_IEXCHANGER_H
#define DUBBOC_IEXCHANGER_H

#include <common/URL.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class IExchangeServer;

        class IExchangeClient;

        class IExchangeHandler;

        //@SPI(HeaderExchanger.NAME)
        class IExchanger {
        public:
            IExchanger() = default;

            virtual ~IExchanger() {}

        public:

            /**
             * bind.
             *
             * @param url
             * @param handler
             * @return message server
             */
            //@Adaptive({Constants.EXCHANGER_KEY})
            virtual shared_ptr<IExchangeServer> bind(shared_ptr<URL> url, shared_ptr<IExchangeHandler> handler) = 0;

            /**
             * connect.
             *
             * @param url
             * @param handler
             * @return message channel
             */
            //@Adaptive({Constants.EXCHANGER_KEY})
            virtual shared_ptr<IExchangeClient> connect(shared_ptr<URL> url, shared_ptr<IExchangeHandler> handler) = 0;

        };
    }
}
#endif //DUBBOC_IEXCHANGER_H
