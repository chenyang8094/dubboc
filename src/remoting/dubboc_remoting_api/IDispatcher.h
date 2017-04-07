//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_IDISPATCHER_H
#define DUBBOC_IDISPATCHER_H

#include <memory>
#include <common/URL.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class IChannelHandler;

        class IDispatcher {

            /**
             * dispatch the message to threadpool.
             *
             * @param handler
             * @param url
             * @return channel handler
             */
            //@Adaptive({Constants::DISPATCHER_KEY, "dispather", "channel.handler"}) // 后两个参数为兼容旧配置
            virtual shared_ptr<IChannelHandler> dispatch(shared_ptr<IChannelHandler> handler, shared_ptr<URL> url) = 0;

        };
    }
}
#endif //DUBBOC_IDISPATCHER_H
