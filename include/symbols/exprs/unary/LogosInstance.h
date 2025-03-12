#ifndef LOGOSINSTANCE_H
#define LOGOSINSTANCE_H
#include "LogosUnaryExpr.h"

class LogosInstance final : public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;
    LogosObject* obj = nullptr;

    LogosInstance(const string& name) : name(name) {}
    Value* getInstanceIRValue(CodeGenMetadata* metadata) const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LogosInstance() override;
};

#endif //LOGOSINSTANCE_H
