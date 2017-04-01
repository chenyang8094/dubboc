//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_WANGLECODECADAPTER_H
#define DUBBOC_WANGLECODECADAPTER_H

#include <iostream>
#include <remoting/dubboc_remoting_api/ICodec.h>
#include <wangle/channel/Handler.h>
#include <folly/io/IOBuf.h>
#include <wangle/codec/ByteToMessageDecoder.h>
#include <wangle/codec/MessageToByteEncoder.h>
#include "WangleChannel.h"


namespace DUBBOC {
    namespace REMOTING {
        using namespace std;
        using namespace DUBBOC::COMMON;
        using DubbocPipeline = wangle::Pipeline<folly::IOBufQueue &, const folly::dynamic &>;

        class WangleCodecAdapter {
        public:
            WangleCodecAdapter(shared_ptr<ICodec> codec, shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) {
                this->codec = codec;
                this->url = url;
                this->handler = handler;
                int b = url->getPositiveParameter(Constants::BUFFER_KEY, Constants::DEFAULT_BUFFER_SIZE);
                this->bufferSize = b >= Constants::MIN_BUFFER_SIZE && b <= Constants::MAX_BUFFER_SIZE ? b
                                                                                                      : Constants::DEFAULT_BUFFER_SIZE;
                encoder = std::make_shared<InternalEncoder>(this);
                decoder = std::make_shared<InternalDecoder>(this);
            }

        private:
            /**
             * 此处之所以不直接使用MessageToByteEncoder的原因是:MessageToByteEncoder中的encode方法无法直接取到Context
             * */
            class InternalEncoder : public wangle::OutboundHandler<folly::dynamic &, std::unique_ptr<folly::IOBuf>> {
            public:
                InternalEncoder() = default;

                InternalEncoder(WangleCodecAdapter *outer) {
                    this->outer = shared_ptr<WangleCodecAdapter>(outer);
                }

            public:
                // encode
                folly::Future<folly::Unit> write(Context *ctx, folly::dynamic &msg) override {
                    std::unique_ptr<folly::IOBuf> buf = std::move(folly::IOBuf::create(1024));// 1K capacity
                    auto ch = std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared());
                    auto channel = WangleChannel::getOrAddChannel(ch, outer->url,
                                                                  outer->handler);
                    std::exception_ptr exe;
                    try {
                        // buf以引用的方式传递过去
                        outer->codec->encode(channel, buf, msg);
                    } catch (...) {
                        exe = std::current_exception();
                    }

                    WangleChannel::removeChannelIfDisconnected(ch);

                    if (exe) {
                        std::rethrow_exception(exe);
                    }
                    return buf ? ctx->fireWrite(std::move(buf)) : folly::makeFuture();
                }

            private:
                shared_ptr<WangleCodecAdapter> outer;
            };

            class InternalDecoder : public wangle::ByteToMessageDecoder<folly::dynamic> {
            public:
                InternalDecoder() = default;

                InternalDecoder(WangleCodecAdapter *outer) {
                    this->outer = shared_ptr<WangleCodecAdapter>(outer);
                }

            public:
                // 返回false表示解码失败，会不同的重试
                bool decode(Context *ctx, folly::IOBufQueue &buf, folly::dynamic &result, size_t &size1) override {

                    auto ch = std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared());
                    auto channel = WangleChannel::getOrAddChannel(ch, outer->url, outer->handler);
                    result = this->outer->codec->decode(channel, buf);

                    return false;
                }

            private:
                shared_ptr<WangleCodecAdapter> outer;
            };

        public:
            shared_ptr<wangle::OutboundHandler<folly::dynamic &, std::unique_ptr<folly::IOBuf>>> getEncoder() {
                return encoder;
            }

            shared_ptr<wangle::ByteToMessageDecoder<folly::dynamic>> getDecoder() {
                return decoder;
            }

        private:
            // netty层的codec(handler)
            shared_ptr<wangle::OutboundHandler<folly::dynamic &, std::unique_ptr<folly::IOBuf>>> encoder{
                    std::make_shared<InternalEncoder>()};
            shared_ptr<wangle::ByteToMessageDecoder<folly::dynamic>> decoder{std::make_shared<InternalDecoder>()};

            // dubbo层的codec
            shared_ptr<ICodec> codec{nullptr};

            shared_ptr<URL> url{nullptr};
            shared_ptr<IChannelHandler> handler{nullptr};

            int bufferSize{0};

        };
    }
}
#endif //DUBBOC_WANGLECODECADAPTER_H
