//
// Created by 云海 on 2017/3/27.
//

#include "WangleTransporter.h"
#include "WangleServer.h"
#include "WangleClient.h"
#include <common/ExtensionLoader.h>

namespace DUBBOC {
    namespace REMOTING {

        /**
         * 注册一定要放在cpp中，否则当头文件被重复包含时会导致重复注册，从而引发异常
         * */
        EXTENSION_REGISTER(ITransporter, WangleTransporter);

        shared_ptr<IServer>
        WangleTransporter::bind(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) {
            return std::make_shared<WangleServer>(url, handler);
        }

        shared_ptr<IClient>
        WangleTransporter::connect(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) {
            return std::make_shared<WangleClient>(url, handler);
        }

    }
}