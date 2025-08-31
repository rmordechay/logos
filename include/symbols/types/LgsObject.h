#pragma once
#include <utility>
#include "LgsType.h"

class LgsInstance;
class LgsLLVMGen;
class LgsField;
class LgsIOPair;

class LgsObject : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> interfaces;
    std::vector<LgsIOPair*> ioPairs;
    LgsInstance* singleton = nullptr;

    explicit LgsObject(std::string  name) : name(std::move(name)) {
        isHeapAlloc = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    void freeValue(LgsLLVMGen& cg, LgsExpr* value) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    std::string strFormatPart() const override;
    bool hasVirtuals() const;
    LgsObject* clone() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    bool canAssignTo(LgsType* other, LgsAssignType op) override;
    json::value asJSON() override;
    ~LgsObject() override;
};
