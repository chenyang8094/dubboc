//
// Created by 云海 on 2017/4/5.
//

#include "SerializationAdaptive.h"
#include <common/ExtensionLoader.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace DUBBOC::CONTAINER;

        shared_ptr<IObjectOutput>
        SerializationAdaptive::serialize(shared_ptr<URL> url, std::ostringstream &output) {
            return nullptr;
        }

        shared_ptr<IObjectInput>
        SerializationAdaptive::deserialize(shared_ptr<URL> url, std::istringstream &input) {
            return nullptr;
        }

        EXTENSION_ADAPTIVE_REGISTER(ISerialization, SerializationAdaptive);
    }
}