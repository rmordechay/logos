#include <sstream>
#include <string>
#include <vector>

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
        print(func4(3))
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 4);
    EXPECT_EQ(lines[0], "1");
    EXPECT_EQ(lines[1], "[1, 2, 3]");
    EXPECT_EQ(lines[2], "3");
    EXPECT_EQ(lines[3], "[3]");
}

TEST(CgGenericsTest, Test2) {
    const auto code = R"(
    map<T, U>(arr: T[], cb: (T): U): U[] {
        newArr: T[]
        for arr {
            newArr.add(cb(for.element))
        }
        return newArr
    }
    main() {
        print(map([1, 2, 3], (x: Int): Int => x + 3))
        print(map<Int, Int>([1, 2, 3], {it + 4}))
        //print(map([1, 2, 3], (x: Int) => x + 5))
        //print(map([1, 2, 3], {it + 2}))
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "[4, 5, 6]");
    EXPECT_EQ(lines[1], "[5, 6, 7]");
    // EXPECT_EQ(lines[2], "[6, 7, 8]");
    // EXPECT_EQ(lines[3], "[3, 4, 5]");
}

TEST(CgGenericsTest, Test3) {
    const auto code = R"(
    object Obj<T> {
        x: T
    }
    main() {
        obj = Obj{x=23}
        obj2 = Obj{x=25}
        print(obj)
        print(obj2)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "Obj{x=23}");
    EXPECT_EQ(lines[1], "Obj{x=25}");
}

TEST(CgGenericsTest, Test4) {
    const auto code = R"(
    object Obj<T> {
        x: T
        func(y: T) {
            print(y)
        }
    }
    main() {
        obj = Obj{x=23}
        obj.func(54)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "54");
}
