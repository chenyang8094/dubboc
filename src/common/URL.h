//
// Created by 云海 on 2017/3/26.
//

#ifndef DUBBOC_URL_H
#define DUBBOC_URL_H

#include <iostream>
#include <map>
#include <list>
#include <folly/dynamic.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class URL {
        public:
            URL() : protocol_(""),
                    username_(""),
                    password_(""),
                    host_(""),
                    port_(0),
                    path_(""),
                    parameters_{nullptr} {}

            URL(const string &protocol, const string &username, const string &password, const string &host,
                uint16_t port, const string &path, const folly::dynamic &parameters) :
                    protocol_(protocol), username_(username), password_(password), host_(host), port_(port),
                    path_(path), parameters_(parameters) {
                if (username.empty() && password.length() > 0) {
//                    throw new IllegalArgumentException("Invalid url, password without username!");
                }

                // trim the beginning "/"
//                while (!path.empty() && path.startsWith("/")) {
//                    path = path.substring(1);
//                }

            }

            URL(const string &protocol, const string &host, uint16_t port) {
                new(this) URL(protocol, "", "", host, port, "", nullptr);
            }

        public:
            std::string getProtocol() {
                return "";
            }

            std::string toString() {
                return "";
            }

            std::string getParameter(const std::string &key, const std::string &defaultValue) {
                return "";
            }

        private:
            std::string protocol_;
            std::string username_;
            std::string password_;
            std::string host_;
            uint16_t port_;
            std::string path_;
            folly::dynamic parameters_{nullptr};

            // ==== cache ====
        private:
            volatile std::map<std::string, folly::dynamic> numbers_;
            volatile std::map<std::string, URL> urls_;
            volatile std::string ip_;
            volatile std::string full_;
            volatile std::string identity_;
            volatile std::string parameter_;
            volatile std::string str_;

        };
    }
}
#endif //DUBBOC_URL_H
