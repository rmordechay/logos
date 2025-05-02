#include "LgsLinker.h"
#include "Logos.h"

#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


using testing::StartsWith;

class SemaLoopTest : public testing::Test {
protected:
    path dataDir = "../tests/analysis/sema/code";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        path a = path(dataDir / "idjf");
        logos.project.parseSrcFile(a)
    }

    void TearDown() override {

    }
};

TEST_F(SemaLoopTest, TestForeachLoopWorks) {
    ASSERT_THAT(logos.errors.size(), 0);
}
