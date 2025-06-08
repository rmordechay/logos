#pragma once


class LgsPair final : public LgsType {
public:
    static constexpr auto name = "Pair";
    LgsType* key;
    LgsType* value;

    explicit LgsPair(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : key(keyType), value(valueType) {}
    Type* getIRType() override;
    string getIRName() override;
    LgsExpr* getZeroValue() override;
    string prettyName() const override;
    bool equals(LgsType* other) override;
    LgsType* inferBinaryType(LgsType* other) override;
};

inline Type* LgsPair::getIRType() {
    assert(false);
}

inline string LgsPair::getIRName() {
    return name;
}

inline LgsExpr* LgsPair::getZeroValue() {
    assert(false);
}

inline string LgsPair::prettyName() const {
    return '<' + key->prettyName() + "," + value->prettyName() + '>';
}

inline bool LgsPair::equals(LgsType* other) {
    const auto otherPair = dynamic_cast<LgsPair*>(other);
    if (!otherPair) return false;
    return key->equals(otherPair->key) && value->equals(otherPair->value);
}

inline LgsType* LgsPair::inferBinaryType(LgsType* other) {
    assert(false);
}


