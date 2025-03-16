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
    void printTree() const;
    ~LgsMainFile() override;
};

inline void LgsMainFile::printTree() const {
    json fileTree;
    fileTree["file"] = name;
    fileTree["mainFunc"] = mainFunc->asJson();
    fileTree["funcs"] = {};
    // for (const auto& func : funcs) {
    //     fileTree["funcs"].emplace_back(func->print());
    // }
    std::cout << fileTree.dump(4) << '\n';
}

inline LgsMainFile::~LgsMainFile() {
    delete mainFunc;
    for (const auto& func : funcs) {
        delete func;
    }
}


#endif //LOGOSMAINFILE_H
