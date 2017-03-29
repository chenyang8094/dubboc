//
// Created by 云海 on 2017/3/27.
//
#include <glog/logging.h>
#include <gtest/gtest.h>
#include "common/ExtensionLoader.h"
#include "common/ExtensionHeader.h"

using namespace std;
using namespace DUBBOC::COMMON;
using namespace DUBBOC::REMOTING;

class TestExtensionLoader : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {}
};


TEST_F(TestExtensionLoader, test){
    auto extension = ExtensionLoader::getInstance()->LoadExtension<ITransporter>("ITransporter:WangleTransporter");
    EXPECT_TRUE(extension != nullptr);

    auto extension2 = ExtensionLoader::getInstance()->LoadExtensionAdaptive<ITransporter>("ITransporter:TransporterAdaptive");
    EXPECT_TRUE(extension2 != nullptr);
}
