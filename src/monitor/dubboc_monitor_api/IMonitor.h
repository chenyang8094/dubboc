//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IMONITOR_H
#define DUBBOC_IMONITOR_H

#include <common/INode.h>

namespace DUBBOC {
    namespace MONITOR {
        using namespace DUBBOC::COMMON;

        class IMonitorService;

        class IMonitor : public INode, public IMonitorService {
        public:
            IMonitor() = default;

            virtual ~IMonitor() {}

        };

    }
}
#endif //DUBBOC_IMONITOR_H
