#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgNullableTest, Test1) {
    const auto code = R"(
    main() {
        a = 1?
        b = "text"?
        c: Int? = null
        print(a)
        print(b)
        print(c)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "1");
    EXPECT_EQ(lines[1], "text");
    EXPECT_EQ(lines[2], "null");
}

TEST(CgNullableTest, Test2) {
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
    func3(x: Int?) {
        print(x)
    }
    main() {
        print(func())
        print(func2())
        func3(3)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "text");
    EXPECT_EQ(lines[1], "null");
    EXPECT_EQ(lines[2], "3");
}
