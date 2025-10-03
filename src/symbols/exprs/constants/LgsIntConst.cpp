#include "exprs/constants/LgsIntConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsLong.h"

Value* LgsIntConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsExpr* LgsIntConst::castTo(LgsType* toType, bool explicitCast) {
    if (toType->getName() == LgsAny::name) return this;
    if (type->getName() == toType->getName()) return this;
    if (toType->asLong()) {
        return new LgsIntConst(&LGS_LONG, value);
    }
    if (toType->asFloat()) {
        return new LgsFloatConst(&LGS_FLOAT, value);
    }
    if (toType->asDouble()) {
        return new LgsFloatConst(&LGS_DOUBLE, value);
    }
    if (explicitCast) {
        if (toType->asStr()) {
            return new LgsStrConst(std::to_string(value));
        }
    }
    assert(0);
}

Value* LgsIntConst::eqIR(LgsLLVMGen& cg, Value* other) {
    return cg.builder.CreateICmpEQ(IRValue, other);
}

Value* LgsIntConst::neIR(LgsLLVMGen& cg, Value* other) {
    return cg.builder.CreateICmpNE(IRValue, other);
}

Value* LgsIntConst::ltIR(LgsLLVMGen& cg, Value* other) {
    return cg.builder.CreateICmpSLT(IRValue, other);
}

Value* LgsIntConst::gtIR(LgsLLVMGen& cg, Value* other) {
    return cg.builder.CreateICmpSGT(IRValue, other);
}

Value* LgsIntConst::geIR(LgsLLVMGen& cg, Value* other) {
    return cg.builder.CreateICmpSGE(IRValue, other);
}

Value* LgsIntConst::leIR(LgsLLVMGen& cg, Value* other) {
    return cg.builder.CreateICmpSLE(IRValue, other);
}

Value* LgsIntConst::andIR(LgsLLVMGen& cg, Value* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("and_right", func);
    const auto endBlock = cg.createBlock("and_end", func);
    cg.builder.CreateCondBr(other, rightBlock, endBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.false_(), currentBlock);
    phi->addIncoming(other, rightBlock);
    return phi;
}

Value* LgsIntConst::orIR(LgsLLVMGen& cg, Value* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("or_right", func);
    const auto endBlock = cg.createBlock("or_end", func);
    cg.builder.CreateCondBr(IRValue, endBlock, rightBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.true_(), currentBlock);
    phi->addIncoming(other, rightBlock);
    return phi;
}


std::string LgsIntConst::getName() {
    return std::to_string(value);
}

LgsExpr* LgsIntConst::clone() {
    return new LgsIntConst(type->clone(), value);
}

json::value LgsIntConst::asJsonStr() {
    json::object jsonObj;
    jsonObj["exprType"] = "intConst";
    jsonObj["name"] = getName();
    jsonObj["type"] = type->asJsonStr();
    return jsonObj;
}
