//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IDATAOUTPUT_H
#define DUBBOC_IDATAOUTPUT_H
namespace DUBBOC {
    namespace COMMON {
        class IDataOutput {
        public:
            /**
             * Write boolean.
             *
             * @param v value.
             */
            virtual void writeBool(bool v) = 0;

            /**
             * Write byte.
             *
             * @param v value.
             */
            virtual void writeByte(char v)  = 0;

            /**
             * Write short.
             *
             * @param v value.
             */
            virtual void writeShort(short v) = 0;

            /**
             * Write integer.
             *
             * @param v value.
             */
            virtual void writeInt(int v) = 0;

            /**
             * Write long.
             *
             * @param v value.
             */
            virtual void writeLong(long v) = 0;

            /**
             * Write float.
             *
             * @param v value.
             */
            virtual void writeFloat(float v) = 0;

            /**
             * Write double.
             *
             * @param v value.
             * @throws IOException
             */
            virtual void writeDouble(double v) = 0;


            /**
             * Write string.
             *
             * @param v value.
             */
            virtual void writeUTF(const string &v) = 0;

            /**
             * Write byte array.
             *
             * @param v value.
             */
//            virtual void writeBytes(byte[] v) = 0;

            /**
             * Write byte array.
             *
             * @param v value.
             * @param off offset.
             * @param len length.
             */
            virtual void writeBytes(char *v, int off, int len) = 0;

            /**
             * Flush buffer.
             *
             */
            virtual void flushBuffer() = 0;
        };
    }
}
#endif //DUBBOC_IDATAOUTPUT_H
