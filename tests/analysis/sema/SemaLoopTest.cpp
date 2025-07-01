#include "logos/Logos.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

class SemaLoopTest : public testing::Test {
protected:
    Logos logos;

    void SetUp() override {
        logos.app.parseSrcFile("main() {}", "");
    }

    void TearDown() override {}
};

TEST_F(SemaLoopTest, TestForeachLoopWorks) {

}
