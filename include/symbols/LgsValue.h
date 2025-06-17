#pragma once
#include "LgsLocation.h"

class LgsExpr;
class LgsRuntime;
class LgsFunc;
using namespace llvm;

class LgsValue {
public:
    Location location;
    Value* IRValue = nullptr;

    void setIRValue(Value* value);
    bool shouldLoadIRArg(Value* value, const LgsExpr* expr = nullptr) const;
    void startBlock(LgsRuntime* runtime, BasicBlock* block) const;
    void startFuncBlock(LgsRuntime* runtime) const;
    Value* hashIRValue(LgsRuntime* runtime, Value* value) const;
    virtual std::string format(std::string& indentStr);
    virtual void setLocation(const Token* ctx, path* filePath);
    virtual ~LgsValue() = default;
};


