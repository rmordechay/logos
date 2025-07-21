#include "logos/LgsApp.h"
#include "logos/LgsModule.h"
#include <gtest/gtest.h>

class ParserTest : public testing::Test {
public:
    LgsApp app;

    void SetUp() override {
        app.loadBuiltins();
    }

    void TearDown() override {
        globals.freeSymbols();
    }
};

TEST_F(ParserTest, TestParser) {
    app.parseSrcFile("main() {a: Str = 34}");
    ASSERT_TRUE(app.errHandler.errors.empty());
}