#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgArithmeticsTest, IntTest1) {
    const auto code = R"(
    main() {
        print(23 + 34)
        print(23 - 235)
        print(23 * 34)
        print(23 + 34 - 235)
        print(23 - 34 * 2)
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 5);
    EXPECT_EQ(lines[0], "57");
    EXPECT_EQ(lines[1], "-212");
    EXPECT_EQ(lines[2], "782");
    EXPECT_EQ(lines[3], "-178");
    EXPECT_EQ(lines[4], "-45");
}

TEST(CgArithmeticsTest, FloatTest1) {
    const auto code = R"(
    main() {
        print(23.53 + 34.7)
        print(23.2 - 235.45)
        print(23.4 * 34)
        print(23.1 + 34.2 - 235)
        print(23.3 - 34.3 * 2.2)
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 5);
    EXPECT_EQ(lines[0], "58.230");
    EXPECT_EQ(lines[1], "-212.250");
    EXPECT_EQ(lines[2], "795.600");
    EXPECT_EQ(lines[3], "-177.700");
    EXPECT_EQ(lines[4], "-52.160");
}

TEST(CgArithmeticsTest, VecTest1) {
    const auto code = R"(
    main() {
        vec1 = Vec3(2.34, 3.71, 8.34)
        vec2 = Vec3(4.24, 6.24, 5.54)
        print(vec1 + 3)
        print(vec1 - 3)
        print(vec1 * 3)
        print(vec1 / 3)
        print(vec1 + vec2)
        print(vec1 - vec2)
        //print(vec1 * vec2)
        //print(vec1 X vec2)
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 6);
    EXPECT_EQ(lines[0], "Vec3(5.34, 6.71, 11.34)");
    EXPECT_EQ(lines[1], "Vec3(-0.66, 0.71, 5.34)");
    EXPECT_EQ(lines[2], "Vec3(7.02, 11.13, 25.02)");
    EXPECT_EQ(lines[3], "Vec3(0.78, 1.23667, 2.78)");
    EXPECT_EQ(lines[4], "Vec3(6.58, 9.95, 13.88)");
    EXPECT_EQ(lines[5], "Vec3(-1.9, -2.53, 2.8)");
}
