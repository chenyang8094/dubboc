//
// Created by 云海 on 2017/4/5.
//
#include "JsonSerialization.h"
#include <common/ExtensionLoader.h>

namespace DUBBOC {
    namespace COMMON {

        shared_ptr<IObjectOutput> JsonSerialization::serialize(shared_ptr<URL> url, std::ostringstream &output) {
            return make_shared<JsonObjectOutput>(output);
        }

        shared_ptr<IObjectInput> JsonSerialization::deserialize(shared_ptr<URL> url, std::istringstream &input) {
            return make_shared<JsonObjectInput>(input);
        }

        EXTENSION_REGISTER(ISerialization, JsonSerialization);
    }
}

