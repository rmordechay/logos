#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"

class LgsMethodImpl final : public LgsFunc {
public:
    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam*>& params = {}) : LgsFunc(name, funcType, params) {
        signature.parentName = parentName;
        setComposedName();
    }
    LgsMethodImpl(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {}) : LgsMethodImpl(name, funcType, "", params) {}
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args = {}) override;
    void setIRFunc(CodeGenMetadata* metadata) override;
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
