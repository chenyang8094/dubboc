//
// Created by 云海 on 2017/3/30.
//

#ifndef DUBBOC_TIMEOUTEXCEPTION_H
#define DUBBOC_TIMEOUTEXCEPTION_H

#include <stdexcept>
#include "RemotingException.h"

namespace DUBBOC {
    namespace REMOTING {
        class TimeoutException : public RemotingException {
        public:
            explicit TimeoutException(bool serverSide, shared_ptr<IChannel> channel, const std::string &message) :
                    RemotingException(channel, message) {
                phase = serverSide ? SERVER_SIDE : CLIENT_SIDE;
            }

            ~TimeoutException() {}

            bool isServerSide() {
                return phase == 1;
            }

            bool isClientSide() {
                return phase == 0;
            }

        public:
            static const int CLIENT_SIDE = 0;
            static const int SERVER_SIDE = 1;
            int phase;
        };
    }
}
#endif //DUBBOC_TIMEOUTEXCEPTION_H
