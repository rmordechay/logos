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

    Type* getIRType(LgsModule* module) override;
    string getName() override;
    string prettyName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    string getStrFormatPart() const override;
    Value* getLength(LgsModule* module, LgsExpr* expr) override;
    Value* getLoopLength(LgsModule* module, LgsExpr* expr) override;
    Value* isEmpty(LgsModule* module, LgsExpr* expr) override;
    Value* isNotEmpty(LgsModule* module, LgsExpr* expr) override;
    bool equals(LgsType* other) override;
    ~LgsSArray() override;
};
