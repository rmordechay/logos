#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LgsDefinitions.h"
#include "LgsFile.h"
#include "funcs/LgsFuncImpl.h"

class LgsMainFile final : public LgsFile {
public:
    LgsFuncImpl* mainFunc = nullptr;
    vector<LgsFuncImpl*> funcs;

    explicit LgsMainFile(const string& path) : LgsFile(LOGOS_MAIN_FILE, path) {}
    json asJson() const;
    ~LgsMainFile() override;
};

inline json LgsMainFile::asJson() const {
    json fileTree;
    fileTree["file"] = name;
    fileTree["mainFunc"] = mainFunc->asJson();
    fileTree["funcs"] = {};
    for (const auto& func : funcs) {
        fileTree["funcs"].emplace_back(func->asJson());
    }
    return fileTree;
}

inline LgsMainFile::~LgsMainFile() {
    delete mainFunc;
    for (const auto& func : funcs) {
        delete func;
    }
}


#endif //LOGOSMAINFILE_H
