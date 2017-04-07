//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_ABSTRACTCONFIG_H
#define DUBBOC_ABSTRACTCONFIG_H


#include <string>
#include <folly/dynamic.h>

namespace DUBBOC {
    namespace CONFIG {
        using namespace std;

        class AbstractConfig {


        public:
            string getId() {
                return id;
            }

            void setId(const string &id) {
                this->id = id;
            }


        protected:
            string id;
        private:
            static const int MAX_LENGTH = 100;
            static const int MAX_PATH_LENGTH = 200;
            static const string PATTERN_NAME;
            static const string PATTERN_MULTI_NAME;
            static const string PATTERN_METHOD_NAME;
            static const string PATTERN_PATH;
            static const string PATTERN_NAME_HAS_SYMBOL;
            static const string PATTERN_KEY;
            static folly::dynamic legacyProperties;
        };
    }
}
#endif //DUBBOC_ABSTRACTCONFIG_H
