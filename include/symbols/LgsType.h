#pragma once
#include "Lgs_types.h"
#include "data/LgsErrors.h"
#include "exprs/LgsBinaryExpr.h"

class LgsAny;
class LgsSubType;
class LgsByte;

namespace llvm {
    class DIBasicType;
    class Value;
    class Type;
}

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
class LgsGroup;
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
class LgsLLVMGen;

using namespace llvm;

class LgsType {
public:
    bool isInt = false;
    bool isFloat = false;
    bool isPrimitive = false;
    bool isUnsigned = false;
    bool isHeapAlloc = false;
    Type* IRType = nullptr;
    LgsLocation location{0, 0, 0};
    std::vector<LgsField*> fields;
    std::map<std::string, LgsFunc*> methods;

    LgsType* extendInt();
    bool addField(LgsField* field);
    bool addMethod(LgsFunc* method);
    bool addEmptyMethod(const std::string& name);
    bool equals(LgsType* other);
    bool isVoid();
    bool isNumber() const;
    bool isBig();
    bool isNullable();
    bool isUnknown();
    bool isSliceable();

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
    LgsMap* asMap();
    LgsEnum* asEnum();
    LgsNullable* asNullable();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsIterable* asIterable();
    LgsDArray* asDArray();
    LgsSArray* asSArray();
    LgsVec* asVec();
    LgsFuncType* asFuncType();
    LgsPtr* asPtr();
    LgsGroup* asGroup();
    LgsSubType* asSubtype();
    LgsTypePair* asPair();

    virtual LgsField* getField(const std::string& name);
    virtual LgsFunc* getMethod(const std::string& name);
    virtual Type* getIRType(LgsLLVMGen& cg) = 0;
    virtual size_t getSizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual Lgs_RTType getRTType() = 0;
    virtual std::string getName() = 0;
    virtual std::string pname() = 0; // pretty name
    virtual bool canCastTo(LgsType* other) = 0;
    virtual LgsType* applyOp(LgsType* other, LgsOperator op);
    virtual std::string strFormatPart() const = 0;
    virtual DIBasicType* getDebugType(LgsLLVMGen& cg);
    virtual LgsType* clone();
    virtual json::value asJSON() = 0;

    virtual Value* addIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* subIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* mulIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* divIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* modIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* eqIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* neIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* ltIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* gtIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* geIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* leIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* bitAndIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* bitOrIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* bitXorIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* lshiftIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* rshiftIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* andIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual Value* orIR(LgsLLVMGen& cg, Value* self, Value* other);
    virtual ~LgsType() = default;
};
