#pragma once
#include "LgsValue.h"

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

class LgsExpr : public LgsValue {
public:
    LgsType* type = nullptr;
    bool isMutable = true;
    bool isImportName = false;
    bool isNull = false;
    bool isReturnExpr = false;
    bool hasUnwrapSuffix = false;
    LgsValue* owner = nullptr;
    Value* pointee = nullptr;

    explicit LgsExpr(LgsType* type = nullptr) : type(type) {}
    void setOwner(LgsValue* newOwner);
    std::optional<int64_t> getConstInt();
    std::optional<std::string> getConstStr();

    virtual void setType(LgsType* newType);
    virtual LgsExpr* castExplicitly(LgsType* toType);
    virtual void castImplicitly(LgsType* toType);
    virtual Value* hashValue(LgsCgModule& cg);
    virtual void assign(LgsCgModule& cg, LgsExpr* expr);
    virtual bool equals(LgsExpr* other);
    LgsExpr* clone() override;
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
