//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_ICONTAINER_H
#define DUBBOC_ICONTAINER_H
namespace DUBBOC {
    namespace CONTAINER {
        //@SPI("spring")
        class Container {
        public:
            Container() = default;

            virtual ~Container() {}

        public:
            /**
             * start.
             */
            virtual void start() = 0;

            /**
             * stop.
             */
            virtual void stop() = 0;
        };
    }
}

#endif //DUBBOC_ICONTAINER_H
