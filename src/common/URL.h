//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_URL_H
#define DUBBOC_URL_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include <list>
#include <folly/dynamic.h>
#include <folly/RWSpinLock.h>
#include <boost/algorithm/string.hpp>
#include <netdb.h>
#include <arpa/inet.h>
#include <boost/regex.hpp>
#include <common/Utils/NetUtils.h>
#include "common/Utils/URLUtils.h"
#include "Constants.h"

namespace DUBBOC {
    namespace COMMON {
        using namespace std;


        class URL : public enable_shared_from_this<URL> {
        protected:
            URL() = default;

        public:
            URL(const string &protocol, const string &username, const string &password, const string &host,
                uint16_t port, const string &path, shared_ptr<unordered_map<string, string>> parameters) {
                if (username.empty() && !password.empty()) {
                    throw std::invalid_argument("Invalid url, password without username!");
                }
                this->protocol_ = protocol;
                this->username_ = username;
                this->password_ = password;
                this->host_ = host;
                this->port_ = port;
                this->path_ = path;

                if (!path.empty() && boost::algorithm::starts_with(path, "/")) {
                    this->path_ = path.substr(1, path.length());
                }

                if (parameters == nullptr) {
                    this->parameters_ = std::make_shared<unordered_map<string, string>>();
                } else {
                    this->parameters_ = parameters;
                }
            }

            URL(const string &protocol, const string &host, uint16_t port) :
                    URL(protocol, "", "", host, port, "", nullptr) {}

            URL(const string &protocol, const string &host, uint16_t port,
                shared_ptr<unordered_map<string, string>> parameters)
                    : URL(protocol, "", "", host, port, "", parameters) {
            }

            URL(const string &protocol, const string &host, uint16_t port, const string &path)
                    : URL(protocol, "", "", host, port, path, nullptr) {
            }

            URL(const string &protocol, const string &host, uint16_t port, string path, ...)
                    : URL(protocol, "", "", host, port, path, nullptr) {
                uint8_t argc = 0;
                va_list args;
                va_start(args, path);
                va_list argsbak;
                va_copy(argsbak, args);
                char *doarg = nullptr;
                do {
                    doarg = va_arg(args, char *);
                    if (doarg != nullptr) {
                        argc++;
                    }
                } while (doarg);
                va_end(args);
                if (argc % 2 != 0) {
                    throw std::invalid_argument("pairs must be even.");
                }

                while (argc) {
                    char *pair_0 = va_arg(argsbak, char *);
                    char *pair_1 = va_arg(argsbak, char *);
                    if (this->parameters_) {
                        parameters_rwSpinLock_.lock();
                        this->parameters_->insert(std::make_pair(pair_0, pair_1));
                        parameters_rwSpinLock_.unlock();
                    }
                    argc -= 2;
                }
                va_end(argsbak);
            }

            URL(const string &protocol, const string &host, uint16_t port, const string &path,
                shared_ptr<unordered_map<string, string>> parameters)
                    : URL(protocol, "", "", host, port, path, parameters) {
            }

            URL(const string &protocol, const string &username, const string &password, const string &host,
                uint16_t port, const string &path)
                    : URL(protocol, username, password, host, port, path, nullptr) {
            }

            URL(const string &protocol, const string &username, const string &password, const string &host,
                uint16_t port, string path, ...)
                    : URL(protocol, username, password, host, port, path, nullptr) {

                uint8_t argc = 0;
                va_list args;
                va_start(args, path);
                va_list argsbak;
                va_copy(argsbak, args);
                char *doarg = nullptr;
                do {
                    doarg = va_arg(args, char *);
                    if (doarg != nullptr) {
                        argc++;
                    }
                } while (doarg);
                va_end(args);
                if (argc % 2 != 0) {
                    throw std::invalid_argument("pairs must be even.");
                }

                while (argc) {
                    char *pair_0 = va_arg(argsbak, char *);
                    char *pair_1 = va_arg(argsbak, char *);
                    if (this->parameters_) {
                        parameters_rwSpinLock_.lock();
                        this->parameters_->insert(std::make_pair(pair_0, pair_1));
                        parameters_rwSpinLock_.unlock();
                    }
                    argc -= 2;
                }
                va_end(argsbak);
            }


        public:
            std::string getProtocol() {
                return protocol_;
            }

            string getUsername() {
                return username_;
            }

