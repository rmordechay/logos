#pragma once
#include "LgsValue.h"

class LgsField;
class LgsParam;
class LgsVarDec;
class LgsComplexConst;
class LgsNullable;
class LgsNullableExpr;
class LgsMetaSelection;
class LgsMatrixExpr;
class LgsEnvVar;
class LgsBinaryExpr;
class LgsJson;
class LgsCast;
class LgsTypeExpr;
class LgsMetaVar;
class LgsIntConst;
class LgsVectorExpr;
class LgsPrefixExpr;
class LgsPostfixExpr;
class LgsCgModule;
class LgsFunc;
class LgsHashMap;
class LgsFuncCall;
class LgsType;
class LgsVariable;
class LgsSelection;
class LgsInstance;
class LgsIterIndex;
class LgsArrayExpr;
class LgsSArray;
class LgsCharConst;
class LgsFloatConst;
class LgsStrConst;
class LgsTypeConst;

enum LgsOwnerType {
    PARAM_OWNER,
    VARDEC_OWNER,
    FIELD_OWNER,
    NO_OWNER,
};

struct LgsOwner {
    LgsOwnerType type;
    union {
        LgsParam* param;
        LgsField* field;
        LgsVarDec* varDec;
        void* noOwner;
    };
    LgsOwner(): type(NO_OWNER), noOwner(nullptr) {}
    explicit LgsOwner(LgsParam* param): type(PARAM_OWNER), param(param) {}
    explicit LgsOwner(LgsField* field): type(FIELD_OWNER), field(field) {}
    explicit LgsOwner(LgsVarDec* varDec): type(VARDEC_OWNER), varDec(varDec) {}
};

class LgsExpr : public LgsValue {
public:
    LgsType* type = nullptr;
    bool isMutable = true;
    bool isImportName = false;
    bool isNull = false;
    bool isReturnExpr = false;
    bool hasUnwrapSuffix = false;
    Value* pointee = nullptr;
    LgsOwner owner;

    explicit LgsExpr(LgsType* type = nullptr) : type(type) {}
    void setOwner(LgsOwner newOwner);
    std::optional<int64_t> getConstInt();
    std::optional<std::string> getConstStr();

    virtual void setType(LgsType* newType);
    virtual LgsExpr* castExplicitly(LgsType* toType);
    virtual void castImplicitly(LgsType* toType);
    virtual Value* hashValue(LgsCgModule& cg);
    virtual void assign(LgsCgModule& cg, LgsExpr* expr);
    virtual bool equals(LgsExpr* other);
    virtual std::string asText() = 0;

    LgsFunc* asFunc();
    LgsVariable* asVariable();
    LgsPrefixExpr* asPrefixExpr();
    LgsFuncCall* asFuncCall();
    LgsPostfixExpr* asPostfixExpr();
    LgsSelection* asSelection();
    LgsIterIndex* asIterIndex();
    LgsTypeExpr* asTypeExpr();
    LgsJson* asJson();
    LgsCast* asCast();
    LgsInstance* asInstance();
    LgsArrayExpr* asArrayExpr();
    LgsHashMap* asHashMap();
    LgsEnvVar* asEnvVar();
    LgsIntConst* asIntConst();
    LgsStrConst* asStrConst();
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsComplexConst* asComplexConst();
    LgsVectorExpr* asVectorExpr();
    LgsMatrixExpr* asMatrixExpr();
    LgsMetaVar* asLoopMetaVar();
    LgsBinaryExpr* asBinExpr();
    LgsMetaSelection* asMetaSelection();
    LgsNullableExpr* asNullableExpr();
    LgsExpr* clone() override;
    ~LgsExpr() override = default;
};

void wrapInNullable(LgsExpr*& expr, LgsNullable* nullable);
void castExprImplicitly(LgsExpr*& expr, LgsType* toType);

void freeExpr(LgsExpr* expr);
template<typename T>
void freeExprs(std::vector<T*>& exprs) {
    for (const auto expr : exprs) {
        freeExpr(static_cast<LgsExpr*>(expr));
    }
    exprs.clear();
}
