#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgFuncCallTest, Test1) {
    const auto code = R"(
    func(x: Int, y: Int): Int {
        return x - y
    }

    main() {
        print(func(5, 3))
        print(func(x=5, y=3))
        print(func(y=5, x=3))
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "2");
    EXPECT_EQ(lines[2], "-2");
}

TEST(CgFuncCallTest, Test2) {
    const auto code = R"(
    func(x: Int = 3) {
        print(x)
    }
    main() {
        func()
        func(2)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "3");
    EXPECT_EQ(lines[1], "2");
}

TEST(CgFuncCallTest, Test3) {
    const auto code = R"(
    func(x: Int = 3, y: Str = "text") {
        print(x)
        print(y)
    }
    main() {
        func()
        func(2)
        func(4, "other text")
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 6);
    EXPECT_EQ(lines[0], "3");
    EXPECT_EQ(lines[1], "text");
    EXPECT_EQ(lines[2], "2");
    EXPECT_EQ(lines[3], "text");
    EXPECT_EQ(lines[4], "4");
    EXPECT_EQ(lines[5], "other text");
}
