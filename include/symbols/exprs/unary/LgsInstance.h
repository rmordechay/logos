#ifndef LOGOSINSTANCE_H
#define LOGOSINSTANCE_H
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    string name;
    LgsObject* obj = nullptr;
    vector<LgsVarDec*> args;

    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), name(obj->name), obj(obj) {}
    explicit LgsInstance(const string& name) : name(name) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    void setImplementsVFuncs(LgsRuntime* runtime) const;
    void free(LgsRuntime* runtime) override;
    string getName() override;
    void setReturnExpr(LgsRuntime* runtime, Type* objIRType);
    ~LgsInstance() override = default;
};

#endif //LOGOSINSTANCE_H
