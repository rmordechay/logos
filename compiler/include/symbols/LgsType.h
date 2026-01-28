#pragma once
#include <map>
#include <ostream>
#include <vector>
#include "errors/LgsErrHandler.h"
#include <unordered_map>
#include "Lgs_Types.h"

class LgsEnumField;
class LgsComplex;
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
class LgsPtr;
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
    bool isInt = false;
    bool isUnsinged = false;
    bool isFloat = false;
    bool isHeapAlloc = false;
    bool passByRef = false;
    Lgs_TypeKind rttKind = RTT_UNKNOWN;

    bool isAny();
    bool isVoid();
    bool isNumber();
    bool isScalar() const;
    bool isUnknown();
    bool isSliceable();
    bool hasGenericTypes();
    ConstantInt* IRSize(LgsCodeGen& cg);
    Type* getTypeOrPtr(LgsCodeGen& cg);

    bool addMethod(LgsFunc* method);
    virtual LgsField* getField(const std::string& fieldName);
    virtual LgsFunc* getMethod(const std::string& methodName);
    virtual std::string getName() = 0;
    virtual size_t sizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual Value* getIRZeroValue(LgsCodeGen& cg, LgsValue* pointee);
    virtual Value* hashValue(LgsCodeGen& cg, Value* value);
    virtual Type* getIRType(LgsCodeGen& cg) = 0;
    virtual Value* asIRStr(LgsCodeGen& cg, Value* v);
    virtual Constant* getRTType(LgsCodeGen& cg) = 0;
    virtual bool canCastTo(LgsType* other) = 0;
    virtual std::string fmtStr() const = 0;
    virtual LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) = 0;
    virtual void hashNode(size_t& oldHash);
    virtual DIType* getDebugType(LgsCodeGen& cg) = 0;
    virtual std::string pname(); // pretty name
    virtual bool equals(LgsType* other);
    virtual LgsType* clone();

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
    virtual Value* crossIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr);

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
    LgsComplex* asComplex();
    LgsFuncType* asFuncType();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsEnum* asEnum();
    LgsGenericType* asGenericType();
    LgsIterable* asIterable();
    LgsSArray* asSArray();
    LgsDArray* asDArray();
    LgsSet* asSet();
    LgsVec* asVec();
    LgsMatrix* asMatrix();
    LgsPtr* asPtr();
    LgsMap* asMap();
    LgsTypePair* asPair();
    LgsSubType* asSubtype();
    LgsVariadic* asVariadic();
    LgsNullable* asNullable();
    virtual ~LgsType();
};

inline void freeType(LgsType* type) {
    if (!type) return;
    if (type->isScalar() || type->asAny() || type->asChar() || type->isVoid()) return;
    if (type->asEnum() || type->asSubtype() || type->asGenericType() || type->asObject() || type->asInterface()) return;
    delete type;
}

template<typename T>
void freeTypes(std::vector<T*>& types) {
    for (const auto type : types) {
        freeType(static_cast<LgsType*>(type));
    }
    types.clear();
}

Value* eqIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* neIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* ltIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* gtIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* geIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* leIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);
Value* andIR(LgsCodeGen& cg, Value* left, Value* right);
Value* orIR(LgsCodeGen& cg, Value* left, Value* right);
LgsType* getBiggestIntType(const std::vector<LgsType*>& types);
std::pair<Value*, Value*> loadNumberPair(LgsCodeGen& cg, Value* left, Value* right, Type* type);
