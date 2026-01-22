#pragma once
#include <map>
#include <ostream>
#include <vector>
#include "errors/LgsErrHandler.h"
#include <unordered_map>
#include <unordered_set>

#include "Lgs_Types.h"

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
class LgsCgModule;

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
    Lgs_TypeKind rtt = RTT_UNKNOWN;

    bool isAny();
    bool isVoid();
    bool isNumber();
    bool isScalar() const;
    bool isBig();
    bool isUnknown();
    bool isSliceable();
    bool hasGenericTypes();
    ConstantInt* IRSize(LgsCgModule& cg);

    bool addMethod(LgsFunc* method);
    virtual LgsField* getField(const std::string& fieldName);
    virtual LgsFunc* getMethod(const std::string& methodName);
    virtual std::string getName() = 0;
    virtual size_t sizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual Type* getIRType(LgsCgModule& cg) = 0;
    virtual Type* getTypeOrPtr(LgsCgModule& cg);
    virtual Constant* getRTType(LgsCgModule& cg) = 0;
    virtual bool canCastTo(LgsType* other) = 0;
    virtual std::string fmtStr() const = 0;
    virtual LgsType* replaceGenerics(LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements);
    virtual LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) = 0;
    virtual void hashNode(size_t& oldHash);
    virtual DIType* getDebugType(LgsCgModule& cg) = 0;
    virtual std::string pname(); // pretty name
    virtual bool equals(LgsType* other);
    virtual LgsType* clone();

    virtual Value* addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* subIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* mulIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* divIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* modIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* powIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* bitAndIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* bitOrIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* bitXorIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* lshiftIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* rshiftIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);
    virtual Value* crossIR(LgsCgModule& cg, LgsBinaryExpr* binExpr);

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
    if (type->isInt || type->isFloat || type->asAny() || type->asChar() || type->isVoid()) return;
    if (type->asGenericType() || type->asObject() || type->asInterface()) return;
    delete type;
}

template<typename T>
void freeTypes(std::vector<T*>& types) {
    for (const auto type : types) {
        freeType(static_cast<LgsType*>(type));
    }
    types.clear();
}

Value* eqIR(LgsCgModule& cg, Value* left, Value* right, LgsType* type);
Value* neIR(LgsCgModule& cg, Value* left, Value* right, LgsType* type);
Value* ltIR(LgsCgModule& cg, Value* left, Value* right, LgsType* type);
Value* gtIR(LgsCgModule& cg, Value* left, Value* right, LgsType* type);
Value* geIR(LgsCgModule& cg, Value* left, Value* right, LgsType* type);
Value* leIR(LgsCgModule& cg, Value* left, Value* right, LgsType* type);
Value* andIR(LgsCgModule& cg, Value* left, Value* right);
Value* orIR(LgsCgModule& cg, Value* left, Value* right);
LgsType* getBiggestIntType(const std::vector<LgsType*>& types);
std::pair<Value*, Value*> loadNumberPair(LgsCgModule& cg, Value* left, Value* right, Type* type);
