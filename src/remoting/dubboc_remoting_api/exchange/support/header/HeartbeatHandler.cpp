//
// Created by 云海 on 2017/4/13.
//

#include "HeartbeatHandler.h"
#include <remoting/dubboc_remoting_api/IChannel.h>
#include <remoting/dubboc_remoting_api/exchange/Response.h>
#include <remoting/dubboc_remoting_api/exchange/Request.h>

namespace DUBBOC {
    namespace REMOTING {

        std::string HeartbeatHandler::KEY_READ_TIMESTAMP = "READ_TIMESTAMP";

        std::string HeartbeatHandler::KEY_WRITE_TIMESTAMP = "WRITE_TIMESTAMP";

        void HeartbeatHandler::connected(shared_ptr<IChannel> channel) {
            setReadTimestamp(channel);
            setWriteTimestamp(channel);
            handler->connected(channel);
        }

        void HeartbeatHandler::disconnected(shared_ptr<IChannel> channel) {
            clearReadTimestamp(channel);
            clearWriteTimestamp(channel);
            handler->disconnected(channel);
        }

        void HeartbeatHandler::sent(shared_ptr<IChannel> channel, const folly::dynamic &message) {
            setWriteTimestamp(channel);
            handler->sent(channel, message);
        }

        void HeartbeatHandler::received(shared_ptr<IChannel> channel, const folly::dynamic &message) {
            setReadTimestamp(channel);
            if (isHeartbeatRequest(message)) {
                Request req(message);
                if (req.isMTwoWay()) {
                    Response res(req.getMId(), req.getMVersion());
                    res.setMEvent(Response::HEARTBEAT_EVENT);
                    channel->send(res.GetDynamic());

                    int heartbeat = channel->getUrl()->getParameter(Constants::HEARTBEAT_KEY, (int) 0);

//                    logger.debug("Received heartbeat from remote channel " + channel.getRemoteAddress()
//                                 + ", cause: The channel has no data-transmission exceeds a heartbeat period"
//                                 + (heartbeat > 0 ? ": " + heartbeat + "ms" : ""));

                }
                return;
            }

            if (isHeartbeatResponse(message)) {

//                    logger.debug(
//                                    new StringBuilder(32)
//                            .append("Receive heartbeat response in thread ")
//                            .append(Thread.currentThread().getName())
//                            .toString());

                return;
            }
            // 不是心跳的话就继续传播事件
            handler->received(channel, message);
        }

        void HeartbeatHandler::setReadTimestamp(std::shared_ptr<IChannel> channel) {
            channel->setAttribute(KEY_READ_TIMESTAMP, std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count());
        }

        void HeartbeatHandler::setWriteTimestamp(std::shared_ptr<IChannel> channel) {
            channel->setAttribute(KEY_WRITE_TIMESTAMP, std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count());
        }

        void HeartbeatHandler::clearReadTimestamp(std::shared_ptr<IChannel> channel) {
            channel->removeAttribute(KEY_READ_TIMESTAMP);
        }

        void HeartbeatHandler::clearWriteTimestamp(std::shared_ptr<IChannel> channel) {
            channel->removeAttribute(KEY_WRITE_TIMESTAMP);
        }

        bool HeartbeatHandler::isHeartbeatRequest(const folly::dynamic &message) {
            if (message.isObject() && message.get_ptr("@type") && (message.get_ptr("@type")->asString() == "Request")) {
                if (message.get_ptr("mEvent") && message.get_ptr("mEvent")->asBool() && message.get_ptr("mData") &&
                    message.get_ptr("mData")->isNull()) {
                    return true;
                }
            }
            return false;
        }

        bool HeartbeatHandler::isHeartbeatResponse(const folly::dynamic &message) {
            if (message.isObject() && message.get_ptr("@type") &&
                (message.get_ptr("@type")->asString() == "Response")) {
                if (message.get_ptr("mEvent") && message.get_ptr("mEvent")->asBool() && message.get_ptr("mResult") &&
                    message.get_ptr("mResult")->isNull()) {
                    return true;
                }
            }
            return false;
        }
    }
}