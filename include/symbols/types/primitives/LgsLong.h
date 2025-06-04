#ifndef LGSLONG_H
#define LGSLONG_H
#include "types/LgsType.h"

class LgsLong final : public LgsType {
public:
    static constexpr auto name = "Long";

    LgsLong() {
        isPrimitive = true;
    }
    Type* getIRType(LgsRuntime* runtime) override;
    LgsExpr* getZeroValue() override;
    LgsType* inferBinaryType(LgsType* other) override;
    string getIRName() override;
    string prettyName() const override;
    bool equals(LgsType* other) override;
    ~LgsLong() override = default;
};

inline LgsLong LGS_LONG;

#endif //LGSLONG_H
