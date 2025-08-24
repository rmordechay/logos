#pragma once
#include "exprs/unary/constants/LgsIntConst.h"
#include "primitives/LgsInt.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsFloat.h"

class LgsVec final : public LgsIterable {
public:
    int8_t dim = 0;
    std::vector<uint8_t> indices;

    explicit LgsVec(const int8_t dim, LgsType* baseType = &LGS_FLOAT) : LgsIterable(baseType), dim(dim) {
        assert(dim > 1 && dim <= 4);
        sizeExpr = new LgsIntConst(&LGS_INT, dim);
    }

    Type* getIRType(LgsLLVM& codeGen) override;
    LgsField* getField(const std::string& fieldName) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsLLVM& codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsLLVM* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsLLVM* codeGen, LgsExpr* iterable) override;
    bool canCastTo(LgsType* other) override;
    static int8_t getSwizzleSet(const char c);
    static int8_t getComponentIndex(const char c);
    std::string strFormatPart() const override;
};
