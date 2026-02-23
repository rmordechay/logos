#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgMemoryTest, Test1) {
    const auto code = R"(
    object Obj {
        x: Int
        name: Str
    }
    func(): Obj[] {
        arr: Obj[]
        arr.add(Obj{x=2, name="text"})
        return arr
    }
    main() {
        arr = func()
        print(arr)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "[Obj{x=2, name=text}]");
}

TEST(CgMemoryTest, Test2) {
    const auto code = R"(
    object Obj1 {
        obj2: Obj2
    }
    object Obj2 {
        id: Int
        name: Str
    }
    func(obj1: Obj1) {
        obj1.obj2 := Obj2{id=5, name="Roi"}
    }
    main() {
        obj1 = Obj1{}
        print(obj1)
        func(obj1)
        print(obj1)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "Obj1{obj2=Obj2{id=0, name=null}}");
    EXPECT_EQ(lines[1], "Obj1{obj2=Obj2{id=5, name=Roi}}");
}

TEST(CgMemoryTest, Test3) {
    const auto code = R"(
    object Obj {
        x: Int
    }

    f(cond: Bool): Obj {
        if cond return Obj{x=48}
        return Obj{x=23}
    }

    main() {
        print(f(true))
        print(f(false))
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "Obj{x=48}");
    EXPECT_EQ(lines[1], "Obj{x=23}");
}
