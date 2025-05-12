#include "types/str/LgsStrMethods.h"
#include "LgsDefinitions.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsVarDec.h"

void replaceNextPlaceholder(string& str, const LgsExpr* expr) {
    const auto pos = str.find(LOGOS_STR_FORMAT_PART);
    if (pos == string::npos) return;
    str.replace(pos, 2, expr->type->getStrFormatPart());
}

string getBaseStr(LgsExpr* baseExpr) {
    if (const auto strConst = baseExpr->asStrConst()) {
        return strConst->value;
    }
    if (const auto var = baseExpr->asVariable()) {
        switch (var->ref->type) {
        case VAR_DEC:
            return var->ref->varDec->expr->asStrConst()->value;
        default:
            break;
        }
    }
    assert(false);
}

FunctionCallee getPrintf(Module* module) {
    const vector<Type*> printfArgsTypes = {ptrTy};
    FunctionType *printfType = FunctionType::get(Type::getInt32Ty(context), printfArgsTypes, true);
    return module->getOrInsertFunction("printf", printfType);
}

Value* LgsStrFormatFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    auto baseStr = getBaseStr(args[0]);
    for (int i = 1; i < args.size(); ++i) {
        replaceNextPlaceholder(baseStr, args[i]);
    }
    std::cout << baseStr << '\n';
    const auto baseIRStr = getIRStr(metadata->module, baseStr);
    vector IRArgs = {baseIRStr};
    for (int i = 1; i < args.size(); ++i) {
        IRArgs.emplace_back(args[i]->getIRValue(metadata));
    }
    const auto printfFunc = getPrintf(metadata->module);
    return metadata->builder.CreateCall(printfFunc, IRArgs);
}
