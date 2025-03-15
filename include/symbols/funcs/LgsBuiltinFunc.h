#ifndef LOGOSBUILTINFUNC_H
#define LOGOSBUILTINFUNC_H
#include "LgsFunc.h"

class LgsBuiltinFunc : public LgsFunc {
public:
    Value* createIRValue(CodeGenMetadata* metadata) override;
    LgsBuiltinFunc(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {}) : LgsFunc(name, funcType, params) {}
    ~LgsBuiltinFunc() override = default;
};

inline Value* LgsBuiltinFunc::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

#endif //LOGOSBUILTINFUNC_H
