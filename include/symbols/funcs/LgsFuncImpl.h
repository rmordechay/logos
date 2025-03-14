#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"

class LgsFuncImpl final : public LgsFunc {
public:

    explicit LgsFuncImpl(const string& name, LgsType* funcType) : LgsFunc(name, funcType) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    void setIRFunc(CodeGenMetadata* metadata);
    void setCombinedName();
    ~LgsFuncImpl() override = default;
};

#endif //LOGOSFUNCIMPL_H
