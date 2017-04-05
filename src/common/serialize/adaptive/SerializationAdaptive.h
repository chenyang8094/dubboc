//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_SERIALIZATIONADAPTIVE_H
#define DUBBOC_SERIALIZATIONADAPTIVE_H

#include <common/serialize/ISerialization.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class SerializationAdaptive : public ISerialization {
        public:
            uint8_t getContentTypeId() override {
                throw std::runtime_error("invoke avstract method,getContentTypeId");
            }

            string getContentType() override {
                throw std::runtime_error("invoke avstract method,getContentType");
            }

            shared_ptr<IObjectOutput> serialize(shared_ptr<URL> url, std::ostringstream &output) override;

            shared_ptr<IObjectInput> deserialize(shared_ptr<URL> url, std::istringstream &input) override;
        };

    }
}
#endif //DUBBOC_SERIALIZATIONADAPTIVE_H
