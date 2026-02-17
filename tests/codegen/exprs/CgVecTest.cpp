#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgVecTest, Test1) {
    const auto code = R"(
    main() {
        print(Vec2(1))
        print(Vec2(1.1))
        print(Vec3(1))
        print(Vec3(1.1))
        print(Vec4(1))
        print(Vec4(1.1))
        print(Vec4(Vec2(1.2), Vec2(1.3)))
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 7);
    EXPECT_EQ(lines[0], "Vec2(1, 1)");
    EXPECT_EQ(lines[1], "Vec2(1.1, 1.1)");
    EXPECT_EQ(lines[2], "Vec3(1, 1, 1)");
    EXPECT_EQ(lines[3], "Vec3(1.1, 1.1, 1.1)");
    EXPECT_EQ(lines[4], "Vec4(1, 1, 1, 1)");
    EXPECT_EQ(lines[5], "Vec4(1.1, 1.1, 1.1, 1.1)");
    EXPECT_EQ(lines[6], "Vec4(1.2, 1.2, 1.3, 1.3)");
}
