#ifndef LOGOSINT_H
#define LOGOSINT_H
#include "CodeGenerator.h"
#include "LgsType.h"
#include "LgsVoid.h"

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

// inline LgsInt LOGOS_INT;

#endif //LOGOSINT_H
