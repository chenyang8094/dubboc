//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_RPCINVOCATION_H
#define DUBBOC_RPCINVOCATION_H

#include "IInvocation.h"
#include <memory>
#include <common/Constants.h>

namespace DUBBOC {
    namespace RPC {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class RpcInvocation : public IInvocation {
        public:
            RpcInvocation() = default;

            RpcInvocation(shared_ptr<IInvocation> invocation, shared_ptr<IInvoker> invoker) :
                    RpcInvocation(invocation->getMethodName(), invocation->getParameterTypes(),
                                  invocation->getArguments(), invocation->getAttachments(),
                                  invocation->getInvoker()) {

                if (invoker != nullptr) {
                    auto url = invoker->getUrl();
                    setAttachment(Constants::PATH_KEY, url->getPath());
                    if (url->hasParameter(Constants::INTERFACE_KEY)) {
                        setAttachment(Constants::INTERFACE_KEY, url->getParameter(Constants::INTERFACE_KEY));
                    }
                    if (url->hasParameter(Constants::GROUP_KEY)) {
                        setAttachment(Constants::GROUP_KEY, url->getParameter(Constants::GROUP_KEY));
                    }
                    if (url->hasParameter(Constants::VERSION_KEY)) {
                        setAttachment(Constants::VERSION_KEY,
                                      url->getParameter(Constants::VERSION_KEY, string("0.0.0")));
                    }
                    if (url->hasParameter(Constants::TIMEOUT_KEY)) {
                        setAttachment(Constants::TIMEOUT_KEY, url->getParameter(Constants::TIMEOUT_KEY));
                    }
                    if (url->hasParameter(Constants::TOKEN_KEY)) {
                        setAttachment(Constants::TOKEN_KEY, url->getParameter(Constants::TOKEN_KEY));
                    }
                    if (url->hasParameter(Constants::APPLICATION_KEY)) {
                        setAttachment(Constants::APPLICATION_KEY, url->getParameter(Constants::APPLICATION_KEY));
                    }
                }
            }

            RpcInvocation(shared_ptr<IInvocation> invocation) :
                    RpcInvocation(invocation->getMethodName(), invocation->getParameterTypes(),
                                  invocation->getArguments(), invocation->getAttachments(), invocation->getInvoker()) {
            }

            RpcInvocation(const string &methodName, const folly::dynamic &parameterTypes,
                          const folly::dynamic &arguments) :
                    RpcInvocation(methodName, parameterTypes, arguments, nullptr, nullptr) {
            }

            RpcInvocation(const string &methodName, const folly::dynamic &parameterTypes,
                          const folly::dynamic &arguments,
                          const folly::dynamic &attachments) :
                    RpcInvocation(methodName, parameterTypes, arguments, attachments, nullptr) {}

            RpcInvocation(const string &methodName, const folly::dynamic &parameterTypes,
                          const folly::dynamic &arguments, const folly::dynamic &attachments,
                          shared_ptr<IInvoker> invoker) {
                this->methodName = methodName;
                this->parameterTypes = parameterTypes;
                this->arguments = arguments;
                this->attachments = attachments;
                this->invoker = invoker;
            }

            shared_ptr<IInvoker> getInvoker() override {
                return invoker;
            }

            void setInvoker(shared_ptr<IInvoker> invoker) {
                this->invoker = invoker;
            }

            string getMethodName() override {
                return methodName;
            }

            void setMethodName(const string &methodName) {
                RpcInvocation::methodName = methodName;
            }

            folly::dynamic getParameterTypes() override {
                return parameterTypes;
            }

            void setParameterTypes(const folly::dynamic &parameterTypes) {
                this->parameterTypes = parameterTypes;
            }

            folly::dynamic getArguments() override {
                return arguments;
            }

            void setArguments(const folly::dynamic &arguments) {
                this->arguments = arguments;
            }

            void setAttachment(const string &key, const string &value) {
                if (attachments == nullptr) {
                    attachments = folly::dynamic::object();
                }
                attachments[key] = value;
            }

            void setAttachmentIfAbsent(const string &key, const string &value) {
                if (attachments == nullptr) {
                    attachments = folly::dynamic::object();
                }
                if (attachments.get_ptr(key) == nullptr) {
                    attachments[key] = value;
                }
            }

            void addAttachments(const folly::dynamic &attachments) {
                if (attachments == nullptr || attachments.empty()) {
                    return;
                }
                if (this->attachments == nullptr) {
                    this->attachments = folly::dynamic::object();
                }
                folly::dynamic::merge(this->attachments, attachments);
            }

            void addAttachmentsIfAbsent(const folly::dynamic &attachments) {
                if (attachments == nullptr || attachments.empty() || !attachments.isObject()) {
                    return;
                }
                for (auto &it : attachments.items()) {
                    setAttachmentIfAbsent(it.first.asString(), it.second.asString());
                }
            }

            string getAttachment(const string &key) override {
                if (attachments == nullptr) {
                    return "";
                }

                if (attachments.get_ptr(key)) {
                    attachments.get_ptr(key)->asString();
                }

                return "";
            }

            string getAttachment(const string &key, const string &defaultValue) override {
                if (attachments == nullptr) {
                    return defaultValue;
                }
                auto value = attachments.get_ptr(key);
                if (value == nullptr || value->asString().empty()) {
                    return defaultValue;
                }
                return value->asString();
            }

            folly::dynamic getAttachments() override {
                return attachments;
            }

        private:
            string methodName;

            // 参数类型全部以字符串的形式表示
            folly::dynamic parameterTypes;

            folly::dynamic arguments;

            folly::dynamic attachments;

            // 不参与序列化
            shared_ptr<IInvoker> invoker;
        };
    }
}
#endif //DUBBOC_RPCINVOCATION_H
