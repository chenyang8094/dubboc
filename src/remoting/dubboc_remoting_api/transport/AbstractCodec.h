//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_ABSTRACTCODEC_H
#define DUBBOC_ABSTRACTCODEC_H

#include <remoting/dubboc_remoting_api/ICodec.h>
#include <memory>
#include <common/serialize/ISerialization.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;
        using namespace COMMON;

        class AbstractCodec : public ICodec {
        public:
            AbstractCodec() = default;

            virtual ~AbstractCodec() {}

        protected:
            virtual shared_ptr<ISerialization> getSerialization(shared_ptr<IChannel> channel){

            }

            static void checkPayload(shared_ptr<IChannel> channel, long size);

            bool isClientSide(shared_ptr<IChannel> channel);

            bool isServerSide(shared_ptr<IChannel> channel) {
                return !isClientSide(channel);
            }
        };
    }
}
#endif //DUBBOC_ABSTRACTCODEC_H
