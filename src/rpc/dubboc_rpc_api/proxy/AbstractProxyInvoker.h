//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_ABSTRACTPROXYINVOKER_H
#define DUBBOC_ABSTRACTPROXYINVOKER_H

#include <memory>
#include <common/URL.h>
#include <rpc/dubboc_rpc_api/IInvoker.h>

namespace DUBBOC {
    namespace RPC {
        using namespace DUBBOC::COMMON;
        using namespace std;

        class IGenericService;

        class IResult;

        class IInvocation;

        class AbstractProxyInvoker : public IInvoker {
        public:
            AbstractProxyInvoker(shared_ptr<IGenericService> proxy, shared_ptr<URL> url) {
                if (proxy == nullptr) {
                    throw std::invalid_argument("proxy == null");
                }

                if (url == nullptr) {
                    throw std::invalid_argument("proxy == url");
                }

                this->proxy = proxy;
                this->url = url;
            }

        public:
            shared_ptr<URL> getUrl() override {
                return url;
            }

            bool isAvailable() override {
                return true;
            }

            void destroy() override {
            }

            shared_ptr<IResult> invoke(shared_ptr<IInvocation> invocation) override;

            virtual folly::dynamic
            doInvoke(shared_ptr<IGenericService> proxy, const string methodName, const folly::dynamic &parameterTypes,
                     const folly::dynamic &arguments) {
                throw std::runtime_error("invoke abstract method, doInvoke");
            }

        private:
            // 泛化服务实现类引用
            shared_ptr<IGenericService> proxy{nullptr};
            shared_ptr<URL> url{nullptr};
        };
    }
}
#endif //DUBBOC_ABSTRACTPROXYINVOKER_H
