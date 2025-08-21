#pragma once
#include "configs/LgsErrors.h"

class LgsType;

namespace llvm {
    class Value;
}

class LgsVariable;
class LgsExpr;
class LgsCodeGen;
class LgsFunc;

class LgsValue {
public:
    llvm::Value* IRValue = nullptr;
    LgsLocation location{0, 0, 0};

    void setIRValue(llvm::Value* value);
    llvm::Value* getIRValue(LgsCodeGen* codeGen);
    virtual void createIRValue(LgsCodeGen* codeGen) = 0;
    virtual void createDebugValue(LgsCodeGen* codeGen);
    virtual json::value asJSON() = 0;
    virtual ~LgsValue() = default;
};
