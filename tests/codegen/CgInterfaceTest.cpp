#include "gtest/gtest.h"
#include "LgsTestUtils.h"

TEST(CgInterfaceTest, Test1) {
    const auto code = R"(
    interface Interface {
        func()
    }
    object Obj {
        implements: Interface
        func() {
            print("From Obj")
        }
    }
    func(obj: Interface) {
        obj.func()
    }
    main() {
        obj = Obj{}
        obj.func()
        func(obj)
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "From Obj");
    EXPECT_EQ(lines[1], "From Obj");
}

TEST(CgInterfaceTest, Test2) {
    const auto code = R"(
    interface Interface {
        func() {
            print("From Interface")
        }
    }
    object Obj {
        implements: Interface
        func() {
            print("From Obj")
        }
    }
    object Obj2 {
        implements: Interface
    }
    main() {
        obj1 = Obj{}
        obj2 = Obj2{}
        obj1.func()
        obj2.func()
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 2);
    EXPECT_EQ(lines[0], "From Obj");
    EXPECT_EQ(lines[1], "From Interface");
}

TEST(CgInterfaceTest, Test3) {
    const auto code = R"(
    interface Interface {
        func()
    }
    func(obj: Interface) {
        obj.func()
    }
    main() {
        obj = Interface{func={print("Hello world")}}
        obj.func()
        func(obj)
        func(Interface{func={print("Hello world")}})
    }
    )";
    std::istringstream stream(runLgsApp(code));
    const auto lines = getLines(stream, 3);
    EXPECT_EQ(lines[0], "Hello world");
    EXPECT_EQ(lines[1], "Hello world");
    EXPECT_EQ(lines[2], "Hello world");
}
