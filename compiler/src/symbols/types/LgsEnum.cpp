#include "types/LgsEnum.h"

#include "LgsUtils.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsSize.h"

#define VALUE_FUNC "value"
#define POSITION_FUNC "index"

LgsFunc* LgsEnum::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == VALUE_FUNC && subtype) {
        if (methods.contains(VALUE_FUNC)) return methods[VALUE_FUNC];
        const auto func = new LgsFunc(VALUE_FUNC, subtype, {this}, flags);
        func->fn = [](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            const auto arg = args.front().expr->asVariable();
            if (arg && arg->ref.symbolType == FIELD && arg->ref.field->expr) return arg->ref.field->expr->IRValue;
            return cg.builder.CreateExtractValue(arg->IRValue, 1);
        };
        addMethod(func);
        return func;
    }
    if (methodName == POSITION_FUNC) {
        if (methods.contains(POSITION_FUNC)) return methods[POSITION_FUNC];
        const auto func = new LgsFunc(POSITION_FUNC, &LGS_SIZE, {this}, flags);
        func->fn = [](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) -> Value* {
            const auto arg = args.front().expr->asVariable();
            if (arg && arg->ref.symbolType == FIELD) return cg.usize(arg->ref.field->position);
            if (arg->IRValue->getType()->isIntegerTy()) return arg->IRValue;
            return cg.builder.CreateExtractValue(arg->IRValue, 0);
        };
        addMethod(func);
        return func;
    }
    return LgsType::getMethod(methodName);
}

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType(LgsCodeGen& cg) {
    if (subtype) {
        return cg.getStructType({cg.sizeTy(), subtype->getIRType(cg)}, getName());
    }
    return cg.sizeTy();
}

Constant* LgsEnum::getRTType(LgsCodeGen& cg) {
    return cg.getRTTypeInfo(getName(), IRSize(cg), rttKind);
}

std::string LgsEnum::getName() {
    return name;
}

bool LgsEnum::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (other->isAny()) return true;
    return name == otherName;
}

LgsType* LgsEnum::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsEnum::fmtStr() const {
    return "%s";
}

Value* LgsEnum::asIRStr(LgsCodeGen& cg, Value* v) {
    return fieldName == "" ? cg.getString(name) : cg.getString(fieldName);
}

Value* LgsEnum::hashValue(LgsCodeGen& cg, Value* value) {
    if (fieldName != "") return cg.usize(fieldIndex);
    if (!subtype) return value;
    return cg.builder.CreateExtractValue(value, 0);
}

size_t LgsEnum::sizeBytes() {
    return sizeof(void*);
}

DIType* LgsEnum::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsEnum::~LgsEnum() {
    for (auto [methodName, method] : methods) {
        if (methodName == VALUE_FUNC || methodName == POSITION_FUNC) {
            method->funcType->rt = nullptr;
            method->funcType->params[0].type = nullptr;
        }
    }
    for (const auto field : fields) {
        delete field->type;
        field->type = nullptr;
    }
}
