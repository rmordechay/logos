#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgHashMapTest, Test1) {
    const auto code = R"(
    main() {
        map: {Str: Str}
        map["key"] := "value"
        print(map)
        map["key2"] := "value2"
        print(map)
        map["key"] := "value2"
        print(map)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "{key: value}");
    EXPECT_EQ(lines[1], "{key2: value2, key: value}");
    EXPECT_EQ(lines[2], "{key2: value2, key: value2}");
}
