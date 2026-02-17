#include "files/LgsFile.h"

#include "LgsDefinitions.h"
#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "files/LgsTestFile.h"
#include "logos/LgsAppConfigs.h"

bool LgsFile::isMain() const {
    return path.filename() == LGS_MAIN_FILE;
}

size_t LgsFile::hashFile() {
    assert(0);
}

void LgsFile::setupCodeGen(LgsAppConfigs& appConfigs) {
    cgFile.appConfigs = &appConfigs;
    cgFile.cg.setupModule(path, appConfigs.debugMode);
}

LgsMainFile* LgsFile::asMainFile() {
    return dynamic_cast<LgsMainFile*>(this);
}

LgsObjectFile* LgsFile::asObjectFile() {
    return dynamic_cast<LgsObjectFile*>(this);
}

LgsInterfaceFile* LgsFile::asInterfaceFile() {
    return dynamic_cast<LgsInterfaceFile*>(this);
}

LgsTestFile* LgsFile::asTestFile() {
    return dynamic_cast<LgsTestFile*>(this);
}

LgsEnvFile* LgsFile::asEnvFile() {
    return dynamic_cast<LgsEnvFile*>(this);
}

LgsAppFile* LgsFile::asAppFile() {
    return dynamic_cast<LgsAppFile*>(this);
}
