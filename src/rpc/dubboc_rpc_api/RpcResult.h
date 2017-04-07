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

        private:
            folly::dynamic result{nullptr};
            std::exception_ptr exception{nullptr};
            folly::dynamic attachments{folly::dynamic::object()};
        };

    }
}
#endif //DUBBOC_RPCRESULT_H
