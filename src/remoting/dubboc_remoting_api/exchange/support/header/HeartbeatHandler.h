
//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_HEARTBEATHANDLER_H
#define DUBBOC_HEARTBEATHANDLER_H

#include <remoting/dubboc_remoting_api/transport/AbstractChannelHandlerDelegate.h>

namespace DUBBOC {
    namespace REMOTING {
        class HeartbeatHandler : public AbstractChannelHandlerDelegate {
        public:
            explicit HeartbeatHandler(std::shared_ptr<IChannelHandler> handler) : AbstractChannelHandlerDelegate(
                    handler) {

            }

        public:
            void connected(shared_ptr<IChannel> channel) override;

            void disconnected(shared_ptr<IChannel> channel) override;

            void sent(shared_ptr<IChannel> channel, const folly::dynamic &message) override;

            void received(shared_ptr<IChannel> channel, const folly::dynamic &message) override;

        private:
            void setReadTimestamp(std::shared_ptr<IChannel> channel);

            void setWriteTimestamp(std::shared_ptr<IChannel> channel);

            void clearReadTimestamp(std::shared_ptr<IChannel> channel);

            void clearWriteTimestamp(std::shared_ptr<IChannel> channel);

            bool isHeartbeatRequest(const folly::dynamic &message);

            bool isHeartbeatResponse(const folly::dynamic &message);

        public:
            static std::string KEY_READ_TIMESTAMP;

            static std::string KEY_WRITE_TIMESTAMP;
        };
    }
}
#endif //DUBBOC_HEARTBEATHANDLER_H
