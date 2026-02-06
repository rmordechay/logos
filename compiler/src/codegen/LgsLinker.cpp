#include "codegen/LgsLinker.h"
#include "codegen/LgsCodeGen.h"
#include "logos/LgsAppConfigs.h"
#include <llvm/Support/FileSystem.h>

bool LgsLinker::link() const {
    assert(paths.lgsRootDir != "" && paths.execFile != "");
    std::string objFileList;
    for (const auto& objPath : fs::directory_iterator(paths.buildDirObjs)) {
        if (objPath.path().extension() == ".bc") {
            objFileList += objPath.path().string() + " ";
        }
    }
    // paths.cblasDir = "../external/libcblas.a";
    assert(objFileList != "");
    std::string additionalCUserLibs;
    for (const auto& libDir : paths.userCLibs) {
        additionalCUserLibs += std::string(libDir) + " ";
    }
    // additionalLibs += std::string(paths.cblasDir) + " ";
    const auto flags = !appConfigs.isLibrary ? "-flto -fstack-protector-strong -Wno-override-module" : "-shared -fPIC";
    char cmd[1024*4];
    std::snprintf(
        cmd,
        sizeof(cmd),
        CLANG_PATH " %s %s -L%s -llgs -Wl,-rpath,%s -o %s",
        flags,
        objFileList.c_str(),
        paths.lgsRootDir.c_str(),
        paths.lgsRootDir.c_str(),
        paths.execFile.c_str()
    );
    if (!runCmd(cmd)) assert(0);
    return true;
}

