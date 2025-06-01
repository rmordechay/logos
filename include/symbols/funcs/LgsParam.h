#ifndef LOGOSPARAM_H
#define LOGOSPARAM_H
#include "exprs/unary/constants/LgsIntConst.h"
#include <LgsValue.h>

class LgsFuncImpl;
class LgsVariable;
class LgsExpr;
class LgsType;

class LgsParam final : public LgsValue {
public:
    std::string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    std::vector<LgsVariable*> refs;
    bool isVariadic = false;
    AllocaInst* vaList = nullptr;

    explicit LgsParam(LgsType* type = nullptr, const string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    std::string format(std::string& indentStr) override;
    Value* getIRValue(Module* module);
    json asJSON() override;
    std::string getIRName();
    ~LgsParam() override = default;
};

#endif //LOGOSPARAM_H
