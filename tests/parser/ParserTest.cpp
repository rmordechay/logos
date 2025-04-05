#include "Logos.h"
#include <gtest/gtest.h>
#include <LogosParser.h>
#include <filesystem>

const string dataDir = "../tests/parser/";

TEST(ParserTest, TestParseFile) {
    const Logos logos(dataDir);
    const directory_entry fileEntry(logos.paths.rootDir / "Main.lgs");
    const auto file = logos.parseFile(fileEntry);
    const auto mainFile = dynamic_cast<LgsMainFile*>(file);

    std::ifstream inputFile(dataDir + "expected.json");
    json expectedJson;
    inputFile >> expectedJson;

    std::cout << mainFile->asJson().dump(2) << '\n';
    ASSERT_EQ(mainFile->asJson(), expectedJson);
}
