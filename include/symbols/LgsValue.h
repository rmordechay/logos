#pragma once
#include "configs/LgsErrors.h"

namespace llvm {
    class Value;
}

class LgsVariable;
class LgsExpr;
class LgsCodeGen;
class LgsFunc;

class LgsValue {
public:
    bool isMutable = false;
    llvm::Value* IRValue = nullptr;
    LgsLocation location{0, 0, nullptr};

    void setIRValue(llvm::Value* value);
    llvm::Value* getIRValue(LgsCodeGen* codeGen);
    virtual void createIRValue(LgsCodeGen* codeGen) = 0;
    virtual void createDebugValue(LgsCodeGen* codeGen);
    virtual std::string format(std::string& indentStr);
    virtual ~LgsValue() = default;
};
