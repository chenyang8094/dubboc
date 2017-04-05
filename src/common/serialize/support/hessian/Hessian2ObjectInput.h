//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_HESSIAN2OBJECTINPUT_H
#define DUBBOC_HESSIAN2OBJECTINPUT_H

#include <common/serialize/IObjectInput.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class Hessian2ObjectInput : public IObjectInput {
        public:
            Hessian2ObjectInput(std::istringstream &is) : is_(is) {}

            folly::dynamic readObject() override {
                return nullptr;
            }

            folly::dynamic readObject(const string &type) override {
                return nullptr;
            }

            bool readBool() override {
                return false;
            }

            char readByte() override {
                return 0;
            }

            short readShort() override {
                return 0;
            }

            int readInt() override {
                return 0;
            }

            long readLong() override {
                return 0;
            }

            float readFloat() override {
                return 0;
            }

            double readDouble() override {
                return 0;
            }

            string readUTF() override {
                return nullptr;
            }

        private:
            std::istringstream &is_;
        };
    }
}
#endif //DUBBOC_HESSIAN2OBJECTINPUT_H
