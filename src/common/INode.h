//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_INODE_H
#define DUBBOC_INODE_H

#include <memory>
#include "URL.h"

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class INode {
        public:
            INode() = default;

            virtual ~INode() {}

        public:

            /**
             * get url.
             *
             * @return url.
             */
            virtual shared_ptr<URL> getUrl() = 0;

            /**
             * is available.
             *
             * @return available.
             */
            virtual bool isAvailable() = 0;

            /**
             * destroy.
             */
            virtual void destroy() = 0;

        };
    }
}
#endif //DUBBOC_INODE_H
