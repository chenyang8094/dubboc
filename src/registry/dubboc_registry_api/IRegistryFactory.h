//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IREGISTRYFACTORY_H
#define DUBBOC_IREGISTRYFACTORY_H

#include "IRegistry.h"

namespace DUBBOC {
    namespace REGISTRY {
        using namespace DUBBOC::COMMON;
        using namespace std;

        //@SPI("zookeeper")
        class IRegistryFactory {
        public:
            IRegistryFactory() = default;

            virtual ~IRegistryFactory() {}

        public:


            /**
             * 连接注册中心.
             *
             * 连接注册中心需处理契约：<br>
             * 1. 当设置check=false时表示不检查连接，否则在连接不上时抛出异常。<br>
             * 2. 支持URL上的username:password权限认证。<br>
             * 3. 支持backup=10.20.153.10备选注册中心集群地址。<br>
             * 4. 支持file=registry.cache本地磁盘文件缓存。<br>
             * 5. 支持timeout=1000请求超时设置。<br>
             * 6. 支持session=60000会话超时或过期设置。<br>
             *
             * @param url 注册中心地址，不允许为空
             * @return 注册中心引用，总不返回空
             */
            //@Adaptive({"protocol"})
            virtual shared_ptr<IRegistry> getRegistry(shared_ptr<URL> url) = 0;

        };
    }
}
#endif //DUBBOC_IREGISTRYFACTORY_H
