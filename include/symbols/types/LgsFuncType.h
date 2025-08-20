#pragma once
#include "LgsType.h"
#include "funcs/LgsParam.h"

namespace llvm {
    class FunctionType;
}

enum LgsFuncFlags : uint32_t {
    METHOD = 1 << 0,
    PUBLIC = 1 << 1,
    INTERNAL = 1 << 2,
    VIRTUAL = 1 << 3,
    STATIC = 1 << 4,
    VARIADIC = 1 << 5,
    ANONYMOUS = 1 << 6,
    HAS_DEFAULTS = 1 << 7,
    OPTIONAL = 1 << 8,
    TERMINATOR = 1 << 9,
};

class LgsFuncType final : public LgsType {
public:
    std::string name;
    std::string IRName;
    std::string parentName;
    LgsType* rt = nullptr;
    std::vector<LgsParam> params;
    bool isMethod = false;
    bool isPublic = false;
    bool isInternal = false;
    bool isVirtual = false;
    bool isVariadic = false;
    bool isStatic = false;
    bool isOptional = false;
    bool isTerminator = false;
    bool isAnonymous = false;
    bool hasDefaults = false;
    llvm::FunctionType* IRType = nullptr;

    void setFuncOptions(uint32_t ops);
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    LgsExpr* getZeroValue() override;
    size_t getSizeBytes() override;
    bool equals(LgsType* other) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    std::string strFormatPart() const override;
    ~LgsFuncType() override;
};
