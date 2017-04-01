//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_ABSTRACTSERVER_H
#define DUBBOC_ABSTRACTSERVER_H

#include <remoting/dubboc_remoting_api/IServer.h>
#include <remoting/dubboc_remoting_api/RemotingException.h>
#include <folly/Executor.h>
#include <folly/futures/ManualExecutor.h>
#include <list>
#include "AbstractEndpoint.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class AbstractServer : public AbstractEndpoint, virtual public IServer {
        public:
            AbstractServer(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) : AbstractEndpoint(url, handler) {
                localAddress = getUrl()->toInetSocketAddress();
                string host = url->getParameter(Constants::ANYHOST_KEY, false)
                              || NetUtils::isInvalidLocalHost(getUrl()->getHost())
                              ? NetUtils::ANYHOST : getUrl()->getHost();
                bindAddress = folly::SocketAddress(host, getUrl()->getPort());
                this->accepts = url->getParameter(Constants::ACCEPTS_KEY, Constants::DEFAULT_ACCEPTS);
                this->idleTimeout = url->getParameter(Constants::IDLE_TIMEOUT_KEY, Constants::DEFAULT_IDLE_TIMEOUT);
                try {
                    doOpen();// 创建Server的时候是自己动绑定打开端口
                    LOG(INFO) << string("Start ") + " bind " + getBindAddress().getAddressStr() + ", export " +
                                 getLocalAddress().getAddressStr();
                } catch (const std::exception &t) {
                    throw RemotingException(url->toInetSocketAddress(), folly::SocketAddress(),
                                            std::string("Failed to bind ") + " on " +
                                            getLocalAddress().getAddressStr() + ", cause: " + t.what());
                }

                executor = std::make_shared<folly::ManualExecutor>();
            }

            virtual folly::SocketAddress getLocalAddress() override {
                return localAddress;
            }

            virtual folly::SocketAddress getBindAddress() {
                return bindAddress;
            }

            virtual void reset(shared_ptr<URL> url) override {
                if (url == nullptr) {
                    return;
                }
                try {
                    if (url->hasParameter(Constants::ACCEPTS_KEY)) {
                        int a = url->getParameter(Constants::ACCEPTS_KEY, (int) 0);
                        if (a > 0) {
                            this->accepts = a;
                        }
                    }
                } catch (const std::exception &t) {
                    LOG(ERROR) << t.what();
                }
                try {
                    if (url->hasParameter(Constants::IDLE_TIMEOUT_KEY)) {
                        int t = url->getParameter(Constants::IDLE_TIMEOUT_KEY, (int) 0);
                        if (t > 0) {
                            this->idleTimeout = t;
                        }
                    }
                } catch (const std::exception &t) {
                    LOG(ERROR) << t.what();
                }
                try {

                } catch (const std::exception &t) {
                    LOG(ERROR) << t.what();
                }
                AbstractEndpoint::setUrl(getUrl()->addParameters(url->getParameters()));
            }

            virtual void send(const folly::dynamic &message, bool sent) override {
                auto channels = getChannels();
                if (channels != nullptr) {
                    for (auto &channel : *channels) {
                        if (channel->isConnected()) {
                            channel->send(message, sent);
                        }
                    }
                }
            }

            virtual void close() override {
                LOG(INFO) << std::string("Close ") + " bind " + getBindAddress().getAddressStr() + ", export " +
                             getLocalAddress().getAddressStr();

//                ExecutorUtil.shutdownNow(executor ,100);
                try {
                    AbstractEndpoint::close();
                } catch (const std::exception &e) {
                    LOG(ERROR) << e.what();
                }
                try {
                    doClose();
                } catch (const std::exception &e) {
                    LOG(ERROR) << e.what();
                }
            }

            virtual void close(uint32_t timeout) override {
//                ExecutorUtil.gracefulShutdown(executor ,timeout);
                close();
            }

            virtual void connected(shared_ptr<IChannel> ch) override;

            virtual void disconnected(shared_ptr<IChannel> ch) override;

        protected:
            virtual void doOpen() {
                throw std::runtime_error("invoke abstract method.");
            };

            virtual void doClose() {
                throw std::runtime_error("invoke abstract method.");
            };

        private:
            std::shared_ptr<folly::Executor> executor{nullptr};
            folly::SocketAddress localAddress;
            folly::SocketAddress bindAddress;
            uint32_t accepts;
            uint32_t idleTimeout;
        protected:
            static const std::string SERVER_THREAD_POOL_NAME;

        };
    }
}
#endif //DUBBOC_ABSTRACTSERVER_H
