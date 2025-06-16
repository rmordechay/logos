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
    string pName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    LgsType* getIndexType() override;
    LgsType* getValueType() override;
    LgsType* inferBinaryType(LgsType* other) override;
    Value* getLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* isEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* isNotEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    bool equals(LgsType* other) override;
    ~LgsStr() override = default;
};
