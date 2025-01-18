#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LogosFile.h"
#include "funcs/LogosFunc.h"

class LogosMainFile final : public LogosFile {
public:
    LogosFunc* mainFunc = nullptr;
    std::vector<LogosFunc*> funcs;
    ~LogosMainFile() override;
};


#endif //LOGOSMAINFILE_H
