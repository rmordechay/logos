#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    const string getName() const override;
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) const override;
    ~LgsInt() override = default;
};

inline LgsInt LGS_INT;

#endif //LOGOSINT_H
