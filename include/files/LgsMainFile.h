#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "data/LgsDefinitions.h"
#include "LgsFile.h"
#include "types/LgsEnum.h"
#include "types/LgsObject.h"

class LgsMainFunc;
class LgsEnum;

class LgsMainFile final : public LgsFile {
public:
    vector<LgsEnum*> enums;
    vector<LgsObject*> objects;
    vector<LgsInterface*> interfaces;
    map<string, LgsFunc*> funcs;

    explicit LgsMainFile(const string& path) : LgsFile(LOGOS_MAIN_FILE_NAME, path) {}
    void format() override;
    json asJSON() override;
    Module* generateIR(LogosProject& project) override;
    ~LgsMainFile() override;
};

#endif //LOGOSMAINFILE_H
