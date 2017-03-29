//
// Created by 云海 on 2017/3/26.
//
#include <gtest/gtest.h>
#include "glog/logging.h"


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    google::InitGoogleLogging("dubboc");
    return RUN_ALL_TESTS();
}