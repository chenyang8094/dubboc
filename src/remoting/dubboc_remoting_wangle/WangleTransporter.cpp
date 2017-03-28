//
// Created by 云海 on 2017/3/27.
//

#include "WangleTransporter.h"
#include <common/ExtensionLoader.h>

namespace DUBBOC {
    namespace REMOTING {

        const static ExtensionLoader::RegisterExtensionT <ITransporter, WangleTransporter> forRegiste(
                "transport:wangle");

        shared_ptr <IServer>
        WangleTransporter::bind(shared_ptr <URL> url, shared_ptr <IChannelHandler> handler)  {
            return nullptr;
        }

        shared_ptr <IClient>
        WangleTransporter::connect(shared_ptr <URL> url, shared_ptr <IChannelHandler> handler)  {
            return nullptr;
        }

    }
}