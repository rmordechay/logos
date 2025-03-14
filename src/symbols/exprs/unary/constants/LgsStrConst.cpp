#include "constants/LgsStrConst.h"

Value* LgsStrConst::createIRValue(CodeGenMetadata* metadata) {
    return ConstantDataArray::getString(context, value, true);
}

void LgsStrConst::iterate(CodeGenMetadata* metadata) {
    auto& builder = metadata->builder;
    // const auto i8Type = builder.getInt1Ty();
    // const auto strPtr = builder.CreateAlloca(i8Type, nullptr);
    // const auto charPtr = builder.CreateGEP(i8Type, strPtr, i);
    // const auto currentChar = builder.CreateLoad(i8Type, charPtr);
    // const auto isNullTerminate = builder.CreateICmpEQ(currentChar, builder.getInt8(0));
    // builder.CreateCondBr(isNullTerminate, loopExit, loopBody);
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

void LgsStrConst::initStr(const std::string& value) {
    cleanStr(value);
    for (const char ch : value) {
        chars.emplace_back(LgsCharConst(ch));
    }
}
