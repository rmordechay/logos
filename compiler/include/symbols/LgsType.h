#pragma once
#include "Lgs_Types.h"
#include "LgsTokens.h"
#include <vector>

class LgsSelf;
class LgsFieldType;
class LgsEnumField;
struct LgsBinOp;
class LgsBinaryExpr;
class LgsValue;
class LgsVariadic;
class LgsGenericType;
class LgsMatrix;
class LgsSubType;
class LgsSet;
class LgsAny;
class LgsByte;
class LgsSize;
class LgsCPtr;
class LgsDouble;
class LgsFloat;
class LgsVec;
class LgsVectorExpr;
class LgsChar;
class LgsVariable;
class LgsSArray;
class LgsNullable;
class LgsUInt;
class LgsShort;
class LgsTypePair;
class LgsLong;
class LgsHashMap;
class LgsVTable;
class LgsFuncType;
class LgsInterface;
class LgsObject;
class LgsBool;
class LgsMap;
class LgsEnum;
class LgsInt;
class LgsDArray;
class LgsIterable;
class LgsStr;
class LgsExpr;
class LgsFuncCall;
class LgsField;
class LgsFunc;
class LgsCodeGen;
class LgsStrBuilder;

namespace llvm {
    class Constant;
    class ConstantInt;
    class DIType;
    class Type;
    class Value;
}

using namespace llvm;

class LgsType {
public:
    LgsLocation location;
    std::vector<LgsField*> fields;
    std::unordered_map<std::string, LgsFunc*> methods;
    std::vector<LgsType*> genericArgs;
    Lgs_TypeKind rttKind = RTT_UNKNOWN;
    bool isInt = false;
    bool isUnsinged = false;
    bool isFloat = false;
    bool isExternal = false;
    bool isHeap = false;
    bool isPrimitive = false;
    bool passByRef = false;

    bool isAny();
    bool isVoid();
    bool isScalar() const;
    bool isUnknown();
    bool isSliceable();
    bool addMethod(LgsFunc* method);
    bool hasRecursiveTypes() const;
    std::string getRTTName();
    Constant* getRTType(LgsCodeGen& cg);
    ConstantInt* IRSize(LgsCodeGen& cg);
    Type* getTypeRef(LgsCodeGen& cg);

    virtual LgsField* getField(const std::string& fieldName);
    virtual LgsFunc* getMethod(const std::string& methodName);
    virtual std::string getName() = 0;
    virtual std::string getBaseName();
    virtual std::string pname(); // pretty name
    virtual size_t sizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual std::string fmtStr() const = 0;
    virtual bool equals(LgsType* other);
    virtual void hashNode(size_t& oldHash);
    virtual bool hasGenerics();
    virtual bool canCastTo(LgsType* other) = 0;
    virtual LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) = 0;
    virtual Value* moveValue(LgsCodeGen& cg, Value* value, Value* toLevel);
    virtual void asIRText(LgsCodeGen& cg, LgsStrBuilder& strBuilder, Value* ptr);
    virtual void replaceGenerics(std::unordered_map<std::string, LgsType*>& replacements);
    virtual Type* getIRType(LgsCodeGen& cg) = 0;
    virtual Constant* getRTTypeExtra(LgsCodeGen& cg);
    virtual Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee);
    virtual Value* hashValue(LgsCodeGen& cg, Value* value);
    virtual DIType* getDebugType(LgsCodeGen& cg) = 0;

    virtual Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* modIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* powIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* bitAndIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* bitOrIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* bitXorIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* lshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);
    virtual Value* rshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);

    LgsAny* asAny();
    LgsChar* asChar();
    LgsStr* asStr();
    LgsBool* asBool();
    LgsByte* asByte();
    LgsInt* asInt();
    LgsShort* asShort();
    LgsLong* asLong();
    LgsSize* asSize();
    LgsUInt* asUInt();
    LgsFloat* asFloat();
    LgsDouble* asDouble();
    LgsFuncType* asFuncType();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsEnum* asEnum();
    LgsSelf* asSelf();
    LgsGenericType* asGenericType();
    LgsIterable* asIterable();
    LgsSArray* asSArray();
    LgsDArray* asDArray();
    LgsSet* asSet();
    LgsVec* asVec();
    LgsMatrix* asMatrix();
    LgsCPtr* asCPtr();
    LgsMap* asMap();
    LgsTypePair* asPair();
    LgsSubType* asSubtype();
    LgsVariadic* asVariadic();
    LgsNullable* asNullable();
    LgsFieldType* asFieldType();
    virtual ~LgsType();
};

void freeType(LgsType* type);

template<typename T>
void freeTypes(std::vector<T*>& types) {
    for (const auto type : types) {
        freeType(static_cast<LgsType*>(type));
    }
    types.clear();
}

Value* loadRTTInfoName(LgsCodeGen& cg, Value* ptr);
Value* loadRTTInfoSize(LgsCodeGen& cg, Value* ptr);
Value* loadRTTInfoKind(LgsCodeGen& cg, Value* ptr);
Value* loadRTTInfoIsHeap(LgsCodeGen& cg, Value* ptr);
Value* loadRTTInfoExtra(LgsCodeGen& cg, Value* ptr);
Value* eqIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* neIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* ltIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* gtIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* geIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* leIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* andIR(LgsCodeGen& cg, Value* left, Value* right);
Value* orIR(LgsCodeGen& cg, Value* left, Value* right);
Value* crossIR(LgsCodeGen& cg, Value* left, Value* right, LgsVec* vec);
LgsType* getBiggestIntType(const std::vector<LgsType*>& types);
Value* loadAsInt(LgsCodeGen& cg, Value* v, Type* intType);
Value* loadAsFloat(LgsCodeGen& cg, Value* v, Type* floatType);
std::pair<Value*, Value*> loadNumberPair(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
