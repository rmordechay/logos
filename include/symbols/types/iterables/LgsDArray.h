#pragma once
#include "LgsIterable.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    StructType* arrStruct = nullptr;

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        addEmptyMethod(MAP_FUNC_NAME);
        addEmptyMethod(FILTER_FUNC_NAME);
        addEmptyMethod(FOREACH_FUNC_NAME);
        isHeapAlloc = true;
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    std::string strFormatPart() const override;
    StructType* getArrStruct(LgsLLVMGen& cg);
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    LgsFunc* getAddFunc() override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    bool canCastTo(LgsType* other) override;
    json::value asJsonStr() override;
};
