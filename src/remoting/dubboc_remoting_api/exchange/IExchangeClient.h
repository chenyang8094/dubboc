//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_EXCHANGECLIENT_H
#define DUBBOC_EXCHANGECLIENT_H

#include <remoting/dubboc_remoting_api/IClient.h>
#include "IExchangeChannel.h"

namespace DUBBOC {
    namespace REMOTING {
        class IExchangeClient : public IClient, public IExchangeChannel {
        public:
            IExchangeClient() = default;

            virtual ~IExchangeClient() {}
        };
    }
}
#endif //DUBBOC_EXCHANGECLIENT_H