            string getPassword() {
                return password_;
            }

            string getAuthority() {
                if (username_.empty() && password_.empty()) {
                    return "";
                }
                return (username_.empty() ? "" : username_) + ":" + (password_.empty() ? "" : password_);
            }

            string getHost() {
                return host_;
            }


            /**
             * 获取IP地址.
             *
             * 请注意：
             * 如果和Socket的地址对比，
             * 或用地址作为Map的Key查找，
             * 请使用IP而不是Host，
             * 否则配置域名会有问题
             *
             * @return ip
             */
            string getIp() {
                if (ip_.empty()) {
                    struct hostent *hp;
                    if ((hp = gethostbyname(host_.c_str())) == nullptr) {
                        return ip_;
                    }
                    /*如果是多个ip*/
                    ip_ = inet_ntoa(*(struct in_addr *) hp->h_addr_list[0]);
                }
                return ip_;
            }

            uint16_t getPort() {
                return port_;
            }

            uint16_t getPort(uint16_t defaultPort) {
                return port_ == 0 ? defaultPort : port_;
            }

            string getAddress() {
                return port_ == 0 ? host_ : host_ + ":" + to_string(port_);
            }

            string getBackupAddress() {
                return getBackupAddress(0);
            }

            string getBackupAddress(uint16_t defaultPort) {
                std::ostringstream os;
                os << appendDefaultPort(getAddress(), defaultPort);

                shared_ptr<list<string>> backups = getParameter(Constants::BACKUP_KEY, make_shared<list<string>>());
                if (backups != nullptr && !backups->empty()) {
                    for (auto &backup : *backups) {
                        os << ",";
                        os << appendDefaultPort(backup, defaultPort);
                    }
                }
                return os.str();
            }

            shared_ptr<list<shared_ptr<URL>>> getBackupUrls() {
                auto urls = make_shared<list<shared_ptr<URL>>>();
                urls->push_back(shared_from_this());

                shared_ptr<list<string>> backups = getParameter(Constants::BACKUP_KEY, make_shared<list<string>>());
                if (backups != nullptr && !backups->empty()) {
                    for (auto &backup : *backups) {
                        urls->push_back(this->setAddress(backup));
                    }
                }
                return urls;
            }

        private:
            string appendDefaultPort(const string &address, uint16_t defaultPort) {
                if (address.empty() && defaultPort > 0) {
                    auto i = address.find(':');
                    if (i == string::npos) {
                        return address + ":" + to_string(defaultPort);
                    } else if (stoi(address.substr(i + 1, address.length())) == 0) {
                        return address.substr(0, i + 1) + to_string(defaultPort);
                    }
                }
                return address;
            }

        public:
            string getPath() {
                return path_;
            }

            string getAbsolutePath() {
                if (!path_.empty() && !boost::algorithm::starts_with(path_, "/")) {
                    return std::string("/") + path_;
                }
                return path_;
            }


            shared_ptr<URL> setProtocol(const string &protocol) {
                return make_shared<URL>(protocol, username_, password_, host_, port_, path_, getParameters());
            }

            shared_ptr<URL> setUsername(const string &username) {
                return make_shared<URL>(protocol_, username, password_, host_, port_, path_, getParameters());
            }

            shared_ptr<URL> setPassword(const string &password) {
                return make_shared<URL>(protocol_, username_, password, host_, port_, path_, getParameters());
            }

            shared_ptr<URL> setAddress(const string &address) {
                auto i = address.find_last_of(':');
                string host;
                int port = port_;
                if (i != string::npos) {
                    host = address.substr(0, i);
                    port = std::stoi(address.substr(i + 1, address.length()));
                } else {
                    host = address;
                }
                return make_shared<URL>(protocol_, username_, password_, host, port, path_, getParameters());
            }

            shared_ptr<URL> setHost(const string &host) {
                return make_shared<URL>(protocol_, username_, password_, host, port_, path_, getParameters());
            }

            shared_ptr<URL> setPort(uint16_t port) {
                return make_shared<URL>(protocol_, username_, password_, host_, port, path_, getParameters());
            }

            shared_ptr<URL> setPath(const string &path) {
                return make_shared<URL>(protocol_, username_, password_, host_, port_, path, getParameters());
            }

            shared_ptr<unordered_map<string, string>> getParameters() {
                return parameters_;
            }

            string getParameterAndDecoded(const string &key) {
                return getParameterAndDecoded(key, "");
            }

