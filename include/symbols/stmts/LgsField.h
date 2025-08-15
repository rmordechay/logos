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
    std::string* parentName;
    size_t position = 0;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isPublic = false;
    bool isVirtual = false;
    bool isOptional = false;
    Type* parentIRType = nullptr;

    LgsField(std::string  name, std::string* parentName, LgsType* type, LgsExpr* expr = nullptr) : name(std::move(name)), parentName(parentName), type(type), expr(expr) {}
    Value* getGEP(LgsCodeGen* codeGen, Value* parentIRValue) const;
    void createIRValue(LgsCodeGen* codeGen) override;
    Value* resolveVirtualField(LgsCodeGen* codeGen, const LgsHashMap* vtable, Value* parentIRValue) const;
    ~LgsField() override;
};
