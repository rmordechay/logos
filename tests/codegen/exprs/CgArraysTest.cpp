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

TEST(CgArraysTest, SArrTest3) {
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

TEST(CgArraysTest, IterableLengthTest1) {
    const auto code = R"(
    main() {
        str = "text"
        list = ["text", "text"]
        list2: Str[2] = ["text", "text"]
        vec = Vec3()
        map = {"text": "text"}
        print(str.len())
        print(list.len())
        print(list2.len())
        print(vec.len())
        print(map.len())
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 5);
    EXPECT_EQ(lines[0], "4");
    EXPECT_EQ(lines[1], "2");
    EXPECT_EQ(lines[2], "2");
    EXPECT_EQ(lines[3], "3");
    EXPECT_EQ(lines[4], "1");
}

TEST(CgArraysTest, IterableIsEmptyTest1) {
    const auto code = R"(
    main() {
        str = "text"
        list = ["text", "text"]
        list2: Str[2] = ["text", "text"]
        vec = Vec3()
        map = {"text": "text"}
        print(str.isEmpty())
        print(list.isEmpty())
        print(list2.isEmpty())
        print(vec.isEmpty())
        print(map.isEmpty())
        print(str.isNotEmpty())
        print(list.isNotEmpty())
        print(list2.isNotEmpty())
        print(vec.isNotEmpty())
        print(map.isNotEmpty())
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 10);
    EXPECT_EQ(lines[0], "false");
    EXPECT_EQ(lines[1], "false");
    EXPECT_EQ(lines[2], "false");
    EXPECT_EQ(lines[3], "false");
    EXPECT_EQ(lines[4], "false");
    EXPECT_EQ(lines[5], "true");
    EXPECT_EQ(lines[6], "true");
    EXPECT_EQ(lines[7], "true");
    EXPECT_EQ(lines[8], "true");
    EXPECT_EQ(lines[9], "true");
}
