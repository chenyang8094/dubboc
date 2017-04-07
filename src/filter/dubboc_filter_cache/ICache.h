//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_ICACHE_H
#define DUBBOC_ICACHE_H

#include <folly/dynamic.h>

namespace DUBBOC {
    namespace FILTER {
        class ICache {
        public:
            ICache() = default;

            virtual ~ICache() {}

        public:
            virtual void put(const folly::dynamic &key, const folly::dynamic &value) = 0;

            virtual folly::dynamic get(const folly::dynamic &key) = 0;

        };

    }
}
#endif //DUBBOC_ICACHE_H
