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

void LgsExpr::initIRValue(CodeGenMetadata* metadata) {
    IRValue = createIRValue(metadata);
    assert(IRValue);
}

Value* LgsExpr::getIRValue(CodeGenMetadata* metadata) {
    if (IRValue) return IRValue;
    initIRValue(metadata);
    return IRValue;
}

void LgsExpr::setType(LgsType* type) {
    this->type = type;
}

LgsExpr* LgsExpr::clone() { assert(false); }
string LgsExpr::prettyName() { assert(false); }
uint32_t LgsExpr::hashValue(CodeGenMetadata* metadata) { assert(false); }
Value* LgsExpr::getLength(CodeGenMetadata* metadata) { assert(false); }
LgsExpr* LgsExpr::convertExpr(LgsType* other) { assert(false); }
Value* LgsExpr::subIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::mulIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::divIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::eqIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::neIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::ltIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::gtIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::geIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::leIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::andIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::orIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::bitAndIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::bitOrIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::bitXorIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::rshiftIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
Value* LgsExpr::lshiftIR(CodeGenMetadata* metadata, LgsExpr* other) { assert(false); }
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
