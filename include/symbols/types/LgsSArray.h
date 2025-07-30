#pragma once
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsInt.h"
#include "types/LgsIterable.h"

class LgsSArray final : public LgsIterable {
public:
    static constexpr auto name = "SArray";
    size_t initialLength = 0;
    LgsBuiltinFunc lenFunc{"len", &LGS_INT, name, {this}, true};

    explicit LgsSArray(LgsType* baseType = nullptr): LgsIterable(baseType) {
        unpackLength = 1;
        canSlice = true;
        addMethod(&lenFunc);
    }

    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    string prettyName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    string getStrFormatPart() const override;
    Value* getLength(LgsExpr* expr) override;
    Value* getLoopLength(LgsExpr* expr) override;
    Value* isEmpty(LgsExpr* expr) override;
    Value* isNotEmpty(LgsExpr* expr) override;
    bool equals(LgsType* other) override;
    ~LgsSArray() override;
};
