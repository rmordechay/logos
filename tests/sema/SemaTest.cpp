#include "logos/LgsApp.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;

class SemaTest : public testing::Test {};

TEST_F(SemaTest, TestSemaHappy) {
    LgsApp app;
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
    EXPECT_EQ(app.errHandler.errors.size(), 0);
}

TEST_F(SemaTest, TestSema10001) {
    LgsApp app;
    app.parseSrcFile("main() {a: Str = 34}");
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10001.errCode);
}

TEST_F(SemaTest, TestSema10002A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 34
        for i in a {}
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10002.errCode);
}

TEST_F(SemaTest, TestSema10002B) {
    LgsApp app;
    const auto code = R"(
    main() {
        num = 1
        a = num[1:3]
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10002.errCode);
}

TEST_F(SemaTest, TestSema10003) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[2]!
        arr[3] := 2
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10003.errCode);
}

TEST_F(SemaTest, TestSema10004) {
    LgsApp app;
    const auto code = R"(
    f(): Int {
        return "str"
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10004.errCode);
}

TEST_F(SemaTest, TestSema10005A) {
    LgsApp app;
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
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
}

TEST_F(SemaTest, TestSema10005B) {
    LgsApp app;
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
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
}

TEST_F(SemaTest, TestSema10006) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = b
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10006.errCode);
}

TEST_F(SemaTest, TestSema10011) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 2
        a = 3
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10011.errCode);
}

TEST_F(SemaTest, TestSema10013A) {
    LgsApp app;
    const auto code = R"(
    object Obj {a: Int}
    main() {
        obj = Obj{}
        obj.func()
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10013.errCode);
}

TEST_F(SemaTest, TestSema10013B) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[34]!
        arr.add(2)
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10013.errCode);
}

TEST_F(SemaTest, TestSema10014) {
    LgsApp app;
    const auto code = R"(
    main() {
        if "str" {
            1: {  }
        }
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10014.errCode);
}

TEST_F(SemaTest, TestSema10015) {
    LgsApp app;
    const auto code = R"(
    func(a: Int) { }
    main() {
        func("str")
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10015.errCode);
}

TEST_F(SemaTest, TestSema10016A) {
    LgsApp app;
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
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10016.errCode);
}

TEST_F(SemaTest, TestSema10016B) {
    LgsApp app;
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
    EXPECT_EQ(app.errHandler.errors.size(), 2);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10016.errCode);
    EXPECT_EQ(app.errHandler.errors[1].errCode, E10016.errCode);
}

TEST_F(SemaTest, TestSema10017) {
    LgsApp app;
    const auto code = R"(
    main() {
        break
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10017.errCode);
}

TEST_F(SemaTest, TestSema10022) {
    LgsApp app;
    const auto code = R"(
    interface A {}
    main() {
        a = A{}
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10022.errCode);
}

TEST_F(SemaTest, TestSema10023) {
    LgsApp app;
    const auto code = R"(
    main() {
        a: Int = null
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10023.errCode);
}

TEST_F(SemaTest, TestSema10024) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = null
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10024.errCode);
}

TEST_F(SemaTest, TestSema10030A) {
    LgsApp app;
    const auto code1 = R"(
    object Obj
    x: Int
    )";
    const auto code2 = R"(
    main() {
        a = Obj{}
        b = a.x
    }
    )";
    app.parseSrcFile(code1, "code1.lgs");
    app.parseSrcFile(code2, "code2.lgs");
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10030.errCode);
}

TEST_F(SemaTest, TestSema10030B) {
    LgsApp app;
    const auto code1 = R"(
    object Obj
    x: Int
    )";
    const auto code2 = R"(
    main() {
        a = Obj{x = 2}
    }
    )";
    app.parseSrcFile(code1, "code1.lgs");
    app.parseSrcFile(code2, "code2.lgs");
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10030.errCode);
}

TEST_F(SemaTest, TestSema10042) {
    LgsApp app;
    const auto code = R"(
    main() {
        map: {Str: Str}
        a = map[1:3]
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10042.errCode);
}

TEST_F(SemaTest, TestSema10046) {
    LgsApp app;
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
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10046.errCode);
}

TEST_F(SemaTest, TestSema10048A) {
    LgsApp app;
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
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10048.errCode);
}

TEST_F(SemaTest, TestSema10048B) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[]!
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10048.errCode);
}

TEST_F(SemaTest, TestSema10055) {
    LgsApp app;
    const auto code = R"(
    f(): Int {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10055.errCode);
}

TEST_F(SemaTest, TestSema10056A) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
        a: Int
    }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10056.errCode);
}

TEST_F(SemaTest, TestSema10056B) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
        a() {}
    }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    EXPECT_EQ(app.errHandler.errors[0].errCode, E10056.errCode);
}
