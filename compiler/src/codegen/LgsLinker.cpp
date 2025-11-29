#include "codegen/LgsLinker.h"
#include "codegen/LgsCgModule.h"
#include "logos/LgsAppConfigs.h"
#include <llvm/Support/FileSystem.h>
#define LINK_CMD_STRING "clang -flto -o3 %s -L%s -llgs %s -Wl,-rpath,%s -Wl,-rpath,%s %s -o %s"

bool LgsLinker::link() const {
    assert(!paths.lgsRootDir.empty() && !paths.execFile.empty());
    std::string objFileList;
    for (const auto& objPath : fs::directory_iterator(paths.buildDirObjs)) {
        if (objPath.path().extension() == ".o")
            objFileList += objPath.path().string() + " ";
    }
    if (objFileList.empty()) return false;

    std::string userLibs;
    for (const auto& lib : paths.userCLibs) {
        userLibs += fs::canonical(paths.rootPath / lib).string() + " ";
    }

    std::string rpath1 = paths.lgsRootDir;
    std::string rpath2;
    if (!paths.userSearchPaths.empty()) {
        rpath2 = fs::canonical(paths.rootPath / paths.userSearchPaths[0]).string();
    } else {
        rpath2 = paths.lgsRootDir;
    }

    const char* flags = appConfigs.isLibrary ? "-shared -fPIC" : "";
    char cmd[4096];
    std::snprintf(
        cmd,
        sizeof(cmd),
        LINK_CMD_STRING,
        objFileList.c_str(),
        paths.lgsRootDir.c_str(),
        userLibs.c_str(),
        rpath1.c_str(),
        rpath2.c_str(),
        flags,
        paths.execFile.c_str()
    );

    return runCmd(cmd);
}

