//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_WANGLEHANDLER_H
#define DUBBOC_WANGLEHANDLER_H

#include <folly/io/IOBuf.h>
#include <folly/dynamic.h>
#include <wangle/channel/Handler.h>
#include "WangleChannel.h"

namespace DUBBOC {
    namespace REMOTING {

        using namespace std;
        using DubbocPipeline = wangle::Pipeline<folly::IOBufQueue &, const folly::dynamic &>;

        class WangleHandler : public wangle::HandlerAdapter<const folly::dynamic &> {
        public:
            WangleHandler(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) {
                if (url == nullptr) {
                    throw std::invalid_argument("url == null");
                }
                if (handler == nullptr) {
                    throw std::invalid_argument("handler == null");
                }
                this->url = url;
                this->handler = handler;
                this->channels = make_shared<unordered_map<string, shared_ptr<IChannel>>>();
            }

        public:
            shared_ptr<unordered_map<string, shared_ptr<IChannel>>> getChannels() {
                folly::RWSpinLock::ReadHolder readHolder(channels_rwSpinLock);
                return channels;
            }

        public:
            void read(Context *ctx, const folly::dynamic &msg) override {
                shared_ptr<WangleChannel> channel = WangleChannel::getOrAddChannel(
                        std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()), url,
                        handler);

                folly::makeFuture().then([this, channel, &msg] {
                    handler->received(channel, msg);
                }).ensure([ctx] {
                    WangleChannel::removeChannelIfDisconnected(
                            std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()));
                });
            }

            folly::Future<folly::Unit> write(Context *ctx, const folly::dynamic &msg) override {

                shared_ptr<WangleChannel> channel = WangleChannel::getOrAddChannel(
                        std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()), url,
                        handler);

                return ctx->fireWrite(msg).then([this, channel, &msg] {
                    handler->sent(channel, msg);
                }).ensure([ctx] {
                    WangleChannel::removeChannelIfDisconnected(
                            std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()));
                });
            }

            void readEOF(Context *ctx) override {
                ctx->fireClose();
            }

            void readException(Context *ctx, folly::exception_wrapper e) override {
                shared_ptr<WangleChannel> channel = WangleChannel::getOrAddChannel(
                        std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()), url,
                        handler);
                folly::makeFuture().then([this, channel, e] {
                    handler->caught(channel, e.to_exception_ptr());
                }).ensure([ctx] {
                    WangleChannel::removeChannelIfDisconnected(
                            std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()));
                });
            }

            void transportActive(Context *ctx) override {
                shared_ptr<WangleChannel> channel = WangleChannel::getOrAddChannel(
                        std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()), url,
                        handler);

                folly::makeFuture().then([this, ctx, channel] {
                    if (channel != nullptr) {
                        channels_rwSpinLock.lock();
                        folly::SocketAddress remoteAddress;
                        ctx->getTransport()->getPeerAddress(&remoteAddress);
                        channels->insert(make_pair(remoteAddress.getAddressStr(), channel));
                        channels_rwSpinLock.unlock();
                    }
                    handler->connected(channel);
                }).ensure([ctx] {
                    WangleChannel::removeChannelIfDisconnected(
                            std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()));
                });
            }

            void transportInactive(Context *ctx) override {

                shared_ptr<WangleChannel> channel = WangleChannel::getOrAddChannel(
                        std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()), url,
                        handler);

                folly::makeFuture().then([this, ctx, channel] {
                    if (channel != nullptr) {
                        channels_rwSpinLock.lock();
                        folly::SocketAddress remoteAddress;
                        ctx->getTransport()->getPeerAddress(&remoteAddress);
                        channels->erase(remoteAddress.getAddressStr());
                        channels_rwSpinLock.unlock();
                    }
                    handler->disconnected(channel);
                }).ensure([ctx] {
                    WangleChannel::removeChannelIfDisconnected(
                            std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()));

                });
            }

            folly::Future<folly::Unit> writeException(Context *ctx, folly::exception_wrapper e) override {
                shared_ptr<WangleChannel> channel = WangleChannel::getOrAddChannel(
                        std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()), url,
                        handler);
                folly::makeFuture().then([this, channel, e] {
                    handler->caught(channel, e.to_exception_ptr());
                }).ensure([ctx] {
                    WangleChannel::removeChannelIfDisconnected(
                            std::dynamic_pointer_cast<DubbocPipeline>(ctx->getPipelineShared()));
                });
                return folly::makeFuture();
            }

            folly::Future<folly::Unit> close(Context *ctx) override {
                return ctx->fireClose();
            }

        private:
            // client发起connect之后，如果连接成功就加入
            shared_ptr<unordered_map<string, shared_ptr<IChannel>>> channels{nullptr};
            // channel与url都是一一对应的
            shared_ptr<URL> url{nullptr};
            // dubbo自己的Handler，Netty的Handler的请求会转发到这里处理
            shared_ptr<IChannelHandler> handler{nullptr};
            folly::RWSpinLock channels_rwSpinLock;

        };

    }
}
#endif //DUBBOC_WANGLEHANDLER_H
