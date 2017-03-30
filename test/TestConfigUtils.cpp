//
// Created by 云海 on 2017/3/30.
//

#include <glog/logging.h>
#include <gtest/gtest.h>

#include "common/Utils/ConfigUtils.h"

using namespace std;
using namespace DUBBOC::COMMON;

class TestConfigUtils : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {}
};


TEST_F(TestConfigUtils, test){
    ConfigUtils::getProperties();
    EXPECT_EQ("value1",ConfigUtils::getProperty("key1"));
    EXPECT_EQ("2",ConfigUtils::getProperty("key2"));
}
