#pragma once
#include "LgsFuncType.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "iterables/LgsStr.h"

class LgsGenericType;
class LgsInstance;
class LgsCgModule;
class LgsField;
class LgsIOPair;

class LgsObject : public LgsType {
public:
    std::string name;
    std::vector<LgsType*> implements;
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::vector<LgsSubType*> subtypes;
    std::vector<LgsIOPair*> ioPairs;
    std::vector<LgsGenericType*> generics;
    LgsInstance* singleton = nullptr;
    std::map<std::string, LgsFunc*> metaMethods;
    bool hasGenerics = false;

    explicit LgsObject(const std::string&  objName) : name(objName) {
        passByRef = true;
        isHeapAlloc = true;
    }
    std::string getName() override;
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    ~LgsObject() override;
};
