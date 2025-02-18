#ifndef LOGOSUSERFUNC_H
#define LOGOSUSERFUNC_H
#include "LogosFunc.h"

class LogosFuncImpl final : public LogosFunc {
public:
    explicit LogosFuncImpl(const string& name, LogosType* funcType) : LogosFunc(name, funcType) {}
    string getFuncName() const;
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    Value* callFunc(CodeGenMetadata* metadata);
    FunctionType* getIRFunc() const;
    ~LogosFuncImpl() override = default;
};

#endif //LOGOSUSERFUNC_H
