#include "files/LgsEnvFile.h"
#include "LgsUtils.h"

size_t LgsEnvFile::hashFile() {
    size_t hash = 0;
    HASH_VECTOR(varDecs, hash);
    return hash;
}

LgsEnvFile::~LgsEnvFile() {
    for (const auto varDec : varDecs) {
        freeStmt(varDec);
    }
    varDecs.clear();
}
