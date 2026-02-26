#include <string>
#include <filesystem>
#include <vector>

#include "logos/LgsApp.h"
#include "LgsUtils.h"
#include "LgsTestUtils.h"
#include "errors/LgsErrors.h"
#include "gtest/gtest.h"
#include "LgsDefinitions.h"
#include "errors/LgsErrHandler.h"
#include "logos/LgsAppConfigs.h"

TEST(ErrorsTest, E10000A) {
    const auto code = R"(
    func() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10000, 1);
}

TEST(ErrorsTest, E10001A) {
    const auto code = R"(
    main() {
        s1: Int[2] = [["text1"], ["text2"]]
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10001, 1);
}

TEST(ErrorsTest, E10002A) {
    const auto code = R"(
    main() {
        a = 6
        for i in a {}
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10002, 1);
}

TEST(ErrorsTest, E10001B) {
    const auto code = R"(
    main() {
        s2: Int[] = [2.234, 2.34]
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10001, 1);
}

TEST(ErrorsTest, E10003A) {
    const auto code = R"(
    main() {
        arr: Int[2]
        a = arr[2]
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10003, 1);
}

TEST(ErrorsTest, E10004A) {
    const auto code = R"(
    f(): Int {
        return "str"
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10004, 1);
}

TEST(ErrorsTest, E10005A) {
    const auto code = R"(
    object Obj {
        b: Int
    }
    main() {
        obj = Obj{}
        a = obj.a
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10005, 1);
}

TEST(ErrorsTest, E10005B) {
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj{a=3487, b=234}
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10005, 1);
}

TEST(ErrorsTest, E10005C) {
    const auto code = R"(
    main() {
        arr: Int[34]
        arr.add(2)
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10005, 1);
}

TEST(ErrorsTest, E10005D) {
    const auto code = R"(
    object Obj {a: Int}
    main() {
        obj = Obj{}
        obj.func()
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10005, 1);
}

TEST(ErrorsTest, E10006A) {
    const auto code = R"(
    main() {
        a = b
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10006, 1);
}

TEST(ErrorsTest, E10006B) {
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
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10006, 1);
}

TEST(ErrorsTest, E10009A) {
    const auto code1 = "main() {}";
    const auto code2 = "main() {}";
    LgsApp app;
    app.configs.appMode = PROJECT_MODE;
    parseAndAnalyse(app, {code1, code2}, {LGS_MAIN_FILE, LGS_MAIN_FILE});
    expectErrors(app, E10009, 1);
}

TEST(ErrorsTest, E10011A) {
    const auto code = R"(
    main() {
        a = 2
        a = 3
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10011, 1);
}

TEST(ErrorsTest, E10011B) {
    const auto code = R"(
    func() {}
    func() {}
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10011, 1);
}

TEST(ErrorsTest, E10011C) {
    const auto code = R"(
    single Obj {}
    object Obj {}
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10011, 1);
}

TEST(ErrorsTest, E10011D) {
    const auto code = R"(
    object Obj<T> {
        func<T>(y: T) {}
    }
    main() {
        obj = Obj{}
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10011, 1);
}

TEST(ErrorsTest, E10012A) {
    const auto code = R"(
    main() {
        a = null?
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10012, 1);
}

TEST(ErrorsTest, E10013A) {
    const auto code = R"(
    object Obj {
        f: (Int): Void
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10013, 1);
}

TEST(ErrorsTest, E10014A) {
    const auto code = R"(
    object Obj {
        implements: Self
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10014, 1);
}

TEST(ErrorsTest, E10015A) {
    const auto code = R"(
    func(a: Int) { }
    main() {
        func("str")
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10015, 1);
}

TEST(ErrorsTest, E10015B) {
    const auto code = R"(
    func<T>(arr: T[]): T[] {
        return arr
    }
    main() {
        func(1)
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10015, 1);
}

TEST(ErrorsTest, E10016A) {
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
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10016, 1);
}

