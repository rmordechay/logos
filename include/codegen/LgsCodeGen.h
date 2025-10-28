#pragma once
#include "LgsLLVMGen.h"
#include "files/LgsFile.h"
#include "logos/LgsStack.h"

struct LgsPaths;
class LgsTernaryExpr;
class LgsMainFunc;
class LgsInterfaceFile;
class LgsTestFile;
class LgsObjectFile;
class LgsVectorExpr;
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
class LgsFloatConst;
class LgsBreak;
class LgsReturn;
class LgsForeachLoop;
class LgsRangeLoop;
class LgsStmtsBlock;
class LgsLoopMetaVar;
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
class LgsIntConst;
class LgsForLoop;
class LgsTypeExpr;
class LgsIOStmt;
struct LgsSymbol;
struct LgsIndex;
struct LgsAppConfigs;

class LgsCodeGen {
public:
    LgsFile& file;
    LgsStack stack;
    LgsLLVMGen& cg;
    LgsPaths& paths;
    LgsAppConfigs& appConfigs;
    Function* currentIRFunc = nullptr;
    static std::atomic<size_t> namesCounter;

    explicit LgsCodeGen(LgsFile& file, LgsAppConfigs& appConfigs, LgsPaths& paths)
        : file(file), cg(file.generator), paths(paths), appConfigs(appConfigs) {
    }

    bool generate();
    void visitMainFile(LgsMainFile* mainFile);
    void visitInterface(const LgsInterface* interface);
    void visitTestFile(const LgsTestFile* testFile);
    void visitObject(LgsObject* obj);
    void visitMainFunc(LgsMainFunc* func);
    void visitFunc(LgsFunc* func);
    void visitGenericFunc(LgsFunc* func);
    void visitField(LgsField* field) const;
    void visitParam(LgsParam* param);
    void visitStmt(LgsStmt* stmt);
    void visitStmtsBlock(const LgsStmtsBlock* stmtsBlock);
    void visitLoop(LgsForLoop* loop);
    void visitRangeLoop(LgsRangeLoop* loop);
    void visitForeachLoop(LgsForeachLoop* loop);
    void visitInfiniteLoop(const LgsInfiniteLoop* loop) const;
    void visitLoopMetaVar(LgsLoopMetaVar* metaVar) const;
    void visitWhileLoop(const LgsWhileLoop* loop);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(const LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitSimpleIf(LgsIfStmt* ifStmt);
    void visitIfWithElse(LgsIfStmt* ifStmt);
    void visitElseIf(LgsIfStmt* ifStmt);
    void visitSwitch(LgsSwitch* pm);
    void visitContinueStmt();
    void visitReturnStmt(LgsReturn* returnStmt);
    void visitBreakStmt(const LgsBreak* breakStmt);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitDeferStmt(const LgsDeferStmt* deferStmt);
    void visitIOStmt(const LgsIOStmt* ioStmt);
    void visitExpr(LgsExpr* expr, bool assign = false);
    void visitBinaryExpr(LgsBinaryExpr* binExpr);
    void visitTernaryExpr(LgsTernaryExpr* ternaryExpr);
    void visitCast(LgsCast* cast);
    void visitLambda(LgsFunc* func);
    void visitIntConst(LgsIntConst* intConst) const;
    void visitFloatConst(LgsFloatConst* floatConst) const;
    void visitArrayExpr(LgsArrayExpr* array);
    void visitHashMap(LgsHashMap* hashMap);
    void visitVectorExpr(LgsVectorExpr* vectorExpr);
    void visitVariable(LgsVariable* variable);
    void visitSelection(LgsSelection* selection, bool assign = false);
    void visitFieldSelection(LgsVariable* var, LgsExpr* parent) const;
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitIterFunc(const LgsFuncCall* funcCall);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitStrConst(LgsStrConst* strConst);
    void visitInstance(LgsInstance* instance);
    void visitIterIndex(LgsIterIndex* iterIndex, bool assign);
    void visitNull(LgsNull* null) const;
    void visitJson(LgsJson* json);

    void setNullableValue(LgsExpr* expr);
    void resolveVirtuals(const LgsInstance* instance) const;
    bool checkMock(LgsExpr* expr);

    // Funcs
    void createPrologue(LgsFunc* func);
    void createEpilogue(LgsFunc* func);
    void initMainArgs(const LgsMainFunc* mainFunc) const;
    Value* getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) const;
    Type* getThunkCtxType(const LgsFuncCall* fc) const;
    Function* getThunkFunc(const LgsFuncCall* fc, Type* ctxTy) const;

    // Iterables
    void setStaticArray(LgsArrayExpr* arrayExpr);
    void setNestedSArr(const LgsArrayExpr* arrayExpr, Type* parentType, Value* parentValue, const std::vector<Value*>& indices);
    void setDynamicArray(LgsArrayExpr* arrayExpr);
    void setSetExpr(LgsArrayExpr* arrayExpr);
    void createMapFunc(LgsFunc* func);
    void createFilterFunc(LgsFunc* func);

    Value* getIRValue(LgsValue* value);
    bool allArgsAreConst(const std::vector<LgsExpr*>& args);
    bool writeIRModule() const;
};
