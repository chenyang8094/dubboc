//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_HESSIAN2OBJECTOUTPUT_H
#define DUBBOC_HESSIAN2OBJECTOUTPUT_H

#include <common/serialize/IObjectOutput.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class Hessian2ObjectOutput : public IObjectOutput {
        public:
            Hessian2ObjectOutput(std::ostringstream &os) : os_(os) {}

            void writeObject(const folly::dynamic &obj) override {

            }

            void writeBool(bool v) override {

            }

            void writeByte(char v) override {

            }

            void writeShort(short v) override {

            }

            void writeInt(int v) override {

            }

            void writeLong(long v) override {

            }

            void writeFloat(float v) override {

            }

            void writeDouble(double v) override {

            }

            void writeUTF(const string &v) override {

            }

            void writeBytes(char *v, int off, int len) override {

            }

            void flushBuffer() override {

            }

        private:
            std::ostringstream &os_;
        };
    }
}
#endif //DUBBOC_HESSIAN2OBJECTOUTPUT_H
