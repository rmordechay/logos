
#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"

size_t LgsStr::getSizeBytes() {
    return sizeof(void*);
}

string LgsStr::getIRName() {
    return name;
}

Type* LgsStr::getIRType() {
    return PointerType::getUnqual(context);
}

string LgsStr::prettyName() const {
    return name;
}

LgsExpr* LgsStr::getZeroValue() {
    if (isNullable) return new LgsNull();
    return new LgsStrConst("");
}

LgsType* LgsStr::inferBinaryType(LgsType* other) {
    return this;
}

string LgsStr::getStrFormatPart() const {
    return "%s";
}

Value* LgsStr::getLength(LgsRuntime* runtime, LgsExpr* expr) {
    return len.call(runtime, {expr});
}

Value* LgsStr::getLoopLength(LgsRuntime* runtime, LgsExpr* expr) {
    return getLength(runtime, expr);
}

Value* LgsStr::callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isEmpty.call(runtime, {expr});
}

Value* LgsStr::callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isNotEmpty.call(runtime, {expr});
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    if (other->getIRName() == "Any") return true;
    return name == other->getIRName();
}

/**
 * FNV-1a 32-bit hash
 */
uint32_t LgsStr::hashString(const string& str) {
    uint32_t hash = 2166136261u;
    for (const auto c : str) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 16777619u;
    }
    return hash;
}

Value* LgsStrFormatFunc::call(LgsRuntime* runtime, const vector<LgsExpr*>& args) {
    const bool isConst = args[0]->type->isConst;
    if (!isConst) assert(false);
    constexpr auto bufferSize = 1024;
    const auto formatString = getFormatString(args);
    const auto baseIRStr = getIRStr(runtime, formatString);
    const auto bufferType = ArrayType::get(runtime->builder.getInt8Ty(), bufferSize);
    const auto buffer = runtime->builder.CreateAlloca(bufferType);
    const auto gep = runtime->builder.CreateGEP(bufferType, buffer, {runtime->builder.getInt32(0), runtime->builder.getInt32(0)});
    vector<Value*> IRArgs = {gep, runtime->builder.getInt64(bufferSize), baseIRStr};
    for (int i = 1; i < args.size(); ++i) {
        IRArgs.emplace_back(args[i]->getIRValue(runtime));
    }
    const auto printfFunc = getSnprintf(runtime);
    runtime->builder.CreateCall(printfFunc, IRArgs);
    return gep;
}

