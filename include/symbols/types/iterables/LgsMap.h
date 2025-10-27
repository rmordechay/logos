#pragma once
#include "LgsStr.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/LgsTypePair.h"
class LgsPair;

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
        addEmptyMethod(KEYS_FUNC_NAME);
        addEmptyMethod(VALUES_FUNC_NAME);
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    LgsFunc* getKeysFunc();
    LgsFunc* getValuesFunc();
    LgsFunc* getAddFunc() override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    bool unpackLoopVarsTypes(LgsForeachLoop* loop) const override;
    void unpackLoopIR(LgsLLVMGen& cg, LgsForeachLoop* loop) const override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    LgsType* clone() override;
    ~LgsMap() override;
};
