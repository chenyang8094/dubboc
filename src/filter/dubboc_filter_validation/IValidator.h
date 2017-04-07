//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_IVALIDATOR_H
#define DUBBOC_IVALIDATOR_H

#include <string>
#include <folly/dynamic.h>

namespace DUBBOC {
    namespace FILTER {
        using namespace std;

        class IValidator {
        public:
            IValidator() = default;

            virtual ~IValidator() {}

        public:

            virtual void validate(const string &methodName, const folly::dynamic &parameterTypes,
                                  const folly::dynamic &arguments) = 0;

        };
    }
}
#endif //DUBBOC_IVALIDATOR_H
