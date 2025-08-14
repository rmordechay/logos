#pragma once
#include "LgsType.h"

class LgsInstance;
class LgsCodeGen;
class LgsField;

class LgsObject : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> interfaces;
    LgsHashMap* vtable = nullptr;
    LgsInstance* singleton = nullptr;

    explicit LgsObject(const std::string& name) : name(name) {}
    std::string prettyName() override;
    Type* getIRType(LgsCodeGen* codeGen) override;
    std::string getName() override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool equals(LgsType* other) override;
    bool hasVirtuals() const;
    void freeValue(LgsCodeGen* codeGen, Value* value) override;
    LgsObject* clone();
    ~LgsObject() override;
};
