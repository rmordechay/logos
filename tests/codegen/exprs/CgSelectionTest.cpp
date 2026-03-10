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

TEST(CgSelectionTest, Test2) {
    const auto code = R"(
    object Obj1 {
        obj2: Obj2[]
        getObj(): Obj2 {
            return self.obj2[0]
        }
    }
    object Obj2 {
        obj3: Obj3
        getObj3(): Obj3 {
            return self.obj3
        }
    }
    object Obj3 {
        x: Str
        y: Int
    }
    main() {
        obj1 = Obj1{}
        obj1.obj2.add(Obj2{})
        print(obj1.obj2[0].obj3)
        print(obj1.obj2[0].obj3.x)
        print(obj1.obj2[0].obj3.y)
        print(obj1.getObj())
        print(obj1.getObj().obj3)
        print(obj1.getObj().getObj3())
        print(obj1.getObj().getObj3().x)
        print(obj1.getObj().getObj3().y)
        print(obj1.obj2[0].getObj3())
        print(obj1.obj2[0].getObj3().x)
        print(obj1.obj2[0].getObj3().y)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 11);
    EXPECT_EQ(lines[0], "Obj3{x=\"\", y=0}");
    EXPECT_EQ(lines[1], "\"\"");
    EXPECT_EQ(lines[2], "0");
    EXPECT_EQ(lines[3], "Obj2{obj3=Obj3{x=\"\", y=0}}");
    EXPECT_EQ(lines[4], "Obj3{x=\"\", y=0}");
    EXPECT_EQ(lines[5], "Obj3{x=\"\", y=0}");
    EXPECT_EQ(lines[6], "\"\"");
    EXPECT_EQ(lines[7], "0");
    EXPECT_EQ(lines[8], "Obj3{x=\"\", y=0}");
    EXPECT_EQ(lines[9], "\"\"");
    EXPECT_EQ(lines[10], "0");
}
