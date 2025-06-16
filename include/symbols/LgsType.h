#pragma once

#include "LgsLocation.h"

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
class LgsInt;
class LgsArray;
class LgsIterable;
class LgsStr;
class LgsExpr;
class LgsFuncCall;
class LgsField;
class LgsFunc;

class LgsType {
public:
    Location location;
    bool isInt = false;
    bool isVoid = false;
    bool isNullable = false;
    bool isPrimitive = false;
    bool isBigType = false;
    bool isBuiltin = false;
    bool isStatic = false;
    bool canSlice = false;
    Type* IRType = nullptr;
    LgsHashMap* vtable = nullptr;
    map<string, LgsField*> fields;
    map<string, LgsFunc*> methods;

    LgsField* getField(const string& name);
    LgsFunc* getMethod(const string& name) const;
    void addMethod(LgsFunc* method);
    void setLocation(const Token* ctx, path* filePath);

    LgsBool* asBool();
    LgsStr* asStr();
    LgsInt* asInt();
    LgsShort* asShort();
    LgsLong* asLong();
    LgsUInt* asUInt();
    LgsMap* asMap();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsIterable* asIterable();
    LgsArray* asArray();
    LgsFuncType* asFuncType();
    LgsGroup* asGroup();
    LgsTypePair* asPair();
    bool isUnknown();

    virtual size_t getSizeBytes();
    virtual bool equals(LgsType& other);
    virtual string getStrFormatPart() const;
    virtual Type* getIRType() = 0;
    virtual string getIRName() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual string pName() const = 0;
    virtual bool equals(LgsType* other) = 0;
    virtual LgsType* inferBinaryType(LgsType* other) = 0;
    virtual ~LgsType();
};
