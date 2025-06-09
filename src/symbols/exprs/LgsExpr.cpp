#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsVarDec.h"

Value* LgsExpr::getIRValue(LgsRuntime* runtime) {
    if (IRValue) return IRValue;
    IRValue = createIRValue(runtime);
    assert(IRValue);
    return IRValue;
}

void LgsExpr::setType(LgsType* type) {
    this->type = type;
}

void LgsExpr::free(LgsRuntime* runtime) { assert(false); }
bool LgsExpr::equals(LgsExpr* other) { assert(false); }
LgsExpr* LgsExpr::clone() { assert(false); }
string LgsExpr::prettyName() { assert(false); }
LgsExpr* LgsExpr::convertExpr(LgsType* toType) { assert(false); }
uint32_t LgsExpr::hashValue(LgsRuntime* runtime) { assert(false); }

// Comparisons
Value* LgsExpr::subIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::mulIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::divIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::eqIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::neIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::ltIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::gtIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::geIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::leIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::andIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::orIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::bitAndIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::bitOrIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::bitXorIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::rshiftIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }
Value* LgsExpr::lshiftIR(LgsRuntime* runtime, LgsExpr* other) { assert(false); }

// Casting
LgsFunc* LgsExpr::asFunc() { return dynamic_cast<LgsFunc*>(this); }
LgsVariable* LgsExpr::asVariable() { return dynamic_cast<LgsVariable*>(this); }
LgsFuncCall* LgsExpr::asFuncCall() { return dynamic_cast<LgsFuncCall*>(this); }
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
