//
// Created by 云海 on 2017/3/30.
//

#ifndef DUBBOC_REMOTINGEXCEPTION_H
#define DUBBOC_REMOTINGEXCEPTION_H

#include <stdexcept>
#include <folly/SocketAddress.h>
#include "IChannel.h"

namespace DUBBOC {
    namespace REMOTING {


        class RemotingException : public std::runtime_error {

        public:
            RemotingException(shared_ptr<IChannel> channel, const string &message) : RemotingException(
                    channel->getLocalAddress(), channel->getRemoteAddress(), message) {
            }

            RemotingException(const folly::SocketAddress &localAddress, const folly::SocketAddress &remoteAddress,
                              const string &message) : std::runtime_error(message) {
                this->localAddress = localAddress;
                this->remoteAddress = remoteAddress;
            }

        private:
            folly::SocketAddress localAddress;
            folly::SocketAddress remoteAddress;
        };

    }
}

#endif //DUBBOC_REMOTINGEXCEPTION_H
