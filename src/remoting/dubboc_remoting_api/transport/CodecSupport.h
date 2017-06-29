//
// Created by 云海 on 2017/4/26.
//

#ifndef DUBBOC_CODECSUPPORT_H
#define DUBBOC_CODECSUPPORT_H

#include <memory>
#include <unordered_map>
#include <common/URL.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;
        using namespace COMMON;

        class CodecSupport {
        public:
            CodecSupport() ;

            virtual ~CodecSupport() = default;

        public:
            static CodecSupport *getInstance() {
                CodecSupport instance;
                return &instance;
            }

            shared_ptr<ISerialization> getSerializationById(int id) {
                auto pos = ID_SERIALIZATION_MAP.find(id);
                return pos == ID_SERIALIZATION_MAP.end() ? nullptr : pos->second;
            }

            shared_ptr<ISerialization> getSerialization(shared_ptr<URL> url) {
//                return ExtensionLoader.getExtensionLoader(Serialization.class).getExtension(
//                        url.getParameter(Constants::SERIALIZATION_KEY, Constants::DEFAULT_REMOTING_SERIALIZATION));
                return nullptr;
            }

            shared_ptr<ISerialization> getSerialization(shared_ptr<URL> url, int id) {
                auto result = getSerializationById(id);
                if (result == nullptr) {
                    result = getSerialization(url);
                }
                return result;
            }

        private:
            unordered_map<int, shared_ptr<ISerialization>> ID_SERIALIZATION_MAP;
        };

    }
}
#endif //DUBBOC_CODECSUPPORT_H
