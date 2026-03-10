#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgVectorTest, Test1) {
    const auto code = R"(
    main() {
        print(Vec2())
        print(Vec3())
        print(Vec4())
        print(Vec2(1.))
        print(Vec3(1.))
        print(Vec4(1.))
        print(Vec2(1.1, 2.2))
        print(Vec3(1.1, 2.2, 3.3))
        print(Vec4(1.1, 2.2, 3.3, 4.4,))
        print(Vec3(1.1, 2.2))
        print(Vec4(1.1, 2.2, 3.3,))
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 11);
    EXPECT_EQ(lines[0], "Vec2(0, 0)");
    EXPECT_EQ(lines[1], "Vec3(0, 0, 0)");
    EXPECT_EQ(lines[2], "Vec4(0, 0, 0, 0)");
    EXPECT_EQ(lines[3], "Vec2(1, 1)");
    EXPECT_EQ(lines[4], "Vec3(1, 1, 1)");
    EXPECT_EQ(lines[5], "Vec4(1, 1, 1, 1)");
    EXPECT_EQ(lines[6], "Vec2(1.1, 2.2)");
    EXPECT_EQ(lines[7], "Vec3(1.1, 2.2, 3.3)");
    EXPECT_EQ(lines[8], "Vec4(1.1, 2.2, 3.3, 4.4)");
    EXPECT_EQ(lines[9], "Vec3(1.1, 2.2, 0)");
    EXPECT_EQ(lines[10], "Vec4(1.1, 2.2, 3.3, 0)");
}
