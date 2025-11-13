#pragma once
#include "LgsType.h"

class LgsTypePair final : public LgsType {
public:
    static constexpr auto name = "Pair";
    LgsType* key;
    LgsType* value;

    explicit LgsTypePair(LgsType* keyType = nullptr, LgsType* valueType = nullptr) : key(keyType), value(valueType) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    Lgs_TypeKind getRTTypeKind() override;
    LgsExpr* getZeroValue() override;
    size_t sizeBytes() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    LgsType* clone() override;
    ~LgsTypePair() override;
};
