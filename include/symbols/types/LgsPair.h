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
    return '<' + key->getName() + ", " + key->getName() + '>';
}

inline bool LgsPair::equals(LgsType* other) const {
    const auto otherPair = dynamic_cast<LgsPair*>(other);
    if (!otherPair) return false;
    return key->equals(otherPair->key) && value->equals(otherPair->value);
}

inline LgsType* LgsPair::inferBinaryType(LgsType* other) {
    assert(false);
}

#endif //LGSPAIR_H
