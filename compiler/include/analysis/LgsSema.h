#pragma once
#include "logos/LgsStack.h"
#include "errors/LgsErrHandler.h"
#include "analysis/LgsTypeResolver.h"
#include "exprs/LgsJson.h"
#include "files/LgsEnvFile.h"
#include "logos/LgsAppConfigs.h"
#include <unordered_map>

#include "stmts/LgsAssignment.h"

class LgsMainFunc;
class LgsMetaSelection;
class LgsAppConfigFile;
class LgsTernaryExpr;
class LgsVec;
class LgsInterfaceFile;
class LgsObjectFile;
class LgsTestFile;
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
    LgsFile* file;
    LgsStack stack;
    LgsAppConfigs& appConfigs;
    LgsGlobals& globals;
    LgsErrHandler errHandler;
    LgsTypeResolver typeResolver;
    std::unordered_map<std::string, size_t> refCount;

    explicit LgsSema(LgsAppConfigs& appConfigs, LgsFile* file, LgsGlobals& globals)
        : file(file), appConfigs(appConfigs), globals(globals), typeResolver(file, errHandler, globals) {}

    void analyse();
    void visitMainFile(LgsMainFile* mainFile);
    void visitObject(LgsObject* obj);
    void visitInterface(LgsInterface* interface);
    void visitEnum(const LgsEnum* enum_);
    void visitTestFile(const LgsTestFile* testFile);
    void visitField(LgsField* field);
    void visitFuncHeader(LgsFuncType* ft);
    void visitFunc(LgsFunc* func);
    void visitMainFunc(LgsMainFunc* mainFunc);
    void visitLambda(LgsFunc* lambda);
    void visitParam(LgsParam* param);
    void visitIOPair(LgsIOPair* ioPair, LgsObject* obj);
    void visitStmt(LgsStmtWrapper& stmt);
    void replaceForLoop(LgsStmtWrapper& stmt);
    void visitStmtsBlock(LgsStmtsBlock* stmtsBlock);
    void visitVarDec(LgsVarDec* varDec);
    void visitAssignment(LgsAssignment* assignment);
    void visitIfStmt(LgsIfStmt* ifStmt);
    void visitMacroIf(LgsIfStmt* ifStmt);
    void visitSwitch(LgsSwitch* switchStmt);
    void visitLoop(LgsForLoop* loopStmt);
    void visitRangeLoop(LgsRangeLoop* rangeLoop);
    void visitForeachLoop(LgsForeachLoop* foreachLoop);
    void visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop);
    void visitWhileLoop(LgsWhileLoop* whileLoop);
    void visitReturnStmt(const LgsReturn* returnStmt);
    void visitContinueStmt(const LgsContinue* continueStmt);
    void visitBreakStmt(const LgsBreak* breakStmt);
    void visitCoroutine(const LgsCoroutine* coroutine);
    void visitDeferStmt(const LgsDeferStmt* deferStmt);
    void visitIOStmt(const LgsIOStmt* ioStmt);
    void visitExpr(LgsExpr*& expr);
    void visitBinaryExpr(LgsBinaryExpr* binaryExpr);
    void visitTernaryExpr(LgsTernaryExpr* ternary);
    void visitCast(LgsCast* cast);
    void visitNullableExpr(LgsNullableExpr* nullableExpr);
    void visitUnwrap(LgsExpr* expr);
    void visitArrayExpr(LgsArrayExpr* arrayExpr);
    void visitStaticArray(const LgsArrayExpr* arrayExpr);
    void visitDynamicArray(LgsArrayExpr* arrayExpr);
    void visitHashMap(LgsHashMap* hashMap);
    void visitVectorExpr(LgsVectorExpr* vectorExpr);
    void visitMatrixExpr(const LgsMatrixExpr* matrixExpr);
    void visitVariable(LgsVariable* variable);
    void visitSelection(LgsSelection* selection);
    void visitFirstSelection(LgsSelection* selection);
    void visitInnerSelections(LgsSelection* selection);
    void visitFieldSelection(LgsVariable* child, LgsType* parentType);
    void visitIterIndexSelection(LgsIterIndex* iterIndex, LgsType* parentType);
    void visitMetaSelection(LgsMetaSelection* metaSelection);
    void visitFuncCall(LgsFuncCall* funcCall);
    void visitMethodCall(LgsFuncCall* methodCall, LgsExpr* parent);
    bool visitFuncArgs(LgsFuncCall* funcCall, LgsFuncType* ft);
    void visitPrefixExpr(LgsPrefixExpr* prefixExpr);
    void visitPostfixExpr(LgsPostfixExpr* postfixExpr);
    void visitStrConst(const LgsStrConst* strConst);
    void visitComplexConst(LgsComplexConst* complex);
    void visitTypeExpr(LgsTypeExpr* typeExpr);
    void visitJson(const LgsJson* json);
    void visitJsonArr(const LgsJsonArray* jsonArr);
    void visitJsonObj(const LgsJsonObject* jsonObj);
    void visitInstance(LgsInstance* instance);
    void visitInlineInterface(LgsInstance* instance, LgsInterface* interface);
    void visitIterIndex(LgsIterIndex* iterIndex);
    void visitIndex(LgsIterIndex* iterIndex);
    void visitSlice(LgsIterIndex* iterIndex);
    void visitLoopMetaVar(LgsMetaVar* metaVar);

    bool validateExprType(const LgsExpr* expr, LgsType* type);
    bool validateTypeName(const std::string& name, const LgsLocation& location);
    bool validateLocalName(const std::string& name, const LgsLocation& location);
    void validateObjImplements(LgsObject* obj, const std::vector<LgsType*>& interfaces);
    void validateIndex(LgsIterIndex* iterIndex);
    bool validateFieldVisibility(LgsField* field, LgsType* parent, const LgsLocation& location);
    bool validateMethodVisibility(const LgsFunc* method, LgsType* parent, const LgsLocation& location);
    bool validateVecElements(const LgsVariable* fieldVar, LgsVec* vec);
    void validateObjDuplicates(LgsObject* type);
    static bool validateBlockControlFlow(const LgsStmtsBlock* stmtBlock, const LgsFunc* func);

    void resolveImports() const;
    void addLocalSymbol(const LgsSymbol& newSymbol);
    LgsSymbol* getSymbol(const std::string& name);
    void createCoroutineFunc(LgsFuncCall* funcCall);
    void makeGenericFuncCall(LgsFuncCall* funcCall, const LgsFunc* func);
    void addError(const LgsBaseMsg& lgsErr, const LgsLocation& location, const std::vector<std::string>& args = {});
    void addErrorIfSuccessful(const LgsBaseMsg& lgsErr, const LgsLocation& location, const std::vector<std::string>& args);
    void addRTType(LgsType* type) const;
    void addGenerics(LgsType* type) const;
};
