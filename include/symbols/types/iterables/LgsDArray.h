#pragma once
#include "types/primitives/LgsLong.h"
#include "funcs/LgsFunc.h"
#include "LgsIterable.h"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";
    StructType* arrStruct = nullptr;

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        addEmptyMethod(MAP_FUNC_NAME);
        addEmptyMethod(FILTER_FUNC_NAME);
        addEmptyMethod(FOREACH_FUNC_NAME);
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    std::string strFormatPart() const override;
    StructType* getArrStruct(LgsLLVMGen& cg);
    LgsFunc* getAddFunc() override;
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    bool canCastTo(LgsType* other) override;
    json::value asJsonStr() override;
};
