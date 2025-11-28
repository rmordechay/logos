#pragma once
#include <utility>
#include "LgsType.h"

class LgsGenericType;
class LgsInstance;
class LgsCgModule;
class LgsField;
class LgsIOPair;

class LgsObject : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> implements;
    std::vector<LgsGenericType*> generics;
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::vector<LgsSubType*> subtypes;
    std::vector<LgsIOPair*> ioPairs;
    LgsInstance* singleton = nullptr;
    bool hasGenerics = false;

    explicit LgsObject(std::string  name) : name(std::move(name)) {
        isHeapAlloc = true;
        passByRef = true;
    }
    std::string getName() override;
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    LgsObject* clone() override;
    llvm::DIType* getDebugType(LgsCgModule& cg) override;
    ~LgsObject() override;
};
