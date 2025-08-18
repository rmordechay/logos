#pragma once
#include <utility>

#include "LgsValue.h"
#include "exprs/unary/LgsHashMap.h"

class LgsEnum;
class LgsObject;
class LgsInstance;
class LgsType;
class LgsExpr;

class LgsField final : public LgsValue {
public:
    std::string name;
    size_t position = 0;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isPublic = false;
    bool isVirtual = false;
    bool isOptional = false;
    Type* parentIRType = nullptr;
    Value* parentIRValue = nullptr;

    LgsField(std::string  name, LgsType* type, LgsExpr* expr = nullptr) : name(std::move(name)), type(type), expr(expr) {}
    Value* resolveVirtualField(LgsCodeGen* codeGen, const LgsHashMap* vtable) const;
    void createIRValue(LgsCodeGen* codeGen) override;
    json::object asJSON() override;
    ~LgsField() override;
};
