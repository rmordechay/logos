#include "logos/LgsApp.h"
#include "LgsUtils.h"
#include <string>
#include "gtest/gtest.h"
#include "errors/LgsErrors.h"

TEST(SemaErrorTest, E10000) {
    LgsApp app;
    const auto code = R"(
    func() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10000, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10000.errCode);
    }
}

TEST(SemaErrorTest, Er0001A) {
    LgsApp app;
    const auto code = R"(
    main() {
        s1: Str[2] = [["adi"], ["roi"]]
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10001, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10001.errCode);
    }
}

TEST(SemaErrorTest, Er0002A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 6
        for i in a {}
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10002, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10002.errCode);
    }
}

TEST(SemaErrorTest, Er0002B) {
    LgsApp app;
    const auto code = R"(
    main() {
        num = 1
        a = num[1:3]
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10002, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10002.errCode);
    }
}

TEST(SemaErrorTest, E10004) {
    LgsApp app;
    const auto code = R"(
    f(): Int {
        return "str"
    }
    main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10004, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10004.errCode);
    }
}

TEST(SemaErrorTest, Er0005A) {
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
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10005, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
    }
}

TEST(SemaErrorTest, Er0005B) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj{a = 3487, b = 234}
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10005, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
    }
}

TEST(SemaErrorTest, Er0006A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = b
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10006, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10006.errCode);
    }
}

TEST(SemaErrorTest, Er0006B) {
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
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10006, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10006.errCode);
    }
}

TEST(SemaErrorTest, Er0011A) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 2
        a = 3
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10011, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10011.errCode);
    }
}

TEST(SemaErrorTest, Er0013A) {
    LgsApp app;
    const auto code = R"(
    object Obj {a: Int}
    main() {
        obj = Obj{}
        obj.func()
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10005, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
    }
}

TEST(SemaErrorTest, Er0013B) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[34]
        arr.add(2)
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10005, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
    }
}

TEST(SemaErrorTest, E10014) {
    LgsApp app;
    const auto code = R"(
    main() {
        switch "str" {
            1: {  }
        }
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10014, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10014.errCode);
    }
}

TEST(SemaErrorTest, Er0015A) {
    LgsApp app;
    const auto code = R"(
    func(a: Int) { }
    main() {
        func("str")
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10015, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10015.errCode);
    }
}

TEST(SemaErrorTest, Er0015B) {
    LgsApp app;
    const auto code = R"(
    object Obj1 {
        x: Int
    }
    object Obj2 {
        obj1: Obj1
    }
    func(obj1: Obj1) {
        obj2 = Obj2{}
        obj2.obj1 := obj1
    }
    main() {
        func(obj2.obj1)
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    // EXPECT_EQ(app.errHandler.errors.size() ==,, EXPECTED_ER) <<(E10015, code);
    if (app.errHandler.errors.size() > 0) {
        // EXPECT_EQ(app.errHandler.errors[0].errCode, E10015.errCode);
    }
}

TEST(SemaErrorTest, Er0016A) {
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
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10016, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10016.errCode);
    }
}

TEST(SemaErrorTest, Er0016B) {
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
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10016.errCode);
    }
}

TEST(SemaErrorTest, E10017) {
    LgsApp app;
    const auto code = R"(
    main() {
        break
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10017, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10017.errCode);
    }
}

TEST(SemaErrorTest, E10018) {
    LgsApp app;
    const auto code = R"(
    main() {
        s2: Int[] = [2.234, 2.34]
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10001, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10001.errCode);
    }
}

TEST(SemaErrorTest, E10021) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = true then "36" else 6
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10021, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10021.errCode);
    }
}

TEST(SemaErrorTest, E10022) {
    LgsApp app;
    const auto code = R"(
    main() {
        var = 2
        a = var{}
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10022, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10022.errCode);
    }
}

TEST(SemaErrorTest, E10023) {
    LgsApp app;
    const auto code = R"(
    main() {

    }
    )";
}

TEST(SemaErrorTest, E10024) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = null
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10024, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10024.errCode);
    }
}

TEST(SemaErrorTest, E10025) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        implements: Int
    }
    main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10025, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10025.errCode);
    }
}

TEST(SemaErrorTest, E10026) {
    LgsApp app;
    const auto code = R"(
    func(): Int { return }
    main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10026, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10026.errCode);
    }
}

TEST(SemaErrorTest, E10027) {
    LgsApp app;
    const auto code = R"(
    fun(): Int { return 2 }
    fun2() {
        return fun()
    }
    main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10027, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10027.errCode);
    }
}

TEST(SemaErrorTest, E10028) {
    LgsApp app;
    const auto code = R"(
    func(x: Int = 23, y: Str) { }
    main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10028, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10028.errCode);
    }
}

TEST(SemaErrorTest, Er0030A) {
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
    assert(app.errHandler.successful);
    app.loadSrcFile(code2);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10030, code1);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10030.errCode);
    }
}

TEST(SemaErrorTest, Er0030B) {
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
    assert(app.errHandler.successful);
    app.loadSrcFile(code2);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10030, code1);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10030.errCode);
    }
}

