#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgDeferTest, Test1) {
    const auto code = R"(
    func(str: Str) {
        print(str)
    }
    main() {
        if true {
            defer func("after")
        } else {
            defer func("after")
        }
        defer func("after")
        print("before")
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "before");
    EXPECT_EQ(lines[1], "after");
    EXPECT_EQ(lines[2], "after");
}
