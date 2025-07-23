#include "files/LgsFile.h"
#include "logos/LgsApp.h"
#include "logos/LgsModule.h"
#include <gtest/gtest.h>
#include <regex>

string normalizeIR(const string& s) {
    const auto result = regex_replace(s, regex(R"(\s+)"), " ");
    return regex_replace(result, regex(R"(^\s+|\s+$)"), "");
}

class CodegenTest : public testing::Test {};

TEST_F(CodegenTest, CodegenTest1) {
    LgsApp app;
    const auto expectedCode = R"(
    define i32 @main() {
    entry:
      call void @Runtime_init(ptr @0)
      %0 = alloca i32, align 4
      store i32 2, ptr %0, align 4
      ret i32 0
    })";
    app.initLLVM();
    app.parseSrcFile("main() {a = 2}");
    app.analyse();

    string irString;
    raw_string_ostream stream(irString);
    const auto module = app.files[0]->generateIR();
    const auto IRModule = module->IRModule;
    const auto func = IRModule->getFunction("main");
    func->print(stream);

    EXPECT_EQ(normalizeIR(stream.str()), normalizeIR(expectedCode));
}
