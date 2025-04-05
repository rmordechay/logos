#ifndef LGSENVFILE_H
#define LGSENVFILE_H
#include "LgsFile.h"

class LgsEnvObject;
class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    vector<LgsVarDec*> varDecs;

    LgsEnvFile(const path& path, const vector<LgsVarDec*>& varDecs) : LgsFile(path.filename(), path), varDecs(varDecs) {}
};

#endif //LGSENVFILE_H
