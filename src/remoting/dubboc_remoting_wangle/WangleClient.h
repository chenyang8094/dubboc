//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_WANGLECLIENT_H
#define DUBBOC_WANGLECLIENT_H

#include <remoting/dubboc_remoting_api/transport/AbstractClient.h>
#include <wangle/bootstrap/ClientBootstrap.h>
#include "WangleHandler.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;
        using DubbocPipeline = wangle::Pipeline<folly::IOBufQueue &, const folly::dynamic &>;

        class WangleClient : public AbstractClient, public enable_shared_from_this<WangleClient> {
        public:
            explicit WangleClient(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) :
                    AbstractClient(url, wrapChannelHandler(url, handler)) {}

        protected:
            void doOpen() override {
                auto wangle_handler = std::make_shared<WangleHandler>(getUrl(), shared_from_this());
                bootstrap = std::make_shared<wangle::ClientBootstrap<DubbocPipeline>>();
                bootstrap->group(std::make_shared<wangle::IOThreadPoolExecutor>(1));
                bootstrap->pipelineFactory(std::make_shared<WangleClientPipelineFactory>(wangle_handler));
            }

            void doConnect() override {
                auto start = std::chrono::system_clock::now();

                auto future = bootstrap->connect(getConnectAddress())
                        .then([this](DubbocPipeline *pipeline) {
                            auto new_channel = shared_ptr<DubbocPipeline>(pipeline);//
//                            new_channel->setWriteFlags()
//                            new_channel->setReadBufferSettings()
                            std::exception_ptr exce;
                            try {
                                auto old_channel = this->channel;
                                if (old_channel != nullptr) {
                                    std::exception_ptr exce;
                                    try {
                                        old_channel->close();
                                        LOG(INFO) << "Close old netty channel  and on create new netty channel ";
                                    } catch (const std::exception &e) {
                                        exce = std::current_exception();
                                    }

                                    WangleChannel::removeChannelIfDisconnected(old_channel);
                                    if (exce) {
                                        std::rethrow_exception(exce);
                                    }
                                }
                            } catch (...) {
                                exce = std::current_exception();
                            }

                            if (this->isClosed()) {
                                std::exception_ptr exce;
                                try {
                                    LOG(INFO) << "Close new netty channel , because the client closed.";
                                    new_channel->close();
                                } catch (...) {
                                    exce = std::current_exception();
                                }

                                this->channel = nullptr;
                                WangleChannel::removeChannelIfDisconnected(new_channel);
                                if (exce) {
                                    std::rethrow_exception(exce);
                                }

                            } else {
                                this->channel = new_channel;
                            }

                            if (exce) {
                                std::rethrow_exception(exce);
                            }
                        })
                        .onError([this](const std::exception &ex) {
                            throw;
                        });
                future.wait(getConnectTimeout() * 1ms);
            }

            void doDisConnect() override {
                try {
                    WangleChannel::removeChannelIfDisconnected(channel);
                } catch (const std::exception &t) {
                    LOG(ERROR) << t.what();
                }
            }

            void doClose() override {

            }

            shared_ptr<IChannel> getChannel() override {
                auto c = channel;
                if (c == nullptr || !c->getTransport()->connecting())
                    return nullptr;

                return WangleChannel::getOrAddChannel(c, getUrl(), shared_from_this());
            }

        private:
            class WangleClientPipelineFactory : public wangle::PipelineFactory<DubbocPipeline> {
            public:
                WangleClientPipelineFactory(std::shared_ptr<WangleHandler> hanlder) {
                    this->handler = handler;
                }

                DubbocPipeline::Ptr newPipeline(std::shared_ptr<folly::AsyncTransportWrapper> sock) {
                    auto pipeline = DubbocPipeline::create();
                    pipeline->addBack(wangle::AsyncSocketHandler(sock));
                    pipeline->addBack(wangle::EventBaseHandler());  //  ensure we can write from any thread

                    pipeline->addBack(handler);  //  业务handler
                    pipeline->finalize();
                    return pipeline;
                }

            private:
                std::shared_ptr<WangleHandler> handler{nullptr};
            };

        private:
            shared_ptr<wangle::ClientBootstrap<DubbocPipeline>> bootstrap{nullptr};
            shared_ptr<DubbocPipeline> channel{nullptr};
        };
    }
}
#endif //DUBBOC_WANGLECLIENT_H
