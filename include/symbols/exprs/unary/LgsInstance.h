#ifndef LOGOSINSTANCE_H
#define LOGOSINSTANCE_H
#include "LgsHashMap.h"
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    LgsObject* obj = nullptr;
    vector<LgsVarDec*> args;
    LgsHashMap vtable = LgsHashMap(&LGS_STR, &LGS_ANY);
    bool isSelf;

    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), obj(obj), isSelf(true) {}
    explicit LgsInstance(LgsType* type) : LgsUnaryExpr(type), isSelf(false) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setVirtualFuncs(CodeGenMetadata* metadata);
    string getName() override;
    ~LgsInstance() override = default;
};

#endif //LOGOSINSTANCE_H
