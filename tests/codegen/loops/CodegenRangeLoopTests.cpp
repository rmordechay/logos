#include "LgsLinker.h"
#include "Logos.h"

#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <regex>

using testing::StartsWith;
using testing::HasSubstr;

class CodegenRangeLoopTests : public testing::Test {
protected:
    path dataDir = "../tests/codegen/loops/";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        logos.loadBuiltins();
    }

    void TearDown() override {
        remove_all(logos.buildDir);
    }

    string getExpectedCode() const {
        std::ifstream inputFile(dataDir / "expected.ll");
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        return normalizeWhitespace(buffer.str());
    }

    string normalizeWhitespace(const string& str) const {
        auto result = regex_replace(str, regex("\\s+"), " ");
        result = regex_replace(result, regex("^\\s+|\\s+$"), "");
        return result;
    }
};

TEST_F(CodegenRangeLoopTests, TestLoopWorks) {
    const auto code = R"(
        main() {
            for i in 0..10 {
                print(i)
            }
        }
    )";
    const auto file = logos.parseFile(code);
    const auto files = {file};
    logos.analyse(files);
    logos.generateCode(logos.getMainFile(files));

    for (const auto& [name, module] : modules) {
        const auto func = module->getFunction("main");
        string funcStr;
        raw_string_ostream stream(funcStr);
        func->print(stream);
        ASSERT_EQ(normalizeWhitespace(funcStr), getExpectedCode());
    }
    ASSERT_THAT(modules.size(), 1);
}
