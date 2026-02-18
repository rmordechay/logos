#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgHashMapTest, Test1) {
    const auto code = R"(
    main() {
        map: {Str: Str}
        map["key"] := "value"
        print(map)
        print(map["key"])
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "{key: value}");
    EXPECT_EQ(lines[1], "value");
}
