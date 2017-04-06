//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_ABSTRACTREGISTRY_H
#define DUBBOC_ABSTRACTREGISTRY_H

#include <registry/dubboc_registry_api/IRegistry.h>
#include <memory>
#include <set>
#include <folly/futures/ManualExecutor.h>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <fstream>

namespace DUBBOC {
    namespace REGISTRY {
        using namespace std;
        using namespace DUBBOC::COMMON;

        class AbstractRegistry : public IRegistry {
        public:
            AbstractRegistry(shared_ptr<URL> url) {
                setUrl(url);
                // 启动文件保存定时器
                syncSaveFile = url->getParameter(Constants::REGISTRY_FILESAVE_SYNC_KEY, false);

                string filename = url->getParameter(Constants::FILE_KEY,
                                                    string(std::getenv("HOME")) + "/.dubboc/dubboc-registry-" +
                                                    url->getHost() + ".cache");

                if (!filename.empty()) {
                    fs.open(filename);
                    if (fs.is_open(),ios::app | ios::trunc) {

                    }
                }
            }


        public:
            shared_ptr<URL> getUrl() {
                return registryUrl;
            }

        protected:
            virtual void setUrl(shared_ptr<URL> url) {
                if (url == nullptr) {
                    throw std::invalid_argument("registry url == null");
                }
                this->registryUrl = url;
            }


        private:
            using subscribed_type=std::unordered_map<shared_ptr<URL>, shared_ptr<unordered_set<INotifyListener>>>;
            using notified_type=std::unordered_map<shared_ptr<URL>, shared_ptr<unordered_map<string, shared_ptr<list<shared_ptr<URL>>>>>>;

            // URL地址分隔符，用于文件缓存中，服务提供者URL分隔
            static char URL_SEPARATOR;
            // URL地址分隔正则表达式，用于解析文件缓存中服务提供者URL列表
            static string URL_SPLIT;
            shared_ptr<URL> registryUrl{nullptr};
            std::ofstream fs;
            folly::dynamic properties{folly::dynamic::object()};
            std::shared_ptr<folly::ManualExecutor> registryCacheExecutor{std::make_shared<folly::ManualExecutor>()};
            bool syncSaveFile;
            std::atomic_ulong lastCacheChanged;
            set<shared_ptr<URL>> registered;
            shared_ptr<subscribed_type> subscribed{make_shared<subscribed_type>()};
            shared_ptr<notified_type> notified{make_shared<notified_type>()};
        };
    }
}
#endif //DUBBOC_ABSTRACTREGISTRY_H
