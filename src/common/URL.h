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

namespace DUBBOC {
    namespace COMMON {
        using namespace std;


        class URL {
        protected:
            URL() = default;

        public:
            URL(const string &protocol, const string &username, const string &password, const string &host,
                uint16_t port, const string &path, shared_ptr<unordered_map<string, string>> parameters) {
                if (username.empty()) {
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
                        rwSpinLock_.lock();
                        this->parameters_->insert(std::make_pair(pair_0, pair_1));
                        rwSpinLock_.unlock();
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
                    // NULL为结束标识
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
                        rwSpinLock_.lock();
                        this->parameters_->insert(std::make_pair(pair_0, pair_1));
                        rwSpinLock_.unlock();
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


            std::string toString() {
                return "";
            }

            std::string getParameter(const std::string &key, const std::string &defaultValue) {
                folly::RWSpinLock::ReadHolder readHolder(rwSpinLock_);
                if (parameters_) {
                    auto iter = this->parameters_->find(key);
                    if (iter != this->parameters_->end()) {
                        return iter->second;
                    }
                }
                return defaultValue;
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
            volatile unordered_map<std::string, folly::dynamic> numbers_;// 缓存参数的各种类型的值
            volatile unordered_map<std::string, shared_ptr<URL>> urls_;
            string ip_{""};
            volatile string full_{""};
            volatile string identity_{""};
            volatile string parameter_{""};
            volatile string str_{""};

        private:
            folly::RWSpinLock rwSpinLock_;

        };
    }
}
#endif //DUBBOC_URL_H
