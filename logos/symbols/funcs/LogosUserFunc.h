#ifndef LOGOSUSERFUNC_H
#define LOGOSUSERFUNC_H
#include "LogosFunc.h"
#include <types/LogosVoid.h>

class LogosUserFunc final : public LogosFunc {
public:
    explicit LogosUserFunc(const std::string& name, LogosType* funcType) : LogosFunc(name, funcType) {}
    explicit LogosUserFunc(const string& name) : LogosUserFunc(name, &LOGOS_VOID) {};
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    ~LogosUserFunc() override = default;
};

#endif //LOGOSUSERFUNC_H
