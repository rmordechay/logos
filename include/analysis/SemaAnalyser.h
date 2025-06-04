#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "files/LgsFile.h"
#include "logos/LgsErrHandler.h"
#include "logos/LgsRuntime.h"

class LgsArray;
class LgsValue;
class LgsVariable;
class LgsUnaryExpr;
class LgsStrConst;
class LgsHashMap;
class LgsExpr;
class LgsType;
class LgsContinueStmt;
class LgsBreakStmt;
class LgsReturn;
class LgsForeachLoop;
class LgsRangeLoop;
class LgsPatternMatch;
class LgsStmtBlock;
class LgsStmt;
class LgsMainFile;
class LogosProject;
class LgsCast;
class LgsVarDec;
class LgsInstance;
class LgsIterIndex;
class LgsSelection;
class LgsFuncCall;
class LgsBinaryExpr;
class LgsArrayExpr;
class LgsIfStmt;
class LgsAssignment;
class LgsForLoop;
struct LgsSymbol;
struct LgsIndex;

class SemaAnalyser final {
public:
    LgsStack stack;
    LgsFile* file = nullptr;
    LgsErrHandler errHandler;

    explicit SemaAnalyser(LgsFile* file) : file(file) {
        errHandler.filePath = file->absPath;
    }
    static void analyseFiles(LogosProject& project);
    void analyse();
    void visitMainFile(LgsMainFile* mainFile);
    void visitObject(LgsObject* obj);
    void visitInterface(LgsInterface* interface) const;
    void visitField(const LgsField* field);
    void visitFunc(LgsFunc* func);
    void visitFuncType(const LgsFuncType* funcType);
    void visitParam(LgsParam* param);
    void validateFuncControlFlow(const LgsFunc* func);
    void visitStmt(LgsStmt* stmt);
    void visitStmtBlock(LgsStmtBlock* stmtBlock);
    void visitAssignment(const LgsAssignment* assignment);
    void visitVarDec(LgsVarDec* varDec);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitPatternMatch(const LgsPatternMatch* patternMatching);
    void visitBoolPatternMatching(const LgsPatternMatch* patternMatching) const;
    void visitLoopStmt(LgsForLoop* loopStmt);
    void visitRangeLoop(const LgsRangeLoop* rangeLoop);
    void visitForeachLoop(const LgsForeachLoop* foreachLoop);
    void visitReturnStmt(const LgsReturn* returnStmt);
    void visitBreakStmt(const LgsBreakStmt* breakStmt);
    void visitContinueStmt(const LgsContinueStmt* continueStmt);
    void visitEnum(const LgsEnum* lgsEnum) const;
    void visitExpr(LgsExpr* expr);
    void visitCast(LgsCast* castExpr);
    void visitArrayExpr(LgsArrayExpr* array);
    void visitHashMap(LgsHashMap* hashMap) const;
    void visitStrConst(LgsStrConst* strConst) const;
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitVariable(LgsVariable* variable);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitAnonymousFunc(LgsFuncCall* funcCall, const LgsFuncType* funcType);
    void visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType);
    void visitSelection(LgsSelection* selection);
    void visitInnerSelections(const LgsSelection* selection);
    void visitFieldSelection(const LgsExpr* parentExpr, LgsVariable* childField);
    void visitFirstSelection(LgsExpr* firstExpr);
    void visitInstance(LgsInstance* instance);
    void visitIterIndex(LgsIterIndex* iterIndex);

    void setBinaryExprType(LgsBinaryExpr* binaryExpr);
    bool setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable);
    void validateExprType(const LgsExpr* expr, LgsType* type);
    void checkMethodVisibility(const LgsFuncCall* methodCall);

    LgsSymbol* getSymbol(const string& name, const LgsValue* value = nullptr);
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    LgsType* resolveType(LgsType* type);
    LgsType* resolveArrayType(LgsArray* array);
    void resolveFuncTypes(LgsFuncType* funcType);
    void resolveObjMemberTypes(LgsObject* const& obj);
    void resolveObjectImplements(LgsObject* obj);
    string getFuncsAsStr(const vector<LgsFunc*>& funcs) const;
    ~SemaAnalyser() = default;
};

#endif //SEMAANALYSER_H
