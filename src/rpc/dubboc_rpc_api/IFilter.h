//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IFILTER_H
#define DUBBOC_IFILTER_H

#include <iostream>
#include <memory>
#include "IResult.h"
#include "IInvoker.h"
#include "IInvocation.h"

namespace DUBBOC {
    namespace RPC {
        using  namespace std;

        class IFilter {
        public:
            IFilter() = default;

            virtual ~IFilter() {}

        public:

            /**
             * do invoke filter.
             *
             * <code>
             * // before filter
             * Result result = invoker.invoke(invocation);
             * // after filter
             * return result;
             * </code>
             *
             * @see com.alibaba.dubbo.rpc.Invoker#invoke(Invocation)
             * @param invoker service
             * @param invocation invocation.
             * @return invoke result.
             * @throws RpcException
             */
            virtual shared_ptr<IResult> invoke(shared_ptr<IInvoker> invoker,shared_ptr<IInvocation> invocation) = 0;

        };
    }
}
#endif //DUBBOC_IFILTER_H
