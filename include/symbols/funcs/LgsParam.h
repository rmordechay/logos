#ifndef LOGOSPARAM_H
#define LOGOSPARAM_H
#include <LgsValue.h>

class LgsType;

class LgsParam final : public LgsValue {
public:
    string name;
    LgsType* type = nullptr;
    LogosExpr* expr = nullptr;

    LgsParam(const string& name, LgsType* type, LogosExpr* expr) : name(name), type(type), expr(expr) {}
    LgsParam(const string& name, LgsType* type) : LgsParam(name, type, nullptr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsParam() override;
};

#endif //LOGOSPARAM_H
