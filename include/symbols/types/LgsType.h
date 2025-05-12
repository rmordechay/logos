#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H
#include "LgsValue.h"
#include <string>
#include <map>

using namespace std;
using namespace llvm;
class LgsMap;
class LgsInt;
class LgsArray;
class LgsIterable;
class LgsStr;
class LgsExpr;
class LgsFuncCall;
class LgsConstExpr;
class LgsField;
class LgsMethodImpl;

class LgsType {
public:
    Location location;
    bool isNullable = false;
    Type* IRType = nullptr;
    bool isVoidType = false;
    bool isConst = false;
    map<string, LgsField*> fields;
    map<string, vector<LgsMethodImpl*>> methods;

    LgsField* getField(const string& name);
    void addMethod(LgsMethodImpl* method);
    LgsMethodImpl* findMethod(LgsFuncCall* funcCall) const;
    vector<LgsMethodImpl*> getMethodOverloads(const string& funcName) const;
    vector<LgsMethodImpl*> getAllMethods() const;
    void setLocation(const antlr4::Token* ctx);

    LgsStr* asStr();
    LgsInt* asInt();
    LgsMap* asMap();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsIterable* asIterable();
    LgsArray* asArray();
    LgsFuncType* asFuncType();

    virtual size_t getSize();
    virtual bool equals(LgsType& other);
    virtual bool isIndexable(LgsType* indexType);
    virtual json asJSON() const;
    virtual string getStrFormatPart();

    virtual Type* getIRType() = 0;
    virtual string getIRName() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual string prettyName() const = 0;
    virtual bool equals(LgsType* other) = 0;
    virtual LgsType* inferBinaryType(LgsType* other) = 0;
    virtual ~LgsType() = default;
};

#endif //LOGOSTYPE_H
