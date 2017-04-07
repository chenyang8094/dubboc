//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IECHOSERVICE_H
#define DUBBOC_IECHOSERVICE_H

#include <string>
#include <folly/dynamic.h>

namespace DUBBOC {
    namespace RPC {
        using namespace std;

        class IEchoService {
        public:
            IEchoService() = default;

            virtual ~IEchoService() {}


        public:
            virtual folly::dynamic $echo(const folly::dynamic &message) = 0;
        };

    }
}
#endif //DUBBOC_IECHOSERVICE_H
