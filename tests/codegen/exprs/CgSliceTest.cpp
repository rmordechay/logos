#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgSliceTest, Test1) {
    const auto code = R"(
    main() {
        t = "text"
        print(t[0:4])
        print(t[1:3])
        print(t[2:2])
        print(t[3:4])
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 4);
    EXPECT_EQ(lines[0], "text");
    EXPECT_EQ(lines[1], "ex");
    EXPECT_EQ(lines[2], "\"\"");
    EXPECT_EQ(lines[3], "t");
}