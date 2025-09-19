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
        if (dim == 2) rtt = RTT_VEC2;
        else if (dim == 3) rtt = RTT_VEC3;
        else if (dim == 4) rtt = RTT_VEC4;
        else rtt = RTT_UNKNOWN;
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
    bool canCastTo(LgsType* other) override;
    Value* IRLength(LgsLLVMGen& cg, Value* iterable) override;
    LgsType* applyOp(LgsType* other, LgsOperator op) override;
    Value* addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) override;
    static int8_t getSwizzleSet(char c);
    static int8_t getComponentIndex(char c);
    std::string strFormatPart() const override;
};
