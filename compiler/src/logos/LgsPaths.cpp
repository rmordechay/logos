#include "logos/LgsPaths.h"
#include "LgsConfigs.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"
#include <iostream>
#include <unistd.h>
#include <llvm/TargetParser/Triple.h>

void LgsPaths::findLgsRootDir() {
    assert(lgsConfigs.isDevMode);
    const auto currentPath = fs::current_path();
    lgsRootDir = lgsConfigs.isTestMode ? currentPath.parent_path() : currentPath;
    lgsPackagesDir = lgsRootDir / LGS_PACKAGES_DIR;
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
        // Try to find c common files to make sure we are certainly in the right dir
        if (fs::exists(dir / "stdio.h") && fs::exists(dir / "stdlib.h")) {
            cLibHeadersDir = dir;
            break;
        }
    }
    if (cLibHeadersDir == "") assert(0);
    pclose(pipe);
    assert(fs::exists(cLibHeadersDir));
}
