//
// Created by 云海 on 2017/4/6.
//

#ifndef DUBBOC_IPROXYFACTORY_H
#define DUBBOC_IPROXYFACTORY_H

#include <memory>
#include <rpc/dubboc_rpc_api/service/IGenericService.h>
#include <common/URL.h>
#include "IInvoker.h"

namespace DUBBOC {
    namespace RPC {
        using namespace std;
        using namespace DUBBOC::COMMON;

        //@SPI
        class IProxyFactory {
        public:
            IProxyFactory() = default;

            virtual ~IProxyFactory() {}

        public:
            /**
             * create proxy.
             *
             * @param invoker
             * @return proxy
             *
             *  用于reference端get时获取
             */

            virtual shared_ptr<IGenericService> getProxy(shared_ptr<IInvoker> invoker) = 0;

            /**
             * create invoker.
             *
             * @param <T>
             * @param proxy
             * @param url
             * @return invoker
             *
             * 用于provider端获取一个调用接口实现的invoker
             */
            virtual shared_ptr<IInvoker> getInvoker(shared_ptr<IGenericService> proxy, shared_ptr<URL> url) = 0;
        };
    }
}
#endif //DUBBOC_IPROXYFACTORY_H
