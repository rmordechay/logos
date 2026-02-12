#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgStrTest, Test1) {
    const auto code = R"(
    main() {
        print("Hello world")
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "Hello world");
}