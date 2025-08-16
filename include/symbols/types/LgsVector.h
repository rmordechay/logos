#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsSArray.h"
#include "types/primitives/LgsFloat.h"

class LgsVector final : public LgsIterable {
public:
    int size = 0;
    static constexpr auto name = "Vector";

    explicit LgsVector(const int size) : LgsIterable(&LGS_FLOAT), size(size) {}
    std::string getName() override;
    std::string prettyName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool equals(LgsType* other) override;
    ~LgsVector() override = default;
};
