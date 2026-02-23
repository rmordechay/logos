#pragma once
#include <string>

#include "LgsValue.h"
#include "exprs/LgsHashMap.h"

class LgsEnum;
class LgsObject;
class LgsInstance;
class LgsType;
class LgsExpr;
class LgsCodeGen;
namespace llvm {
class Value;
}

class LgsField : public LgsValue {
public:
    std::string name;
    unsigned index = 0;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isPublic = false;
    bool isVirtual = false;
    bool isOptional = false;
    bool isMutable = true;
    LgsType* parentType = nullptr;
    Value* gep = nullptr;

    LgsField(const std::string& name, LgsType* type, LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    void setType(LgsType* newType) override;
    Value* getGEP(LgsCodeGen& cg, Value* parentIRPtr);
    LgsType* getType() override;
    Value* loadIRPtr(LgsCodeGen& cg, Value* ptr) const;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsField() override;
};
