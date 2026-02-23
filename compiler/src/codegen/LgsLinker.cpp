#include "codegen/LgsLinker.h"

#include <_stdio.h>
#include <assert.h>
#include <filesystem>

#include "logos/LgsAppConfigs.h"
#include "LgsUtils.h"
#include "logos/LgsPaths.h"

bool LgsLinker::link() const {
    assert(paths.lgsRootDir != "" && paths.execFile != "");
    std::string objFileList;
    for (const auto& fileName : filesToLink) {
        const fs::path path(paths.buildDirObjs / (fileName + ".bc"));
        if (!fs::exists(path)) continue;
        objFileList += path.string() + " ";
    }
    for (auto importPath : importPaths) {
        for (const auto& objPath : fs::directory_iterator(importPath)) {
            if (objPath.path().extension() == ".bc") {
                objFileList += objPath.path().string() + " ";
            }
        }
    }
    assert(objFileList != "");
    std::string additionalLibs;
    for (const auto& libDir : paths.userCLibs) {
        additionalLibs += std::string(libDir) + " ";
    }
    // paths.cblasDir = "../external/libcblas.a";
    // additionalLibs += std::string(paths.cblasDir) + " ";
    const auto flags = !appConfigs.isLibrary ? "-flto -fstack-protector-strong -Wno-override-module" : "-shared -fPIC";
    char cmd[1024*4];
    std::snprintf(
        cmd,
        sizeof(cmd),
        CLANG_PATH " %s %s -L%s %s -llgs -Wl,-rpath,%s -o %s",
        flags,
        objFileList.c_str(),
        paths.lgsRootDir.c_str(),
        additionalLibs.c_str(),
        paths.lgsRootDir.c_str(),
        paths.execFile.c_str()
    );
    if (!runCmd(cmd)) assert(0);
    return true;
}

