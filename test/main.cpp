//
// Created by 云海 on 2017/3/26.
//
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <time.h>
#include <atomic>
#include <future>
#include <zconf.h>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include <unordered_map>

#include <folly/json.h>
#include <folly/io/async/EventBase.h>
#include <folly/io/async/EventBaseManager.h>
#include <folly/io/IOBuf.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/bootstrap/ClientBootstrap.h>
#include <wangle/channel/Pipeline.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/service/Service.h>
#include <wangle/service/ExecutorFilter.h>
#include <wangle/service/ServerDispatcher.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/codec/LengthFieldBasedFrameDecoder.h>
#include <wangle/codec/LengthFieldPrepender.h>
#include <wangle/channel/EventBaseHandler.h>
#include <wangle/concurrent/CPUThreadPoolExecutor.h>
#include <folly/dynamic.h>
#include <remoting/dubboc_remoting_api/ITransporter.h>

#include "common/ExtensionLoader.h"
#include "common/ExtensionHeader.h"

using namespace std;
using namespace DUBBOC::COMMON;
using namespace DUBBOC::REMOTING;


int main(int argc, char **argv) {

    auto extension = ExtensionLoader::getInstance()->LoadExtension<ITransporter>("transport:wangle");
    if (extension != nullptr) {
        std::cout << "found the bean!" << std::endl;
    } else {
        std::cout << "not found the bean!" << std::endl;
    }

    auto extension2 = ExtensionLoader::getInstance()->LoadExtensionAdaptive<ITransporter>("transport");
    if (extension2 != nullptr) {
        std::cout << "found the bean!" << std::endl;
    } else {
        std::cout << "not found the bean!" << std::endl;
    }

    return 0;
}