#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "funcs/LogosFunc.h"

#include <vector>

class LogosMainFile {
public:
    LogosFunc* mainFunc;
    std::vector<LogosFunc*> funcs;
    ~LogosMainFile();
};

#endif //LOGOSMAINFILE_H
