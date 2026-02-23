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

