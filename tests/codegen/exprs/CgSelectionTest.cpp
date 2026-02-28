#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgSelectionTest, Test1) {
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
