//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_ABSTRACTENDPOINT_H
#define DUBBOC_ABSTRACTENDPOINT_H

#include <common/ExtensionLoader.h>
#include <remoting/dubboc_remoting_api/ICodec.h>
#include <common/IResetable.h>
#include "AbstractPeer.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace DUBBOC::COMMON;

        class AbstractEndpoint : public AbstractPeer,public IResetable {
        public:
            AbstractEndpoint(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) : AbstractPeer(url, handler) {
                this->codec = getChannelCodec(url);
                this->timeout = url->getPositiveParameter(Constants::TIMEOUT_KEY, Constants::DEFAULT_TIMEOUT);
                this->connectTimeout = url->getPositiveParameter(Constants::CONNECT_TIMEOUT_KEY,
                                                                 Constants::DEFAULT_CONNECT_TIMEOUT);

            }

            void reset(shared_ptr<URL> url) override {
                if (isClosed()) {
                    throw std::runtime_error(std::string("Failed to reset parameters ")
                                             + url->toFullString() + ", cause: Channel closed. channel: " +
                                             getLocalAddress().getAddressStr());
                }
                try {
                    if (url->hasParameter(Constants::HEARTBEAT_KEY)) {
                        int t = url->getParameter(Constants::TIMEOUT_KEY, (int) 0);
                        if (t > 0) {
                            this->timeout = t;
                        }
                    }
                } catch (const std::exception &t) {
                    LOG(ERROR) << t.what();
                }
                try {
                    if (url->hasParameter(Constants::CONNECT_TIMEOUT_KEY)) {
                        int t = url->getParameter(Constants::CONNECT_TIMEOUT_KEY, 0);
                        if (t > 0) {
                            this->connectTimeout = t;
                        }
                    }
                } catch (const std::exception &t) {
                    LOG(ERROR) << t.what();
                }
                try {
                    if (url->hasParameter(Constants::CODEC_KEY)) {
                        this->codec = getChannelCodec(url);
                    }
                } catch (const std::exception &t) {
                    LOG(ERROR) << t.what();
                }
            }

        protected:
            static shared_ptr<ICodec> getChannelCodec(shared_ptr<URL> url) {
                string codecName = url->getParameter(Constants::CODEC_KEY, std::string("telnet"));
                if (ExtensionLoader::getInstance()->hasExtension(codecName)) {
                    return ExtensionLoader::getInstance()->LoadExtension<ICodec>(codecName);
                }
                return nullptr;
            }

            virtual shared_ptr<ICodec> getCodec() {
                return codec;
            }

            virtual uint32_t getTimeout() {
                return timeout;
            }

            virtual uint32_t getConnectTimeout() {
                return connectTimeout;
            }

        private:
            shared_ptr<ICodec> codec{nullptr};
            uint32_t timeout{0};
            uint32_t connectTimeout{0};
        };

    }
}

#endif //DUBBOC_ABSTRACTENDPOINT_H
