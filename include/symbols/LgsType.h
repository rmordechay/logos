#pragma once
#include "LgsErrors.h"

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
    LgsLocation location;
    bool isVoid = false;
    bool isNumber = false;
    bool isUnsigned = false;
    bool isPrimitive = false;
    bool isBig = false;
    bool isUnknown = false;
    bool canSlice = false;
    Type* IRType = nullptr;
    map<string, LgsField*> fields;
    map<string, LgsFunc*> methods;

    bool addField(LgsField* field);
    bool addMethod(LgsFunc* method);
    LgsField* getField(const string& name);
    LgsFunc* getMethod(const string& name);

    LgsBool* asBool();
    LgsChar* asChar();
    LgsStr* asStr();
    LgsInt* asInt();
    LgsShort* asShort();
    LgsLong* asLong();
    LgsUInt* asUInt();
    LgsMap* asMap();
    LgsEnum* asEnum();
    LgsNullable* asNullable();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsIterable* asIterable();
    LgsDArray* asDArray();
    LgsSArray* asSArray();
    LgsFuncType* asFuncType();
    LgsGroup* asGroup();
    LgsTypePair* asPair();

    virtual string getName() = 0;
    virtual string prettyName() = 0;
    virtual size_t getSizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual Type* getIRType(LgsCodeGen* codeGen) = 0;
    virtual bool equals(LgsType* other) = 0;
    virtual string getStrFormatPart() const;
    virtual void freeValue(LgsCodeGen* codeGen, Value* value);
    virtual ~LgsType() = default;
};
