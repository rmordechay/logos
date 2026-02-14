#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgIfStmtTest, Test1) {
    const auto code = R"(
    main() {
        a = 5
        if a > 5 {
            print(true)
        }
        if a < 5 {
            print(true)
        }
        if a == 5 {
            print(true)
        }
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "true");
}

TEST(CgIfStmtTest, Test2) {
    const auto code = R"(
    main() {
        a = 5
        if a > 5 {
            print(true)
        } else {
            print(false)
        }
        if a < 5 {
            print(true)
        } else {
            print(false)
        }
        if a == 5 {
            print(true)
        } else {
            print(false)
        }
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "false");
    EXPECT_EQ(lines[1], "false");
    EXPECT_EQ(lines[2], "true");
}

TEST(CgIfStmtTest, Test3) {
    const auto code = R"(
    main() {
        a = 5.3
        if a > 5.3 {
            print(false)
        } else if a < 5.3 {
            print(false)
        } else {
            print(false)
        }
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "false");
}
