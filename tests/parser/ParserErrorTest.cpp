#include "logos/LgsApp.h"
#include "LgsUtils.h"
#include "errors/LgsErrors.h"
#include "gtest/gtest.h"

TEST(ParserErrorTest, E10011B) {
    LgsApp app;
    const auto code = R"(
    func() {}
    func() {}
    main() {}
    )";
    app.loadSrcFile(code);
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10011, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10011.errCode);
    }
}

TEST(ParserErrorTest, E10054) {
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
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10054, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10054.errCode);
    }
}
