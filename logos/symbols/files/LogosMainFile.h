#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LogosFile.h"

class LogosMainFile final : public LogosFile {
public:
    LogosUserFunc* mainFunc = nullptr;
    std::vector<LogosFunc*> funcs;

    explicit LogosMainFile() : LogosFile(LOGOS_MAIN_FILE) {}
    Module* generateModule(const TargetMachine& targetMachine, IRBuilder<>& builder) override;
    ~LogosMainFile() override;
};


#endif //LOGOSMAINFILE_H
