#include "logos/LgsApp.h"
#include "utils/LgsUtils.h"
#include <external/doctest.h>

TEST_CASE("Parser10011B") {
    LgsApp app;
    const auto code = R"(
    func() {}
    func() {}
    main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10011, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10011.code);
    }
}

TEST_CASE("ParserError10033A") {
    LgsApp app;
    const auto code = R"(
        object obj
        x: Int
    )";
    app.loadSrcFile(code);
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10033, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.code);
}

TEST_CASE("Parser10033B") {
    LgsApp app;
    const auto code = R"(
        interface inter
        x: Int
    )";
    app.loadSrcFile(code);
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10033, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.code);
}

TEST_CASE("Parser10033C") {
    LgsApp app;
    const auto code = R"(
        interface inter {}
        object obj {}
        main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    CHECK_EQ(app.errHandler.errors.size(), 2);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10033.code);
    CHECK_EQ(app.errHandler.errors[1].errCode, E10033.code);
}
