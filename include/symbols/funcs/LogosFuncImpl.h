#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LogosFunc.h"

class LogosFuncImpl final : public LogosFunc {
public:

    explicit LogosFuncImpl(const string& name, LogosType* funcType) : LogosFunc(name, funcType) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    void setIRFunc(CodeGenMetadata* metadata);
    void setCombinedName();
    ~LogosFuncImpl() override = default;
};

#endif //LOGOSFUNCIMPL_H
