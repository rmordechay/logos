#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "LgsType.h"

class LgsInt final : public LgsType {
public:
    static constexpr auto name = "Int";

    size_t getSize() override;
    string prettyName() const override;
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    bool equals(LgsType* other) override;
    ~LgsInt() override = default;
};

inline LgsInt LGS_INT;

#endif //LOGOSINT_H
