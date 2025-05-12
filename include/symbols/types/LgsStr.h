#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LgsIterable.h"
#include "LgsType.h"
#include <string>
#include "stmts/LgsField.h"
#include "exprs/unary/constants/LgsCharConst.h"

class LgsStrFormatFunc final : public LgsMethodImpl {
public:
    LgsParam self{};
    LgsParam args{};

    explicit LgsStrFormatFunc(LgsType* parent) : LgsMethodImpl("format", parent->getIRName(), parent) {
        self.type = parent;
        funcType.params = {&self, &args};
        funcType.isPublic = true;
        funcType.isVariadic = true;
    }
};

class LgsStr final : public LgsIterable {
public:
    static constexpr auto name = "Str";
    LgsStrFormatFunc format{this};

    LgsStr() : LgsIterable(&LGS_CHAR) {}
    size_t getSize() override;
    Type* getIRType() override;
    string getIRName() override;
    string prettyName() const override;
    string getFormatStr() override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
    static uint32_t hashString(const string& str);
    ~LgsStr() override = default;
};

inline LgsStr LGS_STR;

#endif // LOGOSSTRING_H
