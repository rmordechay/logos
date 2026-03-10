#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgObjectTest, Test1) {
    const auto code = R"(
    object Obj {
        x: Int
        y: Float
        z: Bool
        a: Str
        func() {
            print(self)
        }
    }
    main() {
        obj = Obj{x=23, y=5.345}
        print(obj)
        obj.func()
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "Obj{x=23, y=5.345, z=false, a=\"\"}");
    EXPECT_EQ(lines[1], "Obj{x=23, y=5.345, z=false, a=\"\"}");
}

TEST(CgObjectTest, Test2) {
    const auto code = R"(
    object Obj {
        func() {
            print("Hello world")
        }
    }
    main() {
        obj = Obj{}
        obj.func()
        Obj.func()
        Obj{}.func()
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "Hello world");
    EXPECT_EQ(lines[1], "Hello world");
    EXPECT_EQ(lines[2], "Hello world");
}

TEST(CgObjectTest, Test3) {
    const auto code = R"(
    single Obj {
        func() {
            print("Hello world")
        }
    }
    main() {
        Obj.func()
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "Hello world");
}

TEST(CgObjectTest, Test4) {
    const auto code = R"(
    object Obj {
        x: Int
        name: Str
        arr: Int[]
    }
    main() {
        obj = Obj{x=2, name="text", arr=[1, 2, 3]}
        print(obj::json())
        print(obj::hash())
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "{\"x\": 2, \"name\": \"text\", \"arr\": [1, 2, 3]}");
    EXPECT_EQ(lines[1], "787664486683716969");
}
