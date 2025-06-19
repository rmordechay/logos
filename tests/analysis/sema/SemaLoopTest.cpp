#include "LgsLinker.h"
#include "Logos.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

class SemaLoopTest : public testing::Test {
protected:
    path dataDir = "../../tests/analysis/sema/code";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        logos.project.parseSrcFile(dataDir / "loop.lgs");
        logos.project.loadGlobals();
        logos.analyse(logos.project.files);
    }

    void TearDown() override {}
};

TEST_F(SemaLoopTest, TestForeachLoopWorks) {
    ASSERT_THAT(logos.errors.size(), 0);
}
