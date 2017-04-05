//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_HESSIAN2SERIALIZATION_H
#define DUBBOC_HESSIAN2SERIALIZATION_H

#include <common/serialize/ISerialization.h>
#include "Hessian2ObjectOutput.h"
#include "Hessian2ObjectInput.h"

namespace DUBBOC {
    namespace COMMON {
        class Hessian2Serialization : public ISerialization {
        public:
            uint8_t getContentTypeId() override {
                return 2;
            }

            string getContentType() override {
                return "x-application/hessian2";
            }

            shared_ptr<IObjectOutput> serialize(shared_ptr<URL> url, std::ostringstream &output) override;

            shared_ptr<IObjectInput> deserialize(shared_ptr<URL> url, std::istringstream &input) override;

        };
    }
}
#endif //DUBBOC_HESSIAN2SERIALIZATION_H
