//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_ICODEC_H
#define DUBBOC_ICODEC_H

#include <folly/io/IOBuf.h>
#include <folly/io/IOBufQueue.h>
#include "IChannel.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class ICodec {
        public:
            virtual ~ICodec() {}

        public:

            virtual void encode(shared_ptr<IChannel> channel, std::unique_ptr<folly::IOBuf> &buffer,
                                const folly::dynamic & message) = 0;

            virtual folly::dynamic
            decode(shared_ptr<IChannel> channel, folly::IOBufQueue &buffer) = 0;

            enum DecodeResult {
                NEED_MORE_INPUT, SKIP_SOME_INPUT
            };
        };
    }
}
#endif //DUBBOC_ICODEC_H
