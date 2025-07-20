#include "logos/LgsApp.h"
#include "logos/LgsModule.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

class SemaTest : public testing::Test {
public:
    LgsApp app;

    void SetUp() override {
        app.loadBuiltins();
    }

    void TearDown() override {
        globals.freeSymbols();
    }
};

TEST_F(SemaTest, TestSema10001) {
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

TEST_F(SemaTest, TestSema10011) {
    const auto code = R"(
    main() {
        a = 2
        a = 3
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10011);
}

TEST_F(SemaTest, TestSema10013) {
    const auto code = R"(
    object Obj {a: Int}
    main() {
        obj = Obj{}
        obj.func()
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10013);
}

TEST_F(SemaTest, TestSema10014) {
    const auto code = R"(
    main() {
        if "str" {
            1: {  }
        }
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10014);
}

TEST_F(SemaTest, TestSema10015) {
    const auto code = R"(
    func(a: Int) { }
    main() {
        func("str")
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10015);
}

TEST_F(SemaTest, TestSema10016) {
    const auto code = R"(
    interface Interface {
        func()
    }

    object Object {
        implements: Interface
        a: Int
    }

    main() {

    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10016);
}

TEST_F(SemaTest, TestSema10017) {
    const auto code = R"(
    main() {
        break
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, 10017);
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
