#include "files/LgsFile.h"
#include "logos/LgsApp.h"
#include "logos/LgsModule.h"
#include <gtest/gtest.h>

class CodegenTest : public testing::Test {
public:
    LgsApp app;

    void SetUp() override {
        app.loadBuiltins();
    }

    void TearDown() override {
        globals.freeSymbols();
    }
};

TEST_F(CodegenTest, CodegenTest1) {
    app.initLLVM();
    app.parseSrcFile("main() {}");
    app.analyse();
    const auto module = app.files[0]->generateIR();
    const auto IRModule = module->IRModule;
    const auto func = IRModule->getFunction("main");
    string irString;
    raw_string_ostream stream(irString);
    func->print(stream);
    const auto text = stream.str();
}