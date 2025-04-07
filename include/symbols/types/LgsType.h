#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include "LgsValue.h"

#include <string>
#include <map>

using namespace std;
using namespace llvm;

class LgsExpr;
class LgsFuncCall;
class LgsConstExpr;
class LgsField;
class LgsMethodImpl;


class LgsType {
public:
    Location location;
    bool nullable = false;
    map<string, LgsField*> fields;
    map<string, vector<LgsMethodImpl*>> methods;

    LgsField* getField(const string& name);
    LgsMethodImpl* getMethod(const LgsFuncCall* funcCall) const;
    LgsMethodImpl* getMethod(const LgsFuncSignature* signature) const;
    vector<LgsMethodImpl*> getMethodsOverloads(const string& funcName) const;
    virtual Type* getIRType();
    virtual Type* getIRType(int size);
    virtual bool equals(const LgsType& other);
    virtual LgsExpr* getZeroValue() = 0;
    virtual const string getName() const = 0;
    virtual bool equals(LgsType* other) const = 0;
    virtual LgsType* inferBinaryType(LgsType* other) = 0;
    virtual ~LgsType() = default;
};

class LgsUnknownType final : public LgsType {
public:
    string name;

    explicit LgsUnknownType(const string& name) : name(name) {}
    const string getName() const override { return name; }
    LgsExpr* getZeroValue() override { assert(false && "unknown type should not be called"); }
    bool equals(LgsType* other) const override { assert(false && "unknown type should not be called"); }
    LgsType* inferBinaryType(LgsType* other) override { assert(false && "unknown type should not be called"); }
};

#endif //LOGOSTYPE_H
