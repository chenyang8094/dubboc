
//
// Created by 云海 on 2017/4/7.
//

#include "AbstractProxyInvoker.h"
#include <rpc/dubboc_rpc_api/IResult.h>
#include <rpc/dubboc_rpc_api/IInvocation.h>
#include <rpc/dubboc_rpc_api/RpcResult.h>

namespace DUBBOC {
    namespace RPC {

        shared_ptr<IResult> AbstractProxyInvoker::invoke(shared_ptr<IInvocation> invocation) {
            try {
                return std::make_shared<RpcResult>(
                        doInvoke(proxy, invocation->getMethodName(), invocation->getParameterTypes(),
                                 invocation->getArguments()));
            } catch (const std::exception &e) {

            }

            return nullptr;
        }
    }
}