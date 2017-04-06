//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_RPCCONTEXT_H
#define DUBBOC_RPCCONTEXT_H

#include <folly/ThreadLocal.h>
#include <folly/futures/Future.h>
#include <folly/dynamic.h>
#include <list>
#include <common/URL.h>

namespace DUBBOC {
    namespace RPC {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class RpcContext {
        public:
            RpcContext() {

            }

            ~RpcContext() = default;

        public:
            static folly::ThreadLocal<RpcContext> LOCAL;

            static RpcContext *getContext() {
                return LOCAL.get();
            }

            folly::Future<folly::dynamic> &getFuture() const {
                return std::move(future);
            }

            const list<shared_ptr<URL>, allocator<shared_ptr<URL>>> &getUrls() const {
                return urls;
            }

            shared_ptr<URL> getUrl() const {
                return url;
            }

            const string &getMethodName() const {
                return methodName;
            }

            const folly::dynamic &getParameterTypes() const {
                return parameterTypes;
            }

            const folly::dynamic &getArguments() const {
                return arguments;
            }

            const folly::SocketAddress &getLocalAddress() const {
                return localAddress;
            }

            const folly::SocketAddress &getRemoteAddress() const {
                return remoteAddress;
            }

            const folly::dynamic &getAttachments() const {
                return attachments;
            }

            const folly::dynamic &getValues() const {
                return values;
            }

            const folly::dynamic &getRequest() const {
                return request;
            }

            const folly::dynamic &getResponse() const {
                return response;
            }

            void setFuture(Future<folly::dynamic> &future) {
                this->future = std::move(future);
            }

            void setUrls(const list<shared_ptr<URL>, allocator<shared_ptr<URL>>> &urls) {
                this->urls = urls;
            }

            void setUrl(shared_ptr<URL> url) {
                this->url = url;
            }

            void setMethodName(const string &methodName) {
                this->methodName = methodName;
            }

            void setParameterTypes(const folly::dynamic &parameterTypes) {
                this->parameterTypes = parameterTypes;
            }

            void setArguments(const folly::dynamic &arguments) {
                this->arguments = arguments;
            }

            void setLocalAddress(const folly::SocketAddress &localAddress) {
                this->localAddress = localAddress;
            }

            void setRemoteAddress(const folly::SocketAddress &remoteAddress) {
                this->remoteAddress = remoteAddress;
            }

            void setAttachments(const folly::dynamic &attachments) {
                this->attachments = attachments;
            }

            void setValues(const folly::dynamic &values) {
                this->values = values;
            }

            void setRequest(const folly::dynamic &request) {
                this->request = request;
            }

            void setResponse(const folly::dynamic &response) {
                this->response = response;
            }

        private:
            // 注意保证在move之后future的有效性
            folly::Future<folly::dynamic> future;
            list<shared_ptr<URL>> urls;
            shared_ptr<URL> url;
            string methodName;
            folly::dynamic parameterTypes{nullptr};
            folly::dynamic arguments{nullptr};
            folly::SocketAddress localAddress;
            folly::SocketAddress remoteAddress;
            folly::dynamic attachments{folly::dynamic::object()};
            folly::dynamic values{folly::dynamic::object()};

            folly::dynamic request{folly::dynamic::object()};
            folly::dynamic response{folly::dynamic::object()};
        };

    }
}
#endif //DUBBOC_RPCCONTEXT_H
