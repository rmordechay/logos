#pragma once
#include "pch.h"

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

enum LgsTypeOpts : uint16_t {
    BIG_TYPE = 1 << 0,
    VOID = 1 << 1,
    CONST = 1 << 2,
    INT = 1 << 3,
    NULLABLE = 1 << 4,
    PRIMITIVE = 1 << 5,
    BUILTIN = 1 << 6,

    METHOD = 1 << 8,
    STATIC = 1 << 9,
    PUBLIC = 1 << 10,
    VIRTUAL = 1 << 11,
    VARIADIC = 1 << 12,
    ANONYMOUS = 1 << 13,
    SWAP_RETURN = 1 << 14,
    HAS_DEFAULTS = 1 << 15,
};

class LgsType {
public:
    Location location;
    uint32_t flags = 0;
    Type* IRType = nullptr;
    LgsHashMap* vtable = nullptr;
    map<string, LgsField*> fields;
    map<string, LgsFunc*> methods;

    LgsField* getField(const string& name);
    LgsFunc* getMethod(const string& name);
    void addMethod(LgsFunc* method);
    LgsFunc* findMethod(const string& name) const;
    void setLocation(const Token* ctx);
    bool hasFlag(LgsTypeOpts opt) const;
    void setFlag(LgsTypeOpts opt);

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
    LgsTypePair* asPair();
    bool isUnknown();

    virtual size_t getSizeBytes();
    virtual void castImplicitly(LgsType& toType);
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
