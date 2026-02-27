#pragma once
#include <map>
#include <string>
#include <vector>

#include "exprs/LgsFuncCall.h"
#include "exprs/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "LgsType.h"
#include "LgsValue.h"
#include "Lgs_Types.h"
#include "types/iterables/LgsStr.h"

class LgsTypeParam;
class LgsInstance;
class LgsCodeGen;
class LgsField;
class LgsIOPair;
class LgsEnum;
class LgsFunc;
class LgsSubType;
namespace llvm {
class Function;
class StructType;
class Value;
}

#define OBJ_META_NAME "name"
#define OBJ_HASH_FUNC "hash"
#define OBJ_GET_FIELD_FUNC "getField"
#define OBJ_SET_FIELD_FUNC "setField"
#define OBJ_GET_FIELDS_FUNC "getFields"
#define OBJ_GET_METHOD_FUNC "getMethod"
#define OBJ_AS_JSON "json"

class LgsObject : public LgsType {
public:
    static constexpr std::string metaName = "Object";
    size_t id{};
    std::string name;
    bool isSingleton = false;
    std::vector<LgsType*> implements;
    std::vector<LgsEnum*> enums;
    std::vector<LgsObject*> objects;
    std::vector<LgsSubType*> subtypes;
    std::vector<LgsIOPair*> ioPairs;
    std::vector<LgsTypeParam*> typeParams;
    std::map<std::string, LgsFunc*> metaFuncs;
    std::map<std::string, LgsField*> metaFields;
    std::unordered_map<std::string, LgsType*> replacements;

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
    LgsType* clone() override;
    bool hasTypeParams() override;
    bool canCastTo(LgsType* other) override;
    void hashNode(size_t& oldHash) override;
    Type* getIRType(LgsCodeGen& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    bool isRecursive(std::unordered_set<std::string>& visited) const override;
    void asIRText(LgsStrBuilder& sb, Value* value) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    Value* hashValue(LgsCodeGen& cg, Value* value) override;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    Function* getObjsEqFunc(LgsCodeGen& cg) const;
    Function* getObjsHashFunc(LgsCodeGen& cg) const;
    Function* getJSONFunc(LgsCodeGen& cg);
    static Function* getSetFieldFunc(LgsCodeGen& cg);
    static Function* getGetFieldFunc(LgsCodeGen& cg);
    static StructType* getObjRTTStruct(LgsCodeGen& cg);
    static StructType* getMethodRTTStruct(LgsCodeGen& cg);
    static Value* loadRTFieldsCount(LgsCodeGen& cg, Value* ptr);
    static Value* loadRTFields(LgsCodeGen& cg, Value* ptr);
    ~LgsObject() override;
};
