#pragma once
#include <utility>
#include "LgsValue.h"
#include "../exprs/LgsHashMap.h"

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
    bool isConst = false;
    bool isPublic = false;
    bool isVirtual = false;
    bool isOptional = false;
    bool isOwner = true;
    Type* parentIRType = nullptr;
    Value* parentIRValue = nullptr;

    LgsField(std::string  name, LgsType* type, LgsExpr* expr = nullptr) : name(std::move(name)), type(type), expr(expr) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    Value* resolveVirtualField(LgsLLVMGen* cg, const LgsHashMap* vtable) const;
    json::value asJSON() override;
    LgsField* clone() const;
    ~LgsField() override;
};
