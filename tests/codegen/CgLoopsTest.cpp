#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgLoopsTest, Test1) {
    const auto code = R"(
    main() {
        for 3 {
            print(for.i)
        }
        for i in  0..3 {
            print(i)
        }
        for i in  ..3 {
            print(i)
        }
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 9);
    EXPECT_EQ(lines[0], "0");
    EXPECT_EQ(lines[1], "1");
    EXPECT_EQ(lines[2], "2");
    EXPECT_EQ(lines[3], "0");
    EXPECT_EQ(lines[4], "1");
    EXPECT_EQ(lines[5], "2");
    EXPECT_EQ(lines[6], "0");
    EXPECT_EQ(lines[7], "1");
    EXPECT_EQ(lines[8], "2");
}

TEST(CgLoopsTest, Test2) {
    const auto code = R"(
    main() {
        for i in  5..10 {
            print(i)
        }
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 5);
    EXPECT_EQ(lines[0], "5");
    EXPECT_EQ(lines[1], "6");
    EXPECT_EQ(lines[2], "7");
    EXPECT_EQ(lines[3], "8");
    EXPECT_EQ(lines[4], "9");
}

TEST(CgLoopsTest, Test3) {
    const auto code = R"(
    func(arr: Int[]): Int {
        for arr {
            print(for.i)
            print(for.element)
        }
        return arr[0]
    }
    main() {
        arr = func([1, 2, 3])
        print(arr)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 7);
    EXPECT_EQ(lines[0], "0");
    EXPECT_EQ(lines[1], "1");
    EXPECT_EQ(lines[2], "1");
    EXPECT_EQ(lines[3], "2");
    EXPECT_EQ(lines[4], "2");
    EXPECT_EQ(lines[5], "3");
    EXPECT_EQ(lines[6], "1");
}

TEST(CgLoopsTest, Test4) {
    const auto code = R"(
    main() {
        for i in  0..2 {
            print(i)
            for j in  5..7 {
                print(j)
            }
        }
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 6);
    EXPECT_EQ(lines[0], "0");
    EXPECT_EQ(lines[1], "5");
    EXPECT_EQ(lines[2], "6");
    EXPECT_EQ(lines[3], "1");
    EXPECT_EQ(lines[4], "5");
    EXPECT_EQ(lines[5], "6");
}

TEST(CgLoopsTest, Test5) {
    const auto code = R"(
    main() {
        a = [1, 2]
        b = ["text1", "text2"]
        for i in a {
            print(for.i)
            print(for.element)
            for j in b {
                print(for.i)
                print(for.element)
            }
        }
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 12);
    EXPECT_EQ(lines[0], "0");
    EXPECT_EQ(lines[1], "1");
    EXPECT_EQ(lines[2], "0");
    EXPECT_EQ(lines[3], "text1");
    EXPECT_EQ(lines[4], "1");
    EXPECT_EQ(lines[5], "text2");
    EXPECT_EQ(lines[6], "1");
    EXPECT_EQ(lines[7], "2");
    EXPECT_EQ(lines[8], "0");
    EXPECT_EQ(lines[9], "text1");
    EXPECT_EQ(lines[10], "1");
    EXPECT_EQ(lines[11], "text2");
}

TEST(CgLoopsTest, Test6) {
    const auto code = R"(
    main() {
        a = ["text1", "text2"]
        for i, k in a {
            print(i)
            print(k)
        }
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 4);
    EXPECT_EQ(lines[0], "0");
    EXPECT_EQ(lines[1], "text1");
    EXPECT_EQ(lines[2], "1");
    EXPECT_EQ(lines[3], "text2");
}
