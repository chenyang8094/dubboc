//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_PROVIDERPROXY_H
#define DUBBOC_PROVIDERPROXY_H

#include <rpc/dubboc_rpc_api/proxy/AbstractProxyInvoker.h>

namespace DUBBOC {
    namespace RPC {
        class ProviderInvoker : public AbstractProxyInvoker {
        public:
            ProviderInvoker(shared_ptr<IGenericService> proxy, shared_ptr<URL> url) : AbstractProxyInvoker(proxy, url) {
            }

        public:
            folly::dynamic
            doInvoke(shared_ptr<IGenericService> proxy, const string methodName, const folly::dynamic &parameterTypes,
                     const folly::dynamic &arguments) override {
                return proxy->$invoke(methodName, parameterTypes, arguments);
            }
        };
    }
}
#endif //DUBBOC_PROVIDERPROXY_H
