//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IINVOCATION_H
#define DUBBOC_IINVOCATION_H

#include <folly/dynamic.h>
#include <memory>
#include "IInvoker.h"

namespace DUBBOC {
    namespace RPC {
        using namespace std;

        class IInvocation {
        public:
            IInvocation() = default;

            virtual ~IInvocation() {}

        public:

            /**
             * get method name.
             *
             * @serial
             * @return method name.
             */
            virtual string getMethodName() = 0;

            /**
             * get parameter types.
             *
             * @serial
             * @return parameter types.
             */
            virtual folly::dynamic getParameterTypes() = 0;

            /**
             * get arguments.
             *
             * @serial
             * @return arguments.
             */
            virtual folly::dynamic getArguments() = 0;

            /**
             * get attachments.
             *
             * @serial
             * @return attachments.
             */
            virtual folly::dynamic getAttachments() = 0;

            /**
             * get attachment by key.
             *
             * @serial
             * @return attachment value.
             */
            virtual string getAttachment(const string &key) = 0;

            /**
             * get attachment by key with default value.
             *
             * @serial
             * @return attachment value.
             */
            virtual string getAttachment(const string &key, const string &defaultValue) = 0;

            /**
             * get the invoker in current context.
             *
             * @transient
             * @return invoker.
             */
            virtual shared_ptr<IInvoker> getInvoker() = 0;

        };
    }
}
#endif //DUBBOC_IINVOCATION_H
