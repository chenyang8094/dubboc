//
// Created by 云海 on 2017/4/8.
//

#ifndef DUBBOC_ICONFIGURATORFACTORY_H
#define DUBBOC_ICONFIGURATORFACTORY_H

#include <memory>
#include <common/URL.h>

namespace DUBBOC {
    namespace CLUSTER {
        using namespace DUBBOC::COMMON;
        using namespace std;

        class IConfigurator;

        //@SPI
        class IConfiguratorFactory {

            /**
             * get the configurator instance.
             *
             * @param url - configurator url.
             * @return configurator instance.
             */
            //@Adaptive("protocol")
            virtual shared_ptr<IConfigurator> getConfigurator(shared_ptr<URL> url) = 0;

        };
    }
}
#endif //DUBBOC_ICONFIGURATORFACTORY_H
