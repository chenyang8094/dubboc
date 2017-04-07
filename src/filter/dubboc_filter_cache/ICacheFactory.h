//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_ICACHEFACTORY_H
#define DUBBOC_ICACHEFACTORY_H

#include <memory>
#include <common/URL.h>

namespace DUBBOC {
    namespace FILTER {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class ICache;

        //@SPI("lru")
        class ICacheFactory {

        public:
            ICacheFactory() = default;

            virtual ~ICacheFactory() {}
            

        public:
            //@Adaptive("cache")
            virtual shared_ptr<ICache> getCache(shared_ptr<URL> url) = 0;
        };
    }
}
#endif //DUBBOC_ICACHEFACTORY_H
