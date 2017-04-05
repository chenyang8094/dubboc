//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IEXPORTER_H
#define DUBBOC_IEXPORTER_H

#include <memory>

namespace DUBBOC {
    namespace RPC {
        using namespace std;

        class IInvoker;

        class IExporter {
        public:
            IExporter() = default;

            virtual ~IExporter() {}

        public:

            /**
             * get invoker.
             *
             * @return invoker
             */
            virtual shared_ptr<IInvoker> getInvoker() = 0;

            /**
             * unexport.
             *
             * <code>
             *     getInvoker().destroy();
             * </code>
             */
            virtual void unexport() = 0;

        };
    }
}
#endif //DUBBOC_IEXPORTER_H
