#pragma once
#include <map>
#include <ostream>
#include <vector>
#include "errors/LgsErrHandler.h"
#include <unordered_map>

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

    bool addField(LgsField* field);
    bool addMethod(LgsFunc* method);
    bool isVoid();
    bool isNumber();
    bool isScalar() const;
    bool isBig();
    bool isUnknown();
    bool isSliceable();
    bool hasGenericTypes();

    virtual LgsField* getField(const std::string& fieldName);
    virtual LgsFunc* getMethod(const std::string& methodName);
    virtual LgsType* replaceGenerics(LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements);
    virtual size_t sizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual Value* getIRZeroValue(LgsCgModule& cg, Value* isReturnExpr = nullptr, Value* pointee = nullptr);
    virtual Type* getIRType(LgsCgModule& cg) = 0;
    virtual Type* getTypeOrPtr(LgsCgModule& cg);
    virtual Constant* getRTType(LgsCgModule& cg) = 0;
    virtual bool canCastTo(LgsType* other) = 0;
    virtual std::string fmtStr() const = 0;
    virtual DIType* getDebugType(LgsCgModule& cg) = 0;
    virtual LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) = 0;
    virtual void hashNode(size_t& oldHash);
    virtual std::string getName() = 0;
    virtual std::string pname(); // pretty name
    virtual bool equals(LgsType* other);
    virtual LgsType* clone();

    virtual Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* powIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* crossIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);

    bool isAny();
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

Value* eqIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType);
Value* neIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType);
Value* ltIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType);
Value* gtIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType);
Value* geIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType);
Value* leIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType);
Value* andIR(LgsCgModule& cg, Value* left, Value* right);
Value* orIR(LgsCgModule& cg, Value* left, Value* right);
std::pair<Value*, Value*> loadPairAsFloat(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType);
std::pair<Value*, Value*> loadPairAsDouble(LgsCgModule& cg, Value* left, Value* right);
std::pair<Constant*, Constant*> getRTValuesInfo(LgsCgModule& cg, const std::string& name, const std::vector<LgsValue*>& values);
LgsType* getBiggestIntType(const std::vector<LgsType*>& types);
