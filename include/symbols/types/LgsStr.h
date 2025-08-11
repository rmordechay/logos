#pragma once
#include "funcs/LgsBuiltinFunc.h"
#include "primitives/LgsBool.h"
#include "primitives/LgsChar.h"
#include "primitives/LgsLong.h"
#include "types/LgsIterable.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    size_t initialLength = 0;
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
    Type* getIRBaseType(LgsCodeGen* codeGen) const;
    size_t getSizeBytes() override;
    string getName() override;
    string prettyName() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    LgsType* getIndexType() override;
    Value* IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    Value* IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) override;
    bool equals(LgsType* other) override;
    ~LgsStr() override = default;
};
