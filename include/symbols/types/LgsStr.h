#pragma once
#include "methods/LgsStrMethods.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "types/LgsIterable.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsStrFormatFunc format{this};
    LgsStrLenFunc len{this};
    LgsStrIsEmptyFunc isEmpty{this};
    LgsStrIsNotEmptyFunc isNotEmpty{this};

    LgsStr() : LgsIterable(&LGS_CHAR) {
        addMethod(&format);
        addMethod(&len);
        addMethod(&isEmpty);
        addMethod(&isNotEmpty);
        unpackLength = 1;
    }
    static uint32_t hashString(const string& str);
    size_t getSizeBytes() override;
    string getIRName() override;
    Type* getIRType() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    string getStrFormatPart() const override;
    Value* getLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* getLoopLength(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    Value* callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) override;
    ~LgsStr() override = default;
};

inline LgsStr LGS_STR;