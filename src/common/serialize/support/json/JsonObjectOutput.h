
//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_JSONOBJECTOUTPUT_H
#define DUBBOC_JSONOBJECTOUTPUT_H

#include <common/serialize/IObjectOutput.h>
#include <folly/json.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class JsonObjectOutput : public IObjectOutput {
        public:
            explicit JsonObjectOutput(std::ostringstream &os) : os_(os) {}

        public:
            void writeObject(const folly::dynamic &obj) override {
                auto str = folly::toJson(obj);
                os_ << str;
            }

            void writeBool(bool v) override {
                writeObject(v);
            }

            void writeByte(char v) override {
                writeObject(v);
            }

            void writeShort(short v) override {
                writeObject(v);
            }

            void writeInt(int v) override {
                writeObject(v);
            }

            void writeLong(long v) override {
                writeObject(v);
            }

            void writeFloat(float v) override {
                writeObject(v);
            }

            void writeDouble(double v) override {
                writeObject(v);
            }

            void writeUTF(const string &v) override {
                writeObject(v);
            }

            void writeBytes(char *v, int off, int len) override {
                writeObject(v);
            }

            void flushBuffer() override {
                os_.flush();
            }


        private:
            std::ostringstream &os_;
        };
    }
}
#endif //DUBBOC_JSONOBJECTOUTPUT_H
