#ifndef LGSANY_H
#define LGSANY_H
#include "LgsType.h"

class LgsAny final : public LgsType {
public:
    static constexpr auto name = "Any";

    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
    ~LgsAny() override = default;
};

inline LgsAny LGS_ANY;

#endif //LGSANY_H
