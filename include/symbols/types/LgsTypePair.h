#pragma once

class LgsTypePair final : public LgsType {
public:
    static constexpr auto name = "Pair";
    LgsType* key;
    LgsType* value;
    StructType* pairIRType = nullptr;

    explicit LgsTypePair(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : key(keyType), value(valueType) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    size_t getSizeBytes() override;
    std::string pname() override;
    json::value asJSON() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
};

inline Type* LgsTypePair::getIRType(LgsLLVMGen& cg) {
    assert(0);
}

inline std::string LgsTypePair::getName() {
    return name;
}

inline LgsExpr* LgsTypePair::getZeroValue() {
    assert(false);
}

inline Lgs_RTType LgsTypePair::getRTType() {
    assert(0);
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

inline bool LgsTypePair::canCastTo(LgsType* other) {
    const auto otherPair = dynamic_cast<LgsTypePair*>(other);
    if (!otherPair) return false;
    return key->canCastTo(otherPair->key) && value->canCastTo(otherPair->value);
}

inline std::string LgsTypePair::strFormatPart() const {
    return "%s";
}
