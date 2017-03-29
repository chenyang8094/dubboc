//
// Created by 云海 on 2017/3/29.
//

#include <glog/logging.h>
#include <gtest/gtest.h>
#include "common/ExtensionHeader.h"
#include "common/ExtensionLoader.h"

using namespace std;
using namespace DUBBOC::COMMON;
using namespace DUBBOC::REMOTING;

class TestUrl : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {}
};


TEST_F(TestUrl, test_valueOf_noProtocolAndHost) {
    auto url = URL::valueOf("/context/path?version=1.0.0&application=morgan");
    EXPECT_EQ(url->getProtocol().empty(), true);
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost().empty(), true);
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");

    url = URL::valueOf("context/path?version=1.0.0&application=morgan");
    EXPECT_EQ(url->getProtocol().empty(), true);
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost(), "context");
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath(), "path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");
}

TEST_F(TestUrl, test_valueOf_noProtocol) {
    auto url = URL::valueOf("10.20.130.230");
    EXPECT_EQ(url->getProtocol().empty(), true);
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath().empty(), true);
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("10.20.130.230:20880");
    EXPECT_EQ(url->getProtocol().empty(), true);
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath().empty(), true);
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("10.20.130.230/context/path");
    EXPECT_EQ(url->getProtocol().empty(), true);
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("10.20.130.230:20880/context/path");
    EXPECT_EQ(url->getProtocol().empty(), true);
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan");
    EXPECT_EQ(url->getProtocol().empty(), true);
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");
}

TEST_F(TestUrl, test_valueOf_noHost) {
    auto url = URL::valueOf("file:///home/user1/router.js");
    EXPECT_EQ(url->getProtocol(), "file");
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost().empty(), true);
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath(), "home/user1/router.js");
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("file://home/user1/router.js");
    EXPECT_EQ(url->getProtocol(), "file");
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost(), "home");
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath(), "user1/router.js");
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("file:/home/user1/router.js");
    EXPECT_EQ(url->getProtocol(), "file");
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost().empty(), true);
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath(), "home/user1/router.js");
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("file:///d:/home/user1/router.js");
    EXPECT_EQ(url->getProtocol(), "file");
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost().empty(), true);
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath(), "d:/home/user1/router.js");
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("file:///home/user1/router.js?p1=v1&p2=v2");
    EXPECT_EQ(url->getProtocol(), "file");
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost().empty(), true);
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath(), "home/user1/router.js");
    EXPECT_EQ(url->getParameters()->size(), 2);
    auto map = make_shared<unordered_map<string, string>>();
    map->insert(make_pair("p1", "v1"));
    map->insert(make_pair("p2", "v2"));
    EXPECT_EQ(*(url->getParameters()), *map);

    url = URL::valueOf("file:/home/user1/router.js?p1=v1&p2=v2");
    EXPECT_EQ(url->getProtocol(), "file");
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost().empty(), true);
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath(), "home/user1/router.js");
    EXPECT_EQ(url->getParameters()->size(), 2);
    map = make_shared<unordered_map<string, string>>();
    map->insert(make_pair("p1", "v1"));
    map->insert(make_pair("p2", "v2"));
    EXPECT_EQ(*(url->getParameters()), *map);
}


TEST_F(TestUrl, test_valueOf_WithProtocolHost) {
    auto url = URL::valueOf("dubbo://10.20.130.230");
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 0);
    EXPECT_EQ(url->getPath().empty(), true);
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("dubbo://10.20.130.230:20880/context/path");
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername().empty(), true);
    EXPECT_EQ(url->getPassword().empty(), true);
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880");
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath().empty(), true);
    EXPECT_EQ(url->getParameters()->size(), 0);

    url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880?version=1.0.0");
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath().empty(), true);
    EXPECT_EQ(url->getParameters()->size(), 1);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");

    url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan");
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");

    url = URL::valueOf(
            "dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan&noValue");
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 3);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");
    EXPECT_EQ(url->getParameter("noValue"), "noValue");

}


TEST_F(TestUrl, test_valueOf_spaceSafe) {
    auto url = URL::valueOf("http://1.2.3.4:8080/path?key=value1 value2");
    EXPECT_EQ(url->toString(), "http://1.2.3.4:8080/path?key=value1 value2");
    EXPECT_EQ(url->getParameter("key"), "value1 value2");
}


