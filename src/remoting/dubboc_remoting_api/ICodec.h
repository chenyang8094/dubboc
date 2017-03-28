//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_ICODEC_H
#define DUBBOC_ICODEC_H

#include <remoting/dubboc_remoting_api/buffer/IChannelBuffer.h>
#include "IChannel.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class Codec {
        public:
            virtual ~Codec() {}

        public:

            virtual void encode(shared_ptr<IChannel> channel, shared_ptr<IChannelBuffer> buffer,
                                folly::dynamic message) = 0;

            virtual folly::dynamic
            decode(shared_ptr<IChannel> channel, shared_ptr<IChannelBuffer> buffer) = 0;

            enum DecodeResult {
                NEED_MORE_INPUT, SKIP_SOME_INPUT
            };
        };
    }
}
#endif //DUBBOC_ICODEC_H
