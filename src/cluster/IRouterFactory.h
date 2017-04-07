
//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_IROUTERFACTORY_H
#define DUBBOC_IROUTERFACTORY_H

#include <memory>
#include <common/URL.h>

namespace DUBBOC {
    namespace CLUSTER {

        using namespace std;
        using namespace DUBBOC::COMMON;

        class IRouter;

        //@SPI
        class RouterFactory {
        public:
            RouterFactory() = default;

            virtual ~RouterFactory() {}

        public:
            /**
             * Create router.
             *
             * @param url
             * @return router
             */
            //@Adaptive("protocol")
            virtual shared_ptr<IRouter> getRouter(shared_ptr<URL> url) = 0;

        };
    }
}
#endif //DUBBOC_IROUTERFACTORY_H
