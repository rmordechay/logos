#include "LgsLinker.h"
#include "Logos.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

const path dataDir = "../tests/e2e/";

string executeAndGetOutput(const string& command) {
    ostringstream outputBuffer;
    array<char, 128> buffer;
    const auto sFile = popen(command.c_str(), "r");
    const unique_ptr<FILE, decltype(&pclose)> pipe(sFile, pclose);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        outputBuffer << buffer.data();
    }
    return outputBuffer.str();
}

TEST(SemaTest, TestHelloWorld) {
    Logos logos(dataDir);
    const auto file = logos.parseFile("main() {print(\"Hello world\")}", "");
    logos.loadGlobals();
    logos.analyse({file});
    logos.generateCode(dynamic_cast<LgsMainFile*>(file));
    const LgsLinker linker(logos.objFilePath, logos.execFilePath);
    linker.link(modules);
    logos.cleanup();
    const auto output = executeAndGetOutput(logos.execFilePath.c_str());
    remove_all(logos.buildDir);
    ASSERT_EQ(output, "Hello world\n");
}