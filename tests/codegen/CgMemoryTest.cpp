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
