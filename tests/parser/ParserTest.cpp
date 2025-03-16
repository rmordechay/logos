#include "Logos.h"
#include <gtest/gtest.h>
#include <LogosParser.h>


TEST(ParserTest, TestParseFile) {
    const Logos logos("../tests/parser/data");
    const directory_entry fileEntry(logos.rootDir / "Main.lgs");
    const auto file = logos.parseFile(fileEntry);
    const auto mainFile = dynamic_cast<LgsMainFile*>(file);
    EXPECT_NE(mainFile, nullptr);
    ASSERT_EQ(mainFile->name, "Main");
    EXPECT_NE(mainFile->relPath, "");
    EXPECT_NE(mainFile->mainFunc, nullptr);
    EXPECT_EQ(mainFile->funcs.size(), 2);
}
