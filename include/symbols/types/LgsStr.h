#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LgsIterable.h"
#include "LgsType.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "stmts/LgsField.h"
#include <string>

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";

    LgsStr() : LgsIterable(&LGS_CHAR) {
        isStatic = false;
    }
    const string getName() const override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    static void cleanStr(string& value);
    static uint32_t hashString(const string& str);
    ~LgsStr() override = default;
};

#endif // LOGOSSTRING_H
