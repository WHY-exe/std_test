#include <gtest/gtest.h>
#include "Util.h"
#include <spdlog/spdlog.h>

TEST(HelloTest, TestNum)
{
    // spdlog::info("hello world");
    EXPECT_EQ(1+2, 3);
}