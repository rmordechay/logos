#include "codegen/LgsLinker.h"
#include "codegen/LgsLLVMGen.h"
#include "logos/LgsAppConfigs.h"
#include "llvm/Bitcode/BitcodeWriter.h"

#include <iostream>
#include <llvm/Support/FileSystem.h>

#define LINK_CMD_STRING "clang %s -L%s -llgs %s %s -Wl,-rpath,%s %s -o %s"

bool LgsLinker::link() const {
    assert(paths.lgsRootDir != "" && paths.execFile != "");
    std::string objFileList;
    for (const auto& objPath : fs::directory_iterator(paths.buildDirObjs)) {
        if (objPath.path().extension() == ".o") {
            objFileList += objPath.path().string() + " ";
        }
    }
    assert(objFileList != "");
    std::string additionalLibs;
    for (const auto& appPath : externalLibs) {
        additionalLibs += appPath + "/build/app ";
    }
    const auto flags = appConfigs.isLibrary ? "-shared -fPIC" : "";
    const auto cblasDir = "/Users/r.mordechay/Desktop/Programming/logos/external/libcblas.a";
    char cmd[1024*4];
    std::snprintf(
        cmd,
        sizeof(cmd),
        LINK_CMD_STRING,
        objFileList.c_str(),
        paths.lgsRootDir.c_str(),
        cblasDir,
        additionalLibs.c_str(),
        paths.lgsRootDir.c_str(),
        flags,
        paths.execFile.c_str()
    );
    return runCmd(cmd);
}
