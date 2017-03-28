//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_TRANSPORTERADAPTIVE_H
#define DUBBOC_TRANSPORTERADAPTIVE_H

#include <remoting/dubboc_remoting_api/ITransporter.h>

namespace DUBBOC {
    namespace REMOTING {


        class TransporterAdaptive : public ITransporter {

        public:
            shared_ptr<IServer> bind(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) override;

            shared_ptr<IClient> connect(shared_ptr<URL> url, shared_ptr<IChannelHandler> handler) override;


        };
    }
}
#endif //DUBBOC_TRANSPORTERADAPTIVE_H
