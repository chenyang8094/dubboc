

//
// Created by 云海 on 2017/3/30.
//
#include "DefaultFuture.h"

namespace DUBBOC {
    namespace REMOTING {

        unordered_map<long, shared_ptr<IChannel>> DefaultFuture::CHANNELS;
        unordered_map<long, shared_ptr<DefaultFuture>> DefaultFuture::FUTURES;
        folly::RWSpinLock DefaultFuture::channels_rwlock;
        folly::RWSpinLock DefaultFuture::futures_rwlock;
        std::atomic_flag DefaultFuture::daemon_thread_flag = ATOMIC_FLAG_INIT;
    }
}