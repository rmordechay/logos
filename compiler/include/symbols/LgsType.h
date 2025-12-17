#pragma once
#include <map>
#include <ostream>
#include <vector>
#include "errors/LgsErrHandler.h"

class LgsComplex;
class LgsOwner;
struct LgsBinOp;
class LgsBinaryExpr;
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
    std::map<std::string, LgsFunc*> methods;
    std::vector<LgsType*> genericArgs;
    Type* IRType = nullptr;
    bool isInt = false;
    bool isUnsinged = false;
    bool isFloat = false;
    bool isPrimitive = false;
    bool isHeapAlloc = false;
    bool passByRef = false;

    bool addField(LgsField* field);
    bool addMethod(LgsFunc* method);
    virtual LgsField* getField(const std::string& fieldName);
    virtual LgsFunc* getMethod(const std::string& methodName);
    virtual size_t sizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual Type* getIRType(LgsCgModule& cg) = 0;
    virtual Constant* getRTType(LgsCgModule& cg) = 0;
    virtual bool canCastTo(LgsType* other) = 0;
    virtual std::string fmtStr() const = 0;
    virtual DIType* getDebugType(LgsCgModule& cg) = 0;
    virtual LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) = 0;
    virtual void hashNode(size_t& oldHash);
    virtual std::string getName() = 0;
    virtual std::string pname(); // pretty name
    virtual bool equals(LgsType* other);

    bool isVoid();
    bool isNumber();
    bool isBig();
    bool isUnknown();
    bool isSliceable();
    LgsType* extendInt();
    void cloneFields(LgsType* newType) const;
    void cloneMethods(LgsType* newType) const;

    virtual Value* addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* powIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* other);
    virtual Value* rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* crossIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);

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
    if (type->isPrimitive) return;
    if (type->asGenericType() || type->asObject()) return;
    delete type;
}


template<typename T>
void freeTypes(std::vector<T*>& types) {
    for (const auto type : types) {
        freeType(static_cast<LgsType*>(type));
    }
    types.clear();
}

Value* eqIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
Value* neIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
Value* ltIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
Value* gtIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
Value* geIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
Value* leIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
Value* andIR(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right);
Value* orIR(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right);
std::pair<Value*, Value*> loadPairAsFloat(LgsCgModule& cg, LgsExpr* self, LgsExpr* other);
std::pair<Value*, Value*> loadPairAsDouble(LgsCgModule& cg, LgsExpr* self, LgsExpr* other);
std::pair<Value*, Value*> loadPairAsInt(LgsCgModule& cg, LgsExpr* self, LgsExpr* other);
std::pair<Constant*, Constant*> getRTFieldsInfo(LgsCgModule& cg, const std::string& name, const std::vector<LgsOwner*>& values);
