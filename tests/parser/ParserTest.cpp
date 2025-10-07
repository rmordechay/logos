#include "files/LgsFile.h"
#include "logos/LgsApp.h"
#include "utils/LgsUtils.h"
#include <external/doctest.h>

TEST_CASE("TestParser") {
    LgsApp app;
    const auto code = getFileText("../../tests/parser/ParserTestActual.lgs");
    const auto expectedTree = getFileText("../../tests/parser/ParserTestExpected.json");
    app.loadSrcFile(code, "Main.lgs");
    std::stringstream json;
    app.ast.front()->parseAsJSON(json);
    std::ofstream("../../test.json") << json.str();
    CHECK(app.errHandler.errors.size() == 0);
    CHECK_EQ(json.str(), expectedTree);
}
