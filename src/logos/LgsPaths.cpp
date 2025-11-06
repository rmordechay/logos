#include "logos/LgsPaths.h"
#include "data/LgsConfigs.h"
#include "data/LgsDefinitions.h"
#include <llvm/TargetParser/Triple.h>

void LgsPaths::initPaths() {
    assert(rootPath != "");
    srcDir = rootPath / LGS_SRC_DIR;
    envsDir = rootPath / LGS_ENVS_DIR;
    buildDir = rootPath / LGS_BUILD_DIR;
    appFilePath = rootPath / LGS_APP_FILE;
    lgsPackagePath = rootPath / "../../lgs-packages";
    buildDirIR = buildDir / LGS_BUILD_IR_DIR;
    buildDirObjs = buildDir / LGS_BUILD_OBJECTS_DIR;
    cacheFile = buildDir / LGS_FILES_CACHE_FILE;
    if (!fs::exists(buildDir)) fs::create_directories(buildDir);
    if (!fs::exists(buildDirIR)) fs::create_directories(buildDirIR);
    if (!fs::exists(buildDirObjs)) fs::create_directories(buildDirObjs);
    findLgsLib();
    findCLibRoot();
    findCLibHeaders();
}

void LgsPaths::findLgsLib() {
    const char* libName = nullptr;
    switch (lgsConfigs.os) {
    case MAC_OS:
        libName = LIB_NAME_MACOS;
        break;
    case LINUX:
        libName = LIB_NAME_LINUX;
        break;
    case WINDOWS:
        libName = LIB_NAME_WIN;
        break;
    default:
        assert(0);
    }

    std::vector<fs::path> searchPaths;
    if (lgsConfigs.devMode) {
        searchPaths.push_back(fs::current_path());
        searchPaths.push_back(fs::current_path().parent_path());
    } else {
        searchPaths.push_back("/usr/local/lib");
        searchPaths.push_back("/usr/lib");
        if (const char* home = std::getenv("HOME")) {
            searchPaths.push_back(fs::path(home) / ".local/lib");
        }
        if (const char* localAppData = std::getenv("LOCALAPPDATA")) {
            searchPaths.push_back(fs::path(localAppData) / "Logos" / "lib");
        }
    }

    for (const auto& path : searchPaths) {
        if (!fs::exists(path / libName)) continue;
        lgsLibPath = path;
        return;
    }
    assert(0 && "Could not find Logos runtime library");
}

void LgsPaths::findCLibRoot() {
    FILE* pipe = nullptr;
    char buffer[512];
    switch (lgsConfigs.os) {
    case MAC_OS:
        pipe = popen("xcrun --show-sdk-path 2>/dev/null", "r");
        break;
    case LINUX:
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
    const auto pipe = popen("clang -E -Wp,-v -xc /dev/null 2>&1", "r");
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
