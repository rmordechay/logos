#pragma once
#include "exprs/constants/LgsIntConst.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"

class LgsVec final : public LgsIterable {
public:
    int8_t dim = 0;
    std::vector<uint8_t> indices;

    explicit LgsVec(const int8_t dim, LgsType* baseType = &LGS_FLOAT) : LgsIterable(baseType), dim(dim) {
        assert(dim > 1 && dim <= 4);
        size = new LgsIntConst(&LGS_INT, dim);
        isStatic = true;
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    json::value asJsonStr() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    Value* addIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* subIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* mulIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* divIR(LgsLLVMGen& cg, Value* self, Value* other) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) override;
    static int8_t getSwizzleSet(char c);
    static int8_t getComponentIndex(char c);
    std::string strFormatPart() const override;
};
