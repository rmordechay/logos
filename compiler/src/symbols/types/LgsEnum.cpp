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
        func->fn = [](LgsCodeGen&, const std::vector<LgsFuncArg>& args) {
            const auto arg = args.front().expr->asVariable();
            assert(arg && arg->ref.symbolType == FIELD && arg->ref.field->expr);
            return arg->ref.field->expr->IRValue;
        };
        addMethod(func);
        return func;
    }
    if (methodName == POSITION_FUNC && subtype) {
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

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType(LgsCodeGen& cg) {
    if (subtype) {
        return cg.getStructType({cg.i32Ty(), subtype->getIRType(cg)}, getName());
    }
    return cg.i32Ty();
}

Constant* LgsEnum::getRTType(LgsCodeGen& cg) {
    return cg.getRTTypeInfo(name, IRSize(cg), rtt);
}

std::string LgsEnum::getName() {
    return name;
}

std::string LgsEnum::pname() {
    if (fieldName == "") return name;
    return fieldName;
}

bool LgsEnum::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    return name == otherName;
}

LgsType* LgsEnum::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsEnum::fmtStr() const {
    return "%s";
}

Value* LgsEnum::asIRStr(LgsCodeGen& cg, Value* v) {
    return cg.getString(name);
}

Value* LgsEnum::hashValue(LgsCodeGen& cg, Value* value) {
    if (fieldName == "") return cg.builder.CreateExtractValue(value, 0);
    return cg.i32(fieldIndex);
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
