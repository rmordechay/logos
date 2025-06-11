#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsField.h"

Value* LgsExpr::getIRValue(LgsRuntime* runtime) {
    if (IRValue) return IRValue;
    IRValue = createIRValue(runtime);
    assert(IRValue);
    return IRValue;
}

void LgsExpr::setType(LgsType* type) {
    this->type = type;
}

void LgsExpr::free(LgsRuntime* runtime) { assert(0); }
bool LgsExpr::equals(LgsExpr* other) { assert(0); }
LgsExpr* LgsExpr::clone() { assert(0); }
string LgsExpr::prettyName() { assert(0); }
LgsExpr* LgsExpr::convertExpr(LgsType* toType) { assert(0); }
uint32_t LgsExpr::hashValue(LgsRuntime* runtime) { assert(0); }

// Comparisons
Value* LgsExpr::subIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::mulIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::divIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::eqIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::neIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::ltIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::gtIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::geIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::leIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::andIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::orIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::bitAndIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::bitOrIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::bitXorIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::rshiftIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }
Value* LgsExpr::lshiftIR(LgsRuntime* runtime, LgsExpr* other) { assert(0); }

// Casting
LgsFunc* LgsExpr::asFunc() { return dynamic_cast<LgsFunc*>(this); }
LgsVariable* LgsExpr::asVariable() { return dynamic_cast<LgsVariable*>(this); }
LgsFuncCall* LgsExpr::asFuncCall() { return dynamic_cast<LgsFuncCall*>(this); }
LgsPostfixExpr* LgsExpr::asPostfixExpr() { return dynamic_cast<LgsPostfixExpr*>(this); }
LgsInstance* LgsExpr::asInstance() { return dynamic_cast<LgsInstance*>(this); }
LgsSelection* LgsExpr::asSelection() { return dynamic_cast<LgsSelection*>(this); }
LgsArrayExpr* LgsExpr::asArrayExpr() { return dynamic_cast<LgsArrayExpr*>(this); }
LgsHashMap* LgsExpr::asHashMap() { return dynamic_cast<LgsHashMap*>(this); }
LgsBoolConst* LgsExpr::asBoolConst() { return dynamic_cast<LgsBoolConst*>(this); }
LgsCharConst* LgsExpr::asCharConst() { return dynamic_cast<LgsCharConst*>(this); }
LgsIterIndex* LgsExpr::asIterIndex() { return dynamic_cast<LgsIterIndex*>(this); }
LgsFloatConst* LgsExpr::asFloatConst() { return dynamic_cast<LgsFloatConst*>(this); }
LgsIntConst* LgsExpr::asIntConst() { return dynamic_cast<LgsIntConst*>(this); }
LgsStrConst* LgsExpr::asStrConst() { return dynamic_cast<LgsStrConst*>(this); }
LgsEnumField* LgsExpr::asEnumField() { return dynamic_cast<LgsEnumField*>(this); }
LgsTypeConst* LgsExpr::asTypeConst() { return dynamic_cast<LgsTypeConst*>(this); }
