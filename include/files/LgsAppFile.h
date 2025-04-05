#ifndef LGSAPPFILE_H
#define LGSAPPFILE_H
#include "LgsData.h"
#include "LgsFile.h"

struct RequireEnvVar {
    string name;
    LgsType* type;
};

class LgsAppFile final : public LgsFile {
public:
    vector<LgsVarDec*> varDecs;
    vector<RequireEnvVar> requireEnvVars;

    explicit LgsAppFile(const string& path, const vector<LgsVarDec*>& varDecs) : LgsFile(LOGOS_APP_FILE_NAME, path), varDecs(varDecs) {}
};

#endif //LGSAPPFILE_H
