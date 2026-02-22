#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgBinExprTest, IntTest1) {
    const auto code = R"(
    main() {
        print(23 + 34)
        print(23 - 235)
        print(23 * 34)
        print(23 + 34 - 235)
        print(23 - 34 * 2)
        print((1 + 2) * 2)
        print(1 + 2 * 2)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 7);
    EXPECT_EQ(lines[0], "57");
    EXPECT_EQ(lines[1], "-212");
    EXPECT_EQ(lines[2], "782");
    EXPECT_EQ(lines[3], "-178");
    EXPECT_EQ(lines[4], "-45");
    EXPECT_EQ(lines[5], "6");
    EXPECT_EQ(lines[6], "5");
}

TEST(CgBinExprTest, IntTest2) {
    const auto code = R"(
    main() {
        print(8 << 2)
        print(8 >> 2)
        print(8 | 2)
        print(8 & 2)
        print(8 ^^ 2)
        print(8 ^ 2)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 6);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "32");
    EXPECT_EQ(lines[2], "10");
    EXPECT_EQ(lines[3], "0");
    EXPECT_EQ(lines[4], "10");
    EXPECT_EQ(lines[5], "64.000");
}

TEST(CgBinExprTest, FloatTest1) {
    const auto code = R"(
    main() {
        print(23.53 + 34.7)
        print(23.2 - 235.45)
        print(23.4 * 34)
        print(23.1 + 34.2 - 235)
        print(23.3 - 34.3 * 2.2)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 5);
    EXPECT_EQ(lines[0], "58.230");
    EXPECT_EQ(lines[1], "-212.250");
    EXPECT_EQ(lines[2], "795.600");
    EXPECT_EQ(lines[3], "-177.700");
    EXPECT_EQ(lines[4], "-52.160");
}

TEST(CgBinExprTest, BoolTest1) {
    const auto code = R"(
    main() {
        print(true and true)
        print(false and false)
        print(true and false)
        print(false and true)
        print(true or true)
        print(false or false)
        print(true or false)
        print(false or true)
        print((2 > 5) or (7 > 5))
        print((2 > 5) and (7 > 5))
        print(2 > 5 or 7 > 5)
        print(2 > 5 and 7 > 5)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 12);
    EXPECT_EQ(lines[0], "true");
    EXPECT_EQ(lines[1], "false");
    EXPECT_EQ(lines[2], "false");
    EXPECT_EQ(lines[3], "false");
    EXPECT_EQ(lines[4], "true");
    EXPECT_EQ(lines[6], "true");
    EXPECT_EQ(lines[7], "true");
    EXPECT_EQ(lines[8], "true");
    EXPECT_EQ(lines[9], "false");
    EXPECT_EQ(lines[10], "true");
    EXPECT_EQ(lines[11], "false");
}

TEST(CgBinExprTest, VecTest1) {
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
        print(vec1 * vec2)
        print(vec1 X vec2)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 8);
    EXPECT_EQ(lines[0], "Vec3(5.34, 6.71, 11.34)");
    EXPECT_EQ(lines[1], "Vec3(-0.66, 0.71, 5.34)");
    EXPECT_EQ(lines[2], "Vec3(7.02, 11.13, 25.02)");
    EXPECT_EQ(lines[3], "Vec3(0.78, 1.23667, 2.78)");
    EXPECT_EQ(lines[4], "Vec3(6.58, 9.95, 13.88)");
    EXPECT_EQ(lines[5], "Vec3(-1.9, -2.53, 2.8)");
    EXPECT_EQ(lines[6], "79.276");
    EXPECT_EQ(lines[7], "Vec3(-31.4882, 22.398, -1.1288)");
}
