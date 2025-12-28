#pragma once
#include "LgsDArray.h"
#include "LgsStr.h"
#include "types/LgsTypePair.h"

#define KEYS_FUNC_NAME "keys"
#define VALUES_FUNC_NAME "values"

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsTypePair* mapType = nullptr;

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr): LgsIterable(new LgsTypePair(keyType, valueType)) {
        mapType = baseType->asPair();
        isHeapAlloc = true;
        passByRef = true;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* pointee) override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    bool unpackLoopVarsTypes(LgsForeachLoop* loop) const override;
    void unpackLoopIR(LgsCgModule& cg, LgsForeachLoop* loop) const override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    void addIRElement(LgsCgModule& cg, Value* iterable, Value* index, Value* value) override;
    bool canCastTo(LgsType* other) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

class LgsPair final {
public:
    LgsExpr* key;
    LgsExpr* value;
};
