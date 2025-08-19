#pragma once
#include "exprs/unary/constants/LgsIntConst.h"
#include "primitives/LgsInt.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsFloat.h"

class LgsVec final : public LgsIterable {
public:
    int8_t dim = 0;

    explicit LgsVec(const int8_t dim, LgsType* baseType = &LGS_FLOAT) : LgsIterable(baseType), dim(dim) {
        sizeExpr = new LgsIntConst(&LGS_INT, dim);
    }

    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    json::object asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool equals(LgsType* other) override;
    std::string strFormatPart() const override;
};
