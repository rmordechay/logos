#pragma once

#include "LgsLocation.h"

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
class LgsModule;

class LgsType {
public:
    Location location;
    bool isVoid = false;
    bool isInt = false;
    bool isUnsigned = false;
    bool isPrimitive = false;
    bool isSizeBig = false;
    bool isBuiltin = false;
    bool isUnknown = false;
    bool hasVirtual = false;
    bool canSlice = false;
    Type* IRType = nullptr;
    LgsHashMap* vtable = nullptr;
    vector<LgsVariable*> refs;
    map<string, LgsField*> fields;
    map<string, LgsFunc*> methods;

    bool addField(LgsField* field);
    bool addMethod(LgsFunc* method);
    LgsField* getField(const string& name);
    LgsFunc* getMethod(const string& name) const;
    void setLocation(const Token* begin, const Token* end, const path& filePath);

    LgsBool* asBool();
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

    virtual size_t getSizeBytes();
    virtual bool equals(LgsType& other);
    virtual string getStrFormatPart() const;
    virtual string getName() = 0;
    virtual string prettyName() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual Type* getIRType(LgsModule* module) = 0;
    virtual bool equals(LgsType* other) = 0;
    virtual ~LgsType();
};
