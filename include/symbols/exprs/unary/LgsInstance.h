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
    void setVirtuals(LgsLLVMGen& cg) const;
    json::value asJSON() override;
    std::string pname() override;
    ~LgsInstance() override;
};
