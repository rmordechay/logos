#include "types/LgsEnumField.h"

#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <unordered_map>
#include <vector>

#include "LgsRTTIndices.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/primitives/LgsSize.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "types/LgsEnum.h"
#include "types/LgsFuncType.h"

#define VALUE_FUNC "value"
#define INDEX_FUNC "index"

LgsFunc* LgsEnumField::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == VALUE_FUNC && exprType) {
        if (methods.contains(methodName)) return methods[methodName];
        const auto func = new LgsFunc(methodName, exprType, {this}, flags);
        func->fn = [this](LgsCodeGen& cg, const std::vector<LgsVarDec>& args) -> Value* {
            const auto arg = args.front().expr;
            if (arg->IRValue->getType()->isPointerTy()) {
                const auto fieldTy = arg->type->getIRType(cg);
                const auto exprTy = exprType->getIRType(cg);
                return cg.loadField(fieldTy, arg->IRValue, LgsEnumFieldIndices::value, exprTy);
            }
            return cg.builder.CreateExtractValue(arg->IRValue, LgsEnumFieldIndices::value);
        };
        addMethod(func);
        return func;
    }
    if (methodName == INDEX_FUNC) {
        if (methods.contains(methodName)) return methods[methodName];
        const auto func = new LgsFunc(methodName, &LGS_SIZE, {this}, flags);
        func->fn = [this](LgsCodeGen& cg, const std::vector<LgsVarDec>& args) -> Value* {
            if (!exprType) return cg.usize(index);
            const auto arg = args.front().expr;
            if (arg->IRValue->getType()->isPointerTy()) {
                const auto fieldTy = arg->type->getIRType(cg);
                const auto exprTy = exprType->getIRType(cg);
                return cg.loadField(fieldTy, arg->IRValue, LgsEnumFieldIndices::index, exprTy);
            }
            return cg.builder.CreateExtractValue(arg->IRValue, LgsEnumFieldIndices::index);
        };
        addMethod(func);
        return func;
    }
    return LgsType::getMethod(methodName);
}

std::string LgsEnumField::getName() {
    return fieldName;
}

Type* LgsEnumField::getIRType(LgsCodeGen& cg) {
    if (!exprType) return cg.sizeTy();
    return cg.getStructType({cg.sizeTy(), exprType->getStorageType(cg)}, name);
}

bool LgsEnumField::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    const auto otherEnumField = other->asEnumField();
    if (otherEnumField && fieldName == otherEnumField->fieldName) return true;
    const auto otherEnum = other->asEnum();
    return otherEnum && name == otherEnum->name;
}

Value* LgsEnumField::hashValue(LgsCodeGen& cg, Value* value) {
    return cg.usize(index);
}
