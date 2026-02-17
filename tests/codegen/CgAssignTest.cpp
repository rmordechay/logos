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
    std::istringstream stream(getLgsOutput(code));
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
    std::istringstream stream(getLgsOutput(code));
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
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "4");
}

TEST(CgAssignmentTest, Test4) {
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
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "Obj{x=0}");
    EXPECT_EQ(lines[1], "Obj{x=2}");
}
