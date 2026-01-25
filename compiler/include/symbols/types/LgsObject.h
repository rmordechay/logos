#pragma once
#include "LgsFuncType.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "iterables/LgsStr.h"
#include "stmts/LgsField.h"

class LgsGenericType;
class LgsInstance;
class LgsCodeGen;
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
    std::map<std::string, LgsFunc*> metaMethods;
    std::map<std::string, LgsField*> metaFields;
    LgsInstance* singleton = nullptr;
    bool hasGenerics = false;
    const size_t rttLevelIndex = 0;
    const size_t rttTypeIndex = 1;
    const size_t rttNameIndex = 0;
    const size_t rttSizeIndex = 1;
    const size_t rttFieldsCountIndex = 2;
    const size_t rttFuncsCountIndex = 3;
    const size_t rttFieldsIndex = 4;

    explicit LgsObject(const std::string&  objName) : name(objName) {
        passByRef = true;
        isHeapAlloc = true;
        rtt = RTT_OBJECT;
        // metaFields["name"] = new LgsField("name", new LgsStr(), new LgsStrConst(name));
    }
    std::string getName() override;
    LgsFunc* getMethod(const std::string& methodName) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTType(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    ~LgsObject() override;
};
