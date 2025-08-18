#pragma once
#include "LgsUnaryExpr.h"
#include "types/LgsObject.h"

class LgsInstance final : public LgsUnaryExpr {
public:
    std::string name;
    LgsObject* obj = nullptr;

   std::map<std::string, LgsVarDec*> args;
    explicit LgsInstance(const std::string& name): name(name) {}
    explicit LgsInstance(LgsObject* obj) : LgsUnaryExpr(obj), name(obj->name), obj(obj) {}
    void setObject(LgsObject* newObj);
    void setVirtuals(LgsCodeGen* codeGen) const;
    void initFields(LgsCodeGen* codeGen, std::map<std::string, LgsField*>& fields);
    void createIRValue(LgsCodeGen* codeGen) override;
    json::object asJSON() override;
    bool castTo(LgsType* toType) override;
    std::string pname() override;
    ~LgsInstance() override;
};
