#pragma once
#include "LgsObject.h"
#include "LgsType.h"

class LgsInterface final : public LgsObject {
public:
    explicit LgsInterface(const std::string& name) : LgsObject(name) {}
    json::value asJsonStr() override;
    std::string getName() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    bool canCastTo(LgsType* other) override;
    size_t getSizeBytes() override;
    ~LgsInterface() override;
};
