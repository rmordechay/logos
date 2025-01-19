#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LogosFile.h"
#include "funcs/LogosFunc.h"
#include "funcs/LogosUserFunc.h"

class LogosMainFile final : public LogosFile {
public:
    LogosUserFunc* mainFunc = nullptr;
    std::vector<LogosFunc*> funcs;

    explicit LogosMainFile() : LogosFile(LOGOS_MAIN_FILE) {}

    ~LogosMainFile() override {
        delete mainFunc;
        for (const auto func : funcs) {
            delete func;
        }

    }
};


#endif //LOGOSMAINFILE_H
