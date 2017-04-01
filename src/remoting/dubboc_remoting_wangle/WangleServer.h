//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_WANGLESERVER_H
#define DUBBOC_WANGLESERVER_H

#include <remoting/dubboc_remoting_api/transport/AbstractServer.h>
#include <remoting/dubboc_remoting_api/IServer.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/Handler.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/channel/EventBaseHandler.h>
#include <remoting/dubboc_remoting_api/transport/dispatcher/ChannelHandlers.h>
#include "WangleHandler.h"
#include "WangleCodecAdapter.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        using DubbocPipeline = wangle::Pipeline<folly::IOBufQueue &, const folly::dynamic &>;

        class WangleServer
                : public AbstractServer, virtual public IServer, public enable_shared_from_this<WangleServer> {
        public:
            WangleServer(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler)
                    : AbstractServer(url, ChannelHandlers::wrap(handler, url)) {}

        protected:
            void doOpen() override {

                auto wangle_handler = std::make_shared<WangleHandler>(getUrl(), shared_from_this());
                channels = wangle_handler->getChannels();
                auto adapter = std::make_shared<WangleCodecAdapter>(getCodec(), getUrl(), shared_from_this());
                bootstrap = std::make_shared<wangle::ServerBootstrap<DubbocPipeline>>();
                bootstrap->childPipeline(std::make_shared<WangleServerPipelineFactory>(wangle_handler, adapter));
                bootstrap->group(std::make_shared<wangle::IOThreadPoolExecutor>(1),
                                 std::make_shared<wangle::IOThreadPoolExecutor>(8));
                bootstrap->setReusePort(false);
                folly::SocketAddress addr = getBindAddress();
                try {
                    bootstrap->bind(addr);
                } catch (const std::exception &e) {
                    throw;
                }
                bind_flag = true;
            }

            void doClose() override {
                try {
                    if (channel != nullptr) {
                        // unbind.
                        channel->close();
                    }
                } catch (const std::exception &e) {
                    LOG(ERROR) << e.what();
                }
                try {
                    auto channels = getChannels();
                    if (channels != nullptr && channels->size() > 0) {
                        for (auto &channel : *channels) {
                            try {
                                channel->close();
                            } catch (const std::exception &e) {
                                LOG(ERROR) << e.what();
                            }
                        }
                    }
                } catch (const std::exception &e) {
                    LOG(ERROR) << e.what();
                }
                try {
                    if (bootstrap != nullptr) {
                        // release external resource.
//                        bootstrap.releaseExternalResources();
                        bootstrap->stop();
                        bind_flag = false;
                    }
                } catch (const std::exception &e) {
                    LOG(ERROR) << e.what();
                }
                try {
                    if (channels != nullptr) {
                        channels->clear();
                    }
                } catch (const std::exception &e) {
                    LOG(ERROR) << e.what();
                }
            }

        public:
            shared_ptr<list<shared_ptr<IChannel>>> getChannels() override {
                auto list_channels = make_shared<list<shared_ptr<IChannel>>>();
                for (auto &it:*channels) {
                    if (it.second->isConnected()) {
                        list_channels->push_back(it.second);
                    } else {
                        channels->erase(it.first);
                    }
                }
                return list_channels;
            }

            shared_ptr<IChannel> getChannel(const folly::SocketAddress &remoteAddress) override {
                auto iter = channels->find(remoteAddress.getAddressStr());
                if (iter != channels->end()) {
                    return iter->second;
                }
                return nullptr;
            }

            bool isBound() override {
                return bind_flag;
            }

        private:
            class WangleServerPipelineFactory : public wangle::PipelineFactory<DubbocPipeline> {
            public:
                explicit WangleServerPipelineFactory(std::shared_ptr<WangleHandler> hanlder,
                                                     std::shared_ptr<WangleCodecAdapter> adapter) {
                    this->handler = handler;
                    this->adapter = adapter;
                }

                DubbocPipeline::Ptr newPipeline(std::shared_ptr<folly::AsyncTransportWrapper> sock) {
                    auto pipeline = DubbocPipeline::create();
                    auto transportInfo = std::make_shared<wangle::TransportInfo>();
                    folly::SocketAddress localAddr, peerAddr;
                    sock->getLocalAddress(&localAddr);
                    sock->getPeerAddress(&peerAddr);
                    transportInfo->localAddr = std::make_shared<folly::SocketAddress>(localAddr);
                    transportInfo->remoteAddr = std::make_shared<folly::SocketAddress>(peerAddr);
                    pipeline->setTransportInfo(transportInfo);
                    pipeline->setReadBufferSettings(1024 * 32, 1024 * 64);
                    pipeline->addBack(wangle::AsyncSocketHandler(sock));
                    pipeline->addBack(wangle::EventBaseHandler());
                    pipeline->addBack(adapter->getEncoder());
                    pipeline->addBack(adapter->getDecoder());
                    pipeline->addBack(handler);
                    pipeline->finalize();
                    return pipeline;
                }

            private:
                std::shared_ptr<WangleHandler> handler{nullptr};
                std::shared_ptr<WangleCodecAdapter> adapter{nullptr};
            };

        private:
            // thread safe
            shared_ptr<std::unordered_map<string, std::shared_ptr<IChannel>>> channels{nullptr};
            shared_ptr<wangle::ServerBootstrap<DubbocPipeline>> bootstrap{nullptr};
            shared_ptr<DubbocPipeline> channel{nullptr};
            bool bind_flag{false};
        };
    }
}
#endif //DUBBOC_WANGLESERVER_H
