#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgStrTest, Test1) {
    const auto code = R"(
    main() {
        hello = "Hello "
        world = "world"
        mut hello2 = "Hello "
        mut world2 = "world"
        print("Hello world")
        print("Hello" + " world")
        print("He" + "llo" + " world")
        print(hello + world)
        print("Hello " + world)
        print(hello + "world")
        print(hello2 + world2)
        print("Hello " + world2)
        print(hello2 + "world")
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 9);
    for (auto line : lines) EXPECT_EQ(line, "Hello world");
}
