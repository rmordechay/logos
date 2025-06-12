#include "data/LgsDefinitions.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"
#include "utils/LgsUtils.h"

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
    if (hasFlag(NULLABLE)) return new LgsNull();
    return new LgsStrConst("");
}

LgsType* LgsStr::inferBinaryType(LgsType* other) {
    return this;
}

string LgsStr::getStrFormatPart() const {
    return "%s";
}

Value* LgsStr::getLength(LgsRuntime* runtime, LgsExpr* expr) {
    return lenFunc.call(runtime, {expr});
}

Value* LgsStr::getLoopLength(LgsRuntime* runtime, LgsExpr* expr) {
    return getLength(runtime, expr);
}

Value* LgsStr::callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isEmptyFunc.call(runtime, {expr});
}

Value* LgsStr::callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isNotEmptyFunc.call(runtime, {expr});
}

void LgsStr::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = baseType;
}

bool LgsStr::equals(LgsType* other) {
    assert(other);
    if (other->getIRName() == LgsAny::name) return true;
    return name == other->getIRName();
}

/**
 * FNV-1a 32-bit hash
 */
size_t LgsStr::hashString(const string& str) {
    size_t hash = 2166136261u;
    for (const auto c : str) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 16777619u;
    }
    return hash;
}

Value* LgsStrFormatFunc::call(LgsRuntime* runtime, const vector<LgsExpr*>& args) {
    const bool isConst = args[0]->type->hasFlag(CONST);
    if (!isConst) assert(0);
    constexpr auto bufferSize = 1024;
    auto exprStr = args[0]->getExprStr();
    auto searchPos = 0;
    for (size_t i = 1; i < args.size(); ++i) {
        const auto pos = exprStr.find(LOGOS_STR_FORMAT_PART, searchPos);
        const auto part = args[i]->type->getStrFormatPart();
        if (pos != string::npos) {
            exprStr.replace(pos, 2, part);
            searchPos = pos + part.length();
        }
    }
    const auto baseIRStr = getIRStr(runtime, exprStr);
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
