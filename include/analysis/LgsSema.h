#pragma once
#include "logos/LgsStack.h"
#include "utils/LgsErrHandler.h"
#include "analysis/LgsTypeResolver.h"

class LgsTernaryExpr;
class LgsVec;
class LgsInterfaceFile;
class LgsObjectFile;
class LgsPostfixExpr;
class LgsDeferStmt;
class LgsInfiniteLoop;
class LgsObject;
class LgsWhileLoop;
class LgsFuncType;
class LgsIterable;
class LgsFile;
class LgsCoroutine;
class LgsPrefixExpr;
class LgsDArray;
class LgsValue;
class LgsVariable;
class LgsStrConst;
class LgsHashMap;
class LgsExpr;
class LgsType;
class LgsContinue;
class LgsBreak;
class LgsReturn;
class LgsForeachLoop;
class LgsRangeLoop;
class LgsStmtsBlock;
class LgsStmt;
class LgsMainFile;
class LgsApp;
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

class LgsSema final {
public:
    LgsStack stack;
    LgsFile* file = nullptr;
    LgsErrHandler errHandler;
    LgsSymbolTable& globals;
    LgsTypeResolver typeResolver;

    explicit LgsSema(LgsFile* file, LgsSymbolTable& globals) : file(file), globals(globals), typeResolver(errHandler, globals) {}
    void analyse();
    void visitMainFile(LgsMainFile* mainFile);
    void visitObject(LgsObject* obj);
    void visitInterface(LgsInterface* interface);
    void visitTestFile(const LgsTestFile* testFile);
    void visitField(LgsField* field);
    void visitFunc(LgsFunc* func);
    void visitMainFunc(LgsMainFunc* mainFunc);
    void visitLambda(LgsFunc* lambda);
    void visitParam(LgsParam* param);
    void visitIOPair(LgsIOPair* ioPair, LgsObject* obj);
    void visitStmt(LgsStmt* stmt);
    void visitStmtsBlock(LgsStmtsBlock* stmtsBlock);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitSwitch(LgsSwitch* switchStmt);
    void visitWhileLoop(LgsWhileLoop* whileLoop);
    void visitLoopStmt(LgsForLoop* loopStmt);
    void visitRangeLoop(LgsRangeLoop* rangeLoop);
    void visitForeachLoop(LgsForeachLoop* foreachLoop);
    void visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop);
    void visitReturnStmt(LgsReturn* returnStmt);
    void visitContinueStmt(const LgsContinue* continueStmt);
    void visitBreakStmt(const LgsBreak* breakStmt);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitDeferStmt(const LgsDeferStmt* deferStmt);
    void visitIOStmt(const LgsIOStmt* ioStmt);
    void visitExpr(LgsExpr*& expr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitTernaryExpr(LgsTernaryExpr* ternary);
    void visitCast(LgsCast* cast);
    void visitArrayExpr(LgsArrayExpr* arrayExpr);
    void visitStaticArray(const LgsArrayExpr* arrayExpr);
    void visitDynamicArray(LgsArrayExpr* arrayExpr);
    void visitHashMap(LgsHashMap* hashMap);
    void visitVectorExpr(const LgsVectorExpr* vectorExpr);
    void visitVariable(LgsVariable* variable);
    void visitSelection(LgsSelection* selection);
    void visitFirstSelection(LgsExpr* firstExpr);
    void visitInnerSelections(LgsSelection* selection);
    void visitFieldSelection(LgsVariable* child, LgsType* parentType);
    void visitIterIndexSelection(LgsIterIndex* iterIndex, LgsType* parentType);
    void visitMethodCall(LgsFuncCall* methodCall, LgsExpr* parent);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitStrConst(const LgsStrConst* strConst);
    void visitTypeExpr(LgsTypeExpr* typeExpr);
    void visitJson(const LgsJson* json);
    void visitInstance(LgsInstance* instance);
    void visitInterfaceInstance(LgsInstance* instance, LgsInterface* interface);
    void visitIterIndex(LgsIterIndex* iterIndex);
    void visitIndex(LgsIterIndex* iterIndex);
    void visitSlice(LgsIterIndex* iterIndex);
    void visitLoopMetaVar(LgsLoopMetaVar* metaVar);

    bool validateExprType(LgsExpr* expr, LgsType* type);
    void validateObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces);
    void validateIndex(LgsIterIndex* iterIndex);
    bool validateFieldVisibility(LgsField* field, LgsType* parent);
    bool validateMethodVisibility(const LgsFunc* method, LgsType* parent, const LgsLocation& location);
    bool validateVecElements(const LgsVariable* fieldVar, LgsVec* vec);
    void validateTypeDuplicates(LgsType* type);
    static bool validateBlockControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func);

    void addHeapExpr(LgsExpr* expr);
    LgsSymbol* getSymbol(const std::string& name, const LgsLocation* location);
    void addLocalSymbol(const LgsSymbol& newSymbol);
};

