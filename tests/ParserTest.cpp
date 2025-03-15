#include "Logos.h"
#include <gtest/gtest.h>
#include <LogosParser.h>

TEST(ParserTest, TestParsingWorks) {
    const Logos project("data");
    project.initPaths();
    const directory_entry fileEntry("../tests/data/Main.lgs");
    const auto file = project.parseFile(fileEntry);
    const auto mainFile = dynamic_cast<LgsMainFile*>(file);
    EXPECT_NE(mainFile, nullptr);
    ASSERT_EQ(mainFile->name, "Main");
    EXPECT_NE(mainFile->relPath, "");
    EXPECT_NE(mainFile->mainFunc, nullptr);
    EXPECT_GT(mainFile->funcs.size(), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
