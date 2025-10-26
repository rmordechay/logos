#include "external/doctest.h"
#include "logos/LgsApp.h"

TEST_CASE("TestCodeGen1") {
    const auto code = R"(
    main() {}
        print("Hello world")
    }
    )";
    LgsApp app;
    app.loadSrcFile(code);
    assert(app.errHandler.successful);
    app.analyse();
    assert(app.errHandler.successful);
}

TEST_CASE("TestCodeGen2") {
    // LgsApp app("./");
    // app.appConfigs.logLevel = INFO;
    // const auto code = R"(
    // main() {
    //     print(_/4 + _/4)
    // }
    // )";
    // app.loadBuiltins();
    // app.parseSrcFile(code);
    // app.analyse();
    // app.generate();
    // app.link();
    // app.execute();
}