#include "types/LgsFuncType.h"

#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

Type* LgsFuncType::getIRType() {
    return ptrTy;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(false);
}

const string LgsFuncType::getName() const {
    return name;
}

bool LgsFuncType::equals(LgsType* other) const {
    const auto otherFuncType = dynamic_cast<LgsFuncType*>(other);
    if (!otherFuncType) return false;
    if (name != otherFuncType->name) return false;
    const auto otherParams = otherFuncType->params;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    for (size_t i = 0; i < params.size(); ++i) {
        auto thisTypeName = params[i].type->getName();
        auto otherTypeName = otherFuncType->params[i].type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

bool LgsFuncType::equals(const LgsFuncCall* other) const {
    if (name != other->name) return false;
    const auto args = other->args;
    if (params.size() == 0 && args.size() == 0) return true;
    if (params.size() < args.size()) return false;
    for (size_t i = 0; i < params.size(); ++i) {
        assert(args[i]);
        auto thisTypeName = params[i].type->getName();
        auto otherTypeName = args[i]->type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

LgsType* LgsFuncType::inferBinaryType(LgsType* other) {
    assert(false);
}

string LgsFuncType::getAsStr(const bool withType) const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = 0; i < params.size(); ++i) {
        strStream << params[i].type->getName();
        if (i != params.size() - 1) strStream << ", ";
    }
    if (withType) {
        strStream << "): " << type->getName();
    } else {
        strStream << ")";
    }
    return strStream.str();
}

void LgsFuncType::setStructRet(Function::arg_iterator& args, LgsObject* const obj) const {
    AttrBuilder builder(context);
    builder.addStructRetAttr(obj->getIRType());
    args->addAttrs(builder);
    args->setName("rt");
    args++;
}

string LgsFuncType::getIRName() {
    if (IRName != "") return IRName;
    vector<string> argTypeNames;
    for (const auto& param : params) {
        argTypeNames.emplace_back(param.type->getName());
    }
    IRName = getComposedName(name, "", argTypeNames);
    return IRName;
}

Function* LgsFuncType::getIRFunc(const CodeGenMetadata* metadata) {
    auto func = metadata->module->getOrInsertFunction(getIRName(), getIRFuncType(metadata));
    const auto IRFunc = dyn_cast<Function>(func.getCallee());
    auto args = IRFunc->arg_begin();
    if (const auto obj = type->asObject()) {
        setStructRet(args, obj);
    }
    setIRFuncParams(args);
    return IRFunc;
}

FunctionType* LgsFuncType::getIRFuncType(const CodeGenMetadata* metadata) {
    if (IRFuncType) return IRFuncType;
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < params.size(); ++i) {
        auto paramIRType = params[i].type->getIRType();
        // TODO make generic
        if (dynamic_cast<LgsInterface*>(params[i].type)) {
            paramIRType = paramIRType->getPointerTo();
        }
        IRParamsTypes.emplace_back(paramIRType);
    }
    if (const auto obj = type->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), obj->getIRType()->getPointerTo());
        IRFuncType = FunctionType::get(voidTy, IRParamsTypes, false);
    } else {
        IRFuncType = FunctionType::get(type->getIRType(), IRParamsTypes, false);
    }
    return IRFuncType;
}

void LgsFuncType::setIRFuncParams(Argument* IRParams) {
    for (auto& param : params) {
        param.setIRValue(IRParams);
        if (param.expr) param.expr->setIRValue(IRParams);
        IRParams->setName(param.getIRName());
        IRParams++;
    }
}

