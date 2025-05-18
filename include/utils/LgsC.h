#ifndef LGSC_H
#define LGSC_H

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Tooling/CommonOptionsParser.h"

using namespace clang;
using namespace clang::tooling;
using namespace llvm;

class LgsC : public RecursiveASTVisitor<LgsC> {
public:
    ASTContext* ctx = nullptr;

    void l() const;
    ~LgsC() = default;
};

#endif //LGSC_H
