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
