#include "utils/LgsCInterface.h"

#include "funcs/LgsFuncImpl.h"

LgsType* mapCType(const string& cType) {
    if (cType == "void") {
        return &LGS_VOID;
    }
    assert(false);
}

bool LgsCVisitor::VisitFunctionDecl(const FunctionDecl* func) const {
    if (!func->isThisDeclarationADefinition()) return true;
    const auto& sm = context->getSourceManager();
    const auto loc = func->getLocation();
    if (!sm.isWrittenInMainFile(loc)) return true;
    if (!func->isThisDeclarationADefinition()) {
        return true;
    }
    const auto name = func->getNameAsString();
    const auto returnType = func->getReturnType().getAsString();
    const auto lgsType = mapCType(returnType);
    const auto funcImpl = new LgsFuncImpl(name, lgsType);
    for (int i = 0; i < func->getNumParams(); ++i) {
        auto parmVarDecl = func->getParamDecl(i)->getType();
        auto parmVarDecl2 = func->getParamDecl(i)->getType()->isPointerType();
        std::cout << "parmVarDecl" << std::endl;
    }
    globals.addSymbol(name, LgsSymbol(funcImpl), nullptr);
    return true;
}

void LgsCASTConsumer::HandleTranslationUnit(ASTContext& context) {
    visitor.TraverseDecl(context.getTranslationUnitDecl());
}

std::unique_ptr<ASTConsumer> LgsCFrontendAction::CreateASTConsumer(CompilerInstance& compilerInstance,
    StringRef file) {
    return std::make_unique<LgsCASTConsumer>(&compilerInstance.getASTContext());
}
