#ifndef LOGOSPARAM_H
#define LOGOSPARAM_H
#include <LgsValue.h>

class LgsType;

class LgsParam final : public LgsValue {
public:
    string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;

    LgsParam(const string& name, LgsType* type, LgsExpr* expr) : name(name), type(type), expr(expr) {}
    LgsParam(const string& name, LgsType* type) : LgsParam(name, type, nullptr) {}
    explicit LgsParam(LgsType* type) : LgsParam("", type, nullptr) {}
    json asJson() override;
    ~LgsParam() override;
};

#endif //LOGOSPARAM_H
