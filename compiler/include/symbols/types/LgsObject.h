#pragma once
#include "LgsFuncType.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"

class LgsGenericType;
class LgsInstance;
class LgsCodeGen;
class LgsField;
class LgsIOPair;

class LgsObject : public LgsType {
public:
    size_t id{};
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
    inline static Lgs_ObjectIndices rttIndices;

    explicit LgsObject(const std::string&  objName) : name(objName) {
        passByRef = true;
        isHeapAlloc = true;
        rttKind = RTT_OBJECT;
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
