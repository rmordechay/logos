#include "utils/LgsUtils.h"
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "logos/LgsConfig.h"
#include "logos/LgsProject.h"
#include "logos/Platform.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>

string getFileText(path filePath) {
    ifstream file(canonical(filePath));
    stringstream fileContents;
    fileContents << file.rdbuf();
    return fileContents.str();
}

int getExprConstNumber(LgsExpr* expr) {
    if (const auto asInt = expr->asIntConst()) {
        return asInt->value;
    }
    if (const auto var = expr->asVariable()) {
        switch (var->ref->type) {
        case VAR_DEC:
            return getExprConstNumber(var->ref->varDec->expr);
        case FIELD:
            return getExprConstNumber(var->ref->field->expr);
        default:
            break;
        }
    }
    return -1;
}

string getExprStr(LgsExpr* baseExpr) {
    if (const auto strConst = baseExpr->asStrConst()) {
        return strConst->value;
    }
    if (const auto var = baseExpr->asVariable()) {
        const auto ref = var->ref;
        switch (ref->type) {
        case VAR_DEC: {
            return getExprStr(ref->varDec->expr);
        }
        default:
            break;
        }
    }
    assert(false);
}

string getFormatString(const vector<LgsExpr*>& args) {
    auto result = getExprStr(args[0]);
    auto searchPos = 0;
    for (size_t i = 1; i < args.size(); ++i) {
        const auto pos = result.find(LOGOS_STR_FORMAT_PART, searchPos);
        const auto part = args[i]->type->getStrFormatPart();
        if (pos != string::npos) {
            result.replace(pos, 2, part);
            searchPos = pos + part.length();
        }
    }
    return result;
}

void setIterIndices(const LgsIterIndex* iterIndex, vector<LgsIndex*>& indices) {
    while (iterIndex) {
        if (iterIndex->index) {
            indices.push_back(iterIndex->index);
        }
        iterIndex = iterIndex->baseExpr->asIterIndex();
    }
    reverse(indices.begin(), indices.end());
}

Value* getIRStr(const LgsRuntime* runtime, const string& value) {
    for (auto& globals : runtime->module->globals()) {
        if (!globals.hasInitializer()) continue;
        const auto dataArray = dyn_cast<ConstantDataArray>(globals.getInitializer());
        if (!dataArray || !dataArray->isCString() || dataArray->getAsCString() != value) continue;
        return &globals;
    }
    const auto strConstant = ConstantDataArray::getString(context, value, true);
    const auto globalVariable = new GlobalVariable(*runtime->module, strConstant->getType(), true, GlobalValue::PrivateLinkage, strConstant);
    globalVariable->setUnnamedAddr(GlobalValue::UnnamedAddr::Global);
    return globalVariable;
}

StructType* getIRStructType(LLVMContext& context, const string& name, const vector<Type*>& fields) {
    const auto struct_ = StructType::getTypeByName(context, name);
    if (!struct_) {
        return StructType::create(context, fields, name);
    }
    return struct_;
}

Module* createIRModule(const string& moduleName, LLVMContext& context) {
    const auto targetTriple = sys::getDefaultTargetTriple();
    string error;
    const auto target = TargetRegistry::lookupTarget(targetTriple, error);
    const auto targetMachine = target->createTargetMachine(targetTriple, "generic", "", TargetOptions(), std::nullopt);
    const auto module = new Module(moduleName, context);
    module->setTargetTriple(targetTriple);
    module->setDataLayout(targetMachine->createDataLayout());
    return module;
}

