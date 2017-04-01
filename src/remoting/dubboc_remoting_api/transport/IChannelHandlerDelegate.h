//
// Created by 云海 on 2017/3/30.
//

#ifndef DUBBOC_ICHANNELHANDLERDELEGATE_H
#define DUBBOC_ICHANNELHANDLERDELEGATE_H

#include <iostream>

namespace DUBBOC {
    namespace REMOTING {
        class IChannelHandlerDelegate : virtual public IChannelHandler {
        public:
            virtual std::shared_ptr<IChannelHandler> getHandler() = 0;
        };
    }
}
#endif //DUBBOC_ICHANNELHANDLERDELEGATE_H
