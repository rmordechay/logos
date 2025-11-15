#pragma once
#include "types/iterables/LgsIterable.h"

using llvm::StructType;

class LgsSet final : public LgsIterable {
public:
    static constexpr auto name = "set";
    StructType* arrStruct = nullptr;

    explicit LgsSet(LgsType* baseType = nullptr) : LgsIterable(baseType) {
        passByRef = true;
        isHeapAlloc = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    StructType* getArrStruct(LgsLLVMGen& cg);
    LgsFunc* getAddFunc() override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    LgsType* applyBinOp(LgsBinaryExpr* binExpr) override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
};
