#include "constants/LgsStrConst.h"

Value* LgsStrConst::createIRValue(CodeGenMetadata* metadata) {
    const auto str = ConstantDataArray::getString(context, value);
    metadata->builder.CreateGlobalStringPtr("str");
    return new GlobalVariable(*metadata->currentModule, str->getType(), true, GlobalValue::PrivateLinkage, str);
}

void LgsStrConst::cleanStr(const std::string& value) {
    this->value.erase(0, 1);
    this->value.pop_back();
}

size_t LgsStrConst::size() {
    return value.size();
}

Constant* concatStr(const LgsStrConst* left, const LgsStrConst* right) {
    return ConstantDataArray::getString(context, left->value + right->value, true);
}

void LgsStrConst::initStr(const std::string& value) {
    cleanStr(value);
    for (const char ch : value) {
        chars.emplace_back(LgsCharConst(ch));
    }
}
