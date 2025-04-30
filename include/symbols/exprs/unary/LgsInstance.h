#ifndef LOGOSINSTANCE_H
#define LOGOSINSTANCE_H
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    LgsObject* obj = nullptr;
    vector<LgsVarDec*> args;
    bool isSelf;

    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), obj(obj), isSelf(true) {}
    explicit LgsInstance(LgsType* type) : LgsUnaryExpr(type), isSelf(false) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setVirtualFuncs(CodeGenMetadata* metadata) const;
    string getName() override;
    ~LgsInstance() override = default;
};

#endif //LOGOSINSTANCE_H
