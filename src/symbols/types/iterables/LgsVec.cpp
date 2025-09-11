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

Value* LgsVec::IRLength(LgsLLVMGen& cg, LgsExpr* iterable) {
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

bool LgsVec::canAssignTo(LgsType* other, const LgsAssignType op) {
    if (op == ASSIGN) return canCastTo(other);
    return other->isNumber;
}

bool LgsVec::canApplyOp(LgsType* other, const LgsOperator op) {
    const auto IRName = other->getName();
    switch (op) {
    case ADD:
    case SUB:
        return getName() == IRName;
    case MUL:
    case DIV:
        return getName() == IRName || other->isNumber;
    default:
        break;
    }
    return false;
}

Value* LgsVec::addIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    const auto loadRight = other->loadIR(cg);
    if (other->type->isInt) {
        return cg.builder.CreateAdd(value, loadRight);
    }
    return cg.builder.CreateFAdd(value, loadRight);
}

Value* LgsVec::subIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    const auto loadRight = other->loadIR(cg);
    if (other->type->isInt) {
        return cg.builder.CreateSub(value, loadRight);
    }
    return cg.builder.CreateFSub(value, loadRight);
}

Value* LgsVec::mulIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
    auto loadRight = other->loadIR(cg);
    if (other->type->isInt) {
        const auto vecTy = cast<VectorType>(value->getType());
        loadRight = cg.builder.CreateSIToFP(loadRight, vecTy->getElementType());
        loadRight = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadRight);
        return cg.builder.CreateFMul(value, loadRight);
    }
    if (other->type->asFloat()) {
        const auto vecTy = cast<VectorType>(value->getType());
        loadRight = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadRight);
        return cg.builder.CreateFMul(value, loadRight);
    }
    return cg.builder.CreateFMul(value, loadRight);
}

Value* LgsVec::divIR(LgsLLVMGen& cg, Value* value, LgsExpr* other) {
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
