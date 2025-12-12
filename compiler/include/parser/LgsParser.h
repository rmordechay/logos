#pragma once
#include "LgsBinaryTokens.h"
#include "LgsTokens.h"
#include "errors/LgsErrHandler.h"
#include "lgsc/LgsCCompiler.h"
#include "stmts/LgsAssignment.h"

class LgsJsonObject;
class LgsJsonArray;
class LgsMetaVar;
struct LgsImportPackage;
class LgsStmtsBlock;
class LgsMainFunc;
class LgsMap;
class LgsFuncType;
class LgsAppConfigFile;
struct LgsGlobals;
struct LgsFileMetadata;
class LgsMetaSelection;
class LgsMatrixExpr;
class LgsGenericType;
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
    LgsPaths& paths;
    bool headersOnly;
    LgsToken currentToken;
    size_t currentIndex = 0;
    size_t recursionCount = 0;
    std::vector<LgsToken> tokens;
    LgsFileMetadata* metadata = nullptr;
    LgsGlobals& globals;
    std::string code = "";
    LgsErrHandler errHandler;
    LgsFunc* currentFunc = nullptr;
    LgsCCompiler lgsCC;

    LgsParser(LgsFileMetadata* metadata, LgsPaths& paths, LgsGlobals& globals, const bool headersOnly = false)
        : paths(paths), headersOnly(headersOnly), metadata(metadata), globals(globals), lgsCC(paths) {
    }

    LgsParser(const std::string& code, LgsPaths& paths, LgsGlobals& globals, const bool headersOnly = false)
        : paths(paths), headersOnly(headersOnly), globals(globals), code(code), lgsCC(paths) {}

    // Files
    bool scanTokens();
    LgsFile* parseSrcFile(bool isTestRun);
    LgsFile* parseSrcFileHeaders();
    LgsMainFile* parseMainFile();
    LgsAppConfigFile* parseAppConfigFile();
    LgsObjectFile* parseObjectFile();
    LgsInterfaceFile* parseInterfaceFile();
    LgsEnvFile* parseEnvFile();
    LgsTestFile* parseTestFile();

    // Object
    LgsObject* parseObject();
    LgsInterface* parseInterface();
    LgsObject* parseObjectBody(const LgsToken& tokenName, bool isSingleton);
    LgsInterface* parseInterfaceBody(const LgsToken& tokenName);
    LgsField* parseField(size_t fieldPosition);
    LgsIOPair* parseIOPair();

    // Types
    LgsType* parseType();
    LgsEnum* parseEnum();
    LgsSubType* parseSubtype();
    LgsFuncType* parseFuncType();
    LgsMap* parseMapType();
    LgsGenericType* parseGenericType();
    std::vector<LgsType*> parseGenericArgs();

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
    LgsExpr* parseExpr(bool withLambda = true, bool withInstance = true);
    LgsExpr* parseExprWithPrecedence(int minPrecedence, bool withInstance = true);
    LgsExpr* parseUnary(bool withInstance = true);
    LgsExpr* parseExprOrLambda();
    LgsVariable* parseVariable();
    LgsInstance* parseInstance();
    LgsFuncCall* parseFuncCall();
    LgsStrConst* parseStrConst();
    LgsMetaVar* parseLoopMetaVar();
    LgsExpr* parseConstant();
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
    LgsMetaSelection* parseMetaSelection(LgsExpr* firstExpr);

    // JSON
    LgsJson* parseJson();
    LgsJson* parseJsonValue();
    LgsJson* parseJsonPrimitive();
    LgsJsonArray* parseJsonArray();
    LgsJsonObject* parseJsonObject();

    void parseArgs(LgsInstance* instance);
    void parsePackageString(LgsImportPackage& pkg, const LgsToken& importToken);
    void parseImports(std::vector<LgsStrConst*>& cImports);
    void parseCIncludes(std::vector<LgsStrConst*>& cImports);
    void parseCImports(std::vector<LgsStrConst*> externalImports, LgsFile* file);

    void setLocation(LgsLocation& location, const LgsToken* startToken, const LgsToken* endToken) const;
    void extractStrParts(LgsStrConst& strConst);
    void validateTestFolder(const LgsFile* testFile);
    bool isImportName(LgsExpr* expr) const;
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
    void addParsingError();
    bool validateTypeName(const std::string& typeName, const LgsLocation* location);
    void recursionGuard();
    void addError(const LgsBaseMsg& lgsErr, const LgsLocation& location, const std::vector<std::string>& args = {});
};
