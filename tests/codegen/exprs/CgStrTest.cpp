#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgStrTest, Test1) {
    const auto code = R"(
    main() {
        hello = "Hello "
        world = "world"
        print("Hello world")
        print("Hello" + " world")
        print("He" + "llo" + " world")
        print(hello + world)
        print("Hello " + world)
        print(hello + "world")
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 6);
    for (auto line : lines) EXPECT_EQ(line, "Hello world");
}

TEST(CgStrTest, Test2) {
    const auto code = R"(
    main() {
        mut hello = "Hello "
        mut world = "world"
        print(hello + world)
        print("Hello " + world)
        print(hello + "world")
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    for (auto line : lines) EXPECT_EQ(line, "Hello world");
}

TEST(CgStrTest, Test3) {
    const auto code = R"(
    main() {
        print("".len())
        print("text".len())
        print("".isEmpty())
        print("".isNotEmpty())
        print("text".isEmpty())
        print("text".isNotEmpty())
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 6);
    EXPECT_EQ(lines[0], "0");
    EXPECT_EQ(lines[1], "4");
    EXPECT_EQ(lines[2], "true");
    EXPECT_EQ(lines[3], "false");
    EXPECT_EQ(lines[4], "false");
    EXPECT_EQ(lines[5], "true");
}

TEST(CgStrTest, Test4) {
    const auto code = R"(
    main() {
        print("Hello world")
        print('Hello world')
        print('"Hello" world')
        print("'Hello' world")
        print("""
    Hello world
""")
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 7);
    EXPECT_EQ(lines[0], "Hello world");
    EXPECT_EQ(lines[1], "Hello world");
    EXPECT_EQ(lines[2], "\"Hello\" world");
    EXPECT_EQ(lines[3], "'Hello' world");
    EXPECT_EQ(lines[4], "");
    EXPECT_EQ(lines[5], "    Hello world");
    EXPECT_EQ(lines[6], "");
}
