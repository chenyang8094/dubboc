//
// Created by 云海 on 2017/3/30.
//
#include "Request.h"

namespace DUBBOC {
    namespace REMOTING {

        std::atomic_long Request::INVOKE_ID{0};
        const std::string Request::HEARTBEAT_EVENT{""};
        const std::string Request::READONLY_EVENT{"R"};

        long Request::getMId() const {
            return mId;
        }

        void Request::setMId(long mId) {
            Request::mId = mId;
        }

        const std::string &Request::getMVersion() const {
            return mVersion;
        }

        void Request::setMVersion(const std::string &mVersion) {
            Request::mVersion = mVersion;
        }

        bool Request::isMTwoWay() const {
            return mTwoWay;
        }

        void Request::setMTwoWay(bool mTwoWay) {
            Request::mTwoWay = mTwoWay;
        }

        bool Request::isMEvent() const {
            return mEvent;
        }

        void Request::setMEvent(bool mEvent) {
            Request::mEvent = mEvent;
        }

        bool Request::isMBroken() const {
            return mBroken;
        }

        void Request::setMBroken(bool mBroken) {
            Request::mBroken = mBroken;
        }

        const folly::dynamic &Request::getMData() const {
            return mData;
        }

        void Request::setMData(const folly::dynamic &mData) {
            Request::mData = std::move(mData);
        }

    }
}