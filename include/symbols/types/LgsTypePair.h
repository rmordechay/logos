#pragma once
#include "utils/LgsUtils.h"

class LgsTypePair final : public LgsType {
public:
    static constexpr auto name = "Pair";
    LgsType* key;
    LgsType* value;
    StructType* pairIRType = nullptr;

    explicit LgsTypePair(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : key(keyType), value(valueType) {}
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
};

inline Type* LgsTypePair::getIRType() {
    assert(0);
}

inline string LgsTypePair::getIRName() {
    return name;
}

inline LgsExpr* LgsTypePair::getZeroValue() {
    assert(false);
}

inline string LgsTypePair::prettyName() const {
    return '<' + key->prettyName() + "," + value->prettyName() + '>';
}

inline bool LgsTypePair::equals(LgsType* other) {
    const auto otherPair = dynamic_cast<LgsTypePair*>(other);
    if (!otherPair) return false;
    return key->equals(otherPair->key) && value->equals(otherPair->value);
}

inline LgsType* LgsTypePair::inferBinaryType(LgsType* other) {
    assert(false);
}


