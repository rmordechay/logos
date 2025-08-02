#pragma once
#include "LgsLocation.h"

class LgsVariable;
class LgsExpr;
class LgsCodeGen;
class LgsFunc;
using namespace llvm;

class LgsValue {
public:
    LgsLocation location;
    bool isMutable = false;
    Value* IRValue = nullptr;

    void setIRValue(Value* value);
    virtual string format(string& indentStr);
    virtual ~LgsValue() = default;
};
