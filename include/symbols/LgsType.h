#pragma once

#include "LgsLocation.h"

class LgsNullable;
class LgsPtr;
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
    bool isVoid = false;
    bool isInt = false;
    bool isUnsigned = false;
    bool isPrimitive = false;
    bool isBigType = false;
    bool isBuiltin = false;
    bool canSlice = false;
    Type* IRType = nullptr;
    LgsHashMap* vtable = nullptr;
    map<string, LgsField*> fields;
    map<string, LgsFunc*> methods;

    LgsField* getField(const string& name);
    LgsFunc* getMethod(const string& name) const;
    bool addMethod(LgsFunc* method);
    void setLocation(const Token* ctx, const Token* end, const path& filePath);

    LgsPtr* asPtr();
    LgsBool* asBool();
    LgsStr* asStr();
    LgsInt* asInt();
    LgsShort* asShort();
    LgsLong* asLong();
    LgsUInt* asUInt();
    LgsMap* asMap();
    LgsNullable* asNullable();
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
    virtual Type* getIRType(LLVMContext& context) = 0;
    virtual string getIRName() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual string prettyName() const = 0;
    virtual bool equals(LgsType* other) = 0;
    virtual ~LgsType();
};
