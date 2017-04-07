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
#include <future>

namespace DUBBOC {
    namespace RPC {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class RpcContext {
        public:
            RpcContext() {};

            ~RpcContext() = default;

        public:
            static folly::ThreadLocal<RpcContext> LOCAL;

            static RpcContext *getContext() {
                return LOCAL.get();
            }

            shared_ptr<std::future<folly::dynamic>> getFuture() {
                return future;
            }

            const list<shared_ptr<URL>> &getUrls() const {
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

            void setFuture(shared_ptr<std::future<folly::dynamic>> future) {
                this->future = future;
            }

            void setUrls(const list<shared_ptr<URL>> &urls) {
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

            folly::dynamic get() {
                return values;
            }

            RpcContext &set(const string &key, const folly::dynamic &value) {
                if (value == nullptr) {
                    values.erase(key);
                } else {
                    values[key] = value;
                }
                return *this;
            }

            RpcContext &remove(const string &key) {
                values.erase(key);
                return *this;
            }

            folly::dynamic get(const string &key) {
                auto value = values.get_ptr(key);
                if (value) {
                    return values[key];
                }
                return nullptr;
            }

            RpcContext &setAttachment(const string &key, const string &value) {
                if (value.empty()) {
                    attachments.erase(key);
                } else {
                    attachments[key] = value;
                }
                return *this;
            }

            string getAttachment(const string &key) {
                return attachments.get_ptr(key) ? attachments.get_ptr(key)->asString() : "";
            }

            RpcContext &removeAttachment(const string &key) {
                attachments.erase(key);
                return *this;
            }

            void clearAttachments() {
                attachments = folly::dynamic::object();
            }

            void setRequest(const folly::dynamic &request) {
                this->request = request;
            }

            void setResponse(const folly::dynamic &response) {
                this->response = response;
            }

            /**
             * is provider side.
             *
             * @return provider side.
             */
            bool isProviderSide() {
                auto url = getUrl();
                if (url == nullptr) {
                    return false;
                }
                // 获取对端地址
                folly::SocketAddress address = getRemoteAddress();
                if (!address.isInitialized()) {
                    return false;
                }
                string host = address.getHostStr();

                //如果对端地址的端口或者host不和url中的一致，说明是provider端
                return url->getPort() != address.getPort() ||
                       !(NetUtils::filterLocalHost(url->getIp()) == (NetUtils::filterLocalHost(host)));
            }

            /**
             * is consumer side.
             *
             * @return consumer side.
             */
            bool isConsumerSide() {
                auto url = getUrl();
                if (url == nullptr) {
                    return false;
                }
                // 获取对端地址
                folly::SocketAddress address = getRemoteAddress();
                if (!address.isInitialized()) {
                    return false;
                }
                string host = address.getHostStr();

                //如果对端地址的port和host都和url中的地址相同，说明是consumer端
                return url->getPort() == address.getPort() &&
                       NetUtils::filterLocalHost(url->getIp()) == (NetUtils::filterLocalHost(host));
            }

            string getLocalHost() {
                string host = localAddress.isInitialized() ? "" : NetUtils::filterLocalHost(localAddress.getHostStr());
                if (host.empty()) {
                    return NetUtils::getLocalHost();
                }
                return host;
            }

            uint16_t getLocalPort() {
                return !localAddress.isInitialized() ? 0 : localAddress.getPort();
            }

            string getRemoteHost() {
                string host = remoteAddress.isInitialized() ? "" : NetUtils::filterLocalHost(
                        remoteAddress.getHostStr());
                if (host.empty()) {
                    return NetUtils::getLocalHost();
                }
                return host;
            }

            uint16_t getRemotePort() {
                return !remoteAddress.isInitialized() ? 0 : remoteAddress.getPort();
            }

            shared_ptr<std::future<folly::dynamic>> asyncCall(std::function<folly::dynamic()> &task) {
                return std::make_shared<std::future<folly::dynamic>>(
                        std::move(std::async(std::launch::async, [&task]() {
                            return task();
                        })));
            }

            void asyncCall(std::function<void()> &task) {
                std::async(std::launch::async, [&task]() {
                    task();
                });
            }

        private:
            shared_ptr<std::future<folly::dynamic>> future{nullptr};
            list<shared_ptr<URL>> urls;
            shared_ptr<URL> url{nullptr};
            string methodName{""};
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
