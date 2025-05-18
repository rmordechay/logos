#include "funcs/LgsFunc.h"
#include "LgsDefinitions.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

void LgsFunc::generateIRCode(CodeGenMetadata* metadata) {
    metadata->lgsStack.enterScope(this);
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    if (funcType.rt->isVoid) {
        metadata->builder.CreateRetVoid();
    }
    metadata->lgsStack.exitScope();
}

Value* LgsFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    vector<Value*> argValues;
    const auto isObjReturn = setFuncCallIRArgs(metadata, argValues, args);
    const auto IRFuncType = getIRFuncType(metadata);
    const auto IRFunc = IRValue ? IRValue : getIRFunc(metadata);
    const auto funcCall = metadata->builder.CreateCall(IRFuncType, IRFunc, argValues);
    if (isObjReturn) return argValues[0];
    return funcCall;
}

Value* LgsFunc::callIR(CodeGenMetadata* metadata, const vector<Value*>& args) {
    const auto IRFuncType = getIRFuncType(metadata);
    const auto IRFunc = getIRFunc(metadata);
    return metadata->builder.CreateCall(IRFuncType, IRFunc, args);
}

Function* LgsFunc::getIRFunc(const CodeGenMetadata* metadata) {
    const auto funcIRType = getIRFuncType(metadata);
    auto func = metadata->module->getOrInsertFunction(funcType.getIRName(), funcIRType);
    const auto IRFunc = dyn_cast<Function>(func.getCallee());
    auto args = IRFunc->arg_begin();
    if (const auto obj = funcType.rt->asObject()) {
        AttrBuilder builder(context);
        builder.addStructRetAttr(obj->getIRType());
        args->addAttrs(builder);
        args->setName("rt");
        args++;
    }

    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto param = funcType.params[i];
        param->setIRValue(args);
        if (param->expr) param->expr->setIRValue(args);
        auto paramName = param->name;
        if (funcType.isMethod) args->setName(paramName);
        args++;
    }
    return IRFunc;
}

FunctionType* LgsFunc::getIRFuncType(const CodeGenMetadata* metadata) {
    if (IRFuncType) return IRFuncType;
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto paramType = funcType.params[i]->type;
        auto paramIRType = paramType->getIRType();
        // TODO make generic
        if (paramType->asInterface()) {
            paramIRType = PointerType::get(paramIRType, 0);
        }
        IRParamsTypes.emplace_back(paramIRType);
    }

    Type* rt = nullptr;
    if (const auto obj = funcType.rt->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), PointerType::get(obj->getIRType(), 0));
        rt = voidTy;
    } else {
        rt = funcType.rt->getIRType();
    }

    IRFuncType = FunctionType::get(rt, IRParamsTypes, funcType.isVariadic);
    return IRFuncType;
}

bool LgsFunc::setFuncCallIRArgs(CodeGenMetadata* metadata, vector<Value*>& argValues, const vector<LgsExpr*>& args) const {
    bool isObjReturn = false;
    if (const auto obj = funcType.rt->asObject()) {
        const auto objRtPtr = metadata->builder.CreateAlloca(obj->getIRType(), nullptr);
        argValues.push_back(objRtPtr);
        isObjReturn = true;
    }
    for (int i = funcType.isStatic; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argIRValue = arg->getIRValue(metadata);
        const auto artIRType = arg->type->getIRType();
        if (shouldLoadIRArg(argIRValue)) {
            const auto value = metadata->builder.CreateLoad(artIRType, argIRValue);
            argValues.emplace_back(value);
        } else {
            argValues.emplace_back(argIRValue);
        }
    }
    return isObjReturn;
}

string LgsFunc::format(string& tabs) {
    stringstream str;
    str << funcType.name << "(";
    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto param = funcType.params[i];
        str << param->format(tabs);
        if (i != funcType.params.size() - 1) {
            str << ", ";
        }
    }
    str << ")";
    if (funcType.name != LOGOS_MAIN_FUNC) {
        str << funcType.rt->getIRName();
    }
    str << stmtBlock->format(tabs);
    return str.str();
}

bool LgsFunc::shouldLoadIRArg(Value* value) const {
    assert(value);
    if (isa<GlobalVariable>(value) || isa<LoadInst>(value)) return false;
    if (isa<AllocaInst>(value)) return true;
    if (const auto gep = dyn_cast<GetElementPtrInst>(value)) {
        const auto isArrayTy = gep->getSourceElementType()->isArrayTy();
        const auto isByteTy = gep->getResultElementType()->isIntegerTy(8);
        return isArrayTy && !isByteTy;
    }
    if (isa<ConstantExpr>(value)) {
        const auto constExpr = cast<ConstantExpr>(value);
        return constExpr->getOpcode() == Instruction::GetElementPtr;
    }
    return false;
}

json LgsFunc::asJSON() {
    json tree;
    tree["name"] = funcType.name;
    tree["type"] = funcType.rt->getIRName();
    tree["params"] = {};
    for (auto& param : funcType.params) {
        tree["params"].emplace_back(param->asJSON());
    }
    tree["stmts"] = stmtBlock->asJSON();
    return tree;
}

LgsFunc::~LgsFunc() {
    // TODO free params
    // for (int i = funcType.isMethod; i < funcType.params.size(); ++i) {
    //     delete funcType.params[i];
    // }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
