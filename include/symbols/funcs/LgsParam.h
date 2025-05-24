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
    vector<LgsVariable*> refs;
    bool isVariadic = false;
    AllocaInst* vaList = nullptr;

    explicit LgsParam(LgsType* type = nullptr, const string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    string format(string& indentStr) override;
    Value* getIRValue(CodeGenMetadata* metadata);
    json asJSON() override;
    string getIRName();
    ~LgsParam() override = default;
};

#endif //LOGOSPARAM_H
