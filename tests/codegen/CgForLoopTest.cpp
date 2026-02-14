#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgForLoopTest, Test1) {
    const auto code = R"(
    main() {
        for 3 {
            print(for.i)
        }
        for i in  0..3 {
            print(i)
        }
        for i in  ..3 {
            print(i)
        }
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 9);
    EXPECT_EQ(lines[0], "0");
    EXPECT_EQ(lines[1], "1");
    EXPECT_EQ(lines[2], "2");
    EXPECT_EQ(lines[3], "0");
    EXPECT_EQ(lines[4], "1");
    EXPECT_EQ(lines[5], "2");
    EXPECT_EQ(lines[6], "0");
    EXPECT_EQ(lines[7], "1");
    EXPECT_EQ(lines[8], "2");
}

TEST(CgForLoopTest, Test2) {
    const auto code = R"(
    main() {
        for i in  5..10 {
            print(i)
        }
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 5);
    EXPECT_EQ(lines[0], "5");
    EXPECT_EQ(lines[1], "6");
    EXPECT_EQ(lines[2], "7");
    EXPECT_EQ(lines[3], "8");
    EXPECT_EQ(lines[4], "9");
}
