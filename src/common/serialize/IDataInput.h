//
// Created by 云海 on 2017/4/5.
//

#ifndef DUBBOC_IDATAINPUT_H
#define DUBBOC_IDATAINPUT_H

#include <string>


/*
   enum Type {
    NULLT,
    ARRAY,
    BOOL,
    DOUBLE,
    INT64,
    OBJECT,
    STRING,
  };
*/
namespace DUBBOC {
    namespace COMMON {
        class IDataInput {
        public:
            /**
            * Read boolean.
            *
            * @return boolean.
            */
            virtual bool readBool()  = 0;

            /**
             * Read byte.
             *
             * @return byte value.
             */
            virtual char readByte() = 0;

            /**
             * Read short integer.
             *
             * @return short.
             * @throws IOException.
             */
            virtual short readShort()  = 0;

            /**
             * Read integer.
             *
             * @return integer.
             */
            virtual int readInt() = 0;

            /**
             * Read long.
             *
             * @return long.
             */
            virtual long readLong()  = 0;

            /**
             * Read float.
             *
             * @return float.
             */
            virtual float readFloat() = 0;

            /**
             * Read double.
             *
             * @return double.
             */
            virtual double readDouble() = 0;

            /**
             * Read UTF-8 string.
             *
             * @return string.
             */
            virtual std::string readUTF() = 0;

        };
    }
}
#endif //DUBBOC_IDATAINPUT_H
