#pragma once
#include "LgsLocation.h"

class LgsVariable;
class LgsExpr;
class LgsRuntime;
class LgsFunc;
using namespace llvm;

class LgsValue {
public:
    Location location;
    Value* IRValue = nullptr;
    vector<LgsVariable*> refs;
    bool isMutable = false;

    void setIRValue(Value* value);
    GlobalVariable* createIRGlobal(const LgsRuntime* runtime, Type* type, Constant* value) const;
    bool shouldLoadIRArg(Value* value, const LgsExpr* expr = nullptr) const;
    void startBlock(LgsRuntime* runtime, BasicBlock* block) const;
    void startFuncBlock(LgsRuntime* runtime) const;
    Value* hashIRValue(LgsRuntime* runtime, Value* value) const;
    void copyMem(LgsRuntime* runtime, Value* src, Value* dest, size_t n) const;
    virtual std::string format(std::string& indentStr);
    virtual void setLocation(const Token* ctx, path* filePath);
    virtual ~LgsValue() = default;
};


