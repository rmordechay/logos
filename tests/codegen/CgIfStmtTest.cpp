#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgIfStmtTest, Test1) {
    const auto code = R"(
    main() {
        a = 5
        if a > 5 {
            print(false)
        } else {
            print(true)
        }
        if a < 5 {
            print(true)
        } else {
            print(false)
        }
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "true");
    EXPECT_EQ(lines[1], "false");
}
