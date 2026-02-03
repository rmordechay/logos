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
    inline static Lgs_HashMapIndices rttIndices;

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr): LgsIterable(new LgsTypePair(keyType, valueType)) {
        pairType = baseType->asPair();
        isHeapAlloc = true;
        passByRef = true;
        rttKind = RTT_MAP;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    bool canCastTo(LgsType* other) override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* getIRElement(LgsCodeGen& cg, Value* map, Value* index) override;
    Function* generateAddFunc(LgsCodeGen& cg);
    void addIRElement(LgsCodeGen& cg, Value* map, Value* index, Value* value) override;
    Value* getEntryKey(LgsCodeGen& cg, Value* entry) const;
    Value* getEntryValue(LgsCodeGen& cg, Value* entry) const;
    Value* getEntryNext(LgsCodeGen& cg, Value* entry) const;
    bool unpackLoopVars(LgsForeachLoop* loop) const override;
    void setLoopIRVars(LgsCodeGen& cg, LgsForeachLoop* loop) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    Function* generateGetFunc(LgsCodeGen& cg);
};

