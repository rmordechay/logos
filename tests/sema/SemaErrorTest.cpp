#define DOCTEST_CONFIG_IMPLEMENT
#include "external/doctest.h"
#include "logos/LgsApp.h"
#include "utils/LgsUtils.h"

TEST_CASE("TestSema10000") {
    LgsApp app;
    const auto code = R"(
    func() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10000, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10000.errCode);
}

TEST_CASE("TestSema10002A") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 6
        for i in a {}
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10002, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10002.errCode);
}

TEST_CASE("TestSema10002B") {
    LgsApp app;
    const auto code = R"(
    main() {
        num = 1
        a = num[1:3]
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10002, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10002.errCode);
}

TEST_CASE("TestSema10003") {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[2]!
        arr[3] := 2
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10003, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10003.errCode);
}

TEST_CASE("TestSema10004") {
    LgsApp app;
    const auto code = R"(
    f(): Int {
        return "str"
    }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10004, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10004.errCode);
}

TEST_CASE("TestSema10005A") {
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
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10005, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
}

TEST_CASE("TestSema10005B") {
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
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10005, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
}

TEST_CASE("TestSema10006A") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = b
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10006, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10006.errCode);
}

TEST_CASE("TestSema10006B") {
    LgsApp app;
    const auto code = R"(
    enum Enum {
        ENUM1
    }
    func(x: Int, e: Enum) {
        if e {
            ENUM1: {}
        }
        a = ENUM1
    }
    main() {
        func(10, Enum.ENUM1)
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10006, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10006.errCode);
}

TEST_CASE("TestSema10011A") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 2
        a = 3
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10011, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10011.errCode);
}

TEST_CASE("TestSema10011B") {
    LgsApp app;
    const auto code = R"(
    func() {}
    func() {}
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10011, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10011.errCode);
}

TEST_CASE("TestSema10013A") {
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
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10005, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
}

TEST_CASE("TestSema10013B") {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[34]!
        arr.add(2)
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10005, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10005.errCode);
}

TEST_CASE("TestSema10014") {
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
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10014, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10014.errCode);
}

TEST_CASE("TestSema10015") {
    LgsApp app;
    const auto code = R"(
    func(a: Int) { }
    main() {
        func("str")
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10015, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10015.errCode);
}

TEST_CASE("TestSema10016A") {
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
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10016, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10016.errCode);
}

TEST_CASE("TestSema10016B") {
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
    CHECK_EQ(app.errHandler.errors.size(), 2);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10016.errCode);
    CHECK_EQ(app.errHandler.errors[1].errCode, E10016.errCode);
}

TEST_CASE("TestSema10017") {
    LgsApp app;
    const auto code = R"(
    main() {
        break
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10017, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10017.errCode);
}

TEST_CASE("TestSema10022") {
    LgsApp app;
    const auto code = R"(
    main() {
        var = 2
        a = var{}
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10022, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10022.errCode);
}

TEST_CASE("TestSema10023") {
    LgsApp app;
    const auto code = R"(
    main() {
        a: Int = null
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10023, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10023.errCode);
}

TEST_CASE("TestSema10024") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = null
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10024, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10024.errCode);
}

TEST_CASE("TestSema10025") {
    LgsApp app;
    const auto code = R"(
    object Obj {
        implements: Int
    }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10025, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10025.errCode);
}

TEST_CASE("TestSema10026") {
    LgsApp app;
    const auto code = R"(
    func(): Int { return }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10026, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10026.errCode);
}

TEST_CASE("TestSema10027") {
    LgsApp app;
    const auto code = R"(
    fun(): Int { return 2 }
    fun2() {
        return fun()
    }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10027, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10027.errCode);
}

TEST_CASE("TestSema10028") {
    LgsApp app;
    const auto code = R"(
    func(x: Int = 23, y: Str) { }
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10028, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10028.errCode);
}

TEST_CASE("TestSema10030A") {
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
    app.parseSrcFile(code1);
    app.parseSrcFile(code2);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10030, code1));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10030.errCode);
}

TEST_CASE("TestSema10030B") {
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
    app.parseSrcFile(code1);
    app.parseSrcFile(code2);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10030, code1));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10030.errCode);
}

TEST_CASE("TestSema10031") {
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
    app.parseSrcFile(code1);
    app.parseSrcFile(code2);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10031, code1));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10031.errCode);
}

TEST_CASE("TestSema10032") {
    LgsApp app;
    const auto code = R"(
    single Obj {
        func() {}
    }
    main() {
        obj = Obj{}
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10032, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10032.errCode);
}

TEST_CASE("TestSema10038") {
    LgsApp app;
    const auto code = R"(
    main() {
        continue
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10038, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10038.errCode);
}

TEST_CASE("TestSema10042") {
    LgsApp app;
    const auto code = R"(
    main() {
        map: {Str: Str}
        a = map[1:3]
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10042, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10042.errCode);
}

TEST_CASE("TestSema10046") {
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
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10046, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10046.errCode);
}

TEST_CASE("TestSema10048A") {
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
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10048, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10048.errCode);
}

TEST_CASE("TestSema10048B") {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[]!
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10048, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10048.errCode);
}

TEST_CASE("TestSema10055") {
    LgsApp app;
    const auto code = R"(
    f(): Int {}
    main() {}
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10055, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10055.errCode);
}

TEST_CASE("TestSema10056A") {
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
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10056, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10056.errCode);
}

TEST_CASE("TestSema10056B") {
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
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10056, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10056.errCode);
}

TEST_CASE("TestSema10059") {
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
    app.parseSrcFile(code);
    app.analyse();
    CHECK_EQ(app.errHandler.errors.size(), 2);
    CHECK_EQ(app.errHandler.errors[0].errCode, E10059.errCode);
    CHECK_EQ(app.errHandler.errors[1].errCode, E10059.errCode);
}

TEST_CASE("TestSema10066") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 0
        while a {
            a++
        }
    }
    )";
    app.parseSrcFile(code);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10066, code));
    CHECK_EQ(app.errHandler.errors[0].errCode, E10066.errCode);
}
