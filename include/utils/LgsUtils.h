#ifndef LGSUTILS_H
#define LGSUTILS_H
#include "exprs/LgsExpr.h"

string getFileText(filesystem::path filePath);
string getExprStr(LgsExpr* baseExpr);
int getExprConstNumber(LgsExpr* expr);
string getFormatString(const vector<LgsExpr*>& args);

#endif //LGSUTILS_H
