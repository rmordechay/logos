#include <sstream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgSelectionTest, Test1) {
    const auto code = R"(
    object Obj1 {
        obj2: Obj2
    }
    object Obj2 {
        obj3: Obj3
    }
    object Obj3 {
        obj4: Obj4
    }
    object Obj4 {
        x: Str
        y: Int
    }
    main() {
        obj1 = Obj1{}
        print(obj1)
        print(obj1.obj2)
        print(obj1.obj2.obj3)
        print(obj1.obj2.obj3.obj4)
        print(obj1.obj2.obj3.obj4.x)
        print(obj1.obj2.obj3.obj4.y)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 6);
    EXPECT_EQ(lines[0], "Obj1{obj2=Obj2{obj3=Obj3{obj4=Obj4{x=\"\", y=0}}}}");
    EXPECT_EQ(lines[1], "Obj2{obj3=Obj3{obj4=Obj4{x=\"\", y=0}}}");
    EXPECT_EQ(lines[2], "Obj3{obj4=Obj4{x=\"\", y=0}}");
    EXPECT_EQ(lines[3], "Obj4{x=\"\", y=0}");
    EXPECT_EQ(lines[4], "\"\"");
    EXPECT_EQ(lines[5], "0");
}
