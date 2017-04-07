//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_IEXPORTERLISTENER_H
#define DUBBOC_IEXPORTERLISTENER_H

#include <memory>

namespace DUBBOC {
    namespace RPC {
        using namespace std;

        class IExporter;

        //@SPI
        class IExporterListener {
        public:
            IExporterListener() = default;

            virtual  ~IExporterListener() {}

        public:
            /**
             * The exporter exported.
             *
             * @see com.alibaba.dubbo.rpc.Protocol#export(Invoker)
             * @param exporter
             * @throws RpcException
             */
            virtual void exported(shared_ptr<IExporter> exporter) = 0;

            /**
             * The exporter unexported.
             *
             * @see com.alibaba.dubbo.rpc.Exporter#unexport()
             * @param exporter
             * @throws RpcException
             */
            virtual void unexported(shared_ptr<IExporter> exporter) = 0;
        };
    }
}
#endif //DUBBOC_IEXPORTERLISTENER_H
