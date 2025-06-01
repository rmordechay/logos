#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "LgsValue.h"

class LgsHashMap;
class LgsFuncCall;
class LgsType;
class LgsVariable;
class LgsSelection;
class LgsInstance;
class LgsIterIndex;
class LgsArrayExpr;
class LgsSArray;
class LgsBoolConst;
class LgsCharConst;
class LgsFloatConst;
class LgsIntConst;
class LgsStrConst;
class LgsTypeConst;

class LgsExpr : virtual public LgsValue {
public:
    // TODO free type
    LgsType* type = nullptr;
    bool isReturnValue = false;
    bool isNull = false;

    explicit LgsExpr(LgsType* type) : type(type) {}
    Value* getIRValue(CodegenMetadata* metadata);
    void setType(LgsType* type);

    LgsFunc* asFunc();
    LgsVariable* asVariable();
    LgsFuncCall* asFuncCall();
    LgsIterIndex* asIterIndex();
    LgsInstance* asInstance();
    LgsSelection* asSelection();
    LgsArrayExpr* asArrayExpr();
    LgsHashMap* asHashMap();
    LgsBoolConst* asBoolConst();
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsIntConst* asIntConst();
    LgsStrConst* asStrConst();
    LgsEnumField* asEnumField();
    LgsTypeConst* asTypeConst();

    virtual void free();
    virtual LgsExpr* clone();
    virtual string prettyName();
    virtual LgsExpr* convertExpr(LgsType* type);
    virtual Value* getLength(CodegenMetadata* metadata);
    virtual uint32_t hashValue(CodegenMetadata* metadata);
    virtual Value* createIRValue(CodegenMetadata* metadata) = 0;
    virtual Value* addIR(CodegenMetadata* metadata, LgsExpr* other) = 0;
    virtual Value* subIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* mulIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* divIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* eqIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* neIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* ltIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* gtIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* geIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* leIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* andIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* orIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* bitAndIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* bitOrIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* bitXorIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* rshiftIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual Value* lshiftIR(CodegenMetadata* metadata, LgsExpr* other);
    virtual ~LgsExpr() override = default;
};

#endif //LOGOSEXPR_H