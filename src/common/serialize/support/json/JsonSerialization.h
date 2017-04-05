//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_JSONSERIALIZATION_H
#define DUBBOC_JSONSERIALIZATION_H

#include <common/serialize/ISerialization.h>
#include "JsonObjectOutput.h"
#include "JsonObjectInput.h"

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class JsonSerialization : public ISerialization {
        public:
        private:
            uint8_t getContentTypeId() override {
                return 5;
            }

            string getContentType() override {
                return "text/json";
            }

            shared_ptr<IObjectOutput> serialize(shared_ptr<URL> url, std::ostringstream &output) override ;

            shared_ptr<IObjectInput> deserialize(shared_ptr<URL> url, std::istringstream &input) override ;
        };
    }
}
#endif //DUBBOC_JSONSERIALIZATION_H
