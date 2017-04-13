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

            const folly::dynamic &GetDynamic() {
                if (inner_dynamic_cache.empty()) {
                    inner_dynamic_cache["@type"] = "Request";
                    inner_dynamic_cache["mId"] = mId;
                    inner_dynamic_cache["mVersion"] = mVersion;
                    inner_dynamic_cache["mEvent"] = mEvent;
                    inner_dynamic_cache["mTwoWay"] = mTwoWay;
                    inner_dynamic_cache["mBroken"] = mBroken;
                    inner_dynamic_cache["mData"] = mData;
                }
                return inner_dynamic_cache;
            }

        private:
            folly::dynamic inner_dynamic_cache{folly::dynamic::object};
            static std::atomic_long INVOKE_ID;//原子计数  用于产生invoke id
        };

    }
}
#endif //DUBBOC_REQUEST_H
