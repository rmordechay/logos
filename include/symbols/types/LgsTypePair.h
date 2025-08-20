#pragma once

class LgsTypePair final : public LgsType {
public:
    static constexpr auto name = "Pair";
    LgsType* key;
    LgsType* value;
    StructType* pairIRType = nullptr;

    explicit LgsTypePair(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : key(keyType), value(valueType) {}
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    std::string pname() override;
    json::value asJSON() override;
    bool equals(LgsType* other) override;
    std::string strFormatPart() const override;
};

inline Type* LgsTypePair::getIRType(LgsCodeGen* codeGen) {
    assert(0);
}

inline std::string LgsTypePair::getName() {
    return name;
}

inline LgsExpr* LgsTypePair::getZeroValue() {
    assert(false);
}

inline size_t LgsTypePair::getSizeBytes() {
    return key->getSizeBytes() + value->getSizeBytes() ;
}

inline std::string LgsTypePair::pname() {
    return '<' + key->pname() + "," + value->pname() + '>';
}

inline json::value LgsTypePair::asJSON() {
    json::object obj;
    return obj;
}

inline bool LgsTypePair::equals(LgsType* other) {
    const auto otherPair = dynamic_cast<LgsTypePair*>(other);
    if (!otherPair) return false;
    return key->equals(otherPair->key) && value->equals(otherPair->value);
}

inline std::string LgsTypePair::strFormatPart() const {
    return "%s";
}
