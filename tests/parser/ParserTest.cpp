#include "files/LgsMainFile.h"
#include "logos/LgsApp.h"
#include "tools/LgsJsonParser.h"
#include "LgsUtils.h"
#include "gtest/gtest.h"

const std::string expectedDir = "../../tests/parser/expected";

TEST(ParserTest, Test1) {
    LgsApp app;
    const auto code = R"(
        main() {}
    )";
    const auto expectedTree = getFileText(expectedDir + "/ParserTest1.json");
    app.loadSrcFile(code, LGS_MAIN_FILE);
    const auto mainFile = app.srcFiles.front()->asMainFile();
    LgsJsonParser parser;
    parser.parseMainFile(mainFile);
    //EXPECT_EQ(app.errHandler.errors.size(), 0);
    //EXPECT_EQ(parser.json.str(), expectedTree);
}