//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_ISERIALIZATION_H
#define DUBBOC_ISERIALIZATION_H

#include <iostream>
#include <common/URL.h>
#include <folly/io/Cursor.h>
#include "IObjectInput.h"
#include "IObjectOutput.h"

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class ISerialization {
        public:
            /**
             * get content type id
             *
             * @return content type id
             */
            virtual uint8_t getContentTypeId() = 0;

            /**
             * get content type
             *
             * @return content type
             */
            virtual string getContentType() = 0;

            /**
             * create serializer
             * @param url
             * @param output
             * @return serializer
             *
             */

            virtual shared_ptr<IObjectOutput> serialize(shared_ptr<URL> url, std::ostringstream &output) = 0;

            /**
             * create deserializer
             * @param url
             * @param input
             * @return deserializer
             *
             */
            virtual shared_ptr<IObjectInput> deserialize(shared_ptr<URL> url, std::istringstream &input) = 0;
        };
    }
}
#endif //DUBBOC_ISERIALIZATION_H
