//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IMONITORFACTORY_H
#define DUBBOC_IMONITORFACTORY_H

#include "IMonitor.h"

namespace DUBBOC {
    namespace MONITOR {
        using namespace DUBBOC::COMMON;
        using namespace std;

        //@SPI("dubboc")
        class IMonitorFactory {
        public:
            IMonitorFactory() = default;

            virtual ~IMonitorFactory() {}

        public:
            /**
             * Create monitor.
             *
             * @param url
             * @return monitor
             */
            //@Adaptive("protocol")
            virtual shared_ptr<IMonitor> getMonitor(shared_ptr<URL> url) = 0;

        };
    }
}
#endif //DUBBOC_IMONITORFACTORY_H
