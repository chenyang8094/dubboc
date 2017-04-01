//
// Created by 云海 on 2017/3/27.
//

#ifndef PROJECT_IOCCONTAINER_H
#define PROJECT_IOCCONTAINER_H

#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include <map>
#include <folly/RWSpinLock.h>
#include <folly/dynamic.h>

namespace DUBBOC {
    namespace CONTAINER {
        using namespace std;

        class IocContainer {
        private:
            /* 不允许用户自己创建IOC容器 */
            IocContainer(void) {}

            ~IocContainer(void) {}

            IocContainer(const IocContainer &ioc) = delete;

            const IocContainer &operator=(const IocContainer &ioc) = delete;

        public:
            static IocContainer *getInstance() {
                /* C++11 保证静态局部变量的初始化时安全的 */
                static IocContainer instance;
                return &instance;
            }

            template<class T>
            void RegisterType(const string &strKey) {
                typedef T *I;
                std::function<I()> function = Construct<I, T>::invoke;
                RegisterType(strKey, function);
            }

            template<class I, class T, typename... Ts>
            void RegisterType(const string &strKey) {
                std::function<I *(Ts...)> function = Construct<I *, T, Ts...>::invoke;
                RegisterType(strKey, function);
            }

            template<class I>
            I *Resolve(const string &strKey) {
                folly::RWSpinLock::ReadHolder readHolder(rw_clk_);
                if (m_creatorMap.find(strKey) == m_creatorMap.end())
                    return nullptr;

                boost::any resolver = m_creatorMap[strKey];
                std::function<I *()> function = boost::any_cast<std::function<I *() >>(resolver);

                return function();
            }

            template<class I>
            std::shared_ptr<I> ResolveShared(const string &strKey) {
                auto b = Resolve<I>(strKey);
                return std::shared_ptr<I>(b);
            }

            template<class I, typename... Ts>
            I *Resolve(const string &strKey, Ts... Args) {
                folly::RWSpinLock::ReadHolder readHolder(rw_clk_);
                if (m_creatorMap.find(strKey) == m_creatorMap.end())
                    return nullptr;

                boost::any resolver = m_creatorMap[strKey];
                std::function<I *(Ts...)> function = boost::any_cast<std::function<I *(Ts...) >>(resolver);

                return function(Args...);
            }

            template<class I, typename... Ts>
            std::shared_ptr<I> ResolveShared(const string &strKey, Ts... Args) {
                auto b = Resolve<I, Ts...>(strKey, Args...);
                return std::shared_ptr<I>(b);
            }

            bool hasType(const string &strKey) {
                folly::RWSpinLock::ReadHolder readHolder(rw_clk_);
                if (m_creatorMap.find(strKey) != m_creatorMap.end())
                    return true;
                return false;
            }

        private:

            template<typename I, typename T, typename... Ts>
            struct Construct {
                static I invoke(Ts... Args) { return I(new T(Args...)); }
            };

            void RegisterType(const string &strKey, boost::any constructor) {
                folly::RWSpinLock::WriteHolder writeHolder(rw_clk_);
                if (m_creatorMap.find(strKey) != m_creatorMap.end()) {
                    throw std::runtime_error("this key has already exist!");
                }
                m_creatorMap.insert(make_pair(strKey, constructor));
            }

        private:
            unordered_map<string, boost::any> m_creatorMap;
            folly::RWSpinLock rw_clk_;
        };
    }
}
#endif //PROJECT_IOCCONTAINER_H
