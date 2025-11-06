#pragma once
#include "../data/LgsTokens.h"
#include "exprs/LgsJson.h"
#include "exprs/LgsTernaryExpr.h"
#include "files/LgsAppConfigFile.h"
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
    bool headersOnly;
    fs::path filePath;
    LgsSymbolTable& globals;
    std::string code = "";
    LgsToken currentToken;
    size_t currentIndex = 0;
    size_t recursionCount = 0;
    LgsErrHandler errHandler;
    std::vector<LgsToken> tokens;
    LgsFunc* currentFunc = nullptr;
    LgsFile* currentFile = nullptr;

    LgsParser(const size_t fileID, const fs::path& filePath, LgsPaths& paths, LgsSymbolTable& globals, const std::string& code, const bool headersOnly = false)
        : fileID(fileID), paths(paths), headersOnly(headersOnly), filePath(filePath), globals(globals), code(code) {}

    // Files
    bool scanTokens();
    LgsFile* parseSrcFile(bool isTestRun);
    LgsFile* parseSrcFileHeaders();
    void parseImports(std::unordered_map<std::string, LgsApp*>& imports);
    LgsEnvFile* parseEnvFile();
    LgsMainFile* parseMainFile();
    LgsAppConfigFile* parseAppConfigFile();
    LgsObjectFile* parseObjectFile();
    LgsInterfaceFile* parseInterfaceFile();
    LgsTestFile* parseTestFile();

    // Object
    LgsObject* parseObject();
    LgsInterface* parseInterface();
    LgsObject* parseObjectBody(const LgsToken& tokenName, bool isSingleton);
    LgsInterface* parseInterfaceBody(const LgsToken& tokenName);
    LgsGeneric* parseBaseGeneric();
    LgsField* parseField(size_t fieldPosition);
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
    LgsAssignType parseAssignType();
    LgsStmt* parseAssignOrExpr();
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

    // Exprs
    LgsExpr* parseExpr(bool withLambda = true);
    LgsExpr* parseExprWithPrecedence(int minPrecedence);
    LgsExpr* parseUnary();
    LgsVariable* parseVariable();
    bool parseGenericArgs(std::vector<LgsType*>& types);
    LgsInstance* parseInstance();
    LgsFuncCall* parseFuncCall();
    LgsVectorExpr* parseVectorExpr();
    LgsStrConst* parseStrConst();
    LgsMetaVar* parseLoopMetaVar();
    LgsExpr* parseConstant();
    LgsArrayExpr* parseArrayExpr();
    LgsHashMap* parseHashMap();
    LgsFunc* parseLambda();
    LgsExpr* parsePrefixExpr();
    LgsIterIndex* parseIterIndex(LgsExpr* baseExpr);
    LgsPostfixExpr* parsePostfixExpr(LgsExpr* baseExpr);
    LgsSelection* parseSelection(LgsExpr* firstExpr);
    LgsJson* parseJson();
    LgsJsonObject* parseJsonObject();
    LgsJsonArray* parseJsonArray();
    LgsJson* parseJsonValue();
    void parseJsonPrimitive(LgsJson* json);
    void parseExternalImports(LgsFile* file);

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
    bool isImportName(LgsExpr* expr) const;
};
