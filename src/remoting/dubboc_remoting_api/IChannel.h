//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_ICHANNEL_H
#define DUBBOC_ICHANNEL_H

#include <folly/SocketAddress.h>
#include <folly/dynamic.h>
#include "IEndpoint.h"
#include <boost/any.hpp>

namespace DUBBOC {
    namespace REMOTING {
        class IChannel : virtual public IEndpoint {
        public:
            IChannel() = default;

            virtual ~IChannel() {}

        public:
            /**
            * get remote address.
            *
            * @return remote address.
            */
            virtual folly::SocketAddress getRemoteAddress() = 0;

            /**
             * is connected.
             *
             * @return connected
             */
            virtual bool isConnected() = 0;

            /**
             * has attribute.
             *
             * @param key key.
             * @return has or has not.
             */
            virtual bool hasAttribute(const std::string &key) = 0;

            /**
             * get attribute.
             *
             * @param key key.
             * @return value.
             */
            virtual boost::any getAttribute(const std::string &key) = 0;

            /**
             * set attribute.
             *
             * @param key key.
             * @param value value.
             *
             * 此处之所以需要boost::any，是因为value可能为一个指针类型
             */
            virtual void setAttribute(const std::string &key, const boost::any &value) = 0;

            /**
             * remove attribute.
             *
             * @param key key.
             */
            virtual void removeAttribute(const std::string &key) = 0;
        };
    }
}
#endif //DUBBOC_ICHANNEL_H
