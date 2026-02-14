#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgArraysTest, DArrTest1) {
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

TEST(CgArraysTest, SArrTest1) {
    const auto code = R"(
    main() {
        arr: Int[2] = [1, 2]
        print(arr)
        arr[0] := 3
        print(arr)
        arr[1] := 4
        print(arr)
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "[1, 2]");
    EXPECT_EQ(lines[1], "[3, 2]");
    EXPECT_EQ(lines[2], "[3, 4]");
}

TEST(CgArraysTest, SArrTest2) {
    const auto code = R"(
    func(): Int[3] {
        return [1, 2, 3]
    }
    main() {
        print(func())
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "[1, 2, 3]");
}
