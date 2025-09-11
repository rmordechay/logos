#pragma once
#include "Lgs_types.h"
#include "configs/LgsErrors.h"
#include "exprs/LgsBinaryExpr.h"
#include "symbols/LgsAssignable.h"

namespace llvm {
    class DIBasicType;
    class Value;
    class Type;
}

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
    bool isNumber = false;
    bool isUnsigned = false;
    bool isFloatPoint = false;
    bool isPrimitive = false;
    bool isSliceable = false;
    bool isHeapAlloc = false;
    Type* IRType = nullptr;
    LgsLocation location{0, 0, 0};
    std::vector<LgsField*> fields;
    std::map<std::string, LgsFunc*> methods;
    LgsRTType rtt;

    virtual LgsField* getField(const std::string& name);
    virtual LgsFunc* getMethod(const std::string& name);
    virtual Type* getIRType(LgsLLVMGen& cg) = 0;
    virtual size_t getSizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual std::string getName() = 0;
    virtual std::string pname() = 0; // pretty name
    virtual bool canCastTo(LgsType* other) = 0;
    virtual bool canAssignTo(LgsType* other, LgsAssignType op);
    virtual bool canApplyOp(LgsType* other, LgsOperator op);
    virtual std::string strFormatPart() const = 0;
    virtual DIBasicType* getDebugType(LgsLLVMGen& cg);
    virtual void freeValue(LgsLLVMGen& cg, LgsExpr* value);
    virtual LgsType* clone();
    virtual json::value asJSON() = 0;

    virtual Value* addIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* subIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* mulIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* divIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* inIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* modIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* eqIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* neIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* ltIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* gtIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* geIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* leIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* andIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* orIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* bitAndIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* bitOrIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* bitXorIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* lshiftIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);
    virtual Value* rshiftIR(LgsLLVMGen& cg, Value* value, LgsExpr* other);

    bool addField(LgsField* field);
    bool addMethod(LgsFunc* method);
    bool equals(LgsType* other);
    bool isVoid();
    bool isUnknown();
    bool isBig();
    LgsBool* asBool();
    LgsChar* asChar();
    LgsStr* asStr();
    LgsInt* asInt();
    LgsShort* asShort();
    LgsLong* asLong();
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
    LgsTypePair* asPair();
    virtual ~LgsType();
};
