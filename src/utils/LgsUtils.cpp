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

string getFormatString(const vector<LgsExpr*>& args) {
    auto result = LgsExpr::getExprStr(args[0]);
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
