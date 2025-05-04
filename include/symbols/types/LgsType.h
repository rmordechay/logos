#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include "LgsValue.h"

#include <string>
#include <map>

class LgsInt;
class LgsArrayType;
class LgsIterable;
using namespace std;
using namespace llvm;

class LgsStr;
class LgsExpr;
class LgsFuncCall;
class LgsConstExpr;
class LgsField;
class LgsMethodImpl;


class LgsType {
public:
    Location location;
    bool nullable = false;
    Type* IRType = nullptr;
    map<string, LgsField*> fields;
    map<string, vector<LgsMethodImpl*>> methods;

    LgsField* getField(const string& name);
    void addMethod(LgsMethodImpl* method);
    LgsMethodImpl* findMethod(const LgsFuncCall* funcCall) const;
    vector<LgsMethodImpl*> getMethodsOverloads(const string& funcName) const;
    vector<LgsMethodImpl*> getAllMethods() const;
    void setLocation(const antlr4::Token* ctx);

    virtual bool isVoid();
    virtual bool equals(const LgsType& other);
    virtual Type* getIRType() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual const string getName() const = 0;
    virtual bool equals(LgsType* other) const = 0;
    virtual bool isIterable();
    virtual LgsType* getUnderlyingType();
    virtual LgsType* inferBinaryType(LgsType* other) = 0;
    virtual json asJSON() const;

    LgsStr* asStr();
    LgsInt* asInt();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsIterable* asIterable();
    LgsArrayType* asSArrayType();
    virtual ~LgsType() = default;
};

class LgsUnknownType final : public LgsType {
public:
    static constexpr auto typeName = "Unknown";
    string name;

    LgsUnknownType() = default;
    explicit LgsUnknownType(const string& name) : name(name) {}
    const string getName() const override { return name == "" ? typeName : name; }
    LgsExpr* getZeroValue() override { assert(false && "unknown type should not be called"); }
    bool equals(LgsType* other) const override { assert(false && "unknown type should not be called"); }
    LgsType* inferBinaryType(LgsType* other) override { assert(false && "unknown type should not be called"); }
    Type* getIRType() override;
    ~LgsUnknownType() override = default;
};

#endif //LOGOSTYPE_H
