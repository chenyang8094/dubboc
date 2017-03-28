//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_WANGLETRANSPORTER_H
#define DUBBOC_WANGLETRANSPORTER_H


#include <remoting/dubboc_remoting_api/ITransporter.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace DUBBOC::COMMON;
        using namespace std;

        class WangleTransporter : public ITransporter {
        public:
            WangleTransporter() = default;

        public:
            shared_ptr<IServer> bind(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) override;

            shared_ptr<IClient> connect(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) override;
        };
    }
}
#endif //DUBBOC_WANGLETRANSPORTER_H
