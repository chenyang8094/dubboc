//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IINVOKERLISTENER_H
#define DUBBOC_IINVOKERLISTENER_H

#include <memory>


namespace DUBBOC {
    namespace RPC {
        using namespace std;

        class IInvoker;

        //@SPI
        class IInvokerListener {
        public:
            IInvokerListener() = default;

            virtual ~IInvokerListener() {}

        public:

            /**
             * The invoker referred
             *
             * @see com.alibaba.dubbo.rpc.Protocol#refer(Class, URL)
             * @param invoker
             * @throws RpcException
             */
            virtual void referred(shared_ptr<IInvoker> invoker) = 0;

            /**
             * The invoker destroyed.
             *
             * @see com.alibaba.dubbo.rpc.Invoker#destroy()
             * @param invoker
             */
            virtual void destroyed(shared_ptr<IInvoker> invoker) = 0;

        };
    }
}
#endif //DUBBOC_IINVOKERLISTENER_H
