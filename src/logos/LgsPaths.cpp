#include "logos/LgsPaths.h"
#include "logos/LgsConfigs.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"
#include <iostream>
#include <unistd.h>
#include <llvm/TargetParser/Triple.h>

bool LgsPaths::findLgsRootDir() {
    assert(lgsConfigs.isDevMode);
    const auto current = fs::current_path();
    if (fs::exists(current / LGS_LIB_NAME)) {
        lgsRootDir = current;
    } else {
        const auto parent = current.parent_path();
        if (!fs::exists(parent / LGS_LIB_NAME)) return false;
        lgsRootDir = current;
    }
    lgsPackagesDir = lgsRootDir / LGS_PACKAGES_DIR;
    return true;
}

bool LgsPaths::findCLibRoot() {
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
    if (!pipe) return false;

    fgets(buffer, sizeof(buffer), pipe);
    std::string clibRoot = buffer;
    if (clibRoot == "") {
        pclose(pipe);
        return false;
    }
    clibRoot.pop_back();
    cLibRootDir = fs::path(clibRoot);
    pclose(pipe);
    assert(fs::exists(cLibRootDir));
    return true;
}

bool LgsPaths::findCLibHeaders() {
    const auto pipe = popen("clang -E -Wp,-v -xc /dev/null 2>&1", "r");
    if (!pipe) return false;
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
    if (cLibHeadersDir == "") return false;
    pclose(pipe);
    assert(fs::exists(cLibHeadersDir));
    return true;
}
