#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgFuncTest, Test1) {
    const auto code = R"(
    func(x: Int, y: Int): Int {
        return x - y
    }

    main() {
        print(func(5, 3))
        print(func(x=5, y=3))
        print(func(y=5, x=3))
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "2");
    EXPECT_EQ(lines[2], "-2");
}

TEST(CgFuncTest, Test2) {
    const auto code = R"(
    func(x: Int = 3) {
        print(x)
    }
    main() {
        func()
        func(2)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "3");
    EXPECT_EQ(lines[1], "2");
}

TEST(CgFuncTest, Test3) {
    const auto code = R"(
    func(x: Int = 3, y: Str = "text") {
        print(x)
        print(y)
    }
    main() {
        func()
        func(2)
        func(4, "other text")
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 6);
    EXPECT_EQ(lines[0], "3");
    EXPECT_EQ(lines[1], "text");
    EXPECT_EQ(lines[2], "2");
    EXPECT_EQ(lines[3], "text");
    EXPECT_EQ(lines[4], "4");
    EXPECT_EQ(lines[5], "other text");
}

TEST(CgFuncTest, Test4) {
    const auto code = R"(
    main() {
        arr = [1, 2, 3]
        print(arr.map({ it + 5 }))
        print(arr.filter({ it < 5 }))
        print(arr.map({ it + 5 }).filter({ it > 6 }))
        arr.forEach({ print(it) })
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 6);
    EXPECT_EQ(lines[0], "[6, 7, 8]");
    EXPECT_EQ(lines[1], "[1, 2, 3]");
    EXPECT_EQ(lines[2], "[7, 8]");
    EXPECT_EQ(lines[3], "1");
    EXPECT_EQ(lines[4], "2");
    EXPECT_EQ(lines[5], "3");
}

TEST(CgFuncTest, Test5) {
    const auto code = R"(
    funcBool(x: Bool) {print(x)}
    funcByte(x: Byte) {print(x)}
    funcShort(x: Short) {print(x)}
    funcInt(x: Int) {print(x)}
    funcLong(x: Long) {print(x)}
    funcUInt(x: UInt) {print(x)}
    funcULong(x: ULong) {print(x)}
    funcSize(x: Size) {print(x)}
    funcChar(x: Char) {print(x)}
    funcStr(x: Str) {print(x)}

    main() {
        funcBool(false)
        funcByte(-4)
        funcShort(-65)
        funcInt(-56)
        funcLong(-235456)
        funcUInt(56)
        funcULong(235456)
        funcSize(34656)
        funcChar('R')
        funcStr("text")
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 10);
    EXPECT_EQ(lines[0], "false");
    EXPECT_EQ(lines[1], "-4");
    EXPECT_EQ(lines[2], "-65");
    EXPECT_EQ(lines[3], "-56");
    EXPECT_EQ(lines[4], "-235456");
    EXPECT_EQ(lines[5], "56");
    EXPECT_EQ(lines[6], "235456");
    EXPECT_EQ(lines[7], "34656");
    EXPECT_EQ(lines[8], "'R'");
    EXPECT_EQ(lines[9], "text");
}
