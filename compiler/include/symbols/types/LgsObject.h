#pragma once
#include <unordered_set>

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
#define OBJ_HASH_FUNC "hash"
#define OBJ_GET_FIELD_FUNC "getField"
#define OBJ_SET_FIELD_FUNC "setField"
#define OBJ_GET_FIELDS_FUNC "getFields"
#define OBJ_GET_METHOD_FUNC "getMethod"

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
    static constexpr std::string metaName = "Object";

    explicit LgsObject(const std::string&  name) : name(name) {
        isHeap = true;
        passByRef = true;
        rttKind = RTT_OBJECT;
        metaFields[OBJ_META_NAME] = new LgsField(OBJ_META_NAME, new LgsStr(), new LgsStrConst(name));
    }
    std::string getName() override;
    std::string getBaseName() override;
    LgsFunc* getMethod(const std::string& methodName) override;
    LgsFunc* getMetaFunc(const std::string& methodName);
    std::string fmtStr() const override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    bool canCastTo(LgsType* other) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    void hashNode(size_t& oldHash) override;
    Type* getIRType(LgsCodeGen& cg) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    void cloneFields(LgsInstance* instance) const;
    DIType* getDebugType(LgsCodeGen& cg) override;
    Function* getObjsEqFunc(LgsCodeGen& cg) const;
    Function* getObjsHashFunc(LgsCodeGen& cg) const;
    static Function* getSetFieldFunc(LgsCodeGen& cg);
    static Function* getGetFieldFunc(LgsCodeGen& cg);
    static Value* getInstanceRTType(LgsCodeGen& cg, Value* instance);
    static StructType* getObjRTTStruct(LgsCodeGen& cg);
    static StructType* getMethodRTTStruct(LgsCodeGen& cg);
    static Value* loadRTFieldsCount(LgsCodeGen& cg, Value* ptr);
    static Value* loadRTFields(LgsCodeGen& cg, Value* ptr);
    bool checkRecursiveFields(std::unordered_set<std::string>& nestedObjectNames) const;
    ~LgsObject() override;
};
