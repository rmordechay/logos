#pragma once
#include "configs/LgsErrors.h"

namespace llvm {
    class Value;
    class Type;
}

class LgsVec2;
class LgsVector;

class LgsChar;
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
class LgsCodeGen;

class LgsType {
public:
    bool isNumber = false;
    bool isUnsigned = false;
    bool isPrimitive = false;
    bool canSlice = false;
    llvm::Type* IRType = nullptr;
    LgsLocation location{0, 0, nullptr};
    std::map<std::string, LgsField*> fields;
    std::map<std::string, LgsFunc*> methods;

    bool addField(LgsField* field);
    bool addMethod(LgsFunc* method);
    virtual LgsField* getField(const std::string& name);
    virtual LgsFunc* getMethod(const std::string& name);

    LgsBool* asBool();
    LgsChar* asChar();
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
    LgsVec2* asVec2();
    LgsFuncType* asFuncType();
    LgsGroup* asGroup();
    LgsTypePair* asPair();
    bool isVector();
    bool isVoid();
    bool isUnknown();

    virtual std::string getName() = 0;
    virtual std::string prettyName() = 0;
    virtual size_t getSizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual llvm::Type* getIRType(LgsCodeGen* codeGen) = 0;
    virtual bool equals(LgsType* other) = 0;
    virtual std::string strFormatPart() const;
    virtual void freeValue(LgsCodeGen* codeGen, llvm::Value* value);
    virtual ~LgsType() = default;
};
