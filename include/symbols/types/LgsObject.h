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
    std::vector<LgsType*> implements;
    std::vector<LgsEnum*> enums;
    std::vector<LgsSubType*> subtypes;
    std::vector<LgsObject*> objects;
    std::vector<LgsIOPair*> ioPairs;
    LgsInstance* singleton = nullptr;

    explicit LgsObject(std::string  name) : name(std::move(name)) {
        isHeapAlloc = true;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_rttype getRTType() override;
    std::string strFormatPart() const override;
    bool hasVirtuals() const;
    LgsObject* clone() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    void parseAsJSON(std::stringstream& json) override;
    ~LgsObject() override;
};
