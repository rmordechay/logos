#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"

Value* LgsStrConst::createIRValue(CodeGenMetadata* metadata) {
    return createGlobalStr(metadata->currentModule, value);
}

size_t LgsStrConst::size() {
    return value.size();
}

Value* LgsStrConst::add(CodeGenMetadata* metadata, LgsExpr* other) {
    if (const auto otherStrConst = dynamic_cast<const LgsStrConst*>(other)) {
        return createGlobalStr(metadata->currentModule, this->value + otherStrConst->value);
    }
    if (const auto otherStrConst = dynamic_cast<const LgsIntConst*>(other)) {
        return createGlobalStr(metadata->currentModule, this->value + to_string(otherStrConst->value));
    }
    if (const auto otherStrConst = dynamic_cast<const LgsFloatConst*>(other)) {
        return createGlobalStr(metadata->currentModule, this->value + to_string(otherStrConst->value));
    }
    return nullptr;
}

Value* LgsStrConst::createGlobalStr(Module* module, const std::string& value) const {
    const auto strConstant = ConstantDataArray::getString(context, value, true);
    return createIRGlobal(module, strConstant);
}

LgsExpr* LgsStrConst::add(LgsExpr* other) {
    string otherValue;
    if (const auto intConst = dynamic_cast<LgsIntConst*>(other)) {
        otherValue = to_string(intConst->value);
    } else if (const auto floatConst = dynamic_cast<const LgsFloatConst*>(other)) {
        otherValue = to_string(floatConst->value);
    } else if (const auto strConst = dynamic_cast<const LgsStrConst*>(other)) {
        otherValue = this->value + strConst->value;
    }
    return new LgsStrConst(value + otherValue);
}

void LgsStrConst::cleanStr() {
    this->value.erase(0, 1);
    this->value.pop_back();
}
