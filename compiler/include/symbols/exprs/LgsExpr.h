#pragma once
#include <math.h>

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
class LgsCodeGen;
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
    bool hasUnwrapSuffix = false;

    bool isReturnExpr = false;
    bool hasMoved = false;
    Value* pointee = nullptr;

    explicit LgsExpr(LgsType* type = nullptr) : type(type) {}
    std::optional<int64_t> getConstInt();
    std::optional<double_t> getConstFloat();
    std::optional<std::string> getConstStr();
    LgsType* getType() override;

    virtual void setType(LgsType* newType);
    virtual LgsExpr* castExplicitly(LgsType* toType);
    virtual void castImplicitly(LgsType* toType);
    virtual void assign(LgsCodeGen& cg, LgsExpr* right);
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
Value* moveValue(LgsCodeGen& cg, Value* left, Value* right, LgsType* type);

void freeExpr(LgsExpr* expr);
template<typename T>
void freeExprs(std::vector<T*>& exprs) {
    for (const auto expr : exprs) {
        freeExpr(static_cast<LgsExpr*>(expr));
    }
    exprs.clear();
}
