//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_URLUTILS_H
#define DUBBOC_URLUTILS_H

#include <string>
#include <folly/Range.h>
namespace DUBBOC {
    namespace COMMON {
        class Base64 {
        public:
            static std::string urlDecode(const std::string& b64message);
            static std::string urlEncode(folly::ByteRange buffer);
        };
    }
}
#endif //DUBBOC_URLUTILS_H
