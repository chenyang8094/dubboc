//
// Created by 云海 on 2017/3/29.
//

#ifndef DUBBOC_CONFIGUTILS_H
#define DUBBOC_CONFIGUTILS_H

#include <iostream>
#include <folly/dynamic.h>
#include <folly/json.h>
#include <fstream>
#include <folly/RWSpinLock.h>
#include "boost/algorithm/string.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/format.hpp"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/xml_parser.hpp"
#include "glog/logging.h"
#include "SystemUtils.h"
#include <common/Constants.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        /**
         * 配置文件必须是json各式
         * */
        class ConfigUtils {
        public:

            static folly::dynamic getProperties() {
                folly::RWSpinLock::WriteHolder writeHolder(rwSpinLock);
                if (PROPERTIES.empty()) {
                    auto path = std::getenv(Constants::DUBBOC_PROPERTIES_KEY.c_str());
                    if (path) {
                        PROPERTIES = loadProperties(string(path), false);
                    } else {
                        PROPERTIES = loadProperties(Constants::DEFAULT_DUBBOC_PROPERTIES, false);
                    }
                }
                return PROPERTIES;
            }

            static void addProperties(const folly::dynamic &properties) {
                if (properties.empty()) {
                    return;
                }
                folly::RWSpinLock::WriteHolder writeHolder(rwSpinLock);
                folly::dynamic::merge(PROPERTIES, properties);// override
            }

            static void setProperties(const folly::dynamic &properties) {
                folly::RWSpinLock::WriteHolder writeHolder(rwSpinLock);
                if (!properties.empty()) {
                    PROPERTIES = properties;
                }
            }

            static string getProperty(const string &key) {
                return getProperty(key, "");
            }

            static string getProperty(const string &key, const string &defaultValue) {
                folly::RWSpinLock::ReadHolder readHolder(rwSpinLock);
                auto test = PROPERTIES.get_ptr(key);
                if (test) {
                    return test->asString();
                } else {
                    return defaultValue;
                }
            }

            static folly::dynamic loadProperties(string fileName, bool optional) {
                folly::dynamic properties = folly::dynamic::object();
                string exe_path = SystemUtils::crossPlatformGetExePath();

                if (!boost::algorithm::starts_with(fileName, "/")) {
                    fileName = exe_path + "/" + fileName;
                }

                boost::filesystem::ifstream ifs;
                try {
                    boost::filesystem::path path(fileName);
                    ifs.open(path);
                    if (ifs.is_open()) {
                        stringstream content;
                        content << ifs.rdbuf();
                        properties = folly::parseJson(content.str());
                    }
                    ifs.close();
                } catch (const std::exception &e) {
                    if (ifs.is_open()) {
                        ifs.close();
                    }
                    LOG(WARNING) << "Failed to load " << fileName << " file from " << fileName
                                 << "(ingore this file): " << e.what();
                }
                return properties;
            }

        private:
            static folly::dynamic PROPERTIES;
            static folly::RWSpinLock rwSpinLock;
        };
    }
}
#endif //DUBBOC_CONFIGUTILS_H
