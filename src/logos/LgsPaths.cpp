#include "logos/LgsPaths.h"

#include "data/LgsDefinitions.h"

#include <llvm/TargetParser/Host.h>
#include <llvm/TargetParser/Triple.h>

void LgsPaths::initPaths() {
    assert(rootPath != "");
    srcDir = rootPath / LGS_SRC_DIR;
    envsDir = rootPath / LGS_ENVS_DIR;
    buildDir = rootPath / LGS_BUILD_DIR;
    buildIR = buildDir / LGS_BUILD_IR;
    appFilePath = rootPath / LGS_APP_FILE_NAME LGS_FILE_EXTENSION;
    findLgsRoot();
    findCLibRoot();
    findCLibHeaders();
}

void LgsPaths::findLgsRoot() {
#ifdef __APPLE__
    lgsLib = rootPath.parent_path() / "cmake-build-debug";
#elif defined(__linux__)
    lgsLib = rootPath.parent_path() / "build";
#endif
}

void LgsPaths::findCLibRoot() {
    const llvm::Triple triple(llvm::sys::getDefaultTargetTriple());
    FILE* pipe = nullptr;
    char buffer[512];
    switch (triple.getOS()) {
    case llvm::Triple::Darwin:
        pipe = popen("xcrun --show-sdk-path 2>/dev/null", "r");
        break;
    case llvm::Triple::Linux:
        pipe = popen("clang -print-resource-dir 2>/dev/null", "r");
        break;
    default:
        assert(0);
    }
    fgets(buffer, sizeof(buffer), pipe);
    std::string clibRoot = buffer;
    assert(clibRoot != "");
    clibRoot.pop_back();
    cLibRoot = fs::path(clibRoot);
    if (pipe) pclose(pipe);
}

void LgsPaths::findCLibHeaders() {
    const auto pipe = popen("cc -E -Wp,-v -xc /dev/null 2>&1", "r");
    if (!pipe) assert(0);
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        std::string line = buffer;
        // Include paths starts with a space
        if (line.empty() || !isspace(static_cast<unsigned char>(line[0]))) continue;
        // Ignore frameworks
        const auto frameworks = line.find(" (framework directory)");
        if (frameworks != std::string::npos) continue;
        const auto start = line.find_first_not_of(" \t");
        const auto end = line.find_last_not_of("\r\n");
        if (start == std::string::npos || end == std::string::npos) continue;
        auto dir = fs::path(line.substr(start, end - start + 1));
        if (fs::exists(dir / "stdio.h") && fs::exists(dir / "stdlib.h")) {
            cLibHeadersDir = dir;
            break;
        }
    }
    assert(cLibHeadersDir != "");
    pclose(pipe);
}
