#pragma once
#include <math.h>
#include "LgsValue.h"
#include "types/LgsGenericType.h"

class LgsModuleExpr;
class LgsNull;
class LgsPair;
class LgsField;
class LgsParam;
class LgsVarDec;
class LgsNullable;
class LgsNullableExpr;
class LgsMetaSelection;
class LgsMatrixExpr;
class LgsEnvVar;
class LgsBinaryExpr;
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
    LgsType* implicitCast = nullptr;
    bool isMutable = true;
    bool isNull = false;
    bool isReturnExpr = false;
    bool hasUnwrap = false;
    Value* pointee = nullptr;

    explicit LgsExpr(LgsType* type = nullptr) : type(type) {}
    LgsType* getType() override;
    void setType(LgsType* newType) override;
    LgsExpr* wrapInNullable();
    std::optional<int64_t> getConstInt();
    std::optional<double_t> getConstFloat();
    std::optional<std::string> getConstStr();

    virtual Value* loadIR(LgsCodeGen& cg);
    virtual LgsExpr* cast(bool explicitly);
    virtual bool equals(LgsExpr* other);
    virtual std::string asText() = 0;

    LgsFunc* asFunc();
    LgsCast* asCast();
    LgsVariable* asVariable();
    LgsModuleExpr* asModuleExpr();
    LgsPrefixExpr* asPrefixExpr();
    LgsFuncCall* asFuncCall();
    LgsPostfixExpr* asPostfixExpr();
    LgsSelection* asSelection();
    LgsIterIndex* asIterIndex();
    LgsTypeExpr* asTypeExpr();
    LgsInstance* asInstance();
    LgsArrayExpr* asArrayExpr();
    LgsHashMap* asHashMap();
    LgsPair* asPair();
    LgsEnvVar* asEnvVar();
    LgsIntConst* asIntConst();
    LgsStrConst* asStrConst();
    LgsCharConst* asCharConst();
    LgsFloatConst* asFloatConst();
    LgsVectorExpr* asVectorExpr();
    LgsMatrixExpr* asMatrixExpr();
    LgsMetaVar* asLoopMetaVar();
    LgsBinaryExpr* asBinExpr();
    LgsMetaSelection* asMetaSelection();
    LgsNullableExpr* asNullableExpr();
    LgsExpr* clone() override;
    ~LgsExpr() override = default;
};

void freeExpr(LgsExpr* expr);
template<typename T>
void freeExprs(std::vector<T*>& exprs) {
    for (const auto expr : exprs) {
        freeExpr(static_cast<LgsExpr*>(expr));
    }
    exprs.clear();
}
