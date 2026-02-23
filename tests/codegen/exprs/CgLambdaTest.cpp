#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgLambdaTest, Test1) {
    const auto code = R"(
    main() {
        f1: (Int): Void = x => print(x)
        f2: (Float, Float): Void = (x, y) => print(x + y)
        f3: (Str): Void = (x) => print(x)
        f1(2)
        f2(2.43, .34)
        f3("text")
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "2.770");
    EXPECT_EQ(lines[2], "text");
}

TEST(CgLambdaTest, Test2) {
    const auto code = R"(
    func(f: (Int): Void) {
        f(2)
    }
    func2(x: Int): Void {
        print(x + 2)
    }
    main() {
        func(x => print(x + 2))
        func(func2)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "4");
}

TEST(CgLambdaTest, Test3) {
    const auto code = R"(
    func(f: (Int): Void) {
        f(2)
    }
    main() {
        func({print(it)})
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "2");
}
