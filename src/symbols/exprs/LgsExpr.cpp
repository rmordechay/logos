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

Value* LgsExpr::getIRValue(CodegenMetadata* metadata) {
    if (IRValue) return IRValue;
    IRValue = createIRValue(metadata);
    assert(IRValue);
    return IRValue;
}

void LgsExpr::setType(LgsType* type) {
    this->type = type;
}

void LgsExpr::free() { assert(false); }
LgsExpr* LgsExpr::clone() { assert(false); }
string LgsExpr::prettyName() { assert(false); }
LgsExpr* LgsExpr::convertExpr(LgsType* type) { assert(false); }
uint32_t LgsExpr::hashValue(CodegenMetadata* metadata) { assert(false); }
Value* LgsExpr::getLength(CodegenMetadata* metadata) { assert(false); }

// Comparisons
Value* LgsExpr::subIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::mulIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::divIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::eqIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::neIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::ltIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::gtIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::geIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::leIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::andIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::orIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::bitAndIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::bitOrIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::bitXorIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::rshiftIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::lshiftIR(CodegenMetadata* metadata, LgsExpr* other) { assert(false); }

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
