//
// Created by 云海 on 2017/4/7.
//

#include "ProxyFactory.h"
#include <rpc/dubboc_rpc_api/proxy/default/ConsumerProxy.h>
#include <rpc/dubboc_rpc_api/proxy/default/ProviderInvoker.h>
#include <common/ExtensionLoader.h>

namespace DUBBOC {
    namespace RPC {
        shared_ptr<IGenericService> ProxyFactory::getProxy(shared_ptr<IInvoker> invoker) {
            return std::make_shared<ConsumerProxy>(invoker);
        }

        shared_ptr<IInvoker> ProxyFactory::getInvoker(shared_ptr<IGenericService> proxy, shared_ptr<URL> url) {
            return std::make_shared<ProviderInvoker>(proxy, url);
        }

        EXTENSION_REGISTER(IProxyFactory, ProxyFactory);
    }
}