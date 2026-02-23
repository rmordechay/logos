#pragma once
#include <llvm/IR/DerivedTypes.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "LgsType.h"
#include "funcs/LgsParam.h"

class LgsGenericType;

enum LgsFuncFlags : uint32_t {
    PUBLIC = 1 << 0,
    BUILTIN = 1 << 1,
    VIRTUAL = 1 << 2,
    VARIADIC = 1 << 3,
    OPTIONAL = 1 << 4,
    METHOD = 1 << 5,
    COROUTINE = 1 << 6,
    IO_MEMBER = 1 << 7,
    SYSCALL = 1 << 8,
    EXTERNAL = 1 << 9,
    TERMINATOR = 1 << 10,
    HAS_DEFAULTS = 1 << 11,
};

class LgsFuncType final : public LgsType {
public:
    std::string name;
    std::string parentName;
    LgsType* rt = nullptr;
    std::vector<LgsParam> params;
    std::vector<LgsGenericType*> genericTypes;
    FunctionType* IRType = nullptr;
    bool isPublic = false;
    bool isBuiltin = false;
    bool isVirtual = false;
    bool isVariadic = false;
    bool isOptional = false;
    bool isMethod = false;
    bool isCoroutine = false;
    bool isDeferred = false;
    bool isLambda = false;
    bool isSyscall = false;
    bool isTerminator = false;
    bool swapReturn = false;
    bool hasDefaults = false;
    bool hasSelf = false;
    uint32_t variadicIndex = 0;

    explicit LgsFuncType(const std::string& name = ""): LgsFuncType(name, nullptr) {}
    explicit LgsFuncType(const std::string& name, LgsType* rt, const std::vector<LgsParam>& params = {}, const uint32_t ops = 0) : name(name), rt(rt), params(params) {
        setFuncOptions(ops);
        passByRef = true;
    }
    FunctionType* getIRType(LgsCodeGen& cg) override;
    LgsExpr* getZeroValue() override;
    size_t sizeBytes() override;
    std::string getName() override;
    std::string pname() override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    bool equals(LgsType* other) override;
    bool hasGenerics() override;
    void replaceGenerics(std::unordered_map<std::string, LgsType*>& replacements) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    void setFuncOptions(uint32_t ops);
    std::unordered_map<std::string, LgsParam*> getParamsByName();
    DIType* getDebugType(LgsCodeGen& cg) override;
    void addSelf(LgsType* selfType);
    ~LgsFuncType() override;
};
