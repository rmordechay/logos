#pragma once
#include "LgsAny.h"
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsChar.h"
#include "primitives/LgsLong.h"
#include "types/LgsIterable.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsBuiltinFunc lenFunc{"len", &LGS_LONG, name, {this}};
    LgsBuiltinFunc isEmptyFunc{"isEmpty", &LGS_BOOL, name, {this}};
    LgsBuiltinFunc isNotEmptyFunc{"isNotEmpty", &LGS_BOOL, name, {this}};

    LgsStr() : LgsIterable(&LGS_CHAR) {
        addMethod(&lenFunc);
        addMethod(&isEmptyFunc);
        addMethod(&isNotEmptyFunc);
        unpackLength = 1;
        canSlice = true;
    }
    size_t getSizeBytes() override;
    string getIRName() override;
    string prettyName() const override;
    Type* getIRType(LLVMContext& context) override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    Value* getLength(LgsModule* module, LgsExpr* expr) override;
    Value* getLoopLength(LgsModule* module, LgsExpr* expr) override;
    Value* isEmpty(LgsModule* module, LgsExpr* expr) override;
    Value* isNotEmpty(LgsModule* module, LgsExpr* expr) override;
    bool equals(LgsType* other) override;
    ~LgsStr() override = default;
};
