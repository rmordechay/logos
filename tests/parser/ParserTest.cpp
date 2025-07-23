#include "logos/LgsApp.h"
#include "logos/LgsModule.h"
#include <gtest/gtest.h>

class ParserTest : public testing::Test {};

TEST_F(ParserTest, TestParser) {
    LgsApp app;
    app.parseSrcFile("main() {a: Str = 34}");
    ASSERT_TRUE(app.errHandler.errors.empty());
}