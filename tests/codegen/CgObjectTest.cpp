#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgObjectTest, Test1) {
    const auto code = R"(
    object Obj {
        x: Int
        y: Float
        z: Bool
        a: Str
    }
    main() {
        obj = Obj{x=23, y=5.345}
        print(obj)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "Obj{x=23, y=5.345, z=false, a=\"\"}");
}

TEST(CgObjectTest, Test2) {
    const auto code = R"(
    object Obj {
        x: Int
        name: Str
        arr: Int[]
    }
    main() {
        obj = Obj{x=2, name="text", arr=[1, 2, 3]}
        print(obj::json())
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 1);
    EXPECT_EQ(lines[0], "{\"x\": 2, \"name\": \"text\", \"arr\": [1, 2, 3]}");
}