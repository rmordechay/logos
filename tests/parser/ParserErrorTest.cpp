#include "logos/LgsApp.h"
#include "utils/LgsUtils.h"
#include <external/doctest.h>

TEST_CASE("TestParser10021") {
    LgsApp app;
    const auto code = R"(
    main() {
        obj = Obj{}
        go obj.x
    }
    )";
    app.parseSrcFile(code);
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10021, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10021.errCode);
}

TEST_CASE("TestParser10033A") {
    LgsApp app;
    const auto code = R"(
        object obj
        x: Int
    )";
    app.parseSrcFile(code);
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10033, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.errCode);
}

TEST_CASE("ParserTest10033B") {
    LgsApp app;
    const auto code = R"(
        interface inter
        x: Int
    )";
    app.parseSrcFile(code);
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10033, code));
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