            string getParameterAndDecoded(const string &key, const string &defaultValue) {
                return decode(getParameter(key, defaultValue));
            }

            std::string toString() {
                if (!str_.empty()) {
                    return str_;
                }
                return str_ = buildString(false, true, false, false, nullptr);
            }

            std::string toFullString() {
                if (!full_.empty()) {
                    return full_;
                }
                return full_ = buildString(true, true, false, false, nullptr);
            }


            std::string getParameter(const std::string &key) {
                folly::RWSpinLock::ReadHolder readHolder(parameters_rwSpinLock_);
                string value{""};
                if (parameters_) {
                    auto iter = this->parameters_->find(key);
                    if (iter != this->parameters_->end()) {
                        value = iter->second;
                    } else {
                        auto iter = this->parameters_->find(Constants::DEFAULT_KEY_PREFIX + key);
                        if (iter != this->parameters_->end()) {
                            value = iter->second;
                        }
                    }
                }
                return value;
            }

            std::string getParameter(const std::string &key, const std::string &defaultValue) {
                folly::RWSpinLock::ReadHolder readHolder(parameters_rwSpinLock_);
                if (parameters_) {
                    auto iter = this->parameters_->find(key);
                    if (iter != this->parameters_->end()) {
                        return iter->second;
                    }
                }
                return defaultValue;
            }

            shared_ptr<list<string>> getParameter(const string &key, shared_ptr<list<string>> defaultValue) {
                string value = getParameter(key);
                if (value.empty()) {
                    return defaultValue;
                }
                auto res = make_shared<list<string>>();
                boost::regex e(Constants::COMMA_SPLIT_PATTERN, boost::regbase::normal | boost::regbase::icase);
                boost::regex_split(std::back_inserter(*res), value, e);
                return res;
            }

        private :
            shared_ptr<unordered_map<string, folly::dynamic>> getNumbers() {
                if (numbers_ == nullptr) { // 允许并发重复创建
                    numbers_ = make_shared<unordered_map<std::string, folly::dynamic>>();
                }
                return numbers_;
            }

            shared_ptr<unordered_map<string, shared_ptr<URL>>> getUrls() {
                if (urls_ == nullptr) { // 允许并发重复创建
                    urls_ = make_shared<unordered_map<std::string, shared_ptr<URL>>>();
                }
                return urls_;
            }

        public:
            shared_ptr<URL> getUrlParameter(const string &key) {
                folly::RWSpinLock::ReadHolder readHolder(urls_rwSpinLock_);
                urls_rwSpinLock_.lock_shared();
                auto iter = getUrls()->find(key);
                if (iter != getUrls()->end()) {
                    urls_rwSpinLock_.unlock_shared();
                    return iter->second;
                }
                urls_rwSpinLock_.unlock_shared();

                string value = getParameterAndDecoded(key);
                if (value.empty()) {
                    return nullptr;
                }
                auto u = URL::valueOf(value);
                urls_rwSpinLock_.lock();
                getUrls()->insert(make_pair(key, u));
                urls_rwSpinLock_.unlock();
                return u;
            }

            double getParameter(const string &key, double defaultValue) {
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(key);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return iter->second.asDouble();
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getParameter(key);
                if (value.empty()) {
                    return defaultValue;
                }
                double d = stod(value);
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(key, d));
                numbers_rwSpinLock_.unlock();
                return d;
            }

            float getParameter(const string &key, float defaultValue) {
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(key);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<float>(iter->second.asDouble());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getParameter(key);
                if (value.empty()) {
                    return defaultValue;
                }
                float f = stof(value);
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(key, f));
                numbers_rwSpinLock_.unlock();
                return f;
            }

