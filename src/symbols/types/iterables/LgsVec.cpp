#include "types/iterables/LgsVec.h"
#include "exprs/LgsVectorExpr.h"

Type* LgsVec::getIRType(LgsLLVMGen& cg) {
    IRType = FixedVectorType::get(baseType->getIRType(cg), dim);
    return IRType;
}

LgsField* LgsVec::getField(const std::string& fieldName) {
    for (auto* f : fields) if (f->name == fieldName) return f;
    const size_t newFieldDim = fieldName.size();
    const auto scalarOrVector = newFieldDim == 1 ? baseType : new LgsVec(newFieldDim);
    const auto field = new LgsField(fieldName, scalarOrVector);
    addField(field);
    return field;
}

std::string LgsVec::getName() {
    return "vec" + std::to_string(dim);
}

std::string LgsVec::pname() {
    return getName();
}

json::value LgsVec::asJSON() {
    assert(0);
}

size_t LgsVec::getSizeBytes() {
    return baseType->getSizeBytes() * 2;
}

LgsExpr* LgsVec::getZeroValue() {
    return new LgsVectorExpr(this);
}

LgsType* LgsVec::getIndexType() {
    return &LGS_INT;
}

uint16_t LgsVec::getUnpackCount() const {
    return 1;
}

Value* LgsVec::IRLength(LgsLLVMGen& cg, Value* iterable) {
    return cg.usize(2);
}

Value* LgsVec::IRIsEmpty(LgsLLVMGen* cg, LgsExpr* iterable) {
    return cg->builder.getFalse();
}

Value* LgsVec::IRIsNotEmpty(LgsLLVMGen* cg, LgsExpr* iterable) {
    return cg->builder.getTrue();
}

bool LgsVec::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherVec = other->asVec();
    if (!otherVec) return false;
    return dim == otherVec->dim && baseType->canCastTo(otherVec->baseType);
}

LgsType* LgsVec::applyOp(LgsType* other, const LgsOperator op) {
    const auto IRName = other->getName();
    switch (op) {
    case ADD:
    case SUB:
        if (getName() == IRName) return this;
        break;
    case MUL:
    case DIV:
        if (getName() == IRName || other->isNumber) return this;
        break;
    default:
        break;
    }
    return nullptr;
}

Value* LgsVec::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto loadRight = other->loadIR(cg);
    if (other->type->isInt) {
        return cg.builder.CreateAdd(self->loadIR(cg), loadRight);
    }
    return cg.builder.CreateFAdd(self->loadIR(cg), loadRight);
}

Value* LgsVec::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto loadRight = other->loadIR(cg);
    if (other->type->isInt) {
        return cg.builder.CreateSub(self->loadIR(cg), loadRight);
    }
    return cg.builder.CreateFSub(self->loadIR(cg), loadRight);
}

Value* LgsVec::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto loadOther = other->loadIR(cg);
    const auto loadSelf = self->loadIR(cg);
    if (other->type->isInt) {
        const auto vecTy = cast<VectorType>(self->type->getIRType(cg));
        loadOther = cg.builder.CreateSIToFP(loadOther, vecTy->getElementType());
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFMul(loadSelf, loadOther);
    }
    if (other->type->asFloat()) {
        const auto vecTy = cast<VectorType>(self->type->getIRType(cg));
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFMul(loadSelf, loadOther);
    }
    return cg.builder.CreateFMul(loadSelf, loadOther);
}

Value* LgsVec::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    assert(0);
}

int8_t LgsVec::getSwizzleSet(const char c) {
    if (strchr("xyzw", c)) return 0;
    if (strchr("rgba", c)) return 1;
    if (strchr("stpq", c)) return 2;
    return -1;
}

int8_t LgsVec::getComponentIndex(const char c) {
    switch (c) {
    case 'x': case 'r': case 's': return 0;
    case 'y': case 'g': case 't': return 1;
    case 'z': case 'b': case 'p': return 2;
    case 'w': case 'a': case 'q': return 3;
    default: return -1;
    }
}

std::string LgsVec::strFormatPart() const {
    std::stringstream str;
    str << '<';
    for (int i = 0; i < dim; i++) {
        str << baseType->strFormatPart();
        if (i < dim - 1) str << ", ";
    }
    str << '>';
    return str.str();
}

void LgsVec::setRTT() {
    if (dim == 2) rtt = RTT_VEC2;
    else if (dim == 3) rtt = RTT_VEC3;
    else if (dim == 4) rtt = RTT_VEC4;
    else rtt = RTT_UNKNOWN;
}
