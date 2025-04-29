#ifndef LOGOSPARAM_H
#define LOGOSPARAM_H
#include <LgsValue.h>

class LgsFuncImpl;
class LgsVariable;
class LgsExpr;
class LgsType;

class LgsParam final : public LgsValue {
public:
    string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    LgsFuncImpl* callbackFunc = nullptr;
    vector<LgsVariable*> refs;

    LgsParam(const string& name, LgsType* type, LgsExpr* expr) : name(name), type(type), expr(expr) {}
    explicit LgsParam(LgsFuncImpl* func);
    explicit LgsParam(LgsType* type) : name(""), type(type) {}
    string format(string& indentStr) override;
    json asJSON() override;
    ~LgsParam() override = default;
};

#endif //LOGOSPARAM_H