            long getParameter(const string &key, long defaultValue) {
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(key);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<long>(iter->second.asInt());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getParameter(key);
                if (value.empty()) {
                    return defaultValue;
                }
                long l = stol(value);
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(key, l));
                numbers_rwSpinLock_.unlock();
                return l;
            }

            int getParameter(const string &key, int defaultValue) {
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(key);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<int>(iter->second.asInt());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getParameter(key);
                if (value.empty()) {
                    return defaultValue;
                }
                int i = stoi(value);
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(key, i));
                numbers_rwSpinLock_.unlock();
                return i;
            }

            short getParameter(const string &key, short defaultValue) {
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(key);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<short>(iter->second.asInt());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getParameter(key);
                if (value.empty()) {
                    return defaultValue;
                }
                short s = static_cast<short>(stoi(value));
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(key, s));
                numbers_rwSpinLock_.unlock();
                return s;
            }

            unsigned char getParameter(const string &key, unsigned char defaultValue) {
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(key);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<unsigned char>(iter->second.asInt());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getParameter(key);
                if (value.empty()) {
                    return defaultValue;
                }
                unsigned char c = static_cast<unsigned char>(stoi(value));
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(key, c));
                numbers_rwSpinLock_.unlock();
                return c;
            }

            float getPositiveParameter(const string &key, float defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                float value = getParameter(key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            double getPositiveParameter(const string &key, double defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                double value = getParameter(key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }


            long getPositiveParameter(const string &key, long defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                long value = getParameter(key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            int getPositiveParameter(const string &key, int defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                int value = getParameter(key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            short getPositiveParameter(const string &key, short defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                short value = getParameter(key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            unsigned char getPositiveParameter(const string &key, unsigned char defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                unsigned char value = getParameter(key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            char getPositiveParameter(const string &key, char defaultValue) {
                string value = getParameter(key);
                if (value.empty()) {
                    return defaultValue;
                }
                return value.at(0);
            }

            bool getParameter(const string &key, bool defaultValue) {
                string value = getParameter(key);
                if (value.empty()) {
                    return defaultValue;
                }
                if (value == "true") {
                    return true;
                } else if (value == "false") {
                    return false;
                } else {
                    return defaultValue;
                }
            }

            bool hasParameter(const string &key) {
                string value = getParameter(key);
                return !value.empty();
            }

            string getMethodParameterAndDecoded(const string &method, const string &key) {
                return URL::decode(getMethodParameter(method, key));
            }

            string getMethodParameterAndDecoded(const string &method, const string &key, const string &defaultValue) {
                return URL::decode(getMethodParameter(method, key, defaultValue));
            }


            string getMethodParameter(const string &method, const string &key) {
                folly::RWSpinLock::ReadHolder readHolder(parameters_rwSpinLock_);
                auto iter = parameters_->find(method + "." + key);
                if (iter == parameters_->end()) {
                    return getParameter(key);
                }
                return iter->second;
            }

            string getMethodParameter(const string &method, const string &key, const string &defaultValue) {
                string value = getMethodParameter(method, key);
                if (value.empty()) {
                    return defaultValue;
                }
                return value;
            }

            double getMethodParameter(const string &method, const string &key, double defaultValue) {
                string methodKey = method + "." + key;
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(methodKey);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return iter->second.asDouble();
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getMethodParameter(method, key);
                if (value.empty()) {
                    return defaultValue;
                }
                double d = stod(value);
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(methodKey, d));
                numbers_rwSpinLock_.unlock();
                return d;
            }

            float getMethodParameter(const string &method, const string &key, float defaultValue) {
                string methodKey = method + "." + key;
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(methodKey);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<float>(iter->second.asDouble());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getMethodParameter(method, key);
                if (value.empty()) {
                    return defaultValue;
                }
                float f = stof(value);
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(methodKey, f));
                numbers_rwSpinLock_.unlock();
                return f;
            }

            long getMethodParameter(const string &method, const string &key, long defaultValue) {
                string methodKey = method + "." + key;
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(methodKey);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<long>(iter->second.asInt());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getMethodParameter(method, key);
                if (value.empty()) {
                    return defaultValue;
                }
                long l = stol(value);
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(methodKey, l));
                numbers_rwSpinLock_.unlock();
                return l;
            }

            int getMethodParameter(const string &method, const string &key, int defaultValue) {
                string methodKey = method + "." + key;
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(methodKey);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<int>(iter->second.asInt());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getMethodParameter(method, key);
                if (value.empty()) {
                    return defaultValue;
                }
                int i = stoi(value);
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(methodKey, i));
                numbers_rwSpinLock_.unlock();
                return i;
            }

            short getMethodParameter(const string &method, const string &key, short defaultValue) {
                string methodKey = method + "." + key;
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(methodKey);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<short>(iter->second.asInt());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getMethodParameter(method, key);
                if (value.empty()) {
                    return defaultValue;
                }
                short s = static_cast<short>(stoi(value));
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(methodKey, s));
                numbers_rwSpinLock_.unlock();
                return s;
            }

            unsigned char getMethodParameter(const string &method, const string &key, unsigned char defaultValue) {
                string methodKey = method + "." + key;
                numbers_rwSpinLock_.lock_shared();
                auto iter = getNumbers()->find(methodKey);
                if (iter != getNumbers()->end()) {
                    numbers_rwSpinLock_.unlock_shared();
                    return static_cast<unsigned char>(iter->second.asInt());
                }
                numbers_rwSpinLock_.unlock_shared();

                string value = getMethodParameter(method, key);
                if (value.empty()) {
                    return defaultValue;
                }
                unsigned char c = static_cast<unsigned char>(stoi(value));
                numbers_rwSpinLock_.lock();
                getNumbers()->insert(make_pair(methodKey, c));
                numbers_rwSpinLock_.unlock();
                return c;
            }

            double getMethodPositiveParameter(const string &method, const string &key, double defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                double value = getMethodParameter(method, key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }


            float getMethodPositiveParameter(const string &method, const string &key, float defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                float value = getMethodParameter(method, key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            long getMethodPositiveParameter(const string &method, const string &key, long defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                long value = getMethodParameter(method, key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            int getMethodPositiveParameter(const string &method, const string &key, int defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                int value = getMethodParameter(method, key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            short getMethodPositiveParameter(const string &method, const string &key, short defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                short value = getMethodParameter(method, key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            unsigned char
            getMethodPositiveParameter(const string &method, const string &key, unsigned char defaultValue) {
                if (defaultValue <= 0) {
                    throw std::invalid_argument("defaultValue <= 0");
                }
                unsigned char value = getMethodParameter(method, key, defaultValue);
                if (value <= 0) {
                    return defaultValue;
                }
                return value;
            }

            char getMethodParameter(const string &method, const string &key, char defaultValue) {
                string value = getMethodParameter(method, key);
                if (value.empty()) {
                    return defaultValue;
                }
                return value.at(0);
            }

            bool getMethodParameter(const string &method, const string &key, bool defaultValue) {
                string value = getMethodParameter(method, key);
                if (value.empty()) {
                    return defaultValue;
                }
                if (value == "true") {
                    return true;
                } else if (value == "false") {
                    return false;
                } else {
                    return defaultValue;
                }
            }

            bool hasMethodParameter(const string &method, const string &key) {
                folly::RWSpinLock::ReadHolder readHolder(parameters_rwSpinLock_);
                if (method.empty()) {
                    string suffix = std::string(".") + key;
                    for (auto &it : *parameters_) {
                        if (boost::algorithm::ends_with(it.first, suffix)) {
                            return true;
                        }
                    }
                    return false;
                }
                if (key.empty()) {
                    string prefix = method + ".";
                    for (auto &it : *parameters_) {
                        if (boost::algorithm::starts_with(it.first, prefix)) {
                            return true;
                        }
                    }
                    return false;
                }
                string value = getMethodParameter(method, key);
                return !value.empty();
            }

            bool isLocalHost() {
                return NetUtils::isLocalHost(host_) || getParameter(Constants::LOCALHOST_KEY, false);
            }

            bool isAnyHost() {
                return Constants::ANYHOST_VALUE == host_ || getParameter(Constants::ANYHOST_KEY, false);
            }

            shared_ptr<URL> addParameter(const string &key, const string &value) {
                if (key.empty() || value.empty()) {
                    return shared_from_this();
                }
                folly::RWSpinLock::ReadHolder readHolder(parameters_rwSpinLock_);

                // 如果没有修改，直接返回。
                auto iter = getParameters()->find(key);
                if (iter != getParameters()->end()) {
                    if (value == iter->second) {
                        return shared_from_this();
                    }
                }
                auto map = make_shared<unordered_map<string, string>>(*parameters_);

                (*map)[key] = value;
                return make_shared<URL>(protocol_, username_, password_, host_, port_, path_, map);
            }


            shared_ptr<URL> addParameterAndEncoded(const string &key, const string &value) {
                if (value.empty()) {
                    return shared_from_this();
                }
                return addParameter(key, encode(value));
            }

            shared_ptr<URL> addParameter(const string &key, bool value) {
                return addParameter(key, to_string(value));
            }

            shared_ptr<URL> addParameter(const string &key, char value) {
                return addParameter(key, to_string(value));
            }

            shared_ptr<URL> addParameter(const string &key, unsigned char value) {
                return addParameter(key, to_string(value));
            }

            shared_ptr<URL> addParameter(const string &key, short value) {
                return addParameter(key, to_string(value));
            }

            shared_ptr<URL> addParameter(const string &key, int value) {
                return addParameter(key, to_string(value));
            }

            shared_ptr<URL> addParameter(const string &key, long value) {
                return addParameter(key, to_string(value));
            }

            shared_ptr<URL> addParameter(const string &key, float value) {
                return addParameter(key, to_string(value));
            }

            shared_ptr<URL> addParameter(const string &key, double value) {
                return addParameter(key, to_string(value));
            }

            shared_ptr<URL> addParameterIfAbsent(const string &key, const string &value) {
                if (key.empty() || value.empty()) {
                    return shared_from_this();
                }
                if (hasParameter(key)) {
                    return shared_from_this();
                }
                auto map = make_shared<unordered_map<string, string>>(*parameters_);
                map->insert(make_pair(key, value));
                return make_shared<URL>(protocol_, username_, password_, host_, port_, path_, map);
            }

            /**
             * Add parameters to a new url.
             *
             * @param parameters
             * @return A new URL
             */
            shared_ptr<URL> addParameters(shared_ptr<unordered_map<string, string>> parameters) {
                if (parameters == nullptr || parameters->empty()) {
                    return shared_from_this();
                }

                bool hasAndEqual = true;

                folly::RWSpinLock::ReadHolder readHolder(parameters_rwSpinLock_);
                for (auto &it : *parameters) {
                    auto iter = getParameters()->find(it.first);
                    if (iter == getParameters()->end() || it.second != iter->second) {
                        hasAndEqual = false;
                        break;
                    }
                }

                // 如果没有修改，直接返回。
                if (hasAndEqual) return shared_from_this();

                auto map = make_shared<unordered_map<string, string>>(*parameters_);
                for (auto &it : *parameters) {
                    (*map)[it.first] = it.second;
                }
                return make_shared<URL>(protocol_, username_, password_, host_, port_, path_, map);
            }

            shared_ptr<URL> addParametersIfAbsent(shared_ptr<unordered_map<string, string>> parameters) {
                if (parameters == nullptr || parameters->empty()) {
                    return shared_from_this();
                }

                auto map = make_shared<unordered_map<string, string>>(*parameters_);
                for (auto &it : *parameters) {
                    map->insert(make_pair(it.first, it.second));
                }
                return make_shared<URL>(protocol_, username_, password_, host_, port_, path_, map);
            }

            shared_ptr<URL> addParameters(const char *p1,const char * p2, ...) {
                if (p1 == nullptr || p2 == nullptr) {
                    return shared_from_this();
                }
                uint8_t argc = 0;
                va_list args;
                va_start(args, p2);
                va_list argsbak;
                va_copy(argsbak, args);
                char *doarg = nullptr;
                do {
                    doarg = va_arg(args, char *);
                    if (doarg != nullptr) {
                        argc++;
                    }
                } while (doarg);
                va_end(args);
                if (argc % 2 != 0) {
                    throw std::invalid_argument("Map pairs can not be odd number.");
                }

                auto map = make_shared<unordered_map<string, string>>();
                if(this->parameters_){
                    map->insert(make_pair(p1,p2));
                }

                while (argc) {
                    char *pair_0 = va_arg(argsbak, char *);
                    char *pair_1 = va_arg(argsbak, char *);
                    if (this->parameters_) {
                        map->insert(std::make_pair(pair_0, pair_1));
                    }
                    argc -= 2;
                }
                va_end(argsbak);
                return addParameters(map);
            }

            shared_ptr<URL> removeParameters(const list<string> &keys) {
                if (keys.empty()) {
                    return shared_from_this();
                }

                auto map = make_shared<unordered_map<string, string>>(*getParameters());

                for (auto &it: keys) {
                    map->erase(it);
                }

                if (map->size() == getParameters()->size()) {
                    return shared_from_this();
                }
                return make_shared<URL>(protocol_, username_, password_, host_, port_, path_, map);
            }

            shared_ptr<URL> removeParameters(const char *p1, ...) {
                if (p1 == nullptr) {
                    return shared_from_this();
                }

                auto map = make_shared<unordered_map<string, string>>(*getParameters());

                map->erase(p1);

                va_list args;
                va_start(args, p1);
                char *doarg = nullptr;
                do {
                    doarg = va_arg(args, char *);
                    if (doarg) {
                        map->erase(doarg);
                    }
                } while (doarg);
                va_end(args);

                if (map->size() == getParameters()->size()) {
                    return shared_from_this();
                }
                return make_shared<URL>(protocol_, username_, password_, host_, port_, path_, map);
            }

            shared_ptr<URL> removeParameter(const string &key) {
                if (key.empty()) {
                    return shared_from_this();
                }
                return removeParameters(key.c_str(), nullptr);
            }

            shared_ptr<URL> clearParameters() {
                return make_shared<URL>(protocol_, username_, password_, host_, port_, path_,
                                        make_shared<unordered_map<string, string>>());
            }

            string getRawParameter(const string &key) {
                if (key == "protocol")
                    return protocol_;
                if (key == "username")
                    return username_;
                if (key == "password")
                    return password_;
                if (key == "host")
                    return host_;
                if (key == "port")
                    return to_string(port_);
                if (key == "path")
                    return path_;
                return getParameter(key);
            }

            shared_ptr<unordered_map<string, string>> toMap() {
                auto map = make_shared<unordered_map<string, string>>();
                if (!protocol_.empty())
                    map->insert(make_pair("protocol", protocol_));
                if (!username_.empty())
                    map->insert(make_pair("username", username_));
                if (!password_.empty())
                    map->insert(make_pair("password", password_));
                if (!host_.empty())
                    map->insert(make_pair("host", host_));
                if (port_ > 0)
                    map->insert(make_pair("port", to_string(port_)));
                if (!path_.empty())
                    map->insert(make_pair("path", path_));
                return map;
            }

            static shared_ptr<URL> valueOf(string url) {
                string protocol = "";
                string username = "";
                string password = "";
                string host = "";
                uint16_t port = 0;
                string path = "";
                shared_ptr<unordered_map<string, string>> parameters = nullptr;

                auto i = url.find("?");
                if (i != string::npos) {
                    list<string> parts;
                    boost::regex e(string("\\&"), boost::regbase::normal | boost::regbase::icase);
                    string value = url.substr(i + 1, url.length());
                    boost::regex_split(std::back_inserter(parts), value, e);
                    parameters = make_shared<unordered_map<string, string>>();
                    for (auto &it : parts) {
                        it = boost::algorithm::trim_copy(it);
                        if (!it.empty()) {
                            auto j = it.find('=');
                            if (j != string::npos) {
                                parameters->insert(make_pair(it.substr(0, j), it.substr(j + 1, it.length())));
                            } else {
                                parameters->insert(make_pair(it, it));
                            }
                        }
                    }
                    url = url.substr(0, i);
                }

                i = url.find("://");
                if (i != string::npos) {
                    if (i == 0) {
                        throw std::invalid_argument(string("url missing protocol: \"") + url + "\"");
                    }
                    protocol = url.substr(0, i);
                    url = url.substr(i + 3, url.length());
                } else {
                    // case: file:/path/to/file.txt
                    i = url.find(":/");
                    if (i != string::npos) {
                        if (i == 0) {
                            throw std::invalid_argument(string("url missing protocol: \"") + url + "\"");
                        }
                        protocol = url.substr(0, i);
                        url = url.substr(i + 1, url.length());
                    }
                }

                i = url.find("/");
                if (i != string::npos) {
                    path = url.substr(i + 1, url.length());
                    url = url.substr(0, i);
                }

                i = url.find("@");
                if (i != string::npos) {
                    username = url.substr(0, i);
                    auto j = username.find(":");
                    if (j != string::npos) {
                        password = username.substr(j + 1, username.length());
                        username = username.substr(0, j);
                    }
                    url = url.substr(i + 1);
                }

                i = url.find(":");
                if (i != string::npos && i > 0 && i < url.length() - 1) {
                    port = static_cast<uint16_t>(stoi(url.substr(i + 1)));
                    url = url.substr(0, i);
                }
                if (url.length() > 0) host = url;
                return make_shared<URL>(protocol, username, password, host, port, path, parameters);
            }

            static string encode(const string &value) {
                if (value.empty()) {
                    return "";
                }
                return Base64::urlEncode(folly::ByteRange((const unsigned char *) value.c_str(), value.length()));
            }

            static string decode(const string &value) {
                if (value.empty()) {
                    return "";
                }
                return Base64::urlDecode(value);
            }

            string getServiceInterface() {
                return getParameter(Constants::INTERFACE_KEY, path_);
            }

            shared_ptr<URL> setServiceInterface(const string &service) {
                return addParameter(Constants::INTERFACE_KEY, service);
            }

            string getServiceKey() {
                string inf = getServiceInterface();
                if (inf.empty()) return "";
                std::ostringstream os;

                string group = getParameter(Constants::GROUP_KEY);
                if (!group.empty()) {
                    os << group << "/";
                }
                os << inf;
                string version = getParameter(Constants::VERSION_KEY);
                if (!version.empty()) {
                    os << ":" << version;
                }
                return os.str();
            }

            void buildParameters(std::ostringstream &os, bool concat, const list<string> &params) {
                if (getParameters() != nullptr && getParameters()->size() > 0) {
                    bool first = true;
                    for (auto &it : *getParameters()) {
                        if (!it.first.empty() &&
                            (params.empty() || std::find(params.begin(), params.end(), it.first) != params.end())) {
                            if (first) {
                                if (concat) {
                                    os << "?";
                                }
                                first = false;
                            } else {
                                os << "&";
                            }
                            os << it.first;
                            os << "=";
                            os << (it.second.empty() ? "" : boost::algorithm::trim_copy(it.second));
                        }
                    }
                }
            }

            string buildString(bool appendUser, bool appendParameter, bool useIP, bool useService, ...) {
                std::ostringstream os;

                if (!protocol_.empty()) {
                    os << protocol_ << "://";
                }
                if (appendUser && !username_.empty()) {
                    os << username_;
                    if (!password_.empty()) {
                        os << ":";
                        os << password_;
                    }
                    os << "@";
                }
                string host = "";
                if (useIP) {
                    host = getIp();
                } else {
                    host = getHost();
                }
                if (!host.empty()) {
                    os << host;
                    if (port_ > 0) {
                        os << ":";
                        os << port_;
                    }
                }
                string path = "";
                if (useService) {
                    path = getServiceKey();
                } else {
                    path = getPath();
                }
                if (!path.empty()) {
                    os << "/";
                    os << path_;
                }
                if (appendParameter) {
                    list<string> params;
                    va_list args;
                    va_start(args, useService);
                    char *arg = nullptr;
                    do {
                        arg = va_arg(args, char *);
                        if (arg) {
                            params.push_back(arg);
                        }
                    } while (arg);
                    va_end(args);
                    buildParameters(os, true, params);
                }
                return os.str();
            }

            folly::SocketAddress toInetSocketAddress() {
                return folly::SocketAddress(host_, port_);
            }

            string toServiceString() {
                return buildString(true, false, true, true);
            }


            bool operator==(shared_ptr<URL> url) {
                if (url == shared_from_this()) {
                    return true;
                }

                if (url == nullptr) {
                    return false;
                }

                if (host_ != url->host_) {
                    return false;
                }

                if (parameters_ == nullptr) {
                    if (url->parameters_ != nullptr) {
                        return false;
                    }
                } else {
                    if (url->parameters_ == nullptr) {
                        return false;
                    } else if (*parameters_ != *(url->parameters_)) {
                        return false;
                    }
                }

                if (username_ != url->username_) {
                    return false;
                }

                if (protocol_ != url->protocol_) {
                    return false;
                }

                if (password_ != url->password_) {
                    return false;
                }

                if (port_ != url->port_) {
                    return false;
                }

                return path_ == url->path_;
            }

        private:
            string protocol_{""};
            string username_{""};
            string password_{""};
            string host_{""};
            uint16_t port_{0};
            string path_{""};
            shared_ptr<unordered_map<string, string>> parameters_{nullptr};

            // ==== cache ====
        private:
            shared_ptr<unordered_map<string, folly::dynamic>> numbers_{nullptr};// 缓存参数的各种类型的值
            shared_ptr<unordered_map<string, shared_ptr<URL>>> urls_{nullptr};
            string ip_{""};
            string full_{""};
            string identity_{""};
            string parameter_{""};
            string str_{""};

        private:
            folly::RWSpinLock parameters_rwSpinLock_;
            folly::RWSpinLock numbers_rwSpinLock_;
            folly::RWSpinLock urls_rwSpinLock_;
        };
    }
}
#endif //DUBBOC_URL_H
