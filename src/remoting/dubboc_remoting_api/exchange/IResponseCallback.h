//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_IRESPONSECALLBACK_H
#define DUBBOC_IRESPONSECALLBACK_H

#include <exception>
#include <folly/dynamic.h>

namespace DUBBOC {
    namespace REMOTING {
        class IResponseCallback {
        public:
            virtual ~IResponseCallback() {}

        public:
            /**
               * done.
               *
               * @param response
               */
            virtual void done(const folly::dynamic &response) = 0;

            /**
             * caught exception.
             *
             * @param exception
             */
            virtual void caught(const std::exception &exception) = 0;
        };
    }
}
#endif //DUBBOC_IRESPONSECALLBACK_H
