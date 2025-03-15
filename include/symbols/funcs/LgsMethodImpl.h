#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"

class LgsMethodImpl final : public LgsFunc {
public:
    string parentName;

    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam*>& params = {}) : LgsFunc(name, funcType, params), parentName(parentName) {
        composedName = parentName + "_" + composedName;
    }
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override;
    void setIRFunc(CodeGenMetadata* metadata);
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
