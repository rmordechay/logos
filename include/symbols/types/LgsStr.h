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

    LgsStr() : LgsIterable(&LGS_CHAR) {}
    size_t getSize() override;
    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    static uint32_t hashString(const string& str);
    ~LgsStr() override = default;
};

inline LgsStr LGS_STR;

#endif // LOGOSSTRING_H
