//
// Created by 云海 on 2017/4/7.
//

#ifndef DUBBOC_CONSUMERPROXY_H
#define DUBBOC_CONSUMERPROXY_H

#include <rpc/dubboc_rpc_api/service/IGenericService.h>
#include <rpc/dubboc_rpc_api/service/IEchoService.h>
#include <memory>


namespace DUBBOC {
    namespace RPC {
        using namespace std;

        class IInvoker;

        class ConsumerProxy : public IGenericService{
        public:
            explicit ConsumerProxy(shared_ptr<IInvoker> invoker) {
                this->invoker = invoker;
            }

            ~ConsumerProxy() = default;

        public:
            folly::dynamic
            $invoke(const string &method, const folly::dynamic &parameterTypes, const folly::dynamic &args) override;

        private:
            shared_ptr<IInvoker> invoker{nullptr};
        };
    }
}
#endif //DUBBOC_CONSUMERPROXY_H
