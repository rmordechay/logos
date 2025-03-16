#include "constants/LgsIntConst.h"

#include "constants/LgsFloatConst.h"
#include "constants/LgsStrConst.h"

Value* LgsIntConst::createIRValue(CodeGenMetadata* metadata) {
    return metadata->builder.getInt32(value);
}

LgsExpr* LgsIntConst::add(LgsExpr* other) {
    if (const auto intConst = dynamic_cast<LgsIntConst*>(other)) {
        return new LgsIntConst(value + intConst->value);
    }
    if (const auto floatConst = dynamic_cast<const LgsFloatConst*>(other)) {
        return new LgsFloatConst(value + floatConst->value);
    }
    if (const auto strConst = dynamic_cast<LgsStrConst*>(other)) {
        return strConst->add(this);
    }
    return nullptr;
}

void LgsIntConst::print() {
    std::cout << typeid(this).name() << value << '\n';
}
