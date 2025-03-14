#ifndef LOGOSINSTANCE_H
#define LOGOSINSTANCE_H
#include "LogosUnaryExpr.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;
    LgsObject* obj = nullptr;

    LgsInstance(const string& name) : name(name) {}
    Value* getInstanceIRValue(CodeGenMetadata* metadata) const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LgsInstance() override;
};

#endif //LOGOSINSTANCE_H
