//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_RESPONSE_H
#define DUBBOC_RESPONSE_H

#include <folly/dynamic.h>
#include <string>
#include <folly/json.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace std;

        class Response {
        public:
            Response() : mResult(nullptr) {
            }

            Response(long id) : mResult(nullptr) {
                mId = id;
            }

            Response(long id, const string &version) : mResult(nullptr) {
                mId = id;
                mVersion = version;
            }

        public:

            static const string HEARTBEAT_EVENT;

            static const string READONLY_EVENT;
            /**
             * ok.
             */
            static const int OK = 20;

            /**
             * clien side timeout.
             */
            static const int CLIENT_TIMEOUT = 30;

            /**
             * server side timeout.
             */
            static const int SERVER_TIMEOUT = 31;

            /**
             * request format error.
             */
            static const int BAD_REQUEST = 40;

            /**
             * response format error.
             */
            static const int BAD_RESPONSE = 50;

            /**
             * service not found.
             */
            static const int SERVICE_NOT_FOUND = 60;

            /**
             * service error.
             */
            static const int SERVICE_ERROR = 70;

            /**
             * internal server error.
             */
            static const int SERVER_ERROR = 80;

            /**
             * internal client error.
             */
            static const int CLIENT_ERROR = 90;
        private:

            long mId = 0;                       // 请求id

            string mVersion;                    // 响应体版本

            int mStatus = OK;                   // 响应的状态码

            bool mEvent = false;                // 是否是一个event

            string mErrorMsg;                   // 包含的错误信息

            folly::dynamic mResult;             // 结果值（比如dubbo协议中的RpcResult，这个是和具体协议有关的,比如dubbo）
        public:
            long getMId() const;

            void setMId(long mId);

            const std::string &getMVersion() const;

            void setMVersion(const std::string &mVersion);

            int getMStatus() const;

            void setMStatus(int mStatus);

            bool isMEvent() const;

            void setMEvent(bool mEvent);

            const std::string &getMErrorMsg() const;

            void setMErrorMsg(const std::string &mErrorMsg);

            const folly::dynamic &getMResult() const;

            void setMResult(const folly::dynamic &mResult);

            string toString() {
                std::ostringstream os;
                try {
                    os << "{"
                       << "@type:" << "Response"
                       << "  mId:" << mId
                       << "  mVersion:" << mVersion
                       << "  mStatus:" << mStatus
                       << "  mEvent:" << mEvent
                       << "  mErrorMsg:" << mErrorMsg
                       << "  mResult:" << folly::toJson(mResult)
                       << "}";
                } catch (...) {
                    return "";
                }
                return os.str();
            }

        };
    }
}
#endif //DUBBOC_RESPONSE_H
