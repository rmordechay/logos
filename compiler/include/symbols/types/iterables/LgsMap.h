#pragma once
#include "LgsDArray.h"
#include "LgsStr.h"
#include "types/LgsTypePair.h"

#define KEYS_FUNC_NAME "keys"
#define VALUES_FUNC_NAME "values"

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsTypePair* pairType = nullptr;
    const size_t entriesIndex = 1;
    const size_t lenIndex = 2;
    const size_t capIndex = 3;
    const size_t keyIndex = 0;
    const size_t valueIndex = 1;
    const size_t nextIndex = 2;

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr): LgsIterable(new LgsTypePair(keyType, valueType)) {
        pairType = baseType->asPair();
        isHeapAlloc = true;
        passByRef = true;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    bool canCastTo(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* map, Value* index) override;
    Function* generateAddFunc(LgsCodeGen& cg);
    void addIRElement(LgsCodeGen& cg, Value* map, Value* index, Value* value) override;
    StructType* getEntryStruct(LgsCodeGen& cg) const;
    Value* loadEntriesField(LgsCodeGen& cg, Value* map);
    Value* loadCapField(LgsCodeGen& cg, Value* map);
    Value* getEntryKey(LgsCodeGen& cg, Value* entry) const;
    Value* getEntryValue(LgsCodeGen& cg, Value* entry) const;
    Value* getEntryNext(LgsCodeGen& cg, Value* entry) const;
    bool unpackLoopVars(LgsForeachLoop* loop) const override;
    void setLoopIRVars(LgsCodeGen& cg, LgsForeachLoop* loop) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    Function* generateGetFunc(LgsCodeGen& cg);
};

