//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IGENERICSERVICE_H
#define DUBBOC_IGENERICSERVICE_H

#include <folly/dynamic.h>

namespace DUBBOC {
    namespace RPC {
        using namespace std;

        class IGenericService {
        public:
            IGenericService() = default;

            virtual ~IGenericService() {}

        public:

            /**
             * 泛化调用
             *
             * @param method 方法名，如：findPerson，如果有重载方法，需带上参数列表，如：findPerson(java.lang.String)
             * @param parameterTypes 参数类型
             * @param args 参数列表
             * @return 返回值
             */
            virtual folly::dynamic
            $invoke(const string &method, const folly::dynamic &parameterTypes, const folly::dynamic &args) = 0;
        };
    }
}
#endif //DUBBOC_IGENERICSERVICE_H
