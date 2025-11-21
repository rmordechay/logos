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
    bool isEnumField = false; // Not to be confused with type enum.
    LgsType* parentType = nullptr;
    Value* parentIRPtr = nullptr;
    Value* gep = nullptr;

    LgsField(const std::string& name, LgsType* type, LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    void setType(LgsType* newType);
    Value* getGEP(LgsLLVMGen& cg);
    Value* loadIR(LgsLLVMGen& cg) override;
    Value* resolveVirtualField(LgsLLVMGen* cg, const LgsHashMap* vtable) const;
    ~LgsField() override;
    LgsField* clone() override;
};
