//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_IROUTER_H
#define DUBBOC_IROUTER_H

#include <list>
#include <memory>
#include <common/URL.h>
#include <rpc/dubboc_rpc_api/IInvoker.h>

namespace DUBBOC {
    namespace CLUSTER {
        using namespace std;
        using namespace DUBBOC::COMMON;
        using namespace DUBBOC::RPC;

        class IRouter {
        public:
            IRouter() = default;

            virtual ~IRouter() {}

        public:
            /**
             * get the router url.
             *
             * @return url
             */
            virtual shared_ptr<URL> getUrl() = 0;

            /**
             * route.
             *
             * @param invokers
             * @param url refer url
             * @param invocation
             * @return routed invokers
             * @throws RpcException
             */
            virtual list<shared_ptr<IInvoker>>
            route(list<shared_ptr<IInvoker>> invokers, shared_ptr<URL> url, shared_ptr<IInvocation> invocation) = 0;

        };


    }
}
#endif //DUBBOC_IROUTER_H