TEST_F(TestUrl, test_noValueKey) {
    auto url = URL::valueOf("http://1.2.3.4:8080/path?k0&k1=v1");
    EXPECT_TRUE(url->hasParameter("k0"));
    EXPECT_EQ(url->getParameter("k0"), "k0");
}

TEST_F(TestUrl, test_getAddress) {
    auto url = URL::valueOf(
            "dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan");
    EXPECT_EQ(url->getAddress(), "10.20.130.230:20880");
}

TEST_F(TestUrl, test_getAbsolutePath) {
    auto url = make_shared<URL>("p1", "1.2.2.2", 33);
    EXPECT_EQ(url->getAbsolutePath().empty(), true);

    url = make_shared<URL>("file", "", 90, string("/home/user1/route.js"), nullptr);
    EXPECT_EQ(url->getAbsolutePath(), "/home/user1/route.js");
}

TEST_F(TestUrl, test_equals) {
    auto url1 = URL::valueOf(
            "dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan");
    auto params = make_shared<unordered_map<string, string>>();
    params->insert(make_pair("version", "1.0.0"));
    params->insert(make_pair("application", "morgan"));
    auto url2 = make_shared<URL>("dubbo", "admin", "hello1234", "10.20.130.230", 20880, "context/path", params);
    EXPECT_TRUE(*url1 == url2);
}

TEST_F(TestUrl, test_toString) {
    auto url1 = URL::valueOf(
            "dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan");
    EXPECT_TRUE(url1->toFullString() ==
                "dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan"
                || url1->toFullString() ==
                   "dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan&version=1.0.0");
}

TEST_F(TestUrl, test_set_methods) {
    auto url = URL::valueOf(
            "dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan");
    url = url->setHost("host");
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "host");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");

    url = url->setPort(1);
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "host");
    EXPECT_EQ(url->getPort(), 1);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");

    url = url->setPath("path");
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "host");
    EXPECT_EQ(url->getPort(), 1);
    EXPECT_EQ(url->getPath(), "path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");


    url = url->setProtocol("protocol");
    EXPECT_EQ(url->getProtocol(), "protocol");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "host");
    EXPECT_EQ(url->getPort(), 1);
    EXPECT_EQ(url->getPath(), "path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");

    url = url->setUsername("username");
    EXPECT_EQ(url->getProtocol(), "protocol");
    EXPECT_EQ(url->getUsername(), "username");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "host");
    EXPECT_EQ(url->getPort(), 1);
    EXPECT_EQ(url->getPath(), "path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");

    url = url->setPassword("password");
    EXPECT_EQ(url->getProtocol(), "protocol");
    EXPECT_EQ(url->getUsername(), "username");
    EXPECT_EQ(url->getPassword(), "password");
    EXPECT_EQ(url->getHost(), "host");
    EXPECT_EQ(url->getPort(), 1);
    EXPECT_EQ(url->getPath(), "path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("version"), "1.0.0");
    EXPECT_EQ(url->getParameter("application"), "morgan");

}


TEST_F(TestUrl, test_removeParameters) {
    auto url = URL::valueOf(
            "dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan&k1=v1&k2=v2");
    url = url->removeParameter("version");
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 3);
    EXPECT_EQ(url->getParameter("k1"), "v1");
    EXPECT_EQ(url->getParameter("k2"), "v2");
    EXPECT_EQ(url->getParameter("application"), "morgan");
    EXPECT_EQ(url->getParameter("version").empty(), true);


    url = URL::valueOf(
            "dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan&k1=v1&k2=v2");
    url = url->removeParameters("version", "application", "NotExistedKey", nullptr);

    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("k1"), "v1");
    EXPECT_EQ(url->getParameter("k2"), "v2");
    EXPECT_EQ(url->getParameter("application").empty(), true);
    EXPECT_EQ(url->getParameter("version").empty(), true);

    url = URL::valueOf(
            "dubbo://admin:hello1234@10.20.130.230:20880/context/path?version=1.0.0&application=morgan&k1=v1&k2=v2");
    list<string> list_keys;
    list_keys.push_back("version");
    list_keys.push_back("application");
    url = url->removeParameters(list_keys);

    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("k1"), "v1");
    EXPECT_EQ(url->getParameter("k2"), "v2");
    EXPECT_EQ(url->getParameter("application").empty(), true);
    EXPECT_EQ(url->getParameter("version").empty(), true);


}

