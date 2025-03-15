#ifndef LOGOSBUILTINFUNC_H
#define LOGOSBUILTINFUNC_H
#include "LgsFunc.h"

class LgsBuiltinFunc : public LgsFunc {
public:
    Value* createIRValue(CodeGenMetadata* metadata) override;
    LgsBuiltinFunc(const string& name, LgsType* funcType) : LgsFunc(name, funcType) {}
    ~LgsBuiltinFunc() override = default;
};

inline Value* LgsBuiltinFunc::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

#endif //LOGOSBUILTINFUNC_H
