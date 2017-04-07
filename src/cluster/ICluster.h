//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_ICLUSTER_H
#define DUBBOC_ICLUSTER_H

#include <memory>

namespace DUBBOC {
    namespace CLUSTER {
        using namespace std;

        class IInvoker;
        class IDirectory;

        //@SPI(FailoverCluster.NAME)
        class ICluster {
        public:
            ICluster() = default;

            virtual ~ICluster() {}

        public:


            /**
             * Merge the directory invokers to a virtual invoker.
             *
             * @param <T>
             * @param directory
             * @return cluster invoker
             * @throws RpcException
             */
            //@Adaptive
            virtual shared_ptr<IInvoker> join(shared_ptr<IDirectory> directory)  = 0;

        };
    }
}
#endif //DUBBOC_ICLUSTER_H
