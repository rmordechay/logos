#pragma once
#include <stmts/LgsStmt.h>
#include "LgsValue.h"

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
    LgsValue* owner = nullptr;
    Value* destPtrValue = nullptr;

    explicit LgsExpr(LgsType* type = nullptr) : type(type) {}
    void freeOwner(LgsCgModule& cg);
    std::optional<int64_t> getConstInt();
    std::optional<std::string> getConstStr();
    void setType(LgsType* newType);

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
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsStrConst* asStrConst();
    LgsVectorExpr* asVectorExpr();
    LgsMatrixExpr* asMatrixExpr();
    LgsIntConst* asIntConst();
    LgsMetaVar* asLoopMetaVar();
    LgsBinaryExpr* asBinExpr();
    LgsMetaSelection* asMetaSelection();
    ~LgsExpr() override = default;
};

Value* dotProduct(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
Value* crossProduct(LgsCgModule& cg, LgsExpr* left, LgsExpr* right);
void freeExpr(LgsExpr* expr);

template<typename T>
void freeExprs(std::vector<T*>& exprs) {
    for (const auto expr : exprs) {
        freeExpr(static_cast<LgsExpr*>(expr));
    }
    exprs.clear();
}

