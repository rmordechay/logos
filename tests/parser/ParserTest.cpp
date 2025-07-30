#include "logos/LgsApp.h"
#include <doctest.h>

TEST_CASE("TestParserHappy") {
    LgsApp app;
    app.parseSrcFile("main() {a: Str = 34}");
    CHECK(app.errHandler.errors.empty());
}

TEST_CASE("TestParser10033A") {
    LgsApp app;
    const auto code = R"(
        object obj
        x: Int
    )";
    app.parseSrcFile(code);
    CHECK_EQ(app.errHandler.errors.size(), 1);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.errCode);
}

TEST_CASE("ParserTest10033B") {
    LgsApp app;
    const auto code = R"(
        interface inter
        x: Int
    )";
    app.parseSrcFile(code);
    CHECK_EQ(app.errHandler.errors.size(), 1);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.errCode);
}

TEST_CASE("ParserTest10033C") {
    LgsApp app;
    const auto code = R"(
        interface inter {}
        object obj {}
        main() {}
    )";
    app.parseSrcFile(code);
    CHECK_EQ(app.errHandler.errors.size(), 2);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.errCode);
    CHECK_EQ(app.errHandler.errors[1].errCode, E10033.errCode);
}
