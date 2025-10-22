#pragma once
#include "../data/LgsTokens.h"
#include "exprs/LgsTernaryExpr.h"
#include "files/LgsConfigFile.h"
#include "funcs/LgsMainFunc.h"
#include "loops/LgsForeachLoop.h"
#include "utils/LgsErrHandler.h"
#include "parser/LgsLexer.h"

class LgsGeneric;
struct LgsPaths;
struct LgsSymbol;
struct LgsAppConfigs;
struct LgsSymbolTable;
struct LgsToken;
class LgsStrConst;
class LgsTestFile;
class LgsInterfaceFile;
class LgsObjectFile;
class LgsMainFile;
class LgsEnvFile;
class LgsFile;
class LgsIOPair;
class LgsSubType;
class LgsParam;
class LgsField;
class LgsEnum;
class LgsInterface;
class LgsType;
class LgsJson;
class LgsPostfixExpr;
class LgsIterIndex;
class LgsSelection;
class LgsInstance;
class LgsVectorExpr;
class LgsHashMap;
class LgsArrayExpr;
class LgsSwitch;
class LgsVarDec;
class LgsIOStmt;
class LgsDeferStmt;
class LgsCoroutine;
class LgsBreak;
class LgsInfiniteLoop;
class LgsForLoop;
class LgsWhileLoop;
class LgsIfStmt;
class LgsFunc;
class LgsObject;
class LgsReturn;
class LgsStmt;
class LgsFuncCall;
class LgsExpr;

class LgsParser {
public:
    size_t fileID;
    LgsPaths& paths;
    LgsSymbolTable& globals;
    LgsErrHandler errHandler;
    const fs::path& filePath;
    LgsToken currentToken;
    size_t currentIndex = 0;
    size_t recursionCount = 0;
    LgsFunc* currentFunc = nullptr;
    std::vector<LgsToken> tokens;

    LgsParser(const size_t fileId, const fs::path& filePath, LgsPaths& paths, LgsSymbolTable& globals, const std::vector<LgsToken>& tokens) :
        fileID(fileId), paths(paths), globals(globals), filePath(filePath), tokens(tokens) {
        if (!tokens.empty()) {
            currentToken = tokens[0];
        }
    }

    // Files
    LgsFile* parseSrcFile(bool isTestRun);
    LgsMainFile* parseMainFile();
    LgsObjectFile* parseObjectFile();
    LgsInterfaceFile* parseInterfaceFile();
    LgsTestFile* parseTestFile();
    LgsEnvFile* parseEnvFile();
    LgsConfigFile* parseAppConfigFile();
    bool parseVersion(LgsAppVersion& appVersion);
    void parseExternalImports(LgsFile* file);

    // Object
    LgsObject* parseObject();
    LgsInterface* parseInterface();
    LgsObject* parseObjectBody(const LgsToken& tokenName, bool isSingleton);
    LgsInterface* parseInterfaceBody(const LgsToken& tokenName);
    LgsGeneric* parseGeneric();
    LgsField* parseField();
    LgsIOPair* parseIOPair();

    // Types
    LgsEnum* parseEnum();
    LgsSubType* parseSubtype();
    LgsFuncType* parseFuncType();
    LgsMap* parseMapType();
    LgsType* parseType();

    // Funcs
    LgsFunc* parseFunc();
    LgsMainFunc* parseMainFunc();
    LgsFunc* parseMethod(LgsObject* obj);
    LgsFuncType* parseFuncHeader();
    void parseParams(LgsFuncType* funcType);

    // Statements
    LgsStmt* parseStmt();
    LgsStmtsBlock* parseStmtsBlock(bool withSingleStmt = true);
    LgsVarDec* parseVarDec();
    LgsStmt* parseAssignment();
    LgsStmt* parseIfStmt();
    LgsSwitch* parseSwitch();
    LgsForLoop* parseForLoop();
    LgsWhileLoop* parseWhileLoop();
    LgsInfiniteLoop* parseInfiniteLoop();
    LgsReturn* parseReturnStmt();
    LgsStmt* parseContinueStmt();
    LgsBreak* parseBreakStmt();
    LgsCoroutine* parseCoroutine();
    LgsDeferStmt* parseDeferStmt();
    LgsIOStmt* parseIOStmt();
    LgsJson* parseJson();

    LgsExpr* parseExprWithPrecedence(int minPrecedence);
    // Exprs
    LgsExpr* parseExpr(bool withLambda = true);
    LgsExpr* parseUnary();
    LgsBinOp parseBinaryOp();
    LgsVariable* parseVariable();
    LgsInstance* parseInstance();
    LgsFuncCall* parseFuncCall();
    LgsVectorExpr* parseVectorExpr();
    LgsStrConst* parseStrConst();
    LgsLoopMetaVar* parseLoopMetaVar();
    LgsExpr* parseConstant();
    LgsArrayExpr* parseArrayExpr();
    LgsHashMap* parseHashMap();
    LgsFunc* parseLambda();
    LgsExpr* parsePrefixExpr();
    LgsIterIndex* parseIterIndex(LgsExpr* baseExpr);
    LgsPostfixExpr* parsePostfixExpr(LgsExpr* baseExpr);
    LgsSelection* parseSelection(LgsExpr* firstExpr = nullptr);

    // Helpers
    bool validateTypeName(const std::string& typeName, const LgsLocation* location);
    void addFileSymbol(LgsMainFile* file, const LgsSymbol& newSymbol);
    void setLocation(LgsLocation& location, const LgsToken* token) const;
    void extractStrParts(LgsStrConst& strConst);
    static int getBinOpPrecedence(LgsBinOpType opType);

    // Parser
    bool isEOF();
    void reset(size_t index);
    LgsToken consume();
    LgsToken peek(size_t i = 1);
    bool matchAndConsume(LgsTokenType token);
    bool matchOrReset(LgsTokenType t2, size_t resetIndex);
    bool mustMatch(LgsTokenType t2);
    bool mustParse(const void* value);
    bool parsedOrReset(const void* value, size_t resetIndex);
    void addParsingError();
    void recursionGuard();
    void validateTestFolder(const LgsFile* testFile);
};
