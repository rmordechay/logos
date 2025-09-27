#pragma once
#include "../exprs/LgsHashMap.h"
class LgsVariable;

class LgsGroup final : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> types;
    std::vector<LgsVariable*> targetSymbols;

    explicit LgsGroup(const std::string& name) : name(name) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    std::string getName() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    json::value asJsonStr() override;
    size_t getSizeBytes() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;

};



