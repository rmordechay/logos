#pragma once
#include "LgsValue.h"
#include "exprs/LgsHashMap.h"

class LgsEnum;
class LgsObject;
class LgsInstance;
class LgsType;
class LgsExpr;

class LgsField final : public LgsValue, public LgsOwner {
public:
    std::string name;
    unsigned position = 0;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isConst = false;
    bool isPublic = false;
    bool isVirtual = false;
    bool isOptional = false;
    bool isOwner = true;
    bool isEnumField = false; // Not to be confused with type enum.
    LgsType* parentType = nullptr;

    LgsField(const std::string& name, LgsType* type, LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    void setType(LgsType* newType);
    Value* getGEP(LgsCgModule& cg, Value* parentIRPtr) const;
    Value* loadIR(LgsCgModule& cg) override;
    std::string getName() override;
    LgsType* getType() override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsField() override;
};
