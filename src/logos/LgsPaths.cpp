#include "logos/LgsPaths.h"
#include "logos/LgsConfigs.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"
#include <iostream>
#include <unistd.h>
#include <llvm/TargetParser/Triple.h>

#if defined(_WIN32)
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

bool LgsPaths::findLgsRuntime() {
    char buf[1024];
#if defined(_WIN32)
    DWORD len = GetModuleFileNameA(NULL, buf, MAX_PATH);
    if (len == 0 || len == MAX_PATH) return false;
#elif defined(__APPLE__)
    uint32_t size = sizeof(buf);
    if (_NSGetExecutablePath(buf, &size) != 0) return false;
#else
    ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf)-1);
    if (len == -1) return false;
    buf[len] = '\0';
#endif
    lgsRuntimeLib = fs::path(buf).parent_path();
    validateFilePath(lgsRuntimeLib);
    return true;
}

bool LgsPaths::findLgsRootDir() {
    fs::path root = "";
    switch (lgsConfigs.os) {
    case MAC_OS:
    case LINUX:
        root = "../..";
        break;
    case WINDOWS:
    case UNKNOWN_OS:
        assert(0);
    }
    lgsRootDir = root / LGS_ROOT_DIR;
    lgsPackagesDir = lgsRootDir / LGS_PACKAGES_DIR;
    validateFilePath(lgsRootDir);
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
        break;
    }
    if(!pipe) return false;

    fgets(buffer, sizeof(buffer), pipe);
    std::string clibRoot = buffer;
    if (clibRoot == "") {
        pclose(pipe);
        return false;
    }
    clibRoot.pop_back();
    cLibRootDir = fs::path(clibRoot);
    pclose(pipe);
    validateFilePath(cLibRootDir);
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
    validateFilePath(cLibHeadersDir);
    return true;
}
