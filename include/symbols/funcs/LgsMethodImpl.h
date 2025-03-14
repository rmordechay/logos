#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"

class LgsMethodImpl final : public LgsFunc {
public:
    string parentName;

    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName) : LgsFunc(name, funcType), parentName(parentName) {
        setCombinedName();
    }
    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam*>& params) : LgsFunc(name, funcType, params), parentName(parentName) {
        setCombinedName();
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) override;
    void setIRFunc(CodeGenMetadata* metadata);
    void setCombinedName();
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
