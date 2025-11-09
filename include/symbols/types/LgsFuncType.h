#pragma once
#include "LgsType.h"
#include "funcs/LgsParam.h"

class LgsGeneric;

enum LgsFuncFlags : uint32_t {
    PUBLIC = 1 << 0,
    BUILTIN = 1 << 1,
    VIRTUAL = 1 << 2,
    VARIADIC = 1 << 3,
    OPTIONAL = 1 << 4,
    TERMINATOR = 1 << 5,
    METHOD = 1 << 6,
    IO_MEMBER = 1 << 7,
    SYSCALL = 1 << 8,
    ARR_FUNC = 1 << 9,
    HAS_DEFAULTS = 1 << 10,
};

class LgsFuncType final : public LgsType {
public:
    std::string name;
    std::string IRName;
    std::string parentName;
    std::string genericSuffix;
    LgsType* rt = nullptr;
    std::vector<LgsParam> params;
    std::vector<LgsGeneric*> generics;
    FunctionType* IRType = nullptr;
    bool isPublic = false;
    bool isBuiltin = false;
    bool isVirtual = false;
    bool isVariadic = false;
    bool isLambda = false;
    bool isOptional = false;
    bool isTerminator = false;
    bool isMethod = false;
    bool isCoroutine = false;
    bool isIOMember = false;
    bool isExternal = false;
    bool isArrFunc = false;
    bool hasDefaults = false;
    uint32_t variadicIndex = 0;

    LgsFuncType(): LgsFuncType(nullptr) {}
    explicit LgsFuncType(LgsType* rt, const std::vector<LgsParam>& params = {}) : rt(rt), params(params) {
        passByRef = true;
    }
    void setFuncOptions(uint32_t ops);
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    size_t getSizeBytes() override;
    std::string getName() override;
    std::string pname() override;
    std::string strFormatPart() const override;
    bool canCastTo(LgsType* other) override;
    bool equals(LgsType* other) override;
    LgsType* clone() override;
    ~LgsFuncType() override;
};
