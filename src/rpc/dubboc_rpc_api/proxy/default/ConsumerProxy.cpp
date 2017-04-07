//
// Created by 云海 on 2017/4/7.
//


#include "ConsumerProxy.h"
#include <rpc/dubboc_rpc_api/IInvoker.h>
#include <rpc/dubboc_rpc_api/RpcInvocation.h>

namespace DUBBOC {
    namespace RPC {
        folly::dynamic
        ConsumerProxy::$invoke(const string &method, const folly::dynamic &parameterTypes,
                               const folly::dynamic &args) {
            return invoker->invoke(std::make_shared<RpcInvocation>(method, parameterTypes, args))->recreate();
        }
    }
}
