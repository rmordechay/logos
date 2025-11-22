#pragma once
#include "Lgs_Types.h"
#include "errors/LgsErrors.h"
#include "exprs/LgsBinaryExpr.h"
#include <map>

class LgsMatrix;
class LgsSubType;
class LgsGenericParam;
class LgsSet;
class LgsAny;
class LgsByte;
class LgsSize;
class LgsPtr;
class LgsDouble;
class LgsFloat;
class LgsVec;
class LgsVectorExpr;
class LgsChar;
class LgsVariable;
class LgsSArray;
class LgsNullable;
class LgsUInt;
class LgsShort;
class LgsTypePair;
class LgsLong;
class LgsHashMap;
class LgsVTable;
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
class LgsLLVMGen;

class LgsType {
public:
    LgsLocation location;
    std::vector<LgsField*> fields;
    std::map<std::string, LgsFunc*> methods;
    std::vector<LgsType*> genericArgs;
    Type* IRType = nullptr;
    bool isInt = false;
    bool isFloatingPoint = false;
    bool isPrimitive = false;
    bool isHeapAlloc = false;
    bool passByRef = false;

    bool addField(LgsField* field);
    bool addMethod(LgsFunc* method);
    bool addEmptyMethod(const std::string& name);
    bool isVoid();
    bool isNumber() const;
    bool isBig();
    bool isUnknown();
    bool isSliceable();
    LgsType* extendInt();
    LgsType* applyIntBinOp(LgsType* toType, LgsBinOpType op);
    void cloneFields(LgsType* newType) const;
    void cloneMethods(LgsType* newType) const;
    static Value* orInt(LgsLLVMGen& cg, const LgsExpr* self, const LgsExpr* other);
    static Value* andInt(LgsLLVMGen& cg, LgsExpr* self, const LgsExpr* other);

    virtual LgsField* getField(const std::string& fieldName);
    virtual LgsFunc* getMethod(const std::string& methodName);
    virtual size_t sizeBytes() = 0;
    virtual LgsExpr* getZeroValue() = 0;
    virtual Type* getIRType(LgsLLVMGen& cg) = 0;
    virtual bool canCastTo(LgsType* other) = 0;
    virtual Lgs_TypeKind getRTTypeKind() = 0;
    virtual std::string strFormatPart() const = 0;
    virtual llvm::DIType* getDebugType(LgsLLVMGen& cg) = 0;
    virtual LgsType* applyBinOp(LgsType* toType, LgsBinOp& op);
    virtual void hashNode(size_t& oldHash);
    virtual LgsType* clone() = 0;
    virtual std::string getName() = 0;
    virtual std::string pname(); // pretty name
    virtual bool equals(LgsType* other);

    virtual Value* addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* divIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* modIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* powIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* bitAndIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* bitOrIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* bitXorIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* lshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* other);
    virtual Value* rshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* eqIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* neIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* ltIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* gtIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* geIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* leIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* andIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);
    virtual Value* orIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right);

    LgsAny* asAny();
    LgsChar* asChar();
    LgsStr* asStr();
    LgsBool* asBool();
    LgsByte* asByte();
    LgsInt* asInt();
    LgsShort* asShort();
    LgsLong* asLong();
    LgsSize* asSize();
    LgsUInt* asUInt();
    LgsFloat* asFloat();
    LgsDouble* asDouble();
    LgsFuncType* asFuncType();
    LgsObject* asObject();
    LgsInterface* asInterface();
    LgsEnum* asEnum();
    LgsGenericParam* asGeneric();
    LgsIterable* asIterable();
    LgsSArray* asSArray();
    LgsDArray* asDArray();
    LgsSet* asSet();
    LgsVec* asVec();
    LgsMatrix* asMatrix();
    LgsPtr* asPtr();
    LgsMap* asMap();
    LgsTypePair* asPair();
    LgsSubType* asSubtype();
    LgsNullable* asNullable();
    virtual ~LgsType();
};

void freeType(LgsType* type);
template<typename T>
void freeTypes(std::vector<T*>& types) {
    for (const auto type : types) {
        freeType(static_cast<LgsType*>(type));
    }
    types.clear();
}
