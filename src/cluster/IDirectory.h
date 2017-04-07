//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_IDIRECTORY_H
#define DUBBOC_IDIRECTORY_H

#include <memory>
#include <common/INode.h>
#include <list>
#include <rpc/dubboc_rpc_api/IInvocation.h>

namespace DUBBOC {
    namespace CLUSTER {
        using namespace DUBBOC::COMMON;
        using namespace DUBBOC::RPC;

        class IDirectory : public INode {
        public:
            IDirectory() = default;

            virtual ~IDirectory() {}

        public:
            /**
             * list invokers.
             *
             * @return invokers
             */
            virtual list<shared_ptr<IInvoker>> list(shared_ptr<IInvocation> invocation) = 0;
        };
    }
}
#endif //DUBBOC_IDIRECTORY_H
