#ifndef LOGOSUSERFUNC_H
#define LOGOSUSERFUNC_H
#include "LogosFunc.h"
#include "StackFrame.h"

class LogosUserFunc final : public LogosFunc {
public:
    LogosUserFunc(const std::string& name, const LogosType& funcType) : LogosFunc(name, funcType) {}
    const LogosType& getType() const override;
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame) override;
    ~LogosUserFunc() override = default;
};

#endif //LOGOSUSERFUNC_H
