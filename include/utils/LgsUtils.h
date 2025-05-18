#ifndef LGSUTILS_H
#define LGSUTILS_H
#include "exprs/LgsExpr.h"

string getBaseStr(LgsExpr* baseExpr);
int getExprConstNumber(LgsExpr* expr);
void replaceNextPlaceholder(string& str, const LgsExpr* expr);

#endif //LGSUTILS_H
