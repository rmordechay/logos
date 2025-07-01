#pragma once
#include "LgsLocation.h"

class LgsVariable;
class LgsExpr;
class LgsModule;
class LgsFunc;
using namespace llvm;

class LgsValue {
public:
    Location location;
    Value* IRValue = nullptr;
    vector<LgsVariable*> refs;
    bool isMutable = false;

    void setIRValue(Value* value);
    GlobalVariable* createIRGlobal(const LgsModule* runtime, Type* type, Constant* value) const;
    bool shouldLoadIRArg(Value* value, const LgsExpr* expr = nullptr) const;
    void startBlock(LgsModule* runtime, BasicBlock* block) const;
    void startFuncBlock(LgsModule* runtime) const;
    Value* hashIRValue(LgsModule* runtime, Value* value) const;
    void copyMem(LgsModule* runtime, Value* src, Value* dest, size_t n) const;
    virtual std::string format(std::string& indentStr);
    virtual void setLocation(const Token* start, const Token* end, path* filePath);
    virtual ~LgsValue() = default;
};


