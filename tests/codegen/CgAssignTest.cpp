#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgAssignmentTest, Test1) {
    const auto code = R"(
    main() {
        mut var = 2
        print(var)
        var := 3
        print(var)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "3");
}

TEST(CgAssignmentTest, Test2) {
    const auto code = R"(
    main() {
        var2: Int[2] = [2, 3]
        print(var2)
        var2[0] := 6
        print(var2)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "[2, 3]");
    EXPECT_EQ(lines[1], "[6, 3]");
}

TEST(CgAssignmentTest, Test3) {
    const auto code = R"(
    main() {
        mut var3: Int? = 2
        print(var3)
        var3 := 4
        print(var3)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "4");
}


TEST(CgAssignmentTest, Test4) {
    const auto code = R"(
    main() {
        mut a = "text"?
        print(a)
        a := null
        print(a)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "text");
    EXPECT_EQ(lines[1], "null");
}

TEST(CgAssignmentTest, Test5) {
    const auto code = R"(
    object Obj {
        x: Int
    }
    main() {
        var4 = Obj{}
        print(var4)
        var4.x := 2
        print(var4)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "Obj{x=0}");
    EXPECT_EQ(lines[1], "Obj{x=2}");
}

TEST(CgAssignmentTest, Test6) {
    const auto code = R"(
    main() {
        mut a = 2
        print(a)
        a += 3
        print(a)
        a -= 2
        print(a)
        a *= 3
        print(a)
        a /= 3
        print(a)
        a %= 3
        print(a)
        a <<= 3
        print(a)
        a >>= 3
        print(a)
        a |= 3
        print(a)
        a &= 3
        print(a)
        a ^^= 3
        print(a)
        a ^= 3
        print(a)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 12);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "5");
    EXPECT_EQ(lines[2], "3");
    EXPECT_EQ(lines[3], "9");
    EXPECT_EQ(lines[4], "3");
    EXPECT_EQ(lines[5], "0");
    EXPECT_EQ(lines[6], "0");
    EXPECT_EQ(lines[7], "0");
    EXPECT_EQ(lines[8], "3");
    EXPECT_EQ(lines[9], "3");
    EXPECT_EQ(lines[10], "0");
    EXPECT_EQ(lines[11], "0");
}
