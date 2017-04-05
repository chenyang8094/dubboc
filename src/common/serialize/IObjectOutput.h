//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IOBJECTOUTPUT_H
#define DUBBOC_IOBJECTOUTPUT_H

#include <folly/dynamic.h>
#include "IDataOutput.h"

namespace DUBBOC {
    namespace COMMON {
        class IObjectOutput : public IDataOutput {
        public:
            /**
             * write object.
             *
             * @param obj object.
             */
            virtual void writeObject(const folly::dynamic &obj)  = 0;
        };
    }
}
#endif //DUBBOC_IOBJECTOUTPUT_H
