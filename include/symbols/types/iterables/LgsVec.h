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
        sizeExpr = new LgsIntConst(&LGS_INT, dim);
        setRTT();
    }

    Type* getIRType(LgsLLVMGen& cg) override;
    LgsField* getField(const std::string& fieldName) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsLLVMGen& cg, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsLLVMGen* cg, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsLLVMGen* cg, LgsExpr* iterable) override;
    bool canCastTo(LgsType* other) override;
    bool canAssignTo(LgsType* other, LgsAssignType op) override;
    bool canApplyOp(LgsType* other, LgsOperator op) override;
    Value* addIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) override;
    static int8_t getSwizzleSet(char c);
    static int8_t getComponentIndex(char c);
    std::string strFormatPart() const override;
    void setRTT();
};
