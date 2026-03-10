#include <sstream>
#include <string>
#include <vector>

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

TEST(CgNullableTest, Test3) {
    const auto code = R"(
    main() {
        arr: Int?[4]
        arr2: Int[4]
        arr3: Int?[4][2]
        arr4: Int[4][2]
        print(arr)
        print(arr2)
        print(arr3)
        print(arr4)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 4);
    EXPECT_EQ(lines[0], "[null, null, null, null]");
    EXPECT_EQ(lines[1], "[0, 0, 0, 0]");
    EXPECT_EQ(lines[2], "[[null, null], [null, null], [null, null], [null, null]]");
    EXPECT_EQ(lines[3], "[[0, 0], [0, 0], [0, 0], [0, 0]]");
}
