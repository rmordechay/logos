#ifndef LOGOSUSERFUNC_H
#define LOGOSUSERFUNC_H
#include "LogosFunc.h"
#include <types/LogosVoid.h>

class LogosUserFunc final : public LogosFunc {
public:
    string parentName;

    explicit LogosUserFunc(const string& name, LogosType* funcType) : LogosFunc(name, funcType) {}

    Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    Value* callFunc(const CodeGenMetadata* metadata);
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosUserFunc() override = default;
};

#endif //LOGOSUSERFUNC_H
