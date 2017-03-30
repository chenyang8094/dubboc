//
// Created by 云海 on 2017/3/30.
//
#include "Request.h"

namespace DUBBOC {
    namespace REMOTING {

        std::atomic_long Request::INVOKE_ID{0};

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

//        void operator=(folly::dynamic &dynamic, shared_ptr<Request> request) {
//            if (request == nullptr) {
//                return;
//            }
//            dynamic[Constants::OBJECT_MARK_KRY] = "Request";
//            dynamic["mId"] = request->getMId();
//            dynamic["mVersion"] = request->getMVersion();
//            dynamic["mEvent"] = request->isMEvent();
//            dynamic["mTwoWay"] = request->isMTwoWay();
//            dynamic["mBroken"] = request->isMBroken();
//            dynamic["mData"] = request->getMData();
//        }
//
//        void operator=(shared_ptr<Request> request, const folly::dynamic &dynamic) {
//            request = std::make_shared<Request>();
//            if (dynamic.get_ptr("mId")) {
//                request->setMId(static_cast<long>(dynamic.get_ptr("mId")->asInt()));
//            }
//            if (dynamic.get_ptr("mVersion")) {
//                request->setMVersion(dynamic.get_ptr("mVersion")->asString());
//            }
//            if (dynamic.get_ptr("mEvent")) {
//                request->setMEvent(dynamic.get_ptr("mEvent")->asBool());
//            }
//            if (dynamic.get_ptr("mTwoWay")) {
//                request->setMTwoWay(dynamic.get_ptr("mTwoWay")->asBool());
//            }
//            if (dynamic.get_ptr("mBroken")) {
//                request->setMBroken(dynamic.get_ptr("mBroken")->asBool());
//            }
//            if (dynamic.get_ptr("mData")) {
//                request->setMData(dynamic["mData"]);
//            }
//        }

    }
}