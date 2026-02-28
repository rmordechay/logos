#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgZeroValueTest, Test1) {
    const auto code = R"(
    main() {
        bool: Bool
        byte: Byte
        short: Short
        int: Int
        long: Long
        uByte: UByte
        uShort: UShort
        uInt: UInt
        uLong: ULong
        size: Size
        char: Char
        str: Str
        print(bool)
        print(byte)
        print(short)
        print(int)
        print(long)
        print(uByte)
        print(uShort)
        print(uInt)
        print(uLong)
        print(size)
        print(char)
        print(str)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 12);
    EXPECT_EQ(lines[0], "false");
    EXPECT_EQ(lines[1], "0");
    EXPECT_EQ(lines[2], "0");
    EXPECT_EQ(lines[3], "0");
    EXPECT_EQ(lines[4], "0");
    EXPECT_EQ(lines[5], "0");
    EXPECT_EQ(lines[6], "0");
    EXPECT_EQ(lines[7], "0");
    EXPECT_EQ(lines[8], "0");
    EXPECT_EQ(lines[9], "0");
    EXPECT_EQ(lines[10], "'0'");
    EXPECT_EQ(lines[11], "\"\"");
}

TEST(CgZeroValueTest, Test2) {
    const auto code = R"(
    object Obj {
        bool: Bool
        byte: Byte
        short: Short
        int: Int
        long: Long
        uByte: UByte
        uShort: UShort
        uInt: UInt
        uLong: ULong
        size: Size
        char: Char
        str: Str
    }
    main() {
        obj = Obj{}
        print(obj.bool)
        print(obj.byte)
        print(obj.short)
        print(obj.int)
        print(obj.long)
        print(obj.uByte)
        print(obj.uShort)
        print(obj.uInt)
        print(obj.uLong)
        print(obj.size)
        print(obj.char)
        print(obj.str)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 12);
    EXPECT_EQ(lines[0], "false");
    EXPECT_EQ(lines[1], "0");
    EXPECT_EQ(lines[2], "0");
    EXPECT_EQ(lines[3], "0");
    EXPECT_EQ(lines[4], "0");
    EXPECT_EQ(lines[5], "0");
    EXPECT_EQ(lines[6], "0");
    EXPECT_EQ(lines[7], "0");
    EXPECT_EQ(lines[8], "0");
    EXPECT_EQ(lines[9], "0");
    EXPECT_EQ(lines[10], "'0'");
    EXPECT_EQ(lines[11], "\"\"");
}

TEST(CgZeroValueTest, Test3) {
    const auto code = R"(
    object Obj1 {
        obj2: Obj2
    }
    object Obj2 {
        obj3: Obj3
    }
    object Obj3 {
        obj4: Obj4
    }
    object Obj4 {
        x: Str
        y: Int
    }
    main() {
        obj1 = Obj1{}
        print(obj1)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "Obj1{obj2=Obj2{obj3=Obj3{obj4=Obj4{x=\"\", y=0}}}}");
}
