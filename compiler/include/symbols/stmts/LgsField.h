#pragma once
#include "LgsValue.h"
#include "exprs/LgsHashMap.h"

class LgsEnum;
class LgsObject;
class LgsInstance;
class LgsType;
class LgsExpr;

class LgsField final : public LgsValue {
public:
    std::string name;
    unsigned position = 0;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isPublic = false;
    bool isVirtual = false;
    bool isOptional = false;
    bool isMutable = true;
    LgsType* parentType = nullptr;

    LgsField(const std::string& name, LgsType* type, LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    void setType(LgsType* newType);
    Value* getGEP(LgsCodeGen& cg, Value* parentIRPtr) const;
    Value* loadIR(LgsCodeGen& cg) override;
    std::string getName() override;
    LgsType* getType() override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsField() override;
};
