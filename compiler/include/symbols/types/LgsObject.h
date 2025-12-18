#pragma once
#include "LgsAny.h"
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
    LgsFunc* getFieldFunc = new LgsFunc{"getField", &LGS_ANY, {new LgsStr()}, PUBLIC | BUILTIN | METHOD};
    bool hasGenerics = false;

    explicit LgsObject(const std::string&  objName) : name(objName) {
        passByRef = true;
        isHeapAlloc = true;
        getFieldFunc->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            return cg.callLgsFunc(name, "getObjectField", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy(), cg.ptrTy()}, {getRTType(cg), args[0].expr->IRValue, args[1].expr->IRValue});
        };
        metaMethods[getFieldFunc->funcType->name] = getFieldFunc;
    }
    std::string getName() override;
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCgModule& cg, Value* pointee = nullptr) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCgModule& cg) override;
    ~LgsObject() override;
};
