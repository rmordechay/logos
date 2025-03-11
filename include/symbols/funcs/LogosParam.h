#ifndef LOGOSPARAM_H
#define LOGOSPARAM_H
#include <LogosValue.h>

class LogosType;

class LogosParam final : public LogosValue {
public:
    string name;
    LogosType* type = nullptr;
    LogosExpr* expr = nullptr;

    LogosParam(const string& name, LogosType* type, LogosExpr* expr) : name(name), type(type), expr(expr) {}
    LogosParam(const string& name, LogosType* type) : LogosParam(name, type, nullptr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LogosParam() override = default;
};

#endif //LOGOSPARAM_H
