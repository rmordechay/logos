#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgArraysTest, DArrTest1) {
    const auto code = R"(
    object Obj {
        x: Int
    }

    main() {
        arr = [1, 2]
        print(arr)
        arr.add(3)
        print(arr)
        arr.add(4)
        print(arr)

        arr2: Obj[]
        print(arr2)
        arr2.add(Obj{x=2})
        print(arr2)

        arr3: Int[][]
        print(arr3)
        arr3.add([23])
        print(arr3)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 7);
    EXPECT_EQ(lines[0], "[1, 2]");
    EXPECT_EQ(lines[1], "[1, 2, 3]");
    EXPECT_EQ(lines[2], "[1, 2, 3, 4]");
    EXPECT_EQ(lines[3], "[]");
    EXPECT_EQ(lines[4], "[Obj{x=2}]");
    EXPECT_EQ(lines[5], "[]");
    EXPECT_EQ(lines[6], "[[23]]");
}

TEST(CgArraysTest, DArrTest2) {
    const auto code = R"(
    main() {
        arr1: Int[] = [1, 2]
        arr2: Int[][] = [[1], [2]]
        arr3: Int[][][] = [[[1]], [[2]]]
        print(arr1)
        print(arr2)
        print(arr3)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "[1, 2]");
    EXPECT_EQ(lines[1], "[[1], [2]]");
    EXPECT_EQ(lines[2], "[[[1]], [[2]]]");
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
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "[1, 2]");
    EXPECT_EQ(lines[1], "[3, 2]");
    EXPECT_EQ(lines[2], "[3, 4]");
}

TEST(CgArraysTest, SArrTest2) {
    const auto code = R"(
    main() {
        arr1: Int[2] = [1, 2]
        arr2: Int[2][2] = [[1], [2]]
        arr3: Int[2][2][2] = [[[1]], [[2]]]
        print(arr1)
        print(arr2)
        print(arr3)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "[1, 2]");
    EXPECT_EQ(lines[1], "[[1, 0], [2, 0]]");
    EXPECT_EQ(lines[2], "[[[1, 0], [0, 0]], [[2, 0], [0, 0]]]");
}

TEST(CgArraysTest, SArrTest3) {
    const auto code = R"(
    func(): Int[3] {
        return [1, 2, 3]
    }
    main() {
        print(func())
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "[1, 2, 3]");
}

TEST(CgArraysTest, SArrTest4) {
    const auto code = R"(
    main() {
        arr: Int[2][2][2]
        print(arr)
        arr[0][0][0] := 1
        print(arr)
        arr[0][0][1] := 1
        print(arr)
        arr[0][0][0] := 1
        print(arr)
        arr[0][1][0] := 1
        print(arr)
        arr[0][0][0] := 1
        print(arr)
        arr[1][1][1] := 1
        print(arr)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 7);
    EXPECT_EQ(lines[0], "[[[0, 0], [0, 0]], [[0, 0], [0, 0]]]");
    EXPECT_EQ(lines[1], "[[[1, 0], [0, 0]], [[0, 0], [0, 0]]]");
    EXPECT_EQ(lines[2], "[[[1, 1], [0, 0]], [[0, 0], [0, 0]]]");
    EXPECT_EQ(lines[3], "[[[1, 1], [0, 0]], [[0, 0], [0, 0]]]");
    EXPECT_EQ(lines[4], "[[[1, 1], [1, 0]], [[0, 0], [0, 0]]]");
    EXPECT_EQ(lines[5], "[[[1, 1], [1, 0]], [[0, 0], [0, 0]]]");
    EXPECT_EQ(lines[6], "[[[1, 1], [1, 0]], [[0, 0], [0, 1]]]");
}

TEST(CgArraysTest, SArrTest5) {
    const auto code = R"(
    object Obj {
        func(arr: Int[3]): Int[3] {
            return arr
        }
    }
    func(arr: Int[3]): Int[3] {
        return arr
    }
    main() {
        print(func([1, 2]))
        print(Obj.func([1, 2]))
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "[1, 2, 0]");
    EXPECT_EQ(lines[1], "[1, 2, 0]");
}
