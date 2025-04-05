#ifndef LGSENVFILE_H
#define LGSENVFILE_H
#include "LgsFile.h"

class LgsEnv;
class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    LgsEnv* env;

    LgsEnvFile(const path& path, LgsEnv* env) : LgsFile(path.filename(), path), env(env) {}
};

#endif //LGSENVFILE_H
