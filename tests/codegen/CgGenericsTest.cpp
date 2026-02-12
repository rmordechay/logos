#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgGenericsTest, Test1) {
    const auto code = R"(
    func<T>(arr: T[]): T {
        return arr[0]
    }
    func2<T>(arr: T[]): T[] {
        return arr
    }
    func3<T>(num: T): T {
        return num
    }
    func4<T>(num: T): T[] {
        return [num]
    }
    main() {
        print(func([1, 2, 3]))
        print(func2([1, 2, 3]))
        print(func3(3))
        //print(func4(3))
    }
    )";
    std::istringstream stream(getLgsOutput(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "1");
    EXPECT_EQ(lines[1], "[1, 2, 3]");
    EXPECT_EQ(lines[2], "3");
}