TEST_F(TestUrl, test_addParameter) {
    auto url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan");
    url = url->addParameter("k1", string("v1"));
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("k1"), "v1");

}

TEST_F(TestUrl, test_addParameter_sameKv) {
    auto url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan&k1=v1");
    auto newUrl = url->addParameter("k1", string("v1"));

    EXPECT_TRUE(*url == newUrl);
}

TEST_F(TestUrl, test_addParameters) {
    auto url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan");
    auto map = make_shared<unordered_map<string, string>>();
    map->insert(make_pair("k1", "v1"));
    map->insert(make_pair("k2", "v2"));
    url = url->addParameters(map);

    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 3);
    EXPECT_EQ(url->getParameter("application"), "morgan");
    EXPECT_EQ(url->getParameter("k1"), "v1");
    EXPECT_EQ(url->getParameter("k2"), "v2");


    url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan");
    url = url->addParameters("k1", "v1", "k2", "v2", "application", "xxx", nullptr);
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 3);
    EXPECT_EQ(url->getParameter("application"), "xxx");
    EXPECT_EQ(url->getParameter("k1"), "v1");
    EXPECT_EQ(url->getParameter("k2"), "v2");

    url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan");
    map = make_shared<unordered_map<string, string>>();
    map->insert(make_pair("k1", "v1"));
    map->insert(make_pair("k2", "v2"));
    map->insert(make_pair("application", "xxx"));
    url = url->addParametersIfAbsent(map);
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 3);
    EXPECT_EQ(url->getParameter("application"), "morgan");
    EXPECT_EQ(url->getParameter("k1"), "v1");
    EXPECT_EQ(url->getParameter("k2"), "v2");

    url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan");
    url = url->addParameter("k1", string("v1"));
    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 2);
    EXPECT_EQ(url->getParameter("application"), "morgan");
    EXPECT_EQ(url->getParameter("k1"), "v1");

    url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan");
    url = url->addParameter("application", string("xxx"));

    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 1);
    EXPECT_EQ(url->getParameter("application"), "xxx");

}


TEST_F(TestUrl, test_addParameters_SameKv) {
    {
        auto url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan&k1=v1");
        auto map = make_shared<unordered_map<string, string>>();
        map->insert(make_pair("k1", "v1"));
        auto newUrl = url->addParameters(map);

        EXPECT_TRUE(*url == newUrl);
    }
    {
        auto url = URL::valueOf(
                "dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan&k1=v1&k2=v2");
        auto map = make_shared<unordered_map<string, string>>();
        map->insert(make_pair("k1", "v1"));
        map->insert(make_pair("k2", "v2"));
        auto newUrl = url->addParameters(map);

        EXPECT_TRUE(*newUrl == url);
    }
}


TEST_F(TestUrl, test_addParameterIfAbsent) {
    auto url = URL::valueOf("dubbo://admin:hello1234@10.20.130.230:20880/context/path?application=morgan");
    url = url->addParameterIfAbsent("application", string("xxx"));

    EXPECT_EQ(url->getProtocol(), "dubbo");
    EXPECT_EQ(url->getUsername(), "admin");
    EXPECT_EQ(url->getPassword(), "hello1234");
    EXPECT_EQ(url->getHost(), "10.20.130.230");
    EXPECT_EQ(url->getPort(), 20880);
    EXPECT_EQ(url->getPath(), "context/path");
    EXPECT_EQ(url->getParameters()->size(), 1);
    EXPECT_EQ(url->getParameter("application"), "morgan");

}

TEST_F(TestUrl, test_windowAbsolutePathBeginWithSlashIsValid) {

}

TEST_F(TestUrl, test_Anyhost) {
    auto url = URL::valueOf("dubbo://0.0.0.0:20880");
    EXPECT_EQ(url->getHost(), "0.0.0.0");
    EXPECT_TRUE(url->isAnyHost());
}

TEST_F(TestUrl, test_Localhost) {
    auto url = URL::valueOf("dubbo://127.0.0.1:20880");
    EXPECT_EQ(url->getHost(), "127.0.0.1");
    EXPECT_TRUE(url->isLocalHost());

     url = URL::valueOf("dubbo://127.0.1.1:20880");
    EXPECT_EQ(url->getHost(), "127.0.1.1");
    EXPECT_TRUE(url->isLocalHost());

    url = URL::valueOf("dubbo://localhost:20880");
    EXPECT_EQ(url->getHost(), "localhost");
    EXPECT_TRUE(url->isLocalHost());
}