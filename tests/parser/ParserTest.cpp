#include "Logos.h"
#include <gtest/gtest.h>
#include <LogosParser.h>


TEST(ParserTest, TestParseFile) {
    const Logos project("../tests/parser/data");
    project.initPaths();
    const directory_entry fileEntry(rootDir / "Main.lgs");
    const auto file = project.parseFile(fileEntry);
    const auto mainFile = dynamic_cast<LgsMainFile*>(file);
    EXPECT_NE(mainFile, nullptr);
    ASSERT_EQ(mainFile->name, "Main");
    EXPECT_NE(mainFile->relPath, "");
    EXPECT_NE(mainFile->mainFunc, nullptr);
    EXPECT_EQ(mainFile->funcs.size(), 2);
}
