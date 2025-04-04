#ifndef LOGOSINSTANCE_H
#define LOGOSINSTANCE_H
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    LgsObject* obj = nullptr;
    vector<LgsExpr*> args;
    map<string, LgsField*> fields;

    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), obj(obj) {}
    explicit LgsInstance(LgsType* type) : LgsUnaryExpr(type) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LgsInstance() override;
};

#endif //LOGOSINSTANCE_H
