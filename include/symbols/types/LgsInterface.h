#pragma once
#include "LgsAny.h"
#include "LgsObject.h"
#include "LgsStr.h"
#include "exprs/unary/LgsHashMap.h"

class LgsInterface final : public LgsType {
public:
    string name;
    vector<LgsType*> interfaces;

    explicit LgsInterface(const string& name) : name(name) {
        vtable = new LgsHashMap(new LgsStr(), &LGS_ANY);
    }
    string prettyName() override;
    string getName() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    LgsExpr* getZeroValue() override;
    bool equals(LgsType* other) override;
    ~LgsInterface() override;
};
