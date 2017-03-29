//
// Created by 云海 on 2017/3/28.
//

#ifndef DUBBOC_NETUTILS_H
#define DUBBOC_NETUTILS_H

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#endif

#ifdef __APPLE__

#include <sys/event.h>
#include <sys/time.h>
#include <sys/syscall.h>	// syscall(SYS_gettid)

#else
#include <sys/epoll.h>
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>		// define int8_t ...
#include <signal.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <iostream>
#include <string>
#include <folly/Random.h>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <folly/SocketAddress.h>

namespace DUBBOC {
    namespace COMMON {
        using namespace std;

        class NetUtils {
        public:
            static const string LOCALHOST;

            static const string ANYHOST;

            static const uint16_t RND_PORT_START = 30000;

            static const uint16_t RND_PORT_RANGE = 10000;

            static uint16_t getRandomPort() {
                return RND_PORT_START + static_cast<uint16_t >(folly::Random::rand32(RND_PORT_RANGE));
            }

            static bool isInvalidPort(uint16_t port) {
                return port > MIN_PORT && port <= MAX_PORT;
            }

            static bool isValidAddress(const string &address) {
                boost::regex e(ADDRESS_PATTERN, boost::regbase::normal | boost::regbase::icase);
                return boost::regex_match(address, e);
            }

            static bool isLocalHost(const string &host) {
                if (host.empty()) {
                    return false;
                }
                boost::regex e(LOCAL_IP_PATTERN, boost::regbase::normal | boost::regbase::icase);
                return boost::regex_match(host, e) || boost::algorithm::iequals(host,"localhost");
            }

            static bool isAnyHost(const string &host) {
                return host == "0.0.0.0";
            }

            static bool isInvalidLocalHost(const string &host) {
                if (host.empty()) {
                    return true;
                }

                if (boost::algorithm::iequals(host, "localhost")) {
                    return true;
                }

                if (host == "0.0.0.0") {
                    return true;
                }

                boost::regex e(LOCAL_IP_PATTERN, boost::regbase::normal | boost::regbase::icase);
                return boost::regex_match(host, e);
            }

            static bool isValidLocalHost(const string &host) {
                return !isInvalidLocalHost(host);
            }

            static folly::SocketAddress getLocalSocketAddress(const string &host, uint16_t port) {
                folly::SocketAddress socketAddress;
                if (isInvalidLocalHost(host)) {
                    socketAddress.setFromLocalPort(port);
                } else {
                    socketAddress.setFromHostPort(host, port);
                }
                return socketAddress;
            }

            static string getLocalHost() {
                auto address = getLocalAddress();
                return address == nullptr ? LOCALHOST : address->str();
            }

            /**
             * 遍历本地网卡，返回第一个合理的IP。
             *
             * @return 本地网卡IP
             */
            static shared_ptr<folly::IPAddress> getLocalAddress() {
                if (LOCAL_ADDRESS != nullptr)
                    return LOCAL_ADDRESS;

                auto localAddress = getLocalAddress0();
                LOCAL_ADDRESS = localAddress;
                return localAddress;
            }

            static folly::SocketAddress toAddress(const string &address) {
                auto i = address.find(':');
                string host;
                uint16_t port;
                if (i != string::npos) {
                    host = address.substr(0, i);
                    port = static_cast<uint16_t>(stoi(address.substr(i + 1, address.length())));
                } else {
                    host = address;
                    port = 0;
                }
                return folly::SocketAddress(host, port);
            }

            static string toURL(const string &protocol, const string &host, uint16_t port, const string &path) {
                std::ostringstream os;
                os << protocol << "://" << host << ':' << port;

                if (path.at(0) != '/') {
                    os << '/';
                }
                os << path;
                return os.str();
            }

        private:
            static bool isValidAddress(const folly::SocketAddress &address) {

                if (address.isLoopbackAddress()) {
                    return false;
                }

                string name = address.getHostStr();

                if (name.empty() || name == ANYHOST || name == LOCALHOST) {
                    return false;
                }

                boost::regex e(IP_PATTERN, boost::regbase::normal | boost::regbase::icase);
                return boost::regex_match(name, e);
            }

            static shared_ptr<folly::IPAddress> getLocalAddress0() {
                struct ifaddrs *ifaddrs = nullptr;
                struct ifaddrs *addrs = nullptr;
                if (getifaddrs(&ifaddrs) == -1) {
                    return nullptr;
                }

                addrs = ifaddrs;
                while (addrs != nullptr) {
                    struct in_addr *inaddr = &((struct sockaddr_in *) addrs->ifa_addr)->sin_addr;
                    if (addrs->ifa_addr && addrs->ifa_addr->sa_family == AF_INET) { // check it is IP4
                        if (!((addrs->ifa_flags & IFF_POINTOPOINT) || (addrs->ifa_flags & IFF_LOOPBACK))) {
                            static char addressBuffer[INET_ADDRSTRLEN];
                            inet_ntop(AF_INET, inaddr, addressBuffer, INET_ADDRSTRLEN);
                            freeifaddrs(ifaddrs);
                            return make_shared<folly::IPAddress>(addressBuffer);
                        }
                    }
                    addrs = addrs->ifa_next;
                }
                freeifaddrs(ifaddrs);
                return nullptr;
            }

        private:
            static const int MIN_PORT = 0;

            static const int MAX_PORT = 65535;

            static const string ADDRESS_PATTERN;

            static const string LOCAL_IP_PATTERN;

            static const string IP_PATTERN;

            static shared_ptr<folly::IPAddress> LOCAL_ADDRESS;
        };
    }
}
#endif //DUBBOC_NETUTILS_H
