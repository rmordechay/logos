#ifndef LOGOSPARAM_H
#define LOGOSPARAM_H
#include <LgsValue.h>


class LgsVariable;
class LgsExpr;
class LgsType;

class LgsParam final : public LgsValue {
public:
    std::string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isSelf = false;
    bool isVariadic = false;
    AllocaInst* vaList = nullptr;
    std::vector<LgsVariable*> refs;

    explicit LgsParam(LgsType* type = nullptr, const std::string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    std::string format(std::string& indentStr) override;
    Value* getIRValue(LgsRuntime* runtime);
    nlohmann::json asJSON() override;
    std::string getIRName();
    ~LgsParam() override = default;
};

#endif //LOGOSPARAM_H
