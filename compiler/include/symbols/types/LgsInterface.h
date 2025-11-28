#pragma once
#include "LgsObject.h"
#include "LgsType.h"

class LgsInterface final : public LgsObject {
public:

    explicit LgsInterface(const std::string& name) : LgsObject(name) {}
    LgsFunc* getMethod(const std::string& methodName) override;
    std::string getName() override;
    Type* getIRType(LgsCgModule& cg) override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    size_t sizeBytes() override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
    LgsInterface* clone() override;
};
