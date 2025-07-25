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
    bool isMutable = false;
    Value* IRValue = nullptr;
    vector<LgsVariable*> refs;

    void setIRValue(Value* value);
    void setLocation(const Token* start, const Token* end, const path& filePath);
    virtual string format(string& indentStr);
    virtual ~LgsValue() = default;
};
