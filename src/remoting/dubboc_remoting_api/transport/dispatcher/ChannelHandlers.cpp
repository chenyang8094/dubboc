
//
// Created by 云海 on 2017/3/31.
//
#include "ChannelHandlers.h"

namespace DUBBOC {
    namespace REMOTING {
        shared_ptr<ChannelHandlers> ChannelHandlers::INSTANCE = std::make_shared<ChannelHandlers>();
    }
}