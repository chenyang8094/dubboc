//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_EXTENSIONLOADER_H
#define DUBBOC_EXTENSIONLOADER_H

#include <iostream>
#include <boost/any.hpp>
#include <boost/function.hpp>
//#include <container/IocContainer.h>

#include <container/IocContainer.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;
        using namespace DUBBOC::CONTAINER;

        class ExtensionLoader {
        private:
            /* 不允许用户自己创建IOC容器 */
            ExtensionLoader(void) {}

            ~ExtensionLoader(void) {}

            ExtensionLoader(const ExtensionLoader &ioc) = delete;

            const ExtensionLoader &operator=(const ExtensionLoader &ioc) = delete;

        public:

            static ExtensionLoader *getInstance(){
                static ExtensionLoader instance;
                return &instance;
            }

            template<class I, class T, typename... Ts>
            void RegisterExtension(const string &extensionName) {
                auto container = IocContainer::getInstance();
                container->RegisterType<I, T, Ts...>(extensionName);
            };

            template<class I, class T, typename... Ts>
            void RegisterExtensionAdaptive(const string &extensionName) {
                auto container = IocContainer::getInstance();
                auto extensionAdaptiveName = extensionName + "@Adaptive";
                container->RegisterType<I, T, Ts...>(extensionAdaptiveName);
            }

            template<class I, class T, typename... Ts>
            struct RegisterExtensionT {
                explicit RegisterExtensionT(const string &extensionName) {
                    auto container = IocContainer::getInstance();
                    container->RegisterType<I, T, Ts...>(extensionName);
                }
            };

            template<class I, class T, typename... Ts>
            struct RegisterExtensionAdaptiveT {
                explicit RegisterExtensionAdaptiveT(const string &extensionName) {
                    auto container = IocContainer::getInstance();
                    auto extensionAdaptiveName = extensionName + "@Adaptive";
                    container->RegisterType<I, T, Ts...>(extensionAdaptiveName);
                }
            };

            template<class I>
            std::shared_ptr <I> LoadExtension(const std::string &extensionName) {
                auto container = IocContainer::getInstance();
                return container->ResolveShared<I>(extensionName);
            }

            template<class I>
            std::shared_ptr <I> LoadExtensionAdaptive(const std::string &extensionName) {
                auto extensionAdaptiveName = extensionName + "@Adaptive";
                auto container = IocContainer::getInstance();
                return container->ResolveShared<I>(extensionAdaptiveName);
            }
        };
    }
}
#endif
