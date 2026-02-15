#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgAssignmentTest, Test1) {
    const auto code = R"(
    object Obj {
        x: Int
    }
    main() {
        mut var = 2
        print(var)
        var := 3
        print(var)

        var2: Int[2] = [2, 3]
        print(var2)
        var2[0] := 6
        print(var2)

        mut var3: Int? = 2
        print(var3)
        var3 := 4
        print(var3)

        var4 = Obj{}
        print(var4)
        var4.x := 2
        print(var4)
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 8);
    EXPECT_EQ(lines[0], "2");
    EXPECT_EQ(lines[1], "3");
    EXPECT_EQ(lines[2], "[2, 3]");
    EXPECT_EQ(lines[3], "[6, 3]");
    EXPECT_EQ(lines[4], "2");
    EXPECT_EQ(lines[5], "4");
    EXPECT_EQ(lines[6], "Obj{x=0}");
    EXPECT_EQ(lines[7], "Obj{x=2}");
}