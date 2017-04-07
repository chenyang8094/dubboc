//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_IVALIDATION_H
#define DUBBOC_IVALIDATION_H

#include <memory>
#include <common/URL.h>

namespace DUBBOC {
    namespace FILTER {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class IValidator;

        //@SPI("jvalidation")
        class Validation {
        public:
            Validation() = default;

            virtual ~Validation() {}

        public:

            //@Adaptive(Constants.VALIDATION_KEY)
            virtual shared_ptr<IValidator> getValidator(shared_ptr<URL> url) = 0;

        };

    }
}
#endif //DUBBOC_IVALIDATION_H
