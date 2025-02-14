#ifndef LOGOSUSERFUNC_H
#define LOGOSUSERFUNC_H
#include "LogosFunc.h"
#include <types/LogosVoid.h>

class LogosUserFunc final : public LogosFunc {
public:
    explicit LogosUserFunc(const std::string& name, LogosType* funcType) : LogosFunc(name, funcType) {}
    explicit LogosUserFunc(const string& name) : LogosUserFunc(name, &LOGOS_VOID) {};
    FunctionCallee getFuncCallee(CodeGenMetadata* metadata) override;
    vector<Value*> getArgs(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    Value* writeLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosUserFunc() override = default;
};

#endif //LOGOSUSERFUNC_H
