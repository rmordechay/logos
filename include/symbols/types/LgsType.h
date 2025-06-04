#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H
#include "LgsValue.h"
#include <string>
#include <map>

using namespace std;
using namespace llvm;
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
class LgsMethodImpl;

class LgsType {
public:
    Location location;
    bool isVoid = false;
    bool isConst = false;
    bool isNullable = false;
    bool isPrimitive = false;
    Type* IRType = nullptr;
    map<string, LgsField*> fields;
    map<string, LgsMethodImpl*> methods;

    LgsField* getField(const string& name);
    void addMethod(LgsMethodImpl* method);
    LgsMethodImpl* findMethod(const string& name) const;
    void setLocation(const antlr4::Token* ctx);

    LgsBool* asBool();
    LgsStr* asStr();
    LgsInt* asInt();
    LgsMap* asMap();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsIterable* asIterable();
    LgsArray* asArray();
    LgsFuncType* asFuncType();
    bool isUnknown();

    virtual size_t getSizeBytes();
    virtual bool equals(LgsType& other);
    virtual nlohmann::json asJSON() const;
    virtual string getStrFormatPart() const;
    virtual Type* getIRType(LgsRuntime* runtime) = 0;
    virtual string getIRName() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual string prettyName() const = 0;
    virtual bool equals(LgsType* other) = 0;
    virtual LgsType* inferBinaryType(LgsType* other) = 0;
    virtual LgsType* clone();
    virtual ~LgsType() = default;
};

#endif //LOGOSTYPE_H
