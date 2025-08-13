#pragma once
#include "configs/LgsDefinitions.h"
#include <llvm/MC/TargetRegistry.h>
#include <llvm/TargetParser/Host.h>

using namespace llvm;

struct LgsPaths {
    fs::path relRootDir;
    fs::path rootDir;
    fs::path srcDir;
    fs::path envsDir;
    fs::path buildDir;
    fs::path buildIR;
    fs::path lgsStdlibDir;
    fs::path appFilePath;
    fs::path objFilePath;
    fs::path execFilePath;
    fs::path cLibRoot;
    fs::path cLibHeadersDir;
    void initPaths(const fs::path& rootDirPath);
    void findCLibRoot();
    void findCLibHeaders();
};

inline void LgsPaths::initPaths(const fs::path& rootDirPath) {
    if (rootDirPath == "") return;
    relRootDir = rootDirPath;
    rootDir = canonical(rootDirPath);
    srcDir = rootDir / LGS_SRC_DIR;
    envsDir = rootDir / LGS_ENVS_DIR;
    buildDir = rootDir / LGS_BUILD_DIR;
    buildIR = buildDir / LGS_BUILD_IR;
    objFilePath = buildDir / LGS_OBJECT_FILE;
    execFilePath = buildDir / LGS_EXECUTABLE_FILE;
    appFilePath = rootDir / LGS_APP_FILE_NAME LGS_FILE_EXTENSION;
    findCLibRoot();
    findCLibHeaders();
    assert(cLibRoot != "" && cLibHeadersDir != "");
}

inline void LgsPaths::findCLibRoot() {
    const Triple triple(sys::getDefaultTargetTriple());
    FILE* pipe = nullptr;
    char buffer[512];
    switch (triple.getOS()) {
    case Triple::Darwin:
        pipe = popen("xcrun --show-sdk-path 2>/dev/null", "r");
        break;
    case Triple::Linux:
        pipe = popen("cc -print-sysroot 2>/dev/null", "r");
        break;
    default:
        if (pipe) pclose(pipe);
        assert(0);
    }
    fgets(buffer, sizeof(buffer), pipe);
    string line = buffer;
    line.pop_back();
    cLibRoot = fs::path(line);
    if (pipe) pclose(pipe);
}

inline void LgsPaths::findCLibHeaders() {
    const auto pipe = popen("cc -E -Wp,-v -xc /dev/null 2>&1", "r");
    if (!pipe) assert(0);
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        string line = buffer;
        // Include paths starts with a space
        if (line.empty() || !isspace(static_cast<unsigned char>(line[0]))) continue;
        // Ignore frameworks
        const auto frameworks = line.find(" (framework directory)");
        if (frameworks != std::string::npos) continue;
        const auto start = line.find_first_not_of(" \t");
        const auto end = line.find_last_not_of("\r\n");
        if (start == string::npos || end == string::npos) continue;
        auto dir = fs::path(line.substr(start, end - start + 1));
        if (fs::exists(dir / "stdio.h") && fs::exists(dir / "stdlib.h")) {
            cLibHeadersDir = dir;
            break;
        }
    }
    pclose(pipe);
}
