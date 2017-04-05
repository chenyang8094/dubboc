//
// Created by 云海 on 2017/4/5.
//

#include "RpcContext.h"

namespace DUBBOC {
    namespace RPC {
        folly::ThreadLocal<RpcContext> RpcContext::LOCAL;
    }
}
