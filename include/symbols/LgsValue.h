#pragma once
#include "configs/LgsErrors.h"
#include <llvm/Target/TargetMachine.h>

class LgsVariable;
class LgsExpr;
class LgsCodeGen;
class LgsFunc;
using namespace llvm;

class LgsValue {
public:
    bool isMutable = false;
    Value* IRValue = nullptr;
    LgsLocation location{0, 0, nullptr};

    void setIRValue(Value* value);
    Value* getIRValue(LgsCodeGen* codeGen);
    virtual void createIRValue(LgsCodeGen* codeGen) = 0;
    virtual void createDebugValue(LgsCodeGen* codeGen);
    virtual std::string format(std::string& indentStr);
    virtual ~LgsValue() = default;
};
