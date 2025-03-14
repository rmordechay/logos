#include "constants/LgsStrConst.h"

Value* LgsStrConst::createIRValue(CodeGenMetadata* metadata) {
    return ConstantDataArray::getString(context, value, true);
}

Value* LgsStrConst::operator+(LgsExpr* other) {
    return LgsConstant::operator+(other);
}

void LgsStrConst::cleanStr(const std::string& value) {
    this->value.erase(0, 1);
    this->value.erase(value.size() - 1);
}

size_t LgsStrConst::size() {
    return value.size();
}

Constant* concatStr(const LgsStrConst* left, const LgsStrConst* right) {
    return ConstantDataArray::getString(context, left->value + right->value, true);
}
