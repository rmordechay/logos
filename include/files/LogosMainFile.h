#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LogosDefinitions.h"
#include "LogosFile.h"
#include "funcs/LogosFuncImpl.h"

class LogosFuncImpl;

class LogosMainFile final : public LogosFile {
public:
    LogosFuncImpl* mainFunc = nullptr;
    vector<LogosFuncImpl*> funcs;

    explicit LogosMainFile(const string& path) : LogosFile(LOGOS_MAIN_FILE, path) {}
    ~LogosMainFile() override;
};

inline LogosMainFile::~LogosMainFile() {
    delete mainFunc;
    for (const auto& func : funcs) {
        delete func;
    }
}


#endif //LOGOSMAINFILE_H
