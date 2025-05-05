#ifndef LGSPAIR_H
#define LGSPAIR_H
#include "LgsType.h"

class LgsPair final : public LgsType {
public:
    static constexpr auto name = "Pair";
    LgsType* key;
    LgsType* value;

    explicit LgsPair(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : key(keyType), value(valueType) {}
    Type* getIRType() override;
    LgsExpr* getZeroValue() override;
    const string getName() const override;
    bool equals(LgsType* other) const override;
    LgsType* inferBinaryType(LgsType* other) override;
};

inline Type* LgsPair::getIRType() {
    assert(false);
}

inline LgsExpr* LgsPair::getZeroValue() {
    assert(false);
}

inline const string LgsPair::getName() const {
    assert(false);
}

inline bool LgsPair::equals(LgsType* other) const {
    assert(false);
}

inline LgsType* LgsPair::inferBinaryType(LgsType* other) {
    assert(false);
}

#endif //LGSPAIR_H
