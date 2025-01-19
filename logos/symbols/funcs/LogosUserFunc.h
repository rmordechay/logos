#ifndef LOGOSUSERFUNC_H
#define LOGOSUSERFUNC_H
#include "LogosFunc.h"
#include "StackFrame.h"
#include <types/LogosVoid.h>

class LogosUserFunc final : public LogosFunc {
public:
    explicit LogosUserFunc(const std::string& name, const LogosType* funcType) : LogosFunc(name, funcType) {}
    explicit LogosUserFunc(const string& name) : LogosUserFunc(name, &LOGOS_VOID) {};
    Value* getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) override;
    ~LogosUserFunc() override = default;
};

#endif //LOGOSUSERFUNC_H
