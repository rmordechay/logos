#include "types/LgsEnumField.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsEnum.h"
#include "types/primitives/LgsSize.h"

#define VALUE_FUNC "value"
#define POSITION_FUNC "index"

LgsFunc* LgsEnumField::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == VALUE_FUNC && parentType->subtype) {
        if (methods.contains(VALUE_FUNC)) return methods[VALUE_FUNC];
        const auto func = new LgsFunc(VALUE_FUNC, parentType->subtype, {this}, flags);
        func->fn = [](LgsCodeGen&, const std::vector<LgsFuncArg>& args) {
            const auto arg = args.front().expr->asVariable();
            assert(arg && arg->ref.symbolType == FIELD && arg->ref.field->expr);
            return arg->ref.field->expr->IRValue;
        };
        addMethod(func);
        return func;
    }
    if (methodName == POSITION_FUNC && parentType->subtype) {
        if (methods.contains(POSITION_FUNC)) return methods[POSITION_FUNC];
        const auto func = new LgsFunc(POSITION_FUNC, &LGS_SIZE, {this}, flags);
        func->fn = [](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            const auto arg = args.front().expr->asVariable();
            assert(arg && arg->ref.symbolType == FIELD && arg->ref.field->expr);
            return cg.usize(arg->ref.field->position);
        };
        addMethod(func);
        return func;
    }
    return LgsType::getMethod(methodName);
}

std::string LgsEnumField::getName() {
    return name;
}

size_t LgsEnumField::sizeBytes() {
    assert(0);
}

LgsExpr* LgsEnumField::getZeroValue() {
    assert(0);
}

bool LgsEnumField::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    return parentType->getName() == otherName;
}

LgsType* LgsEnumField::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

Type* LgsEnumField::getIRType(LgsCodeGen& cg) {
    assert(0);
}

Constant* LgsEnumField::getRTType(LgsCodeGen& cg) {
    return cg.getRTTypeInfo(parentType->getName(), IRSize(cg), rtt);
}

std::string LgsEnumField::fmtStr() const {
    return "%s";
}

Value* LgsEnumField::asIRStr(LgsCodeGen& cg, Value* v) {
    return cg.getString(name);
}

Value* LgsEnumField::hashValue(LgsCodeGen& cg, Value* value) {
    for (const auto field : parentType->fields) {
        if (field->name == name) {
            return cg.usize(field->position);
        }
    }
    return nullptr;
}

DIType* LgsEnumField::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsEnumField::~LgsEnumField() {
    for (auto [methodName, method] : methods) {
        if (methodName == VALUE_FUNC || methodName == POSITION_FUNC) {
            method->funcType->rt = nullptr;
            method->funcType->params[0].type = nullptr;
        }
    }
}
