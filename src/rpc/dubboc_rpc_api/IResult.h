//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IRESULT_H
#define DUBBOC_IRESULT_H

#include <exception>
#include <folly/dynamic.h>

namespace DUBBOC {
    namespace RPC {
        using namespace std;

        class IResult {
        public:
            IResult() = default;

            virtual ~IResult() {  }

        public:

            /**
             * Get invoke result.
             *
             * @return result. if no result return null.
             */
            virtual folly::dynamic getValue() = 0;

            /**
             * Get exception.
             *
             * @return exception. if no exception return null.
             */
            virtual std::exception_ptr getException() = 0;

            /**
             * Has exception.
             *
             * @return has exception.
             */
            virtual bool hasException() = 0;

            /**
             * Recreate.
             *
             * <code>
             * if (hasException()) {
             *     throw getException();
             * } else {
             *     return getValue();
             * }
             * </code>
             *
             * @return result.
             * @throws if has exception throw it.
             */
            virtual folly::dynamic recreate() = 0;


            /**
             * get attachments.
             *
             * @return attachments.
             */
            virtual folly::dynamic getAttachments() = 0;

            /**
             * get attachment by key.
             *
             * @return attachment value.
             */
            virtual string getAttachment(const string &key) = 0;

            /**
             * get attachment by key with default value.
             *
             * @return attachment value.
             */
            virtual string getAttachment(const string &key, const string &defaultValue) = 0;

        };
    }
}
#endif //DUBBOC_IRESULT_H