TEST(ErrorsTest, E10016B) {
    const auto code = R"(
    interface Type {
        a: Int
    }

    object Object {
        implements: Type
    }

    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10016, 1);
}

TEST(ErrorsTest, E10017A) {
    const auto code = R"(
    main() {
        break
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10017, 1);
}

TEST(ErrorsTest, E10021A) {
    const auto code = R"(
    main() {
        a = true then "36" else 6
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10021, 1);
}

TEST(ErrorsTest, E10024A) {
    const auto code = R"(
    main() {
        a = null
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10024, 1);
}

TEST(ErrorsTest, E10025A) {
    const auto code = R"(
    object Obj {
        implements: Int
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10025, 1);
}

TEST(ErrorsTest, E10026A) {
    const auto code = R"(
    func(): Int { return }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10026, 1);
}

TEST(ErrorsTest, E10027A) {
    const auto code = R"(
    fun(): Int { return 2 }
    fun2() {
        return fun()
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10027, 1);
}

TEST(ErrorsTest, E10028A) {
    const auto code = R"(
    func(x: Int = 23, y: Str) { }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10028, 1);
}

TEST(ErrorsTest, E10030A) {
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
    LgsApp app;
    parseAndAnalyse(app, {code1, code2}, {"obj.lgs", LGS_MAIN_FILE});
    expectErrors(app, E10030, 1);
}

TEST(ErrorsTest, E10030B) {
    const auto code1 = R"(
    object Obj
    x: Int
    )";
    const auto code2 = R"(
    main() {
        a = Obj{x = 2}
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code1, code2}, {"obj.lgs", LGS_MAIN_FILE});
    expectErrors(app, E10030, 1);
}

TEST(ErrorsTest, E10031A) {
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
    LgsApp app;
    parseAndAnalyse(app, {code1, code2}, {"obj.lgs", LGS_MAIN_FILE});
    expectErrors(app, E10031, 1);
}

TEST(ErrorsTest, E10032A) {
    const auto code = R"(
    single Obj {
        func() {}
    }
    main() {
        obj = Obj{}
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10032, 1);
}

TEST(ErrorsTest, E10033A) {
    const auto code = R"(
    main() {
        var = 2
        a = var{}
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10033, 1);
}

TEST(ErrorsTest, E10033B) {
    const auto code = R"(
        object obj
        x: Int
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {"obj.lgs"});
    expectErrors(app, E10033, 1);
}

TEST(ErrorsTest, E10033C) {
    const auto code = R"(
        interface inter
        x: Int
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {"interface.lgs"});
    expectErrors(app, E10033, 1);
}

TEST(ErrorsTest, E10033D) {
    const auto code = R"(
        interface inter {}
        object obj {}
        main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10033, 2);
}

TEST(ErrorsTest, E10037A) {
    const auto code = R"(
    main() {
        a = "Roi bla"
        b = a[2:1]
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10037, 1);
}

TEST(ErrorsTest, E10038A) {
    const auto code = R"(
    main() {
        continue
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10038, 1);
}

TEST(ErrorsTest, E10042A) {
    const auto code = R"(
    main() {
        map: {Int: Int}
        a = map[1:3]
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10042, 1);
}

TEST(ErrorsTest, E10043A) {
    const auto code = R"(
        func(a: Int = 2, b: Int...) {}
        main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    EXPECT_EQ(app.errHandler.errors.size(), 2) << EXPECTED_ERR(E10043);
    if (app.errHandler.errors.size() > 1) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10028.errCode);
        EXPECT_EQ(app.errHandler.errors[1].errCode, E10043.errCode);
    }
}

TEST(ErrorsTest, E10046A) {
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj()
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10046, 1);
}

TEST(ErrorsTest, E10048A) {
    const auto code = R"(
    object Obj {
        obj: Obj
    }
    object Obj2 {
        func(obj2: Obj2) {}
    }
    object Obj3 {
        func(): Obj3 {}
    }
    object Obj4 {
        obj: Obj
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10048, 4);
}

