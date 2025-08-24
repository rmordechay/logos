#pragma once
#include <utility>
#include "LgsType.h"

class LgsInstance;
class LgsLLVM;
class LgsField;

class LgsObject : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> interfaces;
    LgsInstance* singleton = nullptr;

    explicit LgsObject(std::string  name) : name(std::move(name)) {}
    llvm::Type* getIRType(LgsLLVM& codeGen) override;
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    void freeValue(LgsLLVM& codeGen, llvm::Value* value) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool hasVirtuals() const;
    LgsObject* clone() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    json::value asJSON() override;
    ~LgsObject() override;
};
