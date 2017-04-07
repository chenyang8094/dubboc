//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_ICONFIGURATOR_H
#define DUBBOC_ICONFIGURATOR_H

#include <memory>
#include <common/URL.h>

namespace DUBBOC {
    namespace CLUSTER {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class Configurator {
        public:
            Configurator() = default;

            virtual ~Configurator() {}

        public:

            /**
             * get the configurator url.
             *
             * @return configurator url.
             */
            virtual shared_ptr<URL> getUrl() = 0;

            /**
             * Configure the provider url.
             * O
             * @param url - old rovider url.
             * @return new provider url.
             */
            virtual shared_ptr<URL> configure(shared_ptr<URL> url) = 0;

        };

    }
}
#endif //DUBBOC_ICONFIGURATOR_H
