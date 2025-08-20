#pragma once
#include <utility>

#include "LgsType.h"

class LgsInstance;
class LgsCodeGen;
class LgsField;

class LgsObject : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> interfaces;
    // LgsHashMap* vtable = nullptr;
    LgsInstance* singleton = nullptr;

    explicit LgsObject(std::string  name) : name(std::move(name)) {}
    LgsObject* clone();
    bool hasVirtuals() const;
    llvm::Type* getIRType(LgsCodeGen* codeGen) override;
    LgsField* getField(const std::string& name) override;
    LgsFunc* getMethod(const std::string& name) override;
    void freeValue(LgsCodeGen* codeGen, llvm::Value* value) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool equals(LgsType* other) override;
    std::string getName() override;
    std::string pname() override;
    json::value asJSON() override;
    ~LgsObject() override;
};
