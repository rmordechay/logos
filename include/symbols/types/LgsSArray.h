#pragma once
#include "funcs/LgsFunc.h"
#include "primitives/LgsInt.h"
#include "types/LgsIterable.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArray";
    size_t arrLength = 0;
    LgsFunc lenFunc{"len", &LGS_INT, {this}, PUBLIC | METHOD};

    explicit LgsSArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        canSlice = true;
        addMethod(&lenFunc);
    }

    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string prettyName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    uint16_t getUnpackCount() const override;
    std::string strFormatPart() const override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool equals(LgsType* other) override;
    ~LgsSArray() override;
};
