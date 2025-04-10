#include "CodeGenerator.h"
#include "LgsLinker.h"
#include "Logos.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


class E2ETests : public testing::Test {
protected:
    const path dataDir = "../tests/e2e/";
    Logos logos = Logos(dataDir);

    void SetUp() override {
        LgsFile* file = logos.parseFile("main() {print(\"Hello world\")}");
        logos.loadBuiltins(TODO);
        logos.analyse({file});
        CodeGenerator::generate(logos.project.mainFile);
        const LgsLinker linker(logos.paths.objFilePath, logos.paths.execFilePath);
        linker.link(modules);
    }

    void TearDown() override {
        remove_all(logos.paths.buildDir);
    }

    string executeAndGetOutput(const string& command) const {
        ostringstream outputBuffer;
        array<char, 128> buffer;
        const auto sFile = popen(command.c_str(), "r");
        const unique_ptr<FILE, decltype(&pclose)> pipe(sFile, pclose);
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            outputBuffer << buffer.data();
        }
        return outputBuffer.str();
    }
};

TEST_F(E2ETests, TestHelloWorld) {
    const auto output = executeAndGetOutput(logos.paths.execFilePath.c_str());
    ASSERT_EQ(output, "Hello world\n");
}
