#ifndef LOGOSINSTANCE_H
#define LOGOSINSTANCE_H
#include "LogosUnaryExpr.h"

class LogosInstance final : public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;
    LogosObject* obj = nullptr;

    explicit LogosInstance(LogosObject* obj) : obj(obj) {}
    explicit LogosInstance(const string& name) : name(name) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LogosInstance() override;
};

#endif //LOGOSINSTANCE_H
