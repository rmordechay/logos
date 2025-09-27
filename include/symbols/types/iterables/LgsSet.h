#pragma once
#include "types/iterables/LgsIterable.h"

class LgsSet final : public LgsIterable {
public:
    static constexpr auto name = "Set";
    StructType* arrStruct = nullptr;

    explicit LgsSet(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        addEmptyMethod(MAP_FUNC_NAME);
        addEmptyMethod(FILTER_FUNC_NAME);
        addEmptyMethod(FOREACH_FUNC_NAME);
        isHeapAlloc = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    StructType* getArrStruct(LgsLLVMGen& cg);
    LgsFunc* getAddFunc() override;
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    json::value asJsonStr() override;
};
