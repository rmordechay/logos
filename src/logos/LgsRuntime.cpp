#include "logos/LgsRuntime.h"
#include "data/LgsErrors.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"


void LgsRuntime::initRuntime() {
    const auto voidTy = builder.getVoidTy();
    const auto stackStr = getIRStructType(context, "StackStr", {ArrayType::get(builder.getInt8Ty(), 1024), builder.getInt32Ty()});
    const auto stack = getIRStructType(context, "Stack", {builder.getInt32Ty(), ArrayType::get(stackStr, 512)});
    const auto runtimeType = getIRStructType(context, "Runtime", {stack});
    const auto zeroInit = Constant::getNullValue(runtimeType);
    runtimeStruct = new GlobalVariable(*module, runtimeType, false, GlobalValue::ExternalLinkage, zeroInit);
    const auto initStackFunc = module->getOrInsertFunction("Runtime_init", FunctionType::get(voidTy, {builder.getPtrTy()}, false));
    builder.CreateCall(initStackFunc, {runtimeStruct});
}

void LgsRuntime::pushStackTrace(const string& path) {
    const auto voidTy = builder.getVoidTy();
    const auto pushStackFunc =module->getOrInsertFunction("Runtime_push", FunctionType::get(voidTy, {builder.getPtrTy(), builder.getPtrTy()}, false));
    builder.CreateCall(pushStackFunc, {runtimeStruct, getIRStr(this, path)});
}

void LgsRuntime::printStack() {
    const auto voidTy = builder.getVoidTy();
    const auto printStackFunc =module->getOrInsertFunction("Runtime_print_stack", FunctionType::get(voidTy, {builder.getPtrTy()}, false));
    builder.CreateCall(printStackFunc, {runtimeStruct});
}

void LgsRuntime::addAllocatedExpr(LgsExpr* expr) {
    assert(stack.size() > 0);
    stack.allocatedExprs.push_back(expr);
}

void LgsRuntime::freeExprs() {
    auto& exprs = stack.allocatedExprs;
    exprs.erase(std::remove_if(exprs.begin(), exprs.end(), [this](LgsExpr* expr) {
        if (!expr->isReturnExpr) {
            // expr->free(this);
            return true;
        }
        return false;
    }), exprs.end());
}

void LgsSymbolTable::addSymbol(const string& name, const LgsSymbol& symbol, LgsErrHandler* errHandler) {
    if (symbols.find(name) != symbols.end()) {
    std::cout << name << '+' << std::endl;
        const auto location = symbol.getLocation();
        errHandler->handleError(E10011, location, {name, location->lineNumberStr()});
        return;
    }
    std::lock_guard lock(mtx);
    symbols[name] = symbol;
}

LgsSymbol* LgsSymbolTable::getSymbol(const string& name) {
    if (symbols.find(name) != symbols.end()) {
        return &symbols[name];
    }
    return nullptr;
}

void LgsSymbolTable::addEnum(LgsEnum* lgsEnum, LgsErrHandler* errHandler) {
    if (symbols.find(lgsEnum->name) != symbols.end()) {
        const auto location = lgsEnum->location;
        errHandler->handleError(E10011, &location, {lgsEnum->name, location.lineNumberStr()});
        return;
    }
    lock_guard lock(mtx);
    symbols[lgsEnum->name] = LgsSymbol(lgsEnum);
    for (const auto& [name, field] : lgsEnum->fields) {
        symbols[name] = LgsSymbol(dynamic_cast<LgsEnumField*>(field));
    }
}

LgsSymbolTable::~LgsSymbolTable() {
    for (const auto& [_, symbol] : symbols) {
        switch (symbol.symbolType) {
        case VAR_DEC: delete symbol.varDec; break;
        case PARAM: delete symbol.param; break;
        case OBJECT: delete symbol.object; break;
        case INTERFACE: delete symbol.interface; break;
        case FUNC: if (!symbol.func->funcType->isBuiltin) delete symbol.func; break;
        case ENUM: delete symbol.lgsEnum; break;
        case ENUM_FIELD: delete symbol.enumField; break;
        default: break;
        }
    }
}