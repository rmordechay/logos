#ifndef LGSCHAR_H
#define LGSCHAR_H
#include "funcs/LgsMethodImpl.h"

class LgsChar final : public LgsType {
public:
    static constexpr auto name = "Char";

    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsChar() override = default;
};

inline LgsChar LGS_CHAR;

#endif //LGSCHAR_H
