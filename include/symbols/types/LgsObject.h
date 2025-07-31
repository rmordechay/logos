#pragma once
#include "LgsType.h"
#include "LgsValue.h"

class LgsInstance;
class LgsCodeGen;
class LgsField;

class LgsObject final : public LgsType {
public:
    string name;
    bool hasVirtuals = false;
    vector<LgsType*> interfaces;
    LgsInstance* singleton = nullptr;

    explicit LgsObject(const string& name) : name(name) {}
    string prettyName() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    string getName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    string getStrFormatPart() const override;
    bool equals(LgsType* other) override;
    void freeValue(LgsCodeGen* codeGen, Value* value) override;
    LgsObject* clone();
    ~LgsObject() override;
};
