#ifndef LGSCHAR_H
#define LGSCHAR_H
#include "funcs/LgsMethodImpl.h"

class LgsChar final : public LgsType {
public:

    static constexpr auto name = "Char";

    const string getPrettyName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsChar() override = default;
};

#endif //LGSCHAR_H
