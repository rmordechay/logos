#include "analysis/PostAnalyser.h"

#include "analysis/SemaAnalyser.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "funcs/LgsFunc.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/primitives/LgsVoid.h"

class LgsFile;

void PostAnalyser::analyse(const vector<LgsFile*>& files) {
    for (const auto file : files) {
        SemaAnalyser semaAnalyser(file);
        if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
            for (const auto obj : mainFile->objects) {
                for (const auto [_, method] : obj->methods) {
                    swapReturn(method);
                }
            }
            for (const auto [_, func] : mainFile->funcs) {
                swapReturn(func);
            }
        } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
            const auto obj = objFile->obj;
            for (const auto [_, method] : obj->methods) {
                swapReturn(method);
            }
        } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
            for (const auto [_, method] : interfaceFile->interface->methods) {
                swapReturn(method);
            }
        }
    }
}

void PostAnalyser::swapReturn(const LgsFunc* func) {
    const auto funcType = func->funcType;
    const auto returnExprs = func->returnExprs;
    if (funcType->rt->isPrimitive) return;
    // Check if there are different return expressions in order to check
    // whether a swap is possible
    auto sameReturnExprs = true;
    for (const auto expr1 : returnExprs) {
        for (const auto expr2 : returnExprs) {
            if (expr1 == expr2) continue;
            if (expr1->equals(expr2)) continue;
            sameReturnExprs = false;
            break;
        }
    }
    if (funcType->isSizeBig && sameReturnExprs) {
        funcType->isSwapReturn = true;
        funcType->returnParamIndex = funcType->isMethod && !funcType->isStaticMethod;
        funcType->params.insert(funcType->params.begin(), LgsParam(funcType->rt));
        funcType->rt = &LGS_VOID;
    }
}