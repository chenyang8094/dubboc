//
// Created by 云海 on 2017/3/30.
//
#include "ConfigUtils.h"

namespace DUBBOC {
    namespace COMMON {
        folly::dynamic ConfigUtils::PROPERTIES = folly::dynamic::object();
        folly::RWSpinLock ConfigUtils::rwSpinLock;
    }
}