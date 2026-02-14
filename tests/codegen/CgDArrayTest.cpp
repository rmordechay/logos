#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgDArrTest, Test1) {
    const auto code = R"(
    main() {
        arr = [1, 2]
        print(arr)
        arr.add(3)
        print(arr)
        arr.add(4)
        print(arr)
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "[1, 2]");
    EXPECT_EQ(lines[1], "[1, 2, 3]");
    EXPECT_EQ(lines[2], "[1, 2, 3, 4]");
}
