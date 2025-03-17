#include "Logos.h"
#include <gtest/gtest.h>
#include <LogosParser.h>
#include <filesystem>

const string dataDir = "../tests/analysis/sema/data/";

TEST(ParserTest, TestParseFile) {
    const Logos logos(dataDir);
    const directory_entry fileEntry(logos.rootDir / "Main.lgs");
    const auto file = logos.parseFile(fileEntry);
    const auto mainFile = dynamic_cast<LgsMainFile*>(file);

    std::ifstream input_file(dataDir + "expected.json");
    json expectedJson;
    input_file >> expectedJson;

    ASSERT_EQ(mainFile->asJson().dump(2), expectedJson.dump(2));
}
