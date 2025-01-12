#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LogosValue.h"

class LogosFunc {
public:
    LogosValue* funcType;

    explicit LogosFunc() : funcType(nullptr) {}
    explicit LogosFunc(LogosValue* funcType) : funcType(funcType) {}
    virtual ~LogosFunc() = default;
};

#endif //LOGOSFUNC_H
