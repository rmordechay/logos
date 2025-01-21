#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LogosFile.h"

class LogosMainFile final : public LogosFile {
public:
    LogosUserFunc* mainFunc = nullptr;
    std::vector<LogosFunc*> funcs;

    explicit LogosMainFile() : LogosFile(LOGOS_MAIN_FILE) {}
    Module* generateModule(IRBuilder<>& builder, LogosStack& theStack) override;
    void initModule(IRBuilder<>& builder, LogosStack& theStack) override;
    ~LogosMainFile() override;
};


#endif //LOGOSMAINFILE_H
