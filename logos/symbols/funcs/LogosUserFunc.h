#ifndef LOGOSUSERFUNC_H
#define LOGOSUSERFUNC_H
#include "LogosFunc.h"
#include "StackFrame.h"
#include <types/LogosVoid.h>

class LogosUserFunc final : public LogosFunc {
public:
    LogosUserFunc(const std::string& name, const LogosType& funcType) : LogosFunc(name, funcType) {}
    explicit LogosUserFunc(const string& name) : LogosUserFunc(name, LOGOS_VOID) {};
    const LogosType& getType() const override;
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) override;
    ~LogosUserFunc() override = default;
};

#endif //LOGOSUSERFUNC_H
