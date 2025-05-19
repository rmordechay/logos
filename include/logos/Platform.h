#ifndef PLATFORM_H
#define PLATFORM_H
#include "LgsDefinitions.h"
#include <string>
#include <vector>
#include <lld/Common/Driver.h>

using namespace std;
using namespace llvm;

struct LgsPaths {
    path rootDir;
    path rootDirAbs;
    path srcDir;
    path envsDir;
    path buildDir;
    path appFilePath;
    path objFilePath;
    path execFilePath;
};

struct Platform {
    string osName;
    string linker;
    string libRoot;
    string arch;
    string platformVersion;
    string inputFile;
    string outputFile;
    vector<const char*> linkerOpts;
    bool (*link)(ArrayRef<const char*>, raw_ostream&, raw_ostream&, bool, bool);
};

inline LgsPaths paths;
inline Platform platform;

inline void setPlatform(const string& inputFile, const string& outputFile) {
    platform.inputFile = inputFile;
    platform.outputFile = outputFile;
#if defined(__linux__)
    platform.osName = "Linux";
    platform.linker = "ld";
    platform.libRoot = "/usr/lib/aarch64-linux-gnu/";
    platform.arch = ARCH_NAME;
    platform.linkerOpts = {
        "ld.lld",
        "-L", "/usr/lib/aarch64-linux-gnu",
        "-lc",
        "--dynamic-linker", "/lib/ld-linux-aarch64.so.1",
        "/usr/lib/aarch64-linux-gnu/crti.o",
        "/usr/lib/aarch64-linux-gnu/crtn.o",
        platform.inputFile.c_str(),
        "-o", platform.outputFile.c_str()
    };
    platform.link = lld::elf::link;
#elif defined(__APPLE__) && defined(__MACH__)
    platform.osName = "macos";
    platform.linker = "ld.lld";
    platform.libRoot = "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk";
    platform.platformVersion = "15.0";
    platform.arch = ARCH_NAME;
    platform.linkerOpts = {
        platform.linker.c_str(),
        platform.inputFile.c_str(),
        "../stdlib/lgslib.a",
        "-o", platform.outputFile.c_str(),
        "-lSystem",
        "-syslibroot", platform.libRoot.c_str(),
        "-platform_version", platform.osName.c_str(), platform.platformVersion.c_str(), platform.platformVersion.c_str(),
        "-arch", platform.arch.c_str()
    };
    platform.link = lld::macho::link;
#elif defined(_WIN32)
    platform.osName = "macos";
#endif
}

#endif //PLATFORM_H
