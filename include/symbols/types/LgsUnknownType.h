#pragma once
#include <utility>
#include "LgsType.h"

/**
 * Only named unknown types should be allocated on the heap, otherwise
 * use the singleton instance.
 */
class LgsUnknownType final : public LgsType {
public:
    std::string name;

    explicit LgsUnknownType(std::string  name) : name(std::move(name)) {}
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    std::string pname() override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    bool equals(LgsType* other) override;
    ~LgsUnknownType() override = default;
};

static LgsUnknownType* lgsUnknownType() {
    static LgsUnknownType instance("<Unknown>");
    return &instance;
}
