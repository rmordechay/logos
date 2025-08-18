#pragma once
#include "configs/LgsErrors.h"

class LgsDouble;
class LgsFloat;

namespace llvm {
    class Value;
    class Type;
}

class LgsVec;
class LgsVectorExpr;

class LgsChar;
class LgsVariable;
class LgsSArray;
class LgsNullable;
class LgsCPtr;
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
class LgsCodeGen;

class LgsType {
public:
    bool isNumber = false;
    bool isUnsigned = false;
    bool isPrimitive = false;
    bool isSliceable = false;
    bool isHeapAlloc = false;
    llvm::Type* IRType = nullptr;
    LgsLocation location{0, 0, 0};
    std::map<std::string, LgsField*> fields;
    std::map<std::string, LgsFunc*> methods;

    bool addField(LgsField* field);
    bool addMethod(LgsFunc* method);
    virtual LgsField* getField(const std::string& name);
    virtual LgsFunc* getMethod(const std::string& name);

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
    LgsGroup* asGroup();
    LgsTypePair* asPair();
    bool isVector();
    bool isVoid();
    bool isUnknown();

    virtual llvm::Type* getIRType(LgsCodeGen* codeGen) = 0;
    virtual size_t getSizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual std::string getName() = 0;
    virtual std::string pname() = 0; // pretty name
    virtual bool equals(LgsType* other) = 0;
    virtual std::string strFormatPart() const = 0;
    virtual void freeValue(LgsCodeGen* codeGen, llvm::Value* value);
    virtual ~LgsType();
};
