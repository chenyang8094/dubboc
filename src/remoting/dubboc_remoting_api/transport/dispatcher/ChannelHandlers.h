//
// Created by 云海 on 2017/3/31.
//

#ifndef DUBBOC_CHANNELHANDLERS_H
#define DUBBOC_CHANNELHANDLERS_H

#include <remoting/dubboc_remoting_api/IChannelHandler.h>
#include <common/URL.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace DUBBOC::COMMON;
        using namespace std;

        class ChannelHandlers {

        public:

            static shared_ptr<IChannelHandler> wrap(shared_ptr<IChannelHandler> handler, shared_ptr<URL> url) {
                return ChannelHandlers::getInstance()->wrapInternal(handler, url);
            }

        protected:

            ChannelHandlers() = default;

        protected:

            shared_ptr<IChannelHandler> wrapInternal(shared_ptr<IChannelHandler> handler, shared_ptr<URL> url) {
//                return new MultiMessageHandler(new HeartbeatHandler(ExtensionLoader.getExtensionLoader(Dispatcher.
//                class)
//                .getAdaptiveExtension().dispatch(handler, url)));
                return nullptr;
            }

        private:
            static shared_ptr<ChannelHandlers> INSTANCE;

        protected:

            static shared_ptr<ChannelHandlers> getInstance() {
                return INSTANCE;
            }

            static void setTestingChannelHandlers(shared_ptr<ChannelHandlers> instance) {
                INSTANCE = instance;
            }
        };
    }
}
#endif //DUBBOC_CHANNELHANDLERS_H
