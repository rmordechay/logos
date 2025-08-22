#pragma once
#include "LgsType.h"
#include "exprs/unary/LgsInstance.h"

class LgsInstance;

class LgsTable final : public LgsType {
public:
    std::string name;
    LgsInstance* instance;

    explicit LgsTable(const std::string& name) : name(name) {
        instance = new LgsInstance(name);
    }
    std::string pname() override;
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    json::value asJSON() override;
    ~LgsTable() override;
};
