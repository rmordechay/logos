#pragma once
#include <string>
#include <vector>

#include "exprs/LgsExpr.h"
#include "types/LgsObject.h"
#include "LgsValue.h"

class LgsCodeGen;
class LgsField;
class LgsType;
namespace llvm {
class Type;
class Value;
}

class LgsInstance final : public LgsExpr {
public:
    std::string name;
    LgsObject* obj = nullptr;
    std::vector<LgsVarDec> args;
    std::vector<LgsType*> typeArgs;

    explicit LgsInstance(const std::string& name): name(name) {}
    explicit LgsInstance(LgsObject* obj) : LgsExpr(obj), name(obj->name), obj(obj) {}
    void setType(LgsType* newObj) override;
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCodeGen& cg) override;
    std::string asText() override;
    static Value* getInstanceRTType(LgsCodeGen& cg, Value* instance);
    static Value* loadRTType(LgsCodeGen& cg, Type* ty, Value* ptr);
    ~LgsInstance() override;
};
