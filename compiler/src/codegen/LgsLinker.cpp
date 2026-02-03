#include "codegen/LgsLinker.h"
#include "codegen/LgsCodeGen.h"
#include "logos/LgsAppConfigs.h"
#include <llvm/Support/FileSystem.h>
#define LINK_CMD_STRING "clang -flto -o%d %s -L%s -llgs %s -Wl,-rpath,%s %s -o %s"

bool LgsLinker::link() const {
    assert(paths.lgsRootDir != "" && paths.execFile != "");
    std::string objFileList;
    for (const auto& objPath : fs::directory_iterator(paths.buildDirObjs)) {
        if (objPath.path().extension() == ".o") {
            objFileList += objPath.path().string() + " ";
        }
    }
    // paths.cblasDir = "../external/libcblas.a";
    assert(objFileList != "");
    std::string additionalLibs;
    for (const auto& appPath : paths.userCLibs) {
        additionalLibs += std::string(appPath) + " ";
    }
    additionalLibs += std::string(paths.cblasDir) + " ";
    const auto flags = appConfigs.isLibrary ? "-shared -fPIC" : "";
    char cmd[1024*4];
    std::snprintf(
        cmd,
        sizeof(cmd),
        LINK_CMD_STRING,
        appConfigs.optLevel,
        objFileList.c_str(),
        paths.lgsRootDir.c_str(),
        additionalLibs.c_str(),
        paths.lgsRootDir.c_str(),
        flags,
        paths.execFile.c_str()
    );
    return runCmd(cmd);
}

