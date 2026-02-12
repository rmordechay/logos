#include "logos/LgsApp.h"
#include "LgsUtils.h"
#include "LgsTestUtils.h"
#include "errors/LgsErrors.h"
#include "gtest/gtest.h"
#include <string>

TEST(SemaErrorTest, E10000A) {
    LgsApp app;
    const auto code = R"(
    func() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10000, 1);
}

TEST(SemaErrorTest, E10001A) {
    LgsApp app;
    const auto code = R"(
    main() {
        s1: Str[2] = [["text1"], ["text2"]]
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10001, 1);
}

TEST(SemaErrorTest, E10002A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 6
        for i in a {}
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10002, 1);
}

TEST(SemaErrorTest, E10003A) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[2]
        a = arr[2]
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10003, 1);
}

TEST(SemaErrorTest, E10004A) {
    LgsApp app;
    const auto code = R"(
    f(): Int {
        return "str"
    }
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10004, 1);
}

TEST(SemaErrorTest, E10005A) {
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
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10005, 1);
}

TEST(SemaErrorTest, E10005B) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj{a=3487, b=234}
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10005, 1);
}

TEST(SemaErrorTest, E10006A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = b
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10006, 1);
}

TEST(SemaErrorTest, E10006B) {
    LgsApp app;
    const auto code = R"(
    enum Enum {
        ENUM1
    }
    func(x: Int, e: Enum) {
        switch e {
            ENUM1: {}
        }
        a = ENUM1
    }
    main() {
        func(10, Enum.ENUM1)
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10006, 1);
}

TEST(SemaErrorTest, E10009A) {
    LgsApp app;
    app.configs.appMode = PROJECT_MODE;
    const auto code1 = R"(
    main() {}
    )";
    const auto code2 = R"(
    main() {}
    )";
    app.loadSrcFile(code1, LGS_MAIN_FILE);
    app.loadSrcFile(code2, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10009, 1);
}

TEST(SemaErrorTest, E10011A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 2
        a = 3
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10011, 1);
}

TEST(SemaErrorTest, E10013A) {
    LgsApp app;
    const auto code = R"(
    object Obj {a: Int}
    main() {
        obj = Obj{}
        obj.func()
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10005, 1);
}

TEST(SemaErrorTest, E10013B) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[34]
        arr.add(2)
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10005, 1);
}

TEST(SemaErrorTest, E10015A) {
    LgsApp app;
    const auto code = R"(
    func(a: Int) { }
    main() {
        func("str")
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10015, 1);
}

TEST(SemaErrorTest, E10015B) {
    LgsApp app;
    const auto code = R"(
    func<T>(arr: T[]): T[] {
        return arr
    }
    main() {
        func(1)
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10015, 1);
}

TEST(SemaErrorTest, E10016A) {
    LgsApp app;
    const auto code = R"(
    interface Interface {
        func()
    }
    object Object {
        implements: Interface
        a: Int
    }
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10016, 1);
}

TEST(SemaErrorTest, E10016B) {
    LgsApp app;
    const auto code = R"(
    interface Type {
        a: Int
    }

    object Object {
        implements: Type
    }

    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10016, 1);
}

TEST(SemaErrorTest, E10017A) {
    LgsApp app;
    const auto code = R"(
    main() {
        break
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10017, 1);
}

TEST(SemaErrorTest, E10018A) {
    LgsApp app;
    const auto code = R"(
    main() {
        s2: Int[] = [2.234, 2.34]
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10001, 1);
}

TEST(SemaErrorTest, E10021A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = true then "36" else 6
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10021, 1);
}

TEST(SemaErrorTest, E10024A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = null
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10024, 1);
}

TEST(SemaErrorTest, E10025A) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        implements: Int
    }
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10025, 1);
}

TEST(SemaErrorTest, E10026A) {
    LgsApp app;
    const auto code = R"(
    func(): Int { return }
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10026, 1);
}

TEST(SemaErrorTest, E10027A) {
    LgsApp app;
    const auto code = R"(
    fun(): Int { return 2 }
    fun2() {
        return fun()
    }
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10027, 1);
}

TEST(SemaErrorTest, E10028A) {
    LgsApp app;
    const auto code = R"(
    func(x: Int = 23, y: Str) { }
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10028, 1);
}

TEST(SemaErrorTest, E10030A) {
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
    app.loadSrcFile(code1, "Obj.lgs");
    ASSERT_TRUE(app.errHandler.successful);
    app.loadSrcFile(code2, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10030, 1);
}

TEST(SemaErrorTest, E10030B) {
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
    app.loadSrcFile(code1, "Obj.lgs");
    ASSERT_TRUE(app.errHandler.successful);
    app.loadSrcFile(code2, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10030, 1);
}

