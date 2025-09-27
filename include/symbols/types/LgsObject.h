#pragma once
#include <utility>
#include "LgsType.h"

class LgsInstance;
class LgsLLVMGen;
class LgsField;
class LgsIOPair;
class LgsSubType;

class LgsObject : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> interfaces;
    std::vector<LgsIOPair*> ioPairs;
    std::vector<LgsEnum*> enums;
    std::vector<LgsSubType*> subtypes;
    LgsInstance* singleton = nullptr;

    explicit LgsObject(std::string  name) : name(std::move(name)) {
        isHeapAlloc = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    LgsField* getField(const std::string& fieldName) override;
    LgsFunc* getMethod(const std::string& methodName) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    std::string strFormatPart() const override;
    bool hasVirtuals() const;
    LgsObject* clone() override;
    std::string getName() override;
    std::string pname() override;
    bool canCastTo(LgsType* other) override;
    json::value asJsonStr() override;
};
