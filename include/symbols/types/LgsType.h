#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H

#include <string>
#include <map>
#include <llvm/IR/Type.h>

using namespace std;
using namespace llvm;

class LgsExpr;
class LgsFuncCall;
class LgsConstExpr;
class LgsField;
class LgsMethodImpl;

class LgsType {
public:
    bool nullable = false;
    // TODO make values const
    map<string, LgsField*> fields;
    map<string, vector<LgsMethodImpl*>> methods;

    LgsField* getField(const string& name);
    LgsMethodImpl* getMethod(const LgsFuncCall* funcCall);
    virtual Type* getIRType();
    virtual Type* getIRType(int size);
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
    const string getName() const override { assert(false && "unknown type should not be called"); }
    LgsExpr* getZeroValue() override { assert(false && "unknown type should not be called"); }
    bool equals(LgsType* other) const override { assert(false && "unknown type should not be called"); }
    LgsType* inferBinaryType(LgsType* other) override { assert(false && "unknown type should not be called"); }
};

#endif //LOGOSTYPE_H
