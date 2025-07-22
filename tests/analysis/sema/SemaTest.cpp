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

TEST_F(SemaTest, TestSema) {
    const auto code = R"(
    interface Type1 {
        a: Int
    }
    interface Type2 {
        implements: Type1
        b: Int
    }
    main() {
        a = 2
        arr: Int[a]!
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 0);
}


TEST_F(SemaTest, TestSema10001) {
    app.parseSrcFile("main() {a: Str = 34}");
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10001.errCode);
}

TEST_F(SemaTest, TestSema10002A) {
    const auto code = R"(
    main() {
        a = 34
        for i in a {}
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10002.errCode);
}

TEST_F(SemaTest, TestSema10002B) {
    const auto code = R"(
    main() {
        num = 1
        a = num[1:3]
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10002.errCode);
}

TEST_F(SemaTest, TestSema10003) {
    const auto code = R"(
    main() {
        arr: Int[2]!
        arr[3] := 2
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10003.errCode);
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10004.errCode);
}

TEST_F(SemaTest, TestSema10005A) {
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
}

TEST_F(SemaTest, TestSema10005B) {
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj{a = 3487, b = 234}
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10006.errCode);
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10011.errCode);
}

TEST_F(SemaTest, TestSema10013A) {
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10013.errCode);
}

TEST_F(SemaTest, TestSema10013B) {
    const auto code = R"(
    main() {
        arr: Int[34]!
        arr.add(2)
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10013.errCode);
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10014.errCode);
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10015.errCode);
}

TEST_F(SemaTest, TestSema10016A) {
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10016.errCode);
}

TEST_F(SemaTest, TestSema10016B) {
    const auto code = R"(
    interface Type1 {
        a: Int
    }
    interface Type2 {
        implements: Type1
        b: Int
    }
    object Object {
        implements: Type2
    }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 2);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10016.errCode);
    ASSERT_EQ(app.errHandler.errors[1].errCode, E10016.errCode);
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10017.errCode);
}

TEST_F(SemaTest, TestSema10022) {
    const auto code = R"(
    interface A {}
    main() {
        a = A{}
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10022.errCode);
}

TEST_F(SemaTest, TestSema10042) {
    const auto code = R"(
    main() {
        map: {Str: Str}
        a = map[1:3]
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10042.errCode);
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
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10046.errCode);
}

TEST_F(SemaTest, TestSema10048A) {
    const auto code = R"(
    func(): Int {
        return 2
    }
    main() {
        arr: Int[func()]!
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10048.errCode);
}

TEST_F(SemaTest, TestSema10048B) {
    const auto code = R"(
    main() {
        arr: Int[]!
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10048.errCode);
}

TEST_F(SemaTest, TestSema10055) {
    const auto code = R"(
    f(): Int {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10055.errCode);
}

TEST_F(SemaTest, TestSema10056A) {
    const auto code = R"(
    object Obj {
        a: Int
        a: Int
    }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10056.errCode);
}

TEST_F(SemaTest, TestSema10056B) {
    const auto code = R"(
    object Obj {
        a: Int
        a() {}
    }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    ASSERT_EQ(app.errHandler.errors.size(), 1);
    ASSERT_EQ(app.errHandler.errors[0].errCode, E10056.errCode);
}
