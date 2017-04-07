//
// Created by 云海 on 2017/4/7.
//
#include "AbstractConfig.h"

namespace DUBBOC {
    namespace CONFIG {

        const string AbstractConfig::PATTERN_NAME = "[\\-._0-9a-zA-Z]+";
        const string AbstractConfig::PATTERN_MULTI_NAME = "[,\\-._0-9a-zA-Z]+";
        const string AbstractConfig::PATTERN_METHOD_NAME = "[a-zA-Z][0-9a-zA-Z]*";
        const string AbstractConfig::PATTERN_PATH = "[/\\-$._0-9a-zA-Z]+";
        const string AbstractConfig::PATTERN_NAME_HAS_SYMBOL = "[:*,/\\-._0-9a-zA-Z]+";
        const string AbstractConfig::PATTERN_KEY = "[*,\\-._0-9a-zA-Z]+";
        folly::dynamic AbstractConfig::legacyProperties = folly::dynamic::object
                ("dubbo.protocol.name", "dubbo.service.protocol")
                ("dubboc.protocol.host", "dubboc.service.server.host")
                ("dubboc.protocol.port", "dubboc.service.server.port")
                ("dubboc.protocol.threads", "dubboc.service.max.thread.pool.size")
                ("dubboc.consumer.timeout", "dubboc.service.invoke.timeout")
                ("dubboc.consumer.retries", "dubboc.service.max.retry.providers")
                ("dubboc.consumer.check", "dubboc.service.allow.no.provider")
                ("dubboc.service.url", "dubboc.service.address");
    }
}