//
// Created by 云海 on 2017/4/6.
//

#ifndef DUBBOC_ABSTRACTPROXYFACTORY_H
#define DUBBOC_ABSTRACTPROXYFACTORY_H

#include <rpc/dubboc_rpc_api/IProxyFactory.h>

namespace DUBBOC {
    namespace RPC {

        /*
         * 此处的动态代理工厂不用作为扩展点实现
         * */
        class ProxyFactory : public IProxyFactory {
        public:
            shared_ptr<IGenericService> getProxy(shared_ptr<IInvoker> invoker) override;

            shared_ptr<IInvoker> getInvoker(shared_ptr<IGenericService> proxy, shared_ptr<URL> url) override;
        };
    }
}
#endif //DUBBOC_ABSTRACTPROXYFACTORY_H
