#pragma once
#include "LgsType.h"

class LgsInterface final : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> interfaces;

    explicit LgsInterface(const std::string& name) : name(name) {}
    std::string prettyName() override;
    std::string getName() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    size_t getSizeBytes() override;
    ~LgsInterface() override;
};
