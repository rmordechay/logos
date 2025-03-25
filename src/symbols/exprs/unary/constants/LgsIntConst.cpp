#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsStrConst.h"

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

json LgsIntConst::asJson() {
    json tree;
    tree["exprType"] = "IntConst";
    tree["type"] = type->getName();
    tree["value"] = value;
    return tree;
}
