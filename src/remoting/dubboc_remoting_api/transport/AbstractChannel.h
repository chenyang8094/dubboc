//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_ABSTRACTCHANNEL_H
#define DUBBOC_ABSTRACTCHANNEL_H

#include <remoting/dubboc_remoting_api/RemotingException.h>
#include <folly/json.h>
#include "AbstractPeer.h"

namespace DUBBOC {
    namespace REMOTING {
        class AbstractChannel
                : public AbstractPeer, public IChannel, public std::enable_shared_from_this<AbstractChannel> {
        public:
            AbstractChannel(shared_ptr<URL> url, shared_ptr<IChannelHandler> handleAbstractChannelr)
                    : AbstractPeer(url, handleAbstractChannelr) {}

            virtual void send(const folly::dynamic &message, bool sent) override {
                if (isClosed()) {
                    throw RemotingException(shared_from_this(), std::string("Failed to send message ")
                                                                + folly::toJson(message)
                                                                + ", cause: Channel closed. channel: " +
                                                                getLocalAddress().getAddressStr() +
                                                                " -> " + getRemoteAddress().getAddressStr());
                }
            }


        };
    }
}
#endif //DUBBOC_ABSTRACTCHANNEL_H
