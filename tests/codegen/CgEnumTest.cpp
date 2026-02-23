#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgEnumTest, Test1) {
    const auto code = R"(
    enum Enum {
        ENUM1 = "value1"
        ENUM2 = "value2"
        ENUM3 = "value3"
    }
    main() {
        e = Enum.ENUM1
        print(e.index())
        print(Enum.ENUM1.index())
        print(Enum.ENUM2.index())
        print(Enum.ENUM3.index())

        print(e.value())
        print(Enum.ENUM1.value())
        print(Enum.ENUM2.value())
        print(Enum.ENUM3.value())
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 8);
    EXPECT_EQ(lines[0], "0");
    EXPECT_EQ(lines[1], "0");
    EXPECT_EQ(lines[2], "1");
    EXPECT_EQ(lines[3], "2");
    EXPECT_EQ(lines[4], "value1");
    EXPECT_EQ(lines[5], "value1");
    EXPECT_EQ(lines[6], "value2");
    EXPECT_EQ(lines[7], "value3");
}

TEST(CgEnumTest, Test2) {
    const auto code = R"(
    enum Enum {
        ENUM1
        ENUM2
        ENUM3
    }
    main() {
        e = Enum.ENUM1
        switch e {
            ENUM1: {print(e)}
            ENUM2: {print(e)}
            ENUM3: {print(e)}
            else: {print("else")}
        }
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "ENUM1");
}

TEST(CgEnumTest, Test3) {
    const auto code = R"(
    main() {
        e = "text2"
        switch e {
            "text1": {print(e)}
            "text2": {print(e)}
            "text3": {print(e)}
            else: {print("else")}
        }
        e2 = "text4"
        switch e2 {
            "text1": {print(e)}
            "text2": {print(e)}
            "text3": {print(e)}
            else: {print("else")}
        }
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "text2");
    EXPECT_EQ(lines[1], "else");
}
