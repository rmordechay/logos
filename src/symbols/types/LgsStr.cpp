#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"

LgsStr::LgsStr(): LgsIterable(&LGS_CHAR) {
    lenFunc->fn = [](LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) {
        return codeGen.callStrLen(args[0]->IRValue);
    };
    isEmptyFunc->fn = [](LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) {
        const auto strLen = codeGen.callStrLen(args[0]->IRValue);
        return codeGen.builder.CreateICmpEQ(strLen, codeGen.builder.getInt64(0));
    };
    isNotEmptyFunc->fn = [](LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) {
        const auto strLen = codeGen.callStrLen(args[0]->IRValue);
        return codeGen.builder.CreateICmpNE(strLen, codeGen.builder.getInt64(0));
    };
    addMethod(lenFunc);
    addMethod(isEmptyFunc);
    addMethod(isNotEmptyFunc);
    isSliceable = true;
    rtt = RTT_STR;
}

Type* LgsStr::getIRBaseType(LgsLLVM* codeGen) const {
    return ArrayType::get(baseType->getIRType(*codeGen), sizeExpr->getConstInt());
}

Type* LgsStr::getIRType(LgsLLVM& codeGen) {
    return codeGen.ptrTy();
}

size_t LgsStr::getSizeBytes() {
    return sizeof(void*);
}

uint16_t LgsStr::getUnpackCount() const {
    return 1;
}

std::string LgsStr::getName() {
    return name;
}

json::value LgsStr::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}

std::string LgsStr::pname() {
    return name;
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

std::string LgsStr::strFormatPart() const {
    return "%s";
}

LgsType* LgsStr::getIndexType() {
    return &LGS_INT;
}

Value* LgsStr::IRLength(LgsLLVM& codeGen, LgsExpr* iterable) {
    return lenFunc->call(codeGen, {iterable});
}

Value* LgsStr::IRIsEmpty(LgsLLVM* codeGen, LgsExpr* iterable) {
    return isEmptyFunc->call(*codeGen, {iterable});
}

Value* LgsStr::IRIsNotEmpty(LgsLLVM* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc->call(*codeGen, {iterable});
}

bool LgsStr::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (const auto iter = other->asIterable()) {
        return iter->baseType && iter->baseType->asChar();
    }
    return name == other->getName();
}
