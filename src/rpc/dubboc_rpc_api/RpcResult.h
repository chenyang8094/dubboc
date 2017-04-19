//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_RPCRESULT_H
#define DUBBOC_RPCRESULT_H

#include "IResult.h"

namespace DUBBOC {
    namespace RPC {
        using namespace std;

        class RpcResult : public IResult {
        public:
            RpcResult() = default;

            RpcResult(const folly::dynamic &result) {
                this->result = result;
            }

            RpcResult(std::exception_ptr exception) {
                this->exception = exception;
            }

        public:
            folly::dynamic recreate() override {
                if (exception != nullptr) {
                    std::rethrow_exception(exception);
                }
                return result;
            }

            void setValue(const folly::dynamic &result) {
                this->result = result;
            }

            exception_ptr getException() override {
                return exception;
            }

            folly::dynamic getValue() override {
                return nullptr;
            }

            folly::dynamic getAttachments() override {
                return nullptr;
            }

            void setException(exception_ptr exception) {
                this->exception = exception;
            }

            bool hasException() override {
                return exception != nullptr;
            }

            void setAttachments(const folly::dynamic &attachments) {
                if (attachments == nullptr || !attachments.isObject() || attachments.empty()) {
                    return;
                }
                folly::dynamic::merge(this->attachments, attachments);
            }

            string getAttachment(const string &key) override {
                auto value = attachments.get_ptr(key);
                if (value) {
                    return value->asString();
                }
                return "";
            }

            string getAttachment(const string &key, const string &defaultValue) override {
                auto result = attachments.get_ptr(key);
                if (result == nullptr || result->asString().empty()) {
                    return defaultValue;
                }
                return result->asString();
            }

            folly::dynamic const & GetDynamic(){
                if(inner_dynamic_cache.empty()){
                    inner_dynamic_cache["result"] = result;
                    // 此处的异常应该特殊处理一下
                    inner_dynamic_cache["exception"] = exception;//????
                    inner_dynamic_cache["attachments"] = attachments;
                }
                return inner_dynamic_cache;
            }

        private:
            folly::dynamic inner_dynamic_cache{folly::dynamic::object()};
            folly::dynamic result{nullptr};
            std::exception_ptr exception{nullptr};
            folly::dynamic attachments{folly::dynamic::object()};
        };
    }
}
#endif //DUBBOC_RPCRESULT_H
