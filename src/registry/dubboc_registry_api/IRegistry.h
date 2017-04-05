//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IREGISTRY_H
#define DUBBOC_IREGISTRY_H

#include <common/INode.h>
#include "IRegistryService.h"

namespace DUBBOC {
    namespace REGISTRY {
        using namespace DUBBOC::COMMON;

        class IRegistry : public INode, public IRegistryService {
        public:
            IRegistry() = default;

            virtual ~IRegistry() {}
        };
    }
}
#endif //DUBBOC_IREGISTRY_H
