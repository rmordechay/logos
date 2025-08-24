#pragma once
#include "LgsType.h"
#include "funcs/LgsParam.h"

namespace llvm {
    class FunctionType;
}

enum LgsFuncFlags : uint32_t {
    PUBLIC = 1 << 0,
    INTERNAL = 1 << 1,
    VIRTUAL = 1 << 2,
    VARIADIC = 1 << 3,
    LAMBDA = 1 << 4,
    OPTIONAL = 1 << 5,
    TERMINATOR = 1 << 6,
    METHOD = 1 << 7,
    HAS_DEFAULTS = 1 << 8,
};

class LgsFuncType final : public LgsType {
public:
    std::string name;
    std::string IRName;
    std::string parentName;
    LgsType* rt = nullptr;
    std::vector<LgsParam> params;
    bool isPublic = false;
    bool isInternal = false;
    bool isVirtual = false;
    bool isVariadic = false;
    bool isLambda = false;
    bool isOptional = false;
    bool isTerminator = false;
    bool isMethod = false;
    bool isTest = false;
    bool hasDefaults = false;
    llvm::FunctionType* IRType = nullptr;

    void setFuncOptions(uint32_t ops);
    llvm::Type* getIRType(LgsLLVM& codeGen) override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    LgsType* clone() override;
    ~LgsFuncType() override;
};
