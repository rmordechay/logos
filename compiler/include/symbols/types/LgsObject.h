#pragma once
#include "LgsFuncType.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"

class LgsGenericType;
class LgsInstance;
class LgsCodeGen;
class LgsField;
class LgsIOPair;

#define OBJ_META_NAME "name"
#define OBJ_GET_FIELD "getField"
#define OBJ_GET_METHOD "getMethod"

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
    std::map<std::string, LgsFunc*> metaFuncs;
    std::map<std::string, LgsField*> metaFields;
    LgsInstance* singleton = nullptr;
    bool hasGenerics = false;
    inline static LgsObjIndices rttIndices;
    static constexpr std::string metaName = "Object";

    explicit LgsObject(const std::string&  name) : name(name) {
        isHeapAlloc = true;
        passByRef = true;
        rttKind = RTT_OBJECT;
        metaFields[OBJ_META_NAME] = new LgsField(OBJ_META_NAME, new LgsStr(), new LgsStrConst(name));
    }
    std::string getName() override;
    std::string getBaseName() override;
    LgsFunc* getMethod(const std::string& methodName) override;
    LgsFunc* getMetaFunc(const std::string& methodName);
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    bool canCastTo(LgsType* other) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    std::string fmtStr() const override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    Function* generateObjsEqFunc(LgsCodeGen& cg) const;
    static StructType* getObjRTT(LgsCodeGen& cg);
    static StructType* getFieldRTT(LgsCodeGen& cg);
    static StructType* getMethodRTT(LgsCodeGen& cg);
    ~LgsObject() override;
};
