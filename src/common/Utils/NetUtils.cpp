//
// Created by 云海 on 2017/3/28.
//
#include "NetUtils.h"

namespace DUBBOC {
    namespace COMMON {
        const string NetUtils::LOCALHOST = "127.0.0.1";

        const string NetUtils::ANYHOST = "0.0.0.0";

        const string NetUtils::ADDRESS_PATTERN = "^\\d{1,3}(\\.\\d{1,3}){3}\\:\\d{1,5}$";

        const string NetUtils::LOCAL_IP_PATTERN = "127(\\.\\d{1,3}){3}$";

        const string NetUtils::IP_PATTERN = "\\d{1,3}(\\.\\d{1,3}){3,5}$";

        shared_ptr<folly::IPAddress> NetUtils::LOCAL_ADDRESS = nullptr;
    }
}