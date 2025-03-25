#include "LgsLinker.h"
#include "Logos.h"

#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::StartsWith;
using testing::HasSubstr;

class CodegenForeachLoopTests : public testing::Test {
protected:
    path dataDir = "../tests/codegen/loops/";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        logos.loadBuiltinFuncs();
    }

    void TearDown() override {
        remove_all(logos.buildDir);
    }
};

TEST_F(CodegenForeachLoopTests, TestLoopWorks) {
    const auto code = R"(
    main() {
        for i in [1, 2, 3, 4] {
            print(i)
        }
    }
    )";
    const auto file = logos.parseFile(code);
    const auto files = {file};
    logos.analyse(files);
    logos.generateCode(logos.getMainFile(files));
    for (const auto& [name, module] : modules) {
        std::cout << name << '\n';
        const auto func = module->getFunction("main");
        std::string funcStr;
        raw_string_ostream stream(funcStr);
        func->print(stream);
    }
    ASSERT_THAT(modules.size(), 1);
}
