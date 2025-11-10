#pragma once
#include "LgsIterable.h"
#define RESERVE_FUNC_NAME "reserve"

class LgsDArray final : public LgsIterable {
public:
    static constexpr auto name = "DArray";

    explicit LgsDArray(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        addEmptyMethod(RESERVE_FUNC_NAME);
        passByRef = true;
        isHeapAlloc = true;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    std::string pname() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string strFormatPart() const override;
    LgsType* applyBinOp(LgsBinaryExpr* binExpr) override;
    LgsFunc* getAddFunc() override;
    LgsFunc* getReserveFunc();
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    void initArr(LgsLLVMGen& cg, Value* iterable);
    bool canCastTo(LgsType* other) override;
};
