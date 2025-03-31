#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "LgsAnalyser.h"
#include "LgsInterfaceFile.h"
#include "LgsStack.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "stmts/LgsEnum.h"
#include "stmts/LgsPatternMatching.h"
#include "types/LgsObject.h"
#include "stmts/LgsReturn.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>


class LgsVarDec;
struct LgsSymbol;
class LgsInstance;
class LgsArrayIndex;
class LgsSelection;
class LgsFuncCall;
class LgsBinaryExpr;
class LgsArray;
class LgsIfStmt;
class LgsAssignment;
class LgsLoop;

class SemaAnalyser final : public LgsAnalyser {
public:
    LgsStack logosStack;
    LgsFile* file = nullptr;
    vector<LgsError> errors;

    explicit SemaAnalyser(LgsFile* logosFile) : file(logosFile) {}
    void analyse();
    void visitMainFile(const LgsMainFile* mainFile);
    void visitObjectFile(const LgsObjectFile* objectFile);
    void visitInterfaceFile(LgsInterfaceFile* interfaceFile);
    void visitObject(LgsObject* obj);
    void visitInterface(const LgsInterface* interface);
    void visitField(const LgsField* field);
    void visitMethodImpl(LgsMethodImpl* method, LgsObject* obj);
    void visitMainFunc(LgsFuncImpl* mainFunc);
    void visitFuncImpl(LgsFuncImpl* func);
    void visitParam(LgsParam* param);
    void visitStmt(LgsStmt* stmt);
    void visitStmtBlock(const LgsStmtBlock* stmtBlock);
    void visitAssignment(const LgsAssignment* assignment);
    void visitVarDec(LgsVarDec* varDec);
    void visitIfStmt(const LgsIfStmt* ifStmt);
    void visitPatternMatching(const LgsPatternMatching* patternMatching);
    void visitBoolPatternMatching(const LgsPatternMatching* patternMatching);
    void visitLoopStmt(LgsLoop* loopStmt);
    void visitRangeLoop(const LgsRangeLoop* rangeLoop);
    void visitForeachLoop(const LgsForeachLoop* foreachLoop);
    void visitReturnStmt(const LgsReturn* returnStmt);
    void visitEnum(LgsEnum* lgsEnum);
    void visitExpr(LgsExpr* expr);
    void visitArray(const LgsArray* array);
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitVariable(LgsVariable* variable);
    void setSelectionFieldType(LgsUnaryExpr* parent, LgsVariable* fieldVariable);
    void setMethodCallType(const LgsUnaryExpr* parent, LgsFuncCall* funcCall);
    void visitFuncCall(LgsFuncCall* funcCall);
    void setVariableType(LgsVariable* variable);
    void visitSelection(LgsSelection* selection);
    void visitInnerSelections(const LgsSelection* selection);
    void visitFirstSelection(LgsExpr* firstExpr);
    void visitInstance(LgsInstance* instance);
    void visitArrayIndex(LgsArrayIndex* arrayIndex);

    void setFuncType(LgsFunc* func);
    void setExprType(LgsExpr* expr, LgsType* type);
    void setBinaryExprType(LgsBinaryExpr* binaryExpr);

    bool checkExprType(const LgsExpr* expr, LgsType* userType);
    void handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args);
    LgsSymbol* getSymbol(const string& name, const LgsValue* value);
    LgsFunc* getFunc(const LgsFuncCall* funcCall);
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    Location* getSymbolLocation(const LgsSymbol* symbol) const;
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
