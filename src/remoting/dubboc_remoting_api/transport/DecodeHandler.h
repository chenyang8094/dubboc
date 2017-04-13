//
// Created by 云海 on 2017/4/13.
//

#ifndef DUBBOC_DECODEHANDLER_H
#define DUBBOC_DECODEHANDLER_H

#include "AbstractChannelHandlerDelegate.h"

namespace DUBBOC {
    namespace REMOTING {
        class DecodeHandler : public AbstractChannelHandlerDelegate {
        public:
            explicit DecodeHandler(std::shared_ptr<IChannelHandler> handler) : AbstractChannelHandlerDelegate(handler) {

            }

        public:
            void received(shared_ptr<IChannel> channel, const folly::dynamic &message) override {

//                if (message instanceof Decodeable) {
//                    decode(message);
//                }
//
//                if (message instanceof Request) {
//                    decode(((Request)message).getData());
//                }
//
//                if (message instanceof Response) {
//                    decode( ((Response)message).getResult());
//                }

                handler->received(channel,message);
            }

            void decode(const folly::dynamic & message){

            }
        };
    }
}
#endif //DUBBOC_DECODEHANDLER_H
