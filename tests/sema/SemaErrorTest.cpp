#define DOCTEST_CONFIG_IMPLEMENT
#include "external/doctest.h"
#include "logos/LgsApp.h"
#include "utils/LgsUtils.h"

TEST_CASE("Sema10000") {
    LgsApp app;
    const auto code = R"(
    func() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10000, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10000.code);
    }
}

TEST_CASE("Sema10001A") {
    LgsApp app;
    const auto code = R"(
    main() {
        s1: Str[2] = [["adi"], ["roi"]]
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10001, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10001.code);
    }
}

TEST_CASE("Sema10002A") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 6
        for i in a {}
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10002, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10002.code);
    }
}

TEST_CASE("Sema10002B") {
    LgsApp app;
    const auto code = R"(
    main() {
        num = 1
        a = num[1:3]
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10002, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10002.code);
    }
}

TEST_CASE("Sema10003") {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[2]
        arr[3] := 2
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10048, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10048.code);
    }
}

TEST_CASE("Sema10004") {
    LgsApp app;
    const auto code = R"(
    f(): Int {
        return "str"
    }
    main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10004, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10004.code);
    }
}

TEST_CASE("Sema10005A") {
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
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10005, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10005.code);
    }
}

TEST_CASE("Sema10005B") {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj{a = 3487, b = 234}
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10005, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10005.code);
    }
}

TEST_CASE("Sema10006A") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = b
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10006, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10006.code);
    }
}

TEST_CASE("Sema10006B") {
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
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10006, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10006.code);
    }
}

TEST_CASE("Sema10011A") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 2
        a = 3
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10011, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10011.code);
    }
}

TEST_CASE("Sema10013A") {
    LgsApp app;
    const auto code = R"(
    object Obj {a: Int}
    main() {
        obj = Obj{}
        obj.func()
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10005, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10005.code);
    }
}

TEST_CASE("Sema10013B") {
    LgsApp app;
    const auto code = R"(
    main() {
        arr: Int[34]
        arr.add(2)
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10005, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10005.code);
    }
}

TEST_CASE("Sema10014") {
    LgsApp app;
    const auto code = R"(
    main() {
        switch "str" {
            1: {  }
        }
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10014, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10014.code);
    }
}

TEST_CASE("Sema10015A") {
    LgsApp app;
    const auto code = R"(
    func(a: Int) { }
    main() {
        func("str")
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10015, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10015.code);
    }
}

TEST_CASE("Sema10015B") {
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
        owner obj2 = Obj2{}
        func(obj2.obj1)
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    // CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10015, code));
    if (app.errHandler.errors.size() > 0) {
        // CHECK_EQ(app.errHandler.errors[0].errCode, E10015.errCode);
    }
}

TEST_CASE("Sema10016A") {
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
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10016, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10016.code);
    }
}

TEST_CASE("Sema10016B") {
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
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_EQ(app.errHandler.errors.size(), 1);
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10016.code);
    }
}

TEST_CASE("Sema10017") {
    LgsApp app;
    const auto code = R"(
    main() {
        break
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10017, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10017.code);
    }
}

TEST_CASE("Sema10018") {
    LgsApp app;
    const auto code = R"(
    main() {
        s2: Int[] = [2.234, 2.34]
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10001, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10001.code);
    }
}

TEST_CASE("Sema10021") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = true then "3" else 6
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10021, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10021.code);
    }
}

TEST_CASE("Sema10022") {
    LgsApp app;
    const auto code = R"(
    main() {
        var = 2
        a = var{}
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10022, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10022.code);
    }
}

TEST_CASE("Sema10023") {
    LgsApp app;
    const auto code = R"(
    main() {
        a: Int = null
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10023, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10023.code);
    }
}

TEST_CASE("Sema10024") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = null
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10024, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10024.code);
    }
}

TEST_CASE("Sema10025") {
    LgsApp app;
    const auto code = R"(
    object Obj {
        implements: Int
    }
    main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10025, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10025.code);
    }
}

TEST_CASE("Sema10026") {
    LgsApp app;
    const auto code = R"(
    func(): Int { return }
    main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10026, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10026.code);
    }
}

TEST_CASE("Sema10027") {
    LgsApp app;
    const auto code = R"(
    fun(): Int { return 2 }
    fun2() {
        return fun()
    }
    main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10027, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10027.code);
    }
}

TEST_CASE("Sema10028") {
    LgsApp app;
    const auto code = R"(
    func(x: Int = 23, y: Str) { }
    main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10028, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10028.code);
    }
}

TEST_CASE("Sema10030A") {
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
    app.loadSrcFile(code1, "Obj1.lgs");
    assert(app.errHandler.successful);
    app.loadSrcFile(code2, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10030, code1));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10030.code);
    }
}

TEST_CASE("Sema10030B") {
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
    app.loadSrcFile(code1, "Obj1.lgs");
    assert(app.errHandler.successful);
    app.loadSrcFile(code2, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10030, code1));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10030.code);
    }
}

TEST_CASE("Sema10031") {
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
    app.loadSrcFile(code1, "Obj1.lgs");
    assert(app.errHandler.successful);
    app.loadSrcFile(code2, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10031, code1));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10031.code);
    }
}

TEST_CASE("Sema10032") {
    LgsApp app;
    const auto code = R"(
    single Obj {
        func() {}
    }
    main() {
        obj = Obj{}
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10032, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10032.code);
    }
}

TEST_CASE("Sema10038") {
    LgsApp app;
    const auto code = R"(
    main() {
        continue
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10038, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10038.code);
    }
}

TEST_CASE("Sema10042") {
    LgsApp app;
    const auto code = R"(
    main() {
        map: {Str: Str}
        a = map[1:3]
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10042, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10042.code);
    }
}

TEST_CASE("Sema10046") {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
    }
    main() {
        obj = Obj()
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10046, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10046.code);
    }
}

TEST_CASE("Sema10055") {
    LgsApp app;
    const auto code = R"(
    f(): Int {}
    main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10055, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10055.code);
    }
}

TEST_CASE("Sema10056A") {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
        a: Int
    }
    main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10056, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10056.code);
    }
}

TEST_CASE("Sema10056B") {
    LgsApp app;
    const auto code = R"(
    object Obj {
        a: Int
        a() {}
    }
    main() {}
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10056, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10056.code);
    }
}

TEST_CASE("Sema10059") {
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
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_EQ(app.errHandler.errors.size(), 2);
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10059.code);
    }
    CHECK_EQ(app.errHandler.errors[1].errCode, E10059.code);
}

TEST_CASE("Sema10066") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 0
        while a {
            a++
        }
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10066, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10066.code);
    }
}

TEST_CASE("Sema10076") {
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
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 4, EXPECTED_ERR(E10076, code));
    for (const auto& error : app.errHandler.errors) {
        CHECK_EQ(error.errCode, E10076.code);
    }
}

TEST_CASE("Sema10089") {
    LgsApp app;
    const auto code = R"(
    object Singleton {
        x: Int
    }
    main() {
        Singleton.x := 23
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10089, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10089.code);
    }
}

TEST_CASE("Sema10092") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 34 then "3" else "6"
    }
    )";
    app.loadSrcFile(code, "Main.lgs");
    assert(app.errHandler.successful);
    app.analyse();
    CHECK_MESSAGE(app.errHandler.errors.size() == 1, EXPECTED_ERR(E10092, code));
    if (app.errHandler.errors.size() > 0) {
        CHECK_EQ(app.errHandler.errors[0].errCode, E10092.code);
    }
}