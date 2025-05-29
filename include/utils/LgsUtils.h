#ifndef LGSUTILS_H
#define LGSUTILS_H
#include "exprs/LgsExpr.h"

struct LgsIndex;
string getFileText(filesystem::path filePath);
string getExprStr(LgsExpr* baseExpr);
int getExprConstNumber(LgsExpr* expr);
string getFormatString(const vector<LgsExpr*>& args);
void setIterIndices(const LgsIterIndex* iterIndex, vector<LgsIndex*>& indices);
bool shouldLoadIRArg(Value* value);

#endif //LGSUTILS_H
