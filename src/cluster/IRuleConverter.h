//
// Created by 云海 on 2017/4/8.
//

#ifndef DUBBOC_IRULECONVERTER_H
#define DUBBOC_IRULECONVERTER_H

#include <folly/dynamic.h>
#include <common/URL.h>

namespace DUBBOC {
    namespace CLUSTER {
        using namespace DUBBOC::COMMON;

        //@SPI
        class IRuleConverter {
        public:
            IRuleConverter() = default;

            virtual ~IRuleConverter() {}

        public:

            virtual std::list<std::shared_ptr<URL>>
            convert(std::shared_ptr<URL> subscribeUrl, const folly::dynamic &source) = 0;

        };
    }
}
#endif //DUBBOC_IRULECONVERTER_H
