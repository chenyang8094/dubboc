//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IPROTOCOL_H
#define DUBBOC_IPROTOCOL_H

#include <cstdint>
#include <common/URL.h>
#include "IExporter.h"

namespace DUBBOC {
    namespace RPC {
        using namespace std;
        using namespace DUBBOC::COMMON:

        class IProtocol {
        public:
            IProtocol() = default;

            virtual ~IProtocol() {}

        public:

            /**
             * 获取缺省端口，当用户没有配置端口时使用。
             *
             * @return 缺省端口
             */
            virtual uint16_t getDefaultPort() = 0;

            /**
             * 暴露远程服务：<br>
             * 1. 协议在接收请求时，应记录请求来源方地址信息：RpcContext.getContext().setRemoteAddress();<br>
             * 2. export()必须是幂等的，也就是暴露同一个URL的Invoker两次，和暴露一次没有区别。<br>
             * 3. export()传入的Invoker由框架实现并传入，协议不需要关心。<br>
             *
             * @param invoker 服务的执行体
             * @return exporter 暴露服务的引用，用于取消暴露
             * @throws RpcException 当暴露服务出错时抛出，比如端口已占用
             */

            virtual shared_ptr<IExporter> export(shared_ptr<IInvoker> invoker)  = 0;

            /**
             * 引用远程服务：<br>
             * 1. 当用户调用refer()所返回的Invoker对象的invoke()方法时，协议需相应执行同URL远端export()传入的Invoker对象的invoke()方法。<br>
             * 2. refer()返回的Invoker由协议实现，协议通常需要在此Invoker中发送远程请求。<br>
             * 3. 当url中有设置check=false时，连接失败不能抛出异常，并内部自动恢复。<br>
             *
             * @param url 远程服务的URL地址
             * @return invoker 服务的本地代理
             * @throws RpcException 当连接服务提供方失败时抛出
             */

            virtual shared_ptr<IInvoker> refer(shared_ptr<URL> url) = 0;

            /**
             * 释放协议：<br>
             * 1. 取消该协议所有已经暴露和引用的服务。<br>
             * 2. 释放协议所占用的所有资源，比如连接和端口。<br>
             * 3. 协议在释放后，依然能暴露和引用新的服务。<br>
             */
            virtual void destroy() = 0;

        };
    }
}
#endif //DUBBOC_IPROTOCOL_H
