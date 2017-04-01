//
// Created by 云海 on 2017/3/31.
//
#include "AbstractServer.h"

namespace DUBBOC {
    namespace REMOTING {
        const std::string AbstractServer::SERVER_THREAD_POOL_NAME = "DubboServerHandler";

        void AbstractServer::connected(shared_ptr<IChannel> ch) {
            auto channels = getChannels();
            if (accepts > 0 && channels != nullptr && channels->size() > accepts) {
                LOG(ERROR) << "Close channel " << ", cause: The server " << ch->getLocalAddress().getAddressStr()
                           << " connections greater than max config " << accepts;
                ch->close();
                return;
            }
            AbstractPeer::connected(ch);
        }

        void AbstractServer::disconnected(shared_ptr<IChannel> ch) {
            auto channels = getChannels();
            if (channels == nullptr || channels->size() == 0) {
                LOG(WARNING) << "All clients has discontected from " + ch->getLocalAddress().getAddressStr()
                             << ". You can graceful shutdown now.";
            }
            AbstractPeer::disconnected(ch);
        }

    }
}