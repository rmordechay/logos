#pragma once
#include "LgsDArray.h"
#include "LgsStr.h"
#include "types/LgsTypePair.h"

#define KEYS_FUNC_NAME "keys"
#define VALUES_FUNC_NAME "values"

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsTypePair* typePair = nullptr;

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr): LgsIterable(new LgsTypePair(keyType, valueType)) {
        typePair = baseType->asPair();
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
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    bool canCastTo(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* pointee) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* loadEntriesField(LgsCgModule& cg, Value* map);
    Value* loadCapField(LgsCgModule& cg, Value* map);
    Value* getEntryKey(LgsCgModule& cg, Value* entry) const;
    Value* getEntryValue(LgsCgModule& cg, Value* entry) const;
    Value* getEntryNext(LgsCgModule& cg, Value* entry) const;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsCgModule& cg, LgsExpr* map, LgsExpr* index) override;
    void addIRElement(LgsCgModule& cg, LgsExpr* map, LgsExpr* index, LgsExpr* value) override;
    StructType* getEntryStruct(LgsCgModule& cg) const;
    bool unpackLoopVarsTypes(LgsForeachLoop* loop) const override;
    void unpackLoopIR(LgsCgModule& cg, LgsForeachLoop* loop) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
};

class LgsPair final {
public:
    LgsExpr* key;
    LgsExpr* value;
};
