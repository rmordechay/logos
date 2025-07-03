#include "logos/Logos.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

class SemaTest : public testing::Test {
public:
    LgsApp app;
};

TEST_F(SemaTest, TestSema10001) {
    app.loadGlobals();
    app.resolveGlobalTypes();
    app.parseSrcFile("main() {a: Str = 34}");
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10001);
}

TEST_F(SemaTest, TestSema10002) {
    const auto code = R"(
    main() {
        a = 34
        for i in a {}
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10002);
}

TEST_F(SemaTest, TestSema10004) {
    const auto code = R"(
    f(): Int {
        return "str"
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10004);
}

TEST_F(SemaTest, TestSema10005) {
    const auto code = R"(
    object Obj {
        b: Int
    }
    main() {
        obj = Obj{}
        a = obj.a
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10005);
}

TEST_F(SemaTest, TestSema10006) {
    const auto code = R"(
    main() {
        a = b
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10006);
}

TEST_F(SemaTest, TestSema10046) {
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj()
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10046);
}

TEST_F(SemaTest, TestSema10055) {
    const auto code = R"(
    f(): Int {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10055);
}
