
//
// Created by 云海 on 2017/3/30.
//
#include "WangleChannel.h"

namespace DUBBOC {
    namespace REMOTING {
        unordered_map<std::shared_ptr<DubbocPipeline>, std::shared_ptr<WangleChannel>> WangleChannel::channelMap;
        folly::RWSpinLock WangleChannel::rwSpinLock;

    }
}