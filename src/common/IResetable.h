//
// Created by 云海 on 2017/4/20.
//

#ifndef DUBBOC_IRESETABLE_H
#define DUBBOC_IRESETABLE_H

#include "URL.h"

namespace DUBBOC {
    namespace COMMON {

        class IResetable {
        public:
            IResetable() = default;

            virtual ~IResetable() {}

        public:
            virtual void reset(shared_ptr<URL> url) = 0;
        };
    }
}

#endif //DUBBOC_IRESETABLE_H
