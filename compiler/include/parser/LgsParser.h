#pragma once
#include <unordered_set>
#include <filesystem>
#include <string>
#include <utility>
#include <vector>

#include "LgsBinaryTokens.h"
#include "LgsTokens.h"
#include "lgsc/LgsCCompiler.h"
#include "errors/LgsErrHandler.h"
#include "logos/LgsPaths.h"
#include "stmts/LgsImport.h"

class LgsCharConst;
class LgsModuleExpr;
class LgsImport;
class LgsMetaVar;
struct LgsImportPkg;
class LgsStmtsBlock;
class LgsMainFunc;
class LgsMap;
class LgsFuncType;
class LgsAppFile;
struct LgsFileMetadata;
class LgsMetaSelection;
class LgsMatrixExpr;
class LgsTypeParam;
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
class LgsVariable;
struct LgsBaseMsg;

class LgsParser {
public:
    bool headersOnly;
    const LgsPaths& paths;
    const fs::path filePath;
    LgsSymbolTable& globals;
    LgsErrHandler errHandler;
    const std::string lgsCode;
    LgsToken currentToken;
    size_t currentIndex = 0;
    size_t recursionCount = 0;
    std::vector<LgsToken> tokens;
    LgsFunc* currentFunc = nullptr;
    const LgsAppConfigs& appConfigs;
    std::vector<LgsImport> importPaths;
    std::unordered_set<std::string> importAppNames;

    LgsParser(const std::string& lgsCode, const fs::path& filePath, const LgsAppConfigs& appConfigs, const LgsPaths& paths, LgsSymbolTable& globals, const bool headersOnly = false)
        : headersOnly(headersOnly), paths(paths), filePath(filePath), globals(globals), lgsCode(lgsCode), appConfigs(appConfigs) {
    }
    // Files
    bool scanTokens();
    LgsFile* parseSrcFile();
    LgsFile* parseSrcFileHeaders();
    LgsMainFile* parseMainFile();
    LgsObjectFile* parseObjectFile();
    LgsObject* parseObject(bool withParen);
    LgsInterfaceFile* parseInterfaceFile();
    LgsTestFile* parseTestFile();
    LgsAppFile* parseAppFile();
    LgsEnvFile* parseEnvFile();

    // Object
    LgsInterface* parseInterface();
    LgsInterface* parseInterfaceBody(const LgsToken& tokenName);
    LgsField* parseField(size_t fieldPosition);
    LgsIOPair* parseIOPair();

    // Types
    LgsType* parseType();
    LgsEnum* parseEnum();
    LgsSubType* parseSubtype();
    LgsFuncType* parseFuncType();
    LgsMap* parseMapType();
    LgsTypeParam* parseTypeParam();
    std::vector<LgsType*> parseTypeArgs();

    // Funcs
    LgsFunc* parseFunc();
    LgsMainFunc* parseMainFunc();
    LgsFunc* parseMethod(LgsObject* obj);
    LgsFuncType* parseFuncHeader();
    void parseParams(LgsFuncType* funcType);

    // Statements
    LgsStmt* parseStmt();
    LgsStmtsBlock* parseStmtsBlock(bool wrapInFunc = false, bool withSingleStmt = true);
    LgsVarDec* parseVarDec();
    LgsStmt* parseAssignment();
    LgsStmt* parseIfStmt();
    LgsSwitch* parseSwitch();
    LgsStmt* parseBoolSwitch();
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
    LgsExpr* parseBinExpr(int minPrecedence, bool withLambda = true);
    LgsExpr* parseUnary(bool withInstance = true);
    LgsVariable* parseVariable();
    LgsModuleExpr* parseModuleExpr();
    LgsInstance* parseInstance();
    LgsFuncCall* parseFuncCall();
    LgsStrConst* parseStrConst();
    LgsCharConst* parseCharConst();
    LgsExpr* parseConstant();
    LgsMetaVar* parseLoopMetaVar();
    LgsArrayExpr* parseArrayExpr();
    LgsVectorExpr* parseVectorExpr();
    LgsMatrixExpr* parseMatrixExpr();
    LgsHashMap* parseHashMap();
    LgsFunc* parseLambda();
    LgsExpr* parsePrefixExpr();
    LgsExpr* parseEnvVar();
    LgsIterIndex* parseIterIndex(LgsExpr* baseExpr);
    LgsPostfixExpr* parsePostfixExpr(LgsExpr* baseExpr);
    LgsSelection* parseSelection(LgsExpr* firstExpr);
    LgsMetaSelection* parseMetaSelection(LgsExpr* baseExpr);

    void parseArgs(LgsInstance* instance);
    void parsePackageString(LgsImportPkg& pkg, const LgsToken& importToken);
    void parseImports();

    void setLocation(LgsLocation& location, const LgsToken* startToken, const LgsToken* endToken) const;
    void extractStrParts(LgsStrConst* strConst);
    std::pair<size_t, size_t> extractMatDims(const LgsToken& matToken);
    void validateTestFolder(const LgsFile* testFile);
    LgsExpr* determineIntConst(const std::string& tokenStr, int base) const;
    static int getBinOpPrecedence(LgsBinOpType opType);

    // Parser
    bool isEOF();
    void reset(size_t index);
    LgsToken consume(size_t times = 1);
    LgsToken peek(size_t i = 1);
    bool matchAndConsume(LgsTokenType token);
    bool matchOrReset(LgsTokenType t2, size_t resetIndex);
    bool mustMatch(LgsTokenType t2);
    bool mustParse(const void* value);
    bool parsedOrReset(const void* value, size_t resetIndex);
    bool validateTypeName(const std::string& typeName, const LgsLocation* location);
    void addError(const LgsBaseMsg& lgsErr, const LgsLocation& location, const std::vector<std::string>& args = {});
    void addParsingError(const LgsLocation* location = nullptr);
    void recursionGuard();
};
