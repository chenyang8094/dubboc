//
// Created by 云海 on 2017/4/8.
//

#ifndef DUBBOC_IMERGER_H
#define DUBBOC_IMERGER_H

#include <list>

namespace DUBBOC {
    namespace CLUSTER {
        //@SPI
        template<typename T>
        class IMerger {
        public:
            IMerger() = default;

            virtual ~IMerger() {}

        public:
            /**
             * 此处不能使用变长参数，因为变长参数的类型只能为基本类型和pod类型
             * */
            virtual T merge(const std::list<T> &items) = 0;

        };


    }
}
#endif //DUBBOC_IMERGER_H
