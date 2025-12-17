#include "logos/LgsApp.h"
#include "LgsUtils.h"
#include <../../external/include/doctest.h>

TEST_CASE("ParserError10011B") {
    LgsApp app;
    const auto code = R"(
    func() {}
    func() {}
    main() {}
    )";
    app.loadSrcFile(code);
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10011, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10011.errCode);
    }
}

TEST_CASE("ParserErrorError10033A") {
    LgsApp app;
    const auto code = R"(
        object obj
        x: Int
    )";
    app.loadSrcFile(code, "Obj.lgs");
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10033, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.errCode);
}

TEST_CASE("ParserError10033B") {
    LgsApp app;
    const auto code = R"(
        interface inter
        x: Int
    )";
    app.loadSrcFile(code, "Interface.lgs");
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10033, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.errCode);
}

TEST_CASE("ParserError10033C") {
    LgsApp app;
    const auto code = R"(
        interface inter {}
        object obj {}
        main() {}
    )";
    app.loadSrcFile(code);
    CHECK_EQ(app.errHandler.errors.size(), 2);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.errCode);
    CHECK_EQ(app.errHandler.errors[1].errCode, E10033.errCode);
}

TEST_CASE("ParserError10054") {
    LgsApp app;
    const auto code = R"(
    object Obj {
        x: Int?
        y: Float
        z: Str
    }
    main() {
        obj1 = Obj{x = 2, z = "Test", z = 3.23}
    }
    )";
    app.loadSrcFile(code);
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10054, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10054.errCode);
    }
}