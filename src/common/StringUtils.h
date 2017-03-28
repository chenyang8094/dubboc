//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_STRINGUTILS_H
#define DUBBOC_STRINGUTILS_H

#include <iostream>
#include <unordered_map>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class StringUtils {
        public:
            static shared_ptr<unordered_map<string, string>> toStringMap(string...) {
                auto shared_map = std::make_shared<unordered_map<string, string>>();

                return nullptr;
            }
        };
    }
}
#endif //DUBBOC_STRINGUTILS_H
