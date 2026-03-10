#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgSwitchTest, Test1) {
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

TEST(CgSwitchTest, Test2) {
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
