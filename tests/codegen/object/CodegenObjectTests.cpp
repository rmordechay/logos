#include "CodeGenerator.h"
#include "Logos.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <regex>

using testing::StartsWith;
using testing::HasSubstr;

class CodegenObjectTests : public testing::Test {
protected:
    path dataDir = "../tests/codegen/object/";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        logos.loadBuiltins();
    }

    void TearDown() override {
        remove_all(logos.paths.buildDir);
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

TEST_F(CodegenObjectTests, TestObjectWorks) {
    const auto codeMain = R"(
        main() {
            obj = MyObject()
            product = obj.mul(2, 345)
        }
    )";
    const auto codeObj = R"(
        object: MyObject
        implements: MyInterface

        x: Int
        y: Int

        add(): Int {
            return self.x + self.y
        }

        mul(a: Int, b: Int): Int {
            return a * b
        }
    )";
    const auto fileMain = logos.parseFile(codeMain);
    const auto fileObject = logos.parseFile(codeObj);
    logos.loadBuiltins();
    logos.analyse({fileMain, fileObject});
    CodeGenerator::generate(logos.project.mainFile);
}
