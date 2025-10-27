#pragma once
#include <utility>
#include "LgsType.h"

class LgsGeneric;
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
    std::vector<LgsObject*> objects;
    std::vector<LgsGeneric*> generics;
    std::vector<LgsSubType*> subtypes;
    std::vector<LgsIOPair*> ioPairs;
    LgsInstance* singleton = nullptr;

    explicit LgsObject(std::string  name) : name(std::move(name)) {
        isHeapAlloc = true;
    }
    LgsFunc* getMethod(const std::string& methodName) override;
    std::string getName() override;
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t getSizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_RTType getRTType() override;
    bool hasVirtuals() const;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    LgsObject* clone() override;
    ~LgsObject() override;
};
