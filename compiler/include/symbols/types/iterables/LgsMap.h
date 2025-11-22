#pragma once
#include "LgsStr.h"
#include "types/LgsTypePair.h"

#define KEYS_FUNC_NAME "keys"
#define VALUES_FUNC_NAME "values"

class LgsMap final : public LgsIterable {
public:
    static constexpr auto name = "Map";
    LgsTypePair* typePair = nullptr;

    explicit LgsMap(LgsType* keyType = nullptr, LgsType* valueType = nullptr) {
        typePair = new LgsTypePair(keyType, valueType);
        baseType = typePair;
        isHeapAlloc = true;
        passByRef = true;
        addEmptyMethod(KEYS_FUNC_NAME);
        addEmptyMethod(VALUES_FUNC_NAME);
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    LgsFunc* getKeysFunc();
    LgsFunc* getValuesFunc();
    LgsFunc* getAddFunc() override;
    std::string getName() override;
    std::string pname() override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    bool unpackLoopVarsTypes(LgsForeachLoop* loop) const override;
    void unpackLoopIR(LgsLLVMGen& cg, LgsForeachLoop* loop) const override;
    Value* lenIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    llvm::DIType* getDebugType(LgsLLVMGen& cg) override;
    LgsType* clone() override;
    ~LgsMap() override;
};

class LgsPair final {
public:
    LgsExpr* key;
    LgsExpr* value;
};