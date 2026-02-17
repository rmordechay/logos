#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgNullableTest, Test1) {
    const auto code = R"(
    func(): Str? {
        mut a = "text"?
        return a
    }
    func2(): Str? {
        mut a = "text"?
        a := null
        return a
    }
    main() {
        print(func())
        print(func2())
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "text");
    EXPECT_EQ(lines[1], "null");
}
