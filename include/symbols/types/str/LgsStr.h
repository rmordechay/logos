#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LgsStrMethods.h"
#include <string>
#include "stmts/LgsField.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "types/LgsIterable.h"

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsStrFormatFunc format{this};

    LgsStr() : LgsIterable(&LGS_CHAR) {
        addMethod(&format);
    }
    size_t getSize() override;
    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    static uint32_t hashString(const string& str);
    ~LgsStr() override = default;
};

inline LgsStr LGS_STR;

#endif // LOGOSSTRING_H
