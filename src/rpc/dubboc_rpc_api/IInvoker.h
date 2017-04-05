//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IINVOKER_H
#define DUBBOC_IINVOKER_H

#include <common/INode.h>
#include <rpc/dubboc_rpc_api/service/IGenericService.h>
#include "IResult.h"

namespace DUBBOC {
    namespace RPC {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class IInvocation;

        class IInvoker : public INode {
        public:
            IInvoker() = default;

            virtual ~IInvoker() {}

        public:
            /**
               * get service interface.
               *
               * @return service interface.
               * 这个是获取接口的类型，因为这里只有一种固定的泛化接口，故此接口无效
            */
            virtual std::shared_ptr<IGenericService> getInterface() = 0;

            /**
             * invoke.
             *
             * @param invocation
             * @return result
             * @throws RpcException
             */
            virtual shared_ptr<IResult> invoke(shared_ptr<IInvocation> invocation) = 0;
        };
    }
}
#endif //DUBBOC_IINVOKER_H
