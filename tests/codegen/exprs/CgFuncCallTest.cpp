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
