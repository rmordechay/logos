#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgIterableTest, Test1) {
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

TEST(CgIterableTest, Test2) {
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
