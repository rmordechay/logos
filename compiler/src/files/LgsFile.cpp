#include "files/LgsFile.h"

#include "LgsDefinitions.h"
#include "logos/LgsAppConfigs.h"

bool LgsFile::isMain() const {
    return path.filename() == LGS_MAIN_FILE;
}

size_t LgsFile::hashFile() {
    assert(0);
}

void LgsFile::setupCodeGen(LgsAppConfigs& appConfigs_) {
    cgFile.appConfigs = &appConfigs_;
    cgFile.cg.setupModule(path, appConfigs_.debugMode);
}