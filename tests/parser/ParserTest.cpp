#include "files/LgsMainFile.h"
#include "logos/LgsApp.h"
#include "tools/LgsJsonParser.h"
#include "LgsUtils.h"
#include "gtest/gtest.h"

const std::string expectedDir = "../../tests/parser/expected";

TEST(TestParser, Test1) {
    LgsApp app;
    const auto code = R"(
    object Obj {
        implements: Interface
        x: Int
        func() {
            print("Hello")
        }
    }
    interface Interface {
        func(x: Int[])
    }
    enum Enum {
        AR = "Roi"
    }
    )";
    const auto expectedTree = getFileText(expectedDir + "/ParserTest1.json");
    app.loadSrcFile(code);
    const auto mainFile = dynamic_cast<LgsMainFile*>(app.srcFiles.front());
    LgsJsonParser parser;
    parser.parseMainFile(mainFile);
    EXPECT_EQ(app.errHandler.errors.size(), 0);
    EXPECT_EQ(parser.json.str(), expectedTree);
}

TEST(TestParser, Test2) {
    LgsApp app;
    const auto code = R"(
    f2(x: Interface) {
        x.func()
    }
    f(x: Int, y: Int): Obj {
        print(x + y)
    }
    func2() {
        a = 2
        switch a {
            2: print("1")
            3: print("2")
            else: print("3")
        }
        if false {
            print("roi")
        }
    }
    )";
    const auto expectedTree = getFileText(expectedDir + "/ParserTest2.json");
    app.loadSrcFile(code);
    const auto mainFile = dynamic_cast<LgsMainFile*>(app.srcFiles.front());
    LgsJsonParser parser;
    parser.parseMainFile(mainFile);
    std::ofstream("../../test.json") << parser.json.str();
    EXPECT_EQ(app.errHandler.errors.size(), 0);
    EXPECT_EQ(parser.json.str(), expectedTree);
}

TEST(TestParser, Test3) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = {"key": "value"}
        f(1, 2)
        f: (Int): Int = it => {
            print("Hello")
            return 2 + it
        }
        print(f(2))
        if true {
            if true {
                print("inside")
                break if
            }
            print("outside")
        }
    }
    )";
    const auto expectedTree = getFileText(expectedDir + "/ParserTest3.json");
    app.loadSrcFile(code);
    const auto mainFile = dynamic_cast<LgsMainFile*>(app.srcFiles.front());
    LgsJsonParser parser;
    parser.parseMainFile(mainFile);
    EXPECT_EQ(app.errHandler.errors.size(), 0);
    EXPECT_EQ(parser.json.str(), expectedTree);
}

TEST(TestParser, Test4) {
    LgsApp app;
    const auto code = R"(
    main() {
        a = 2 + 2
        print(a)
        a := 4 + 2
        print(a)
        a += 2
        print(a)
        a -= 2
        print(a)
        a *= 2
        print(a)
        a /= 2
        print(a)
        a %= 2
        print(a)
        a ^= 2
        print(a)
        a &= 2
        print(a)
        a |= 2
        print(a)
        a <<= 2
        print(a)
        a >>= 2
        print(a)
    }
    )";
    const auto expectedTree = getFileText(expectedDir + "/ParserTest4.json");
    app.loadSrcFile(code);
    const auto mainFile = dynamic_cast<LgsMainFile*>(app.srcFiles.front());
    LgsJsonParser parser;
    parser.parseMainFile(mainFile);
    EXPECT_EQ(app.errHandler.errors.size(), 0);
    EXPECT_EQ(parser.json.str(), expectedTree);
}
