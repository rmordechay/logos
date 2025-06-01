#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "../builtin/LgsStrMethods.h"
#include <string>
#include "exprs/unary/constants/LgsCharConst.h"
#include "types/LgsIterable.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsStrFormatFunc format{this};
    LgsStrLenFunc len{this};

    LgsStr() : LgsIterable(&LGS_CHAR) {
        addMethod(&format);
        unpackLength = 1;
    }
    size_t getSize() override;
    string getIRName() override;
    Type* getIRType() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    Value* getElement(Module* module, Value* iterPtr, Value* iPtr) override;
    Value* getLength(Module* module, Value* iterValue) override;
    string getStrFormatPart() const override;
    static uint32_t hashString(const string& str);
    ~LgsStr() override = default;
};

#endif // LOGOSSTRING_H
