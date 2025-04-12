#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LgsData.h"
#include "LgsFile.h"
#include "funcs/LgsFuncImpl.h"

class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    LgsFuncImpl* mainFunc = nullptr;
    vector<LgsFuncImpl*> funcs;
    vector<LgsEnum*> enums;
    vector<LgsObject*> objects;

    explicit LgsMainFile(const string& path) : LgsFile(LOGOS_MAIN_FILE_NAME, path) {}
    ~LgsMainFile() override;
};

inline LgsMainFile::~LgsMainFile() {
    delete mainFunc;
    for (const auto& func : funcs) {
        delete func;
    }
}


#endif //LOGOSMAINFILE_H
