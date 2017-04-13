//
// Created by 云海 on 2017/3/30.
//

#ifndef DUBBOC_ICHANNELHANDLERDELEGATE_H
#define DUBBOC_ICHANNELHANDLERDELEGATE_H

#include <iostream>
#include <remoting/dubboc_remoting_api/IChannelHandler.h>

namespace DUBBOC {
    namespace REMOTING {
        class IChannelHandlerDelegate : public IChannelHandler {
        public:
            IChannelHandlerDelegate() = default;

            virtual ~IChannelHandlerDelegate() {}

        public:
            virtual std::shared_ptr<IChannelHandler> getHandler() = 0;
        };
    }
}
#endif //DUBBOC_ICHANNELHANDLERDELEGATE_H