TEST(ErrorsTest, E10051A) {
    const auto code = R"(
    main() {
        var = 2
        var := 3
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10051, 1);
}

TEST(ErrorsTest, E10051B) {
    const auto code = R"(
    main() {
        a = 1
        a++
        a--
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10051, 2);
}

TEST(ErrorsTest, E10054A) {
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
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10054, 1);
}

TEST(ErrorsTest, E10055A) {
    const auto code = R"(
    f(): Int {}
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10055, 1);
}

TEST(ErrorsTest, E10055B) {
    const auto code = R"(
    func(): Str {
        if true {
            return ""
        }
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10055, 1);
}

TEST(ErrorsTest, E10056A) {
    const auto code = R"(
    object Obj {
        a: Int
        a: Int
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10056, 1);
}

TEST(ErrorsTest, E10056B) {
    const auto code = R"(
    object Obj {
        a: Int
        a() {}
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10056, 1);
}

TEST(ErrorsTest, E10059A) {
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
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10059, 2);
}

TEST(ErrorsTest, E10064A) {
    const auto code = R"(
        interface Inter { func() }
        interface Inter2 { func() }
        object Obj2 {
            implements: Inter, Inter2
            func() {print("Hello world")}
        }
        main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10064, 1);
}

TEST(ErrorsTest, E10066A) {
    const auto code = R"(
    main() {
        mut a = 0
        while a {
            a++
        }
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10066, 1);
}

TEST(ErrorsTest, E10076A) {
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
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10076, 4);
}

TEST(ErrorsTest, E10083A) {
    const auto code = R"(
    object Obj {
        x: Int
        func() {
            dummy = self.x
        }
    }
    main() {
        Obj.func()
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10083, 1);
}

TEST(ErrorsTest, E10089A) {
    const auto code = R"(
    object Obj {
        x: Int
    }
    main() {
        Obj.x := 23
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10089, 1);
}

TEST(ErrorsTest, E10092A) {
    const auto code = R"(
    main() {
        a = 34 then "3" else "6"
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10092, 1);
}

TEST(ErrorsTest, E10097A) {
    const auto code = R"(
    main() {
        switch 2 {}
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10097, 1);
}

TEST(ErrorsTest, E10105A) {
    const auto code = R"(
    func(arr: Int[2]) {
        print(arr)
    }
    main() {
        arr: Str[2][2] = [["text1"], ["text"], ["text"]]
        func([1, 2, 3])
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10105, 2);
}

TEST(ErrorsTest, E100108A) {
    const auto code = R"(
    main() {
        num = 1
        a = num[1:3]
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10108, 1);
}

TEST(ErrorsTest, E100115A) {
    const auto code = R"(
    func<T>(t: T) {}
    main() {
        func<Float, Float>(2)
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10115, 1);
}

TEST(ErrorsTest, E100115B) {
    const auto code = R"(
    object Obj<T> {}
    main() {
        obj = Obj<Int, Int>{}
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10115, 1);
}

TEST(ErrorsTest, E100117A) {
    const auto code = R"(
    object Obj {
        func() {}
    }
    main() {
        obj = Obj{}
        obj.func() := 2
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10117, 1);
}

TEST(ErrorsTest, E100118A) {
    const auto code = R"(
    enum Enum {
        ENUM1 = "value1"
        ENUM2 = "value2"
        ENUM3
    }
    main() {}
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10118, 1);
}

TEST(ErrorsTest, E100119A) {
    const auto code = R"(
    func() {}
    main() {
        func<Int>()
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10119, 1);
}

TEST(ErrorsTest, E100120A) {
    const auto code = R"(
    object Obj {}
    main() {
        obj = Obj<Int>{}
    }
    )";
    LgsApp app;
    parseAndAnalyse(app, {code}, {LGS_MAIN_FILE});
    expectErrors(app, E10120, 1);
}
