//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_IRESPONSEFUTURE_H
#define DUBBOC_IRESPONSEFUTURE_H

#include <memory>
#include <folly/dynamic.h>
#include "IResponseCallback.h"

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class IResponseFuture {
        public:
            virtual ~IResponseFuture() {}

        public:
            /**
               * get result.
               *
               * @return result.
               */
            virtual folly::dynamic get() = 0;

            /**
             * get result with the specified timeout.
             *
             * @param timeoutInMillis timeout.
             * @return result.
             */
            virtual folly::dynamic get(uint32_t timeoutInMillis) = 0;

            /**
             * set callback.
             *
             * @param callback
             */
            virtual void setCallback(shared_ptr<IResponseCallback> callback) = 0;

            /**
             * check is done.
             *
             * @return done or not.
             */
            virtual bool isDone() = 0;

        };
    }
}
#endif //DUBBOC_IRESPONSEFUTURE_H
