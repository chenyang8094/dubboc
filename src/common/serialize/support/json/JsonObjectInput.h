//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_JSONOBJECTINPUT_H
#define DUBBOC_JSONOBJECTINPUT_H

#include <sstream>
#include <common/serialize/IObjectInput.h>
#include <folly/dynamic.h>
#include <folly/json.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class JsonObjectInput : public IObjectInput {
        public:
            explicit JsonObjectInput(std::istringstream &is) : is_(is) {}

        public:
            folly::dynamic readObject() override {
                try {
                    return folly::parseJson(is_.str());
                } catch (const std::exception &e) {
                    throw;
                }
            }

            folly::dynamic readObject(const string &type) override {
                try {
                    auto obj = folly::parseJson(is_.str());
                    if (obj.get_ptr("@type") == nullptr || obj.get_ptr("@type")->asString() != type) {
                        throw std::invalid_argument("deserialize object type is error.");
                    }
                    return obj;
                } catch (...) {
                    throw;
                }
            }

            bool readBool() override {
                return readObject().asBool();
            }

            char readByte() override {
                return static_cast<char>(readObject().asInt());
            }

            short readShort() override {
                return static_cast<short>(readObject().asInt());
            }

            int readInt() override {
                return static_cast<int>(readObject().asInt());
            }

            long readLong() override {
                return static_cast<long>(readObject().asInt());
            }

            float readFloat() override {
                return static_cast<float>(readObject().asDouble());
            }

            double readDouble() override {
                return readObject().asDouble();
            }

            string readUTF() override {
                return readObject().asString();
            }

        private:
            std::istringstream &is_;
        };
    }
}
#endif //DUBBOC_JSONOBJECTINPUT_H
