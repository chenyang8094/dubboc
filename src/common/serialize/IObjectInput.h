//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IOBJECTINPUT_H
#define DUBBOC_IOBJECTINPUT_H

#include <folly/dynamic.h>
#include "IDataInput.h"

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class IObjectInput : public IDataInput {
        public:
            /**
             * read object.
             *
             * @return object.
             */
            virtual folly::dynamic readObject() = 0;


            /**
             * read object.
             *
             * @param cls object type.
             * @return object.
             */
            virtual folly::dynamic readObject(const string &type) = 0;

        };
    }
}
#endif //DUBBOC_IOBJECTINPUT_H
