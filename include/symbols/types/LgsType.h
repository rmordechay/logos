#pragma once
#include "pch.h"
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
class LgsConstExpr;
class LgsField;
class LgsFunc;

class LgsType {
public:
    Location location;
    bool isVoid = false;
    bool isConst = false;
    bool isInt = false;
    bool isNullable = false;
    bool isPrimitive = false;
    bool isBuiltin = false;
    Type* IRType = nullptr;
    LgsHashMap* vtable = nullptr;
    map<string, LgsField*> fields;
    map<string, LgsFunc*> methods;

    LgsField* getField(const string& name);
    LgsFunc* getMethod(const string& name);
    void addMethod(LgsFunc* method);
    LgsFunc* findMethod(const string& name) const;
    void setLocation(const antlr4::Token* ctx);

    LgsBool* asBool();
    LgsStr* asStr();
    LgsInt* asInt();
    LgsLong* asLong();
    LgsMap* asMap();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsIterable* asIterable();
    LgsArray* asArray();
    LgsFuncType* asFuncType();
    LgsGroup* asGroup();
    bool isUnknown();

    virtual size_t getSizeBytes();
    virtual bool equals(LgsType& other);
    virtual json asJSON() const;
    virtual string getStrFormatPart() const;
    virtual Type* getIRType() = 0;
    virtual string getIRName() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual string prettyName() const = 0;
    virtual bool equals(LgsType* other) = 0;
    virtual LgsType* inferBinaryType(LgsType* other) = 0;
    virtual LgsType* clone();
    virtual ~LgsType();
};
