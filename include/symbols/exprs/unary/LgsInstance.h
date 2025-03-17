#ifndef LOGOSINSTANCE_H
#define LOGOSINSTANCE_H
#include "LgsUnaryExpr.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    string name;
    vector<LgsExpr*> args;
    LgsObject* obj = nullptr;
    map<string, LgsField*> fields;

    explicit LgsInstance(const string& name) : name(name) {}
    Value* getInstanceIRValue(CodeGenMetadata* metadata) const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LgsInstance() override;
};

#endif //LOGOSINSTANCE_H
