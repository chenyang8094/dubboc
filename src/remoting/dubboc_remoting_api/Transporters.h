//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_TRANSPORTERS_H
#define DUBBOC_TRANSPORTERS_H

#include <iostream>
#include <common/ExtensionLoader.h>
#include "IServer.h"
#include "IClient.h"
#include "ITransporter.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;
        using namespace DUBBOC::CONTAINER;

        class Transporters {
        public:

            static shared_ptr<IServer> bind(const string &url, shared_ptr<IChannelHandler>... handler) {
//                return bind(URL.valueOf(url), handler);
                return nullptr;
            }

            static shared_ptr<IServer> bind(shared_ptr<URL> url, shared_ptr<IChannelHandler>... handlers) {
                if (url == nullptr) {

                }
//                if (handlers == nullptr || handlers.length == 0) {
//
//                }
//                shared_ptr<IChannelHandler> handler{nullptr};
//
//                // 只有一个handler
//                if (handlers.length == 1) {
//                    handler = handlers[0];
//                } else {
//                    // 当存在多个handler时，将多个handler合并成一个dispatcher，这个dispatcher会负责将事件依次传递各个handler
//                    handler = new ChannelHandlerDispatcher(handlers);
//                }
//                // 这里会启用扩展点，使用具体的(比如netty)
//                return getTransporter().bind(url, handler);
                return nullptr;
            }

            static shared_ptr<IClient> connect(const string &url, shared_ptr<IChannelHandler>... handler) {
//                return connect(URL.valueOf(url), handler);
                return nullptr;
            }

            static shared_ptr<IClient> connect(shared_ptr<URL> url, shared_ptr<IChannelHandler>... handlers) {
                if (url == nullptr) {

                }
//                shared_ptr<IChannelHandler> handler{nullptr};
//                if (handlers == null || handlers.length == 0) {
//                    handler = new ChannelHandlerAdapter();
//                } else if (handlers.length == 1) {
//                    handler = handlers[0];
//                } else {
//                    handler = new ChannelHandlerDispatcher(handlers);
//                }
//                return getTransporter().connect(url, handler);
                return nullptr;
            }

            // 扩展点 静态方法
            static shared_ptr<ITransporter> getTransporter() {
                return ExtensionLoader::getInstance()->LoadExtensionAdaptive<ITransporter>("ITransporter");
            }

        private:
            Transporters() = default;

        };
    }
}
#endif //DUBBOC_TRANSPORTERS_H
