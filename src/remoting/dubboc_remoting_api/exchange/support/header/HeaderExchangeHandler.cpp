//
// Created by 云海 on 2017/4/19.
//
#include "HeaderExchangeHandler.h"
#include "HeaderExchangeChannel.h"
#include <remoting/dubboc_remoting_api/exchange/Request.h>
#include <remoting/dubboc_remoting_api/exchange/Response.h>
#include "HeartbeatHandler.h"
#include <remoting/dubboc_remoting_api/IChannel.h>
#include <remoting/dubboc_remoting_api/exchange/support/DefaultFuture.h>

namespace DUBBOC {
    namespace REMOTING {
        string HeaderExchangeHandler::KEY_READ_TIMESTAMP{HeartbeatHandler::KEY_READ_TIMESTAMP};
        string HeaderExchangeHandler::KEY_WRITE_TIMESTAMP{HeartbeatHandler::KEY_WRITE_TIMESTAMP};


        void HeaderExchangeHandler::handlerEvent(shared_ptr<IChannel> channel, shared_ptr<Request> req) {
            if (!req->getMData().isNull() && req->getMData() == Request::READONLY_EVENT) {
                channel->setAttribute(Constants::CHANNEL_ATTRIBUTE_READONLY_KEY, true);
            }
        }

        shared_ptr<Response>
        HeaderExchangeHandler::handleRequest(shared_ptr<IExchangeChannel> channel, shared_ptr<Request> req) {
            auto response = std::make_shared<Response>(req->getMId(), req->getMVersion());
            if (req->isMBroken()) {
                auto data = req->getMData();
                std::string msg{""};
                if (!data.isNull()) {
                    msg = folly::toJson(data);
                }
                response->setMErrorMsg(msg);
                response->setMStatus(Response::BAD_REQUEST);
                return response;
            }

            auto msg = req->getMData();
            try {
                auto result = this->handler->reply(channel, msg);
                response->setMStatus(Response::OK);
                response->setMResult(result);
            } catch (const std::exception &e) {
                response->setMErrorMsg(e.what());
                response->setMStatus(Response::SERVICE_ERROR);
            }
            return response;
        }

        void HeaderExchangeHandler::handleResponse(shared_ptr<IChannel> channel, shared_ptr<Response> response) {
            if (response != nullptr && !response->isHeartbeat()) {
                DefaultFuture::received(channel, response);
            }
        }

        void HeaderExchangeHandler::connected(shared_ptr<IChannel> channel) {
            channel->setAttribute(KEY_READ_TIMESTAMP, std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count());
            channel->setAttribute(KEY_WRITE_TIMESTAMP, std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count());
            auto exchangeChannel = HeaderExchangeChannel::getOrAddChannel(channel);

        }

        void HeaderExchangeHandler::disconnected(shared_ptr<IChannel> channel)  {

        }

        void HeaderExchangeHandler::sent(shared_ptr<IChannel> channel, const folly::dynamic &message)  {

        }

        void HeaderExchangeHandler::received(shared_ptr<IChannel> channel, const folly::dynamic &message)  {

        }

        void HeaderExchangeHandler::caught(shared_ptr<IChannel> channel, std::exception_ptr exception)  {

        }
    }
}
