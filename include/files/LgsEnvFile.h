#ifndef LGSENVFILE_H
#define LGSENVFILE_H
#include "LgsFile.h"

class LgsEnvObj;
class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    LgsEnvObj* env;

    LgsEnvFile(const path& path, LgsEnvObj* env) : LgsFile(path.filename(), path), env(env) {}
};

#endif //LGSENVFILE_H
