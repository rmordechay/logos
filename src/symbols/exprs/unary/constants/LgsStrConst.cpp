#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"

Value* LgsStrConst::createIRValue(CodeGenMetadata* metadata) {
    return createGlobalStr(metadata->currentModule, value);
}

size_t LgsStrConst::size() {
    return value.size();
}

Value* LgsStrConst::createGlobalStr(Module* module, const std::string& value) const {
    const auto strConstant = ConstantDataArray::getString(context, value, true);
    return createIRGlobal(module, strConstant);
}

LgsExpr* LgsStrConst::add(LgsExpr* other) {
    string otherValue;
    if (const auto intConst = other->asIntConst()) {
        otherValue = to_string(intConst->value);
    } else if (const auto floatConst = other->asFloatConst()) {
        otherValue = to_string(floatConst->value);
    } else if (const auto strConst = other->asStrConst()) {
        otherValue = this->value + strConst->value;
    }
    return new LgsStrConst(value + otherValue);
}

Value* LgsStrConst::addIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (const auto otherStrConst = other->asIntConst()) {
        return createGlobalStr(metadata->currentModule, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asFloatConst()) {
        return createGlobalStr(metadata->currentModule, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = other->asStrConst()) {
        return createGlobalStr(metadata->currentModule, this->value + otherStrConst->value);
    }
    return nullptr;
}

Value* LgsStrConst::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (const auto otherStrConst = other->asStrConst()) {
        const auto func = metadata->currentModule->getOrInsertFunction("Str_compare_Str_Str", compareStrIRFuncType);
        return metadata->builder.CreateCall(func, {getIRValue(metadata), otherStrConst->getIRValue(metadata)});
    }
    return nullptr;
}

json LgsStrConst::asJson() {
    json tree;
    tree["exprType"] = "StrConst";
    tree["name"] = type->getName();
    tree["value"] = value;
    return tree;
}
