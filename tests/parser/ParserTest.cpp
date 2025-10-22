#include "files/LgsFile.h"
#include "files/LgsMainFile.h"
#include "logos/LgsApp.h"
#include "parser/LgsJsonParser.h"
#include "utils/LgsUtils.h"
#include <external/doctest.h>

TEST_CASE("Parser1") {
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
    const auto expectedTree = getFileText("../../tests/parser/ParserTest1.json");
    app.loadSrcFile(code, "Main.lgs");
    const auto mainFile = static_cast<LgsMainFile*>(app.srcFiles.front());
    LgsJsonParser parser;
    parser.parseMainFile(mainFile);
    std::ofstream("../../test.json") << parser.json.str();
    CHECK(app.errHandler.errors.size() == 0);
    CHECK_EQ(parser.json.str(), expectedTree);
}

TEST_CASE("Parser2") {
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
    const auto expectedTree = getFileText("../../tests/parser/ParserTest2.json");
    app.loadSrcFile(code, "Main.lgs");
    const auto mainFile = static_cast<LgsMainFile*>(app.srcFiles.front());
    LgsJsonParser parser;
    parser.parseMainFile(mainFile);
    CHECK(app.errHandler.errors.size() == 0);
    CHECK_EQ(parser.json.str(), expectedTree);
}

TEST_CASE("Parser3") {
    LgsApp app;
    const auto code = R"(
    main() {
        a = {"roi": "roi"}
        f(1, 2)
        f: (Int): Int = it -> {
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
    const auto expectedTree = getFileText("../../tests/parser/ParserTest3.json");
    app.loadSrcFile(code, "Main.lgs");
    const auto mainFile = static_cast<LgsMainFile*>(app.srcFiles.front());
    LgsJsonParser parser;
    parser.parseMainFile(mainFile);
    CHECK(app.errHandler.errors.size() == 0);
    CHECK_EQ(parser.json.str(), expectedTree);
}
