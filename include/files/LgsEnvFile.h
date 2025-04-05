#ifndef LGSENVFILE_H
#define LGSENVFILE_H
#include "LgsFile.h"

#include <__filesystem/filesystem_error.h>


class LgsVarDec;

class LgsEnvFile final : public LgsFile {
public:
    vector<LgsVarDec*> varDecs;
    explicit LgsEnvFile(const filesystem::path& path) : LgsFile(path.filename(), path) {}
};

#endif //LGSENVFILE_H
