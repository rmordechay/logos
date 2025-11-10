#pragma once
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"

class LgsVec final : public LgsIterable {
public:
    int8_t vectorDim = 0;
    std::vector<uint8_t> indices;

    explicit LgsVec(const int8_t dim, LgsType* baseType = &LGS_FLOAT) : LgsIterable(baseType), vectorDim(dim) {
        assert(dim > 1 && dim <= 4);
        size = new LgsIntConst(&LGS_INT, dim);
        isStatic = true;
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsBinaryExpr* binExpr) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    Value* dotProduct(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) const;
    static int8_t getSwizzleSet(char c);
    static int8_t getComponentIndex(char c);
    std::string strFormatPart() const override;
};
