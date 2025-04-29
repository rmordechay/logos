#ifndef LOGOSSTRING_H
#define LOGOSSTRING_H
#include "LgsType.h"
#include "stmts/LgsField.h"
#include <string>

class LgsStr final : public LgsType {
public:
    static constexpr auto name = "Str";

    const string getName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    static void cleanStr(string& value);
    static uint32_t hashString(const string& str);
    ~LgsStr() override = default;
};



#endif // LOGOSSTRING_H
