//
// Created by 云海 on 2017/4/5.
//
#include "Hessian2Serialization.h"
#include <common/ExtensionLoader.h>

namespace DUBBOC {
    namespace COMMON {

        shared_ptr<IObjectOutput>
        Hessian2Serialization::serialize(shared_ptr<URL> url, std::ostringstream &output) {
            return make_shared<Hessian2ObjectOutput>(output);
        }

        shared_ptr<IObjectInput>
        Hessian2Serialization::deserialize(shared_ptr<URL> url, std::istringstream &input) {
            return make_shared<Hessian2ObjectInput>(input);
        }

        EXTENSION_REGISTER(ISerialization, Hessian2Serialization);
    }
}