TEST(SemaErrorTest, E10031A) {
    LgsApp app;
    const auto code1 = R"(
    object Obj
    func() {}
    )";
    const auto code2 = R"(
    main() {
        a = Obj{}
        a.func()
    }
    )";
    app.loadSrcFile(code1, "Obj.lgs");
    ASSERT_TRUE(app.errHandler.successful);
    app.loadSrcFile(code2, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10031, 1);
}

TEST(SemaErrorTest, E10032A) {
    LgsApp app;
    const auto code = R"(
    single Obj {
        func() {}
    }
    main() {
        obj = Obj{}
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10032, 1);
}

TEST(SemaErrorTest, E10033A) {
    LgsApp app;
    const auto code = R"(
    main() {
        var = 2
        a = var{}
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10033, 1);
}

TEST(SemaErrorTest, E10033B) {
    LgsApp app;
    const auto code = R"(
        object obj
        x: Int
    )";
    app.loadSrcFile(code, "Obj.lgs");
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10033, 1);
}

TEST(SemaErrorTest, E10033C) {
    LgsApp app;
    const auto code = R"(
        interface inter
        x: Int
    )";
    app.loadSrcFile(code, "Interface.lgs");
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10033, 1);
}

TEST(SemaErrorTest, E10033D) {
    LgsApp app;
    const auto code = R"(
        interface inter {}
        object obj {}
        main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10033, 2);
}

TEST(SemaErrorTest, E10037A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = "Roi bla"
        b = a[2:1]
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10037, 1);
}

TEST(SemaErrorTest, E10038A) {
    LgsApp app;
    const auto code = R"(
    main() {
        continue
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10038, 1);
}

TEST(SemaErrorTest, E10042A) {
    LgsApp app;
    const auto code = R"(
    main() {
        map: {Int: Int}
        a = map[1:3]
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10042, 1);
}

TEST(SemaErrorTest, E10043A) {
    LgsApp app;
    const auto code = R"(
        func(a: Int = 2, b: Int...) {}
        main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 2) << EXPECTED_ERR(E10043);
    if (app.errHandler.errors.size() > 1) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10028.errCode);
        EXPECT_EQ(app.errHandler.errors[1].errCode, E10043.errCode);
    }
}

TEST(SemaErrorTest, E10046A) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj()
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10046, 1);
}


TEST(SemaErrorTest, E10055A) {
    LgsApp app;
    const auto code = R"(
    f(): Int {}
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10055, 1);
}

TEST(SemaErrorTest, E10056A) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
        a: Int
    }
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10056, 1);
}

TEST(SemaErrorTest, E10056B) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
        a() {}
    }
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10056, 1);
}

TEST(SemaErrorTest, E10059A) {
    LgsApp app;
    const auto code = R"(
    func(): Int {
        if true {
            return 1
            return 2
        }
        for i in 0..10 {
            break
            return 2
        }
        return 3
    }
    main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10059, 2);
}

TEST(SemaErrorTest, E10064A) {
    LgsApp app;
    const auto code = R"(
        interface Inter { func() }
        interface Inter2 { func() }
        object Obj2 {
            implements: Inter, Inter2
            func() {print("Hello world")}
        }
        main() {}
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10064, 1);
}

TEST(SemaErrorTest, E10066A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 0
        while a {
            a++
        }
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10066, 1);
}

TEST(SemaErrorTest, E10076A) {
    LgsApp app;
    const auto code = R"(
    main() {
        v1 = Vec3(.23, .578, .17)
        v2 = Vec2(.32, .38)
        v3 = v1 + v2
        v4 = v1 - v2
        v5 = v1 * v2
        v6 = v1 / v2
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10076, 4);
}

TEST(SemaErrorTest, E10089A) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        x: Int
    }
    main() {
        Obj.x := 23
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10089, 1);
}

TEST(SemaErrorTest, E10092A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 34 then "3" else "6"
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10092, 1);
}

TEST(SemaErrorTest, E10097A) {
    LgsApp app;
    const auto code = R"(
    main() {
        switch 2 {}
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10097, 1);
}

TEST(SemaErrorTest, E100108A) {
    LgsApp app;
    const auto code = R"(
    main() {
        num = 1
        a = num[1:3]
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10108, 1);
}

TEST(SemaErrorTest, E100115A) {
    LgsApp app;
    const auto code = R"(
    func<T>(t: T) {}
    main() {
        func<Float, Float>(2)
    }
    )";
    app.loadSrcFile(code, LGS_MAIN_FILE);
    ASSERT_TRUE(app.errHandler.successful);
    app.analyse();
    expectErrors(app, E10115, 1);
}
