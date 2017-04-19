
//
// Created by 云海 on 2017/3/30.
//
#include "Response.h"

namespace DUBBOC {
    namespace REMOTING {
        const std::string Response::HEARTBEAT_EVENT = "";
        const std::string Response::READONLY_EVENT = "R";

        long Response::getMId() const {
            return mId;
        }

        void Response::setMId(long mId) {
            this->mId = mId;
        }

        const std::string &Response::getMVersion() const {
            return mVersion;
        }

        void Response::setMVersion(const std::string &mVersion) {
            this->mVersion = mVersion;
        }

        int Response::getMStatus() const {
            return mStatus;
        }

        void Response::setMStatus(int mStatus) {
            Response::mStatus = mStatus;
        }

        bool Response::isMEvent() const {
            return mEvent;
        }

        void Response::setMEvent(const string &mEvent) {
            this->mEvent = true;
            if (mEvent.empty()) {
                this->mResult = nullptr;
            } else {
                this->mResult = mEvent;
            }
        }

        const std::string &Response::getMErrorMsg() const {
            return mErrorMsg;
        }

        void Response::setMErrorMsg(const std::string &mErrorMsg) {
            this->mErrorMsg = mErrorMsg;
        }

        const folly::dynamic &Response::getMResult() const {
            return mResult;
        }

        void Response::setMResult(const folly::dynamic &mResult) {
            this->mResult = mResult;
        }
    }
}