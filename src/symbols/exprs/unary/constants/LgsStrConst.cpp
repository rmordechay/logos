#include "constants/LgsStrConst.h"

#include "constants/LgsFloatConst.h"
#include "constants/LgsIntConst.h"
#include "types/LgsFloat.h"

Value* LgsStrConst::createIRValue(CodeGenMetadata* metadata) {
    return createGlobalStr(metadata->currentModule, value);
}

void LgsStrConst::cleanStr() {
    this->value.erase(0, 1);
    this->value.pop_back();
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
    return new GlobalVariable(*module, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
}