TEST(SemaErrorTest, E10031) {
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
    assert(app.errHandler.successful);
    app.loadSrcFile(code2);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10031, code1);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10031.errCode);
    }
}

TEST(SemaErrorTest, E10032) {
    LgsApp app;
    const auto code = R"(
    single Obj {
        func() {}
    }
    main() {
        obj = Obj{}
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10032, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10032.errCode);
    }
}

TEST(SemaErrorTest, E10033A) {
    LgsApp app;
    const auto code = R"(
        object obj
        x: Int
    )";
    app.loadSrcFile(code, "Obj.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10032, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10032.errCode);
    }
}

TEST(SemaErrorTest, E10033B) {
    LgsApp app;
    const auto code = R"(
        interface inter
        x: Int
    )";
    app.loadSrcFile(code, "Interface.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10032, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10032.errCode);
    }
}

TEST(SemaErrorTest, E10033C) {
    LgsApp app;
    const auto code = R"(
        interface inter {}
        object obj {}
        main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 2) << EXPECTED_ERR(E10032, code);
    if (app.errHandler.errors.size() > 1) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10032.errCode);
        EXPECT_EQ(app.errHandler.errors[1].errCode, E10033.errCode);
    }
}

TEST(SemaErrorTest, E10037) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = "Roi bla"
        b = a[2:1]
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10037, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10037.errCode);
    }
}

TEST(SemaErrorTest, E10038) {
    LgsApp app;
    const auto code = R"(
    main() {
        continue
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10038, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10038.errCode);
    }
}

TEST(SemaErrorTest, E10042) {
    LgsApp app;
    const auto code = R"(
    main() {
        map: {Str: Str}
        a = map[1:3]
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10042, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10042.errCode);
    }
}

TEST(SemaErrorTest, E10043) {
    LgsApp app;
    const auto code = R"(
        func(a: Int = 2, b: Int...) {}
        main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 2) << EXPECTED_ERR(E10043, code);
    if (app.errHandler.errors.size() > 1) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10028.errCode);
        EXPECT_EQ(app.errHandler.errors[1].errCode, E10043.errCode);
    }
}

TEST(SemaErrorTest, E10046) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj()
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10046, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10046.errCode);
    }
}

TEST(SemaErrorTest, Er0048A) {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[2]
        arr[3] := 2
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10048, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10048.errCode);
    }
}

TEST(SemaErrorTest, Er0048B) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = "Roi bla"
        b = a[1:7]
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10048, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10048.errCode);
    }
}

TEST(SemaErrorTest, E10055) {
    LgsApp app;
    const auto code = R"(
    f(): Int {}
    main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10055, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10055.errCode);
    }
}

TEST(SemaErrorTest, Er0056A) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
        a: Int
    }
    main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10056, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10056.errCode);
    }
}

TEST(SemaErrorTest, Er0056B) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
        a() {}
    }
    main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10056, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10056.errCode);
    }
}

TEST(SemaErrorTest, E10058) {
    LgsApp app;
    const auto code = R"(
        interface Inter { x: Int }
        interface Inter2 { x: Int }
        object Obj2 {
            implements: Inter, Inter2
            x: Int
        }
        main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 2);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10058.errCode);
    }
    EXPECT_EQ(app.errHandler.errors[1].errCode, E10058.errCode);
}

TEST(SemaErrorTest, E10059) {
    LgsApp app;
    const auto code = R"(
    func(): Int {
        if true {
            return 1
            return 2
        }
        for i in 0..10 {
            break
            return i
        }
        return 3
    }
    main() {}
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 2);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10059.errCode);
    }
    EXPECT_EQ(app.errHandler.errors[1].errCode, E10059.errCode);
}

TEST(SemaErrorTest, E10064) {
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
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 2);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10064.errCode);
    }
    EXPECT_EQ(app.errHandler.errors[1].errCode, E10064.errCode);
}

TEST(SemaErrorTest, E10066) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 0
        while a {
            a++
        }
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10066, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10066.errCode);
    }
}

TEST(SemaErrorTest, E10076) {
    LgsApp app;
    const auto code = R"(
    main() {
        v1 = vec3(.23, .578, .17)
        v2 = vec2(.32, .38)
        v3 = v1 + v2
        v4 = v1 - v2
        v5 = v1 * v2
        v6 = v1 / v2
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 4) << EXPECTED_ERR(E10076, code);
    for (const auto& error : app.errHandler.errors) {
        EXPECT_EQ(error.errCode, E10076.errCode);
    }
}

TEST(SemaErrorTest, E10089) {
    LgsApp app;
    const auto code = R"(
    object Singleton {
        x: Int
    }
    main() {
        Singleton.x := 23
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10089, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10089.errCode);
    }
}

TEST(SemaErrorTest, E10092) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 34 then "3" else "6"
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10092, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10092.errCode);
    }
}

TEST(SemaErrorTest, E10097) {
    LgsApp app;
    const auto code = R"(
    main() {
        switch 2 {}
    }
    )";
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    EXPECT_EQ(app.errHandler.errors.size(), 1) << EXPECTED_ERR(E10097, code);
    if (app.errHandler.errors.size() > 0) {
        EXPECT_EQ(app.errHandler.errors[0].errCode, E10097.errCode);
    }
}