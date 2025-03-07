#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LogosFunc.h"

class LogosFuncImpl final : public LogosFunc {
public:
    explicit LogosFuncImpl(const string& name, LogosType* funcType) : LogosFunc(name, funcType) {}

    Function* getIRFunc(CodeGenMetadata* metadata);
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    Value* call(CodeGenMetadata* metadata);
    ~LogosFuncImpl() override = default;
};

#endif //LOGOSFUNCIMPL_H
