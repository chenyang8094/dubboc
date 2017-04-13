//
// Created by 云海 on 2017/4/13.
//

#ifndef DUBBOC_ITELNETHANDLER_H
#define DUBBOC_ITELNETHANDLER_H

#include <memory>

namespace DUBBOC {
    namespace REMOTING {
        class IChannel;

        //@SPI
        class ITelnetHandler {
        public:
            ITelnetHandler() = default;

            virtual ~ITelnetHandler() {}

        public:
            /**
             * telnet.
             *
             * @param channel
             * @param message
             */
            virtual std::string telnet(std::shared_ptr<IChannel> channel, const std::string &message) = 0;

        };
    }
}
#endif //DUBBOC_ITELNETHANDLER_H
