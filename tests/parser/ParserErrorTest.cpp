#include "logos/LgsApp.h"
#include <../../include/external/doctest.h>

TEST_CASE("TestSema10012") {
    LgsApp app;
    const auto code = R"(
    main() {
        obj = Obj{}
        obj.func() := 23
    }
    )";
    app.parseSrcFile("code.lgs");
    CHECK_EQ(app.errHandler.errors.size(), 1);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10012.errCode);
}

TEST_CASE("TestSema10017A") {
    LgsApp app;
    const auto code = R"(
    main() {
        break
    }
    )";
    app.parseSrcFile();
    CHECK_EQ(app.errHandler.errors.size(), 1);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10017.errCode);
}

TEST_CASE("TestSema10021") {
    LgsApp app;
    const auto code = R"(
    main() {
        obj = Obj{}
        go obj.x
    }
    )";
    app.parseSrcFile();
    CHECK_EQ(app.errHandler.errors.size(), 1);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10021.errCode);
}

TEST_CASE("TestParser10033A") {
    LgsApp app;
    const auto code = R"(
        object obj
        x: Int
    )";
    app.parseSrcFile();
    CHECK_EQ(app.errHandler.errors.size(), 1);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.errCode);
}

TEST_CASE("ParserTest10033B") {
    LgsApp app;
    const auto code = R"(
        interface inter
        x: Int
    )";
    app.parseSrcFile();
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
    app.parseSrcFile();
    CHECK_EQ(app.errHandler.errors.size(), 2);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.errCode);
    CHECK_EQ(app.errHandler.errors[1].errCode, E10033.errCode);
}
