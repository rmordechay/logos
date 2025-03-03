#ifndef LOGOSBUILTINFUNC_H
#define LOGOSBUILTINFUNC_H
#include "LogosFunc.h"

class LogosBuiltinFunc : public LogosFunc {
public:
    LogosBuiltinFunc(const string& name, LogosType* funcType) : LogosFunc(name, funcType) {}
    ~LogosBuiltinFunc() override = default;
};

#endif //LOGOSBUILTINFUNC_H
