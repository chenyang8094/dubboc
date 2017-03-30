//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_REQUEST_H
#define DUBBOC_REQUEST_H

#include <iostream>
#include <folly/dynamic.h>
#include <common/Constants.h>
#include <folly/json.h>

namespace DUBBOC {
    namespace REMOTING {
        using namespace DUBBOC::COMMON;
        using namespace std;

        class Request {
        public:
            Request() : mData(nullptr) {
                mId = INVOKE_ID++;
            }

            ~Request() = default;

        private:
            long mId;       // 请求ID

            std::string mVersion;         // 请求的版本号

            bool mTwoWay = true;          // 是否是twoway方式

            bool mEvent = false;          // 是否是一个event

            bool mBroken = false;         // 这是一个坏请求

            folly::dynamic mData;         // 请求体 比如dubbo协议中的RpcInvocation
        public:
            long getMId() const;

            void setMId(long mId);

            const string &getMVersion() const;

            void setMVersion(const string &mVersion);

            bool isMTwoWay() const;

            void setMTwoWay(bool mTwoWay);

            bool isMEvent() const;

            void setMEvent(bool mEvent);

            bool isMBroken() const;

            void setMBroken(bool mBroken);

            const folly::dynamic &getMData() const;

            void setMData(const folly::dynamic &mData);

            string toString() {
                std::ostringstream os;
                try {
                    os << "{"
                       << "  @type:" << "Request"
                       << "  mId:" << mId
                       << "  mVersion:" << mVersion
                       << "  mEvent:" << mEvent
                       << "  mTwoWay:" << mTwoWay
                       << "  mBroken:" << mBroken
                       << "  mData:" << folly::toJson(mData)
                       << "}";
                } catch (...) {
                    return "";
                }
                return os.str();
            }
//        public:
//            friend  void operator=(shared_ptr<Request> request, const folly::dynamic &dynamic);
//            friend  void operator=(folly::dynamic &dynamic, shared_ptr<Request> request);
        private:
            static std::atomic_long INVOKE_ID;//原子计数  用于产生invoke id
        };

    }
}
#endif //DUBBOC_REQUEST_H
