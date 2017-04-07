//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_ILOADBALANCE_H
#define DUBBOC_ILOADBALANCE_H

#include <list>
#include <rpc/dubboc_rpc_api/IInvoker.h>
#include <common/URL.h>

namespace DUBBOC {
    namespace CLUSTER {
        using namespace std;
        using namespace DUBBOC::COMMON;
        using namespace DUBBOC::RPC;

        //@SPI(RandomLoadBalance.NAME)
        class ILoadBalance {
        public:
            ILoadBalance() = default;

            virtual ~ILoadBalance() {}

        public:

            /**
             * select one invoker in list.
             *
             * @param invokers invokers.
             * @param url refer url
             * @param invocation invocation.
             * @return selected invoker.
             */
            //@Adaptive("loadbalance")
            virtual shared_ptr<IInvoker>
            select(list<shared_ptr<IInvoker>> invokers, shared_ptr<URL> url, shared_ptr<IInvocation> invocation) = 0;

        };
    }
}
#endif //DUBBOC_ILOADBALANCE_H
