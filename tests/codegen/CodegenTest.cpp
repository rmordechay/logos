#include "external/doctest.h"
#include "logos/LgsApp.h"
#include "utils/LgsUtils.h"

TEST_CASE("TestCodeGen1") {
    LgsApp app("./");
    app.appConfigs.logLevel = INFO;
    const auto code = R"(
    main() {
        print("Hello world")
    }
    )";
    app.loadBuiltins();
    app.parseSrcFile(code);
    app.analyse();
    app.generate();
    app.link();
    app.execute();
}

TEST_CASE("TestCodeGen2") {
    LgsApp app("./");
    app.appConfigs.logLevel = INFO;
    const auto code = R"(
    main() {
        print(_/4 + _/4)
    }
    )";
    app.loadBuiltins();
    app.parseSrcFile(code);
    app.analyse();
    app.generate();
    app.link();
    app.execute();
}