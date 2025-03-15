#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"

class LgsFuncImpl final : public LgsFunc {
public:
    explicit LgsFuncImpl(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {}) : LgsFunc(name, funcType, params) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override;
    void setIRFunc(CodeGenMetadata* metadata);
    void setIRName();
    ~LgsFuncImpl() override = default;
};

#endif //LOGOSFUNCIMPL_H
