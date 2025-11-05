#pragma once
#include <utility>
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
    size_t position = 0;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isConst = false;
    bool isPublic = false;
    bool isVirtual = false;
    bool isOptional = false;
    bool isOwner = false;
    // Not to be confused with type enum. This flag is for direct fields.
    bool isEnumField = false;
    Value* parentIRValue = nullptr;
    LgsType* parent = nullptr;

    LgsField(std::string name, LgsType* type, LgsExpr* expr = nullptr) : name(std::move(name)), type(type), expr(expr) {}
    void setType(LgsType* newType);
    Value* getGEP(LgsLLVMGen& cg) const;
    Value* loadIR(LgsLLVMGen& cg) override;
    Value* resolveVirtualField(LgsLLVMGen* cg, const LgsHashMap* vtable) const;
    ~LgsField() override;
    LgsField* clone();
};
