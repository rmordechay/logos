#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgUnaryExprTest, PostfixExprTest) {
    const auto code = R"(
    main() {
        mut a = 1
        a++
        print(a)
        a--
        print(a)
        print(a++)
        print(a--)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 4);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "1");
    EXPECT_EQ(lines[2], "2");
    EXPECT_EQ(lines[3], "1");
}

TEST(CgUnaryExprTest, PrefixExprTest) {
    const auto code = R"(
    main() {
        a = not false
        b = not true
        print(a)
        print(b)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "true");
    EXPECT_EQ(lines[1], "false");
}
