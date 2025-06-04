#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "files/LgsFile.h"
#include "logos/LgsASTVisitor.h"
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

class SemaAnalyser final : public LgsAstVisitor {
public:
    LgsStack stack;
    LgsFile* file = nullptr;
    LgsErrHandler errHandler;

    explicit SemaAnalyser(LgsFile* file) : file(file) {
        errHandler.filePath = file->absPath;
    }
    static void analyseFiles(LogosProject& project);
    void start() override;
    void visitMainFile(LgsMainFile* mainFile) override;
    void visitObject(LgsObject* obj) override;
    void visitInterface(LgsInterface* interface) const override;
    void visitField(const LgsField* field) override;
    void visitFunc(LgsFunc* func) override;
    void visitFuncType(const LgsFuncType* funcType) override;
    void visitParam(LgsParam* param) override;
    void visitStmt(LgsStmt* stmt) override;
    void visitStmtBlock(LgsStmtBlock* stmtBlock) override;
    void visitAssignment(const LgsAssignment* assignment) override;
    void visitVarDec(LgsVarDec* varDec) override;
    void visitIfStmt(LgsIfStmt* ifStmt) override;
    void visitPatternMatch(const LgsPatternMatch* patternMatching) override;
    void visitBoolPatternMatching(const LgsPatternMatch* patternMatching) const override;
    void visitLoopStmt(LgsForLoop* loopStmt) override;
    void visitRangeLoop(const LgsRangeLoop* rangeLoop) override;
    void visitForeachLoop(const LgsForeachLoop* foreachLoop) override;
    void visitReturnStmt(const LgsReturn* returnStmt) override;
    void visitBreakStmt(const LgsBreakStmt* breakStmt) override;
    void visitContinueStmt(const LgsContinueStmt* continueStmt) override;
    void visitEnum(const LgsEnum* lgsEnum) const override;
    void visitExpr(LgsExpr* expr) override;
    void visitCast(LgsCast* castExpr) override;
    void visitArrayExpr(LgsArrayExpr* array) override;
    void visitHashMap(LgsHashMap* hashMap) const override;
    void visitStrConst(LgsStrConst* strConst) const override;
    void visitUnaryExpr(LgsUnaryExpr* unaryExpr) override;
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr) override;
    void visitVariable(LgsVariable* variable) override;
    void visitFuncCall(LgsFuncCall* funcCall) override;
    void visitAnonymousFunc(LgsFuncCall* funcCall, const LgsFuncType* funcType) override;
    void visitMethodCall(LgsFuncCall* methodCall, const LgsType* parentType) override;
    void visitSelection(LgsSelection* selection) override;
    void visitInnerSelections(const LgsSelection* selection) override;
    void visitFieldSelection(const LgsExpr* parentExpr, LgsVariable* childField) override;
    void visitFirstSelection(LgsExpr* firstExpr) override;
    void visitInstance(LgsInstance* instance) override;
    void visitIterIndex(LgsIterIndex* iterIndex) override;

    void setBinaryExprType(LgsBinaryExpr* binaryExpr);
    bool setSelectionFieldType(const LgsUnaryExpr* parent, LgsVariable* fieldVariable);
    void validateExprType(const LgsExpr* expr, LgsType* type);
    void validateFuncControlFlow(const LgsFunc* func);
    void checkMethodVisibility(const LgsFuncCall* methodCall);

    LgsSymbol* getSymbol(const string& name, const LgsValue* value = nullptr);
    void addLocalSymbol(const string& name, const LgsSymbol& symbol);
    LgsType* resolveType(LgsType* type);
    LgsType* resolveArrayType(LgsArray* array);
    void resolveFuncTypes(LgsFuncType* funcType);
    void resolveObjMemberTypes(LgsObject* const& obj);
    void resolveObjectImplements(LgsObject* obj);
    string getFuncsAsStr(const vector<LgsFunc*>& funcs) const;
    ~SemaAnalyser() override = default;
};

#endif //SEMAANALYSER_H
