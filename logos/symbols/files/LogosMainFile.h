#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LogosFile.h"
#include "funcs/LogosFunc.h"
#include "funcs/LogosUserFunc.h"

class LogosMainFile final : public LogosFile {
public:
    LogosUserFunc* mainFunc = nullptr;
    std::vector<LogosFunc*> funcs;
    ~LogosMainFile() override;
};


#endif //LOGOSMAINFILE_H
