
// Generated from Logos.g4 by ANTLR 4.13.2



#include "LogosParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct LogosParserStaticData final {
  LogosParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LogosParserStaticData(const LogosParserStaticData&) = delete;
  LogosParserStaticData(LogosParserStaticData&&) = delete;
  LogosParserStaticData& operator=(const LogosParserStaticData&) = delete;
  LogosParserStaticData& operator=(LogosParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag logosParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<LogosParserStaticData> logosParserStaticData = nullptr;

void logosParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (logosParserStaticData != nullptr) {
    return;
  }
#else
  assert(logosParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<LogosParserStaticData>(
    std::vector<std::string>{
      "logosFile", "mainFile", "interfaceFile", "objectFile", "importStatement", 
      "importPath", "objectDeclaration", "interfaceDeclaration", "objectImplements", 
      "funcSignature", "funcImplementation", "funcBody", "funcCall", "constructorCall", 
      "explicitVarDecList", "explicitVarDec", "implicitVarDec", "funcArg", 
      "funcArgList", "statement", "enumDeclaration", "enumField", "statementsBlock", 
      "exprList", "expr", "unaryExpr", "constant", "selection", "ifStatement", 
      "elseStatement", "patternMatching", "pattern", "loopStatement", "range", 
      "controlFlowStatement"
    },
    std::vector<std::string>{
      "", "'=='", "'>='", "'<='", "'('", "')'", "'{'", "'}'", "'['", "']'", 
      "'<'", "'>'", "','", "'..'", "'.'", "':'", "'='", "'-'", "'+'", "'*'", 
      "'/'", "'#'", "'\\u003F'", "'!'", "'%'", "'$'", "'&'", "'object'", 
      "'interface'", "'enum'", "'implements'", "'import'", "'if'", "'else'", 
      "'for'", "'break'", "'continue'", "'return'", "'and'", "'or'", "'not'", 
      "'in'"
    },
    std::vector<std::string>{
      "", "DOUBLE_EQUAL", "GE", "LE", "LPAREN", "RPAREN", "LBRACE", "RBRACE", 
      "LBRACK", "RBRACK", "LANGLE", "RANGLE", "COMMA", "DOUBLE_DOT", "DOT", 
      "COLON", "EQUAL", "MINUS", "PLUS", "STAR", "SLASH", "HASH", "QUEST_MARK", 
      "EXCLA_MARK", "PERCENT", "DOLLAR", "AMPERSAND", "OBJECT", "INTERFACE", 
      "ENUM", "IMPLEMENTS", "IMPORT", "IF", "ELSE", "FOR", "BREAK", "CONTINUE", 
      "RETURN", "AND", "OR", "NOT", "IN", "INTEGER", "FLOAT", "BOOL", "CONST", 
      "TYPE", "VARIABLE", "STRING", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,393,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,1,0,3,
  	0,72,8,0,1,0,1,0,1,0,3,0,77,8,0,1,1,1,1,3,1,81,8,1,1,1,4,1,84,8,1,11,
  	1,12,1,85,1,1,1,1,1,2,1,2,3,2,92,8,2,1,2,5,2,95,8,2,10,2,12,2,98,9,2,
  	1,2,4,2,101,8,2,11,2,12,2,102,1,2,5,2,106,8,2,10,2,12,2,109,9,2,1,2,1,
  	2,1,3,1,3,3,3,115,8,3,1,3,5,3,118,8,3,10,3,12,3,121,9,3,1,3,5,3,124,8,
  	3,10,3,12,3,127,9,3,1,3,1,3,1,4,1,4,1,4,5,4,134,8,4,10,4,12,4,137,9,4,
  	1,4,1,4,1,5,1,5,1,5,5,5,144,8,5,10,5,12,5,147,9,5,1,6,1,6,1,6,1,6,1,7,
  	1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,9,1,9,1,9,3,9,164,8,9,1,9,1,9,1,9,3,9,169,
  	8,9,1,10,1,10,1,10,1,11,1,11,1,12,1,12,1,12,3,12,179,8,12,1,12,1,12,1,
  	13,1,13,1,13,3,13,186,8,13,1,13,1,13,1,14,1,14,1,14,5,14,193,8,14,10,
  	14,12,14,196,9,14,1,14,3,14,199,8,14,1,15,1,15,1,15,1,15,1,15,3,15,206,
  	8,15,1,15,3,15,209,8,15,1,16,1,16,1,16,3,16,214,8,16,1,17,1,17,3,17,218,
  	8,17,1,17,1,17,1,18,1,18,1,18,5,18,225,8,18,10,18,12,18,228,9,18,1,18,
  	3,18,231,8,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,240,8,19,1,20,1,
  	20,1,20,1,20,5,20,246,8,20,10,20,12,20,249,9,20,1,20,1,20,1,21,1,21,1,
  	21,3,21,256,8,21,1,22,1,22,5,22,260,8,22,10,22,12,22,263,9,22,1,22,1,
  	22,1,23,1,23,1,23,5,23,270,8,23,10,23,12,23,273,9,23,1,23,3,23,276,8,
  	23,1,24,1,24,1,24,1,24,1,24,1,24,3,24,284,8,24,1,24,1,24,1,24,1,24,1,
  	24,1,24,1,24,1,24,1,24,5,24,295,8,24,10,24,12,24,298,9,24,1,25,1,25,1,
  	25,1,25,3,25,304,8,25,1,26,1,26,1,27,1,27,1,27,5,27,311,8,27,10,27,12,
  	27,314,9,27,1,28,1,28,1,28,1,28,1,28,1,28,3,28,322,8,28,1,29,1,29,1,29,
  	1,29,5,29,328,8,29,10,29,12,29,331,9,29,1,29,1,29,3,29,335,8,29,1,30,
  	1,30,3,30,339,8,30,1,30,1,30,5,30,343,8,30,10,30,12,30,346,9,30,1,30,
  	1,30,1,30,3,30,351,8,30,1,30,1,30,1,31,1,31,1,31,1,31,1,32,1,32,3,32,
  	361,8,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,
  	1,32,3,32,376,8,32,1,33,3,33,379,8,33,1,33,1,33,1,33,1,34,1,34,1,34,1,
  	34,1,34,1,34,1,34,3,34,391,8,34,1,34,0,1,48,35,0,2,4,6,8,10,12,14,16,
  	18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,
  	64,66,68,0,4,1,0,19,20,1,0,17,18,2,0,1,3,10,11,2,0,42,44,48,48,416,0,
  	71,1,0,0,0,2,80,1,0,0,0,4,89,1,0,0,0,6,112,1,0,0,0,8,130,1,0,0,0,10,140,
  	1,0,0,0,12,148,1,0,0,0,14,152,1,0,0,0,16,156,1,0,0,0,18,160,1,0,0,0,20,
  	170,1,0,0,0,22,173,1,0,0,0,24,175,1,0,0,0,26,182,1,0,0,0,28,189,1,0,0,
  	0,30,208,1,0,0,0,32,210,1,0,0,0,34,217,1,0,0,0,36,221,1,0,0,0,38,239,
  	1,0,0,0,40,241,1,0,0,0,42,252,1,0,0,0,44,257,1,0,0,0,46,266,1,0,0,0,48,
  	283,1,0,0,0,50,303,1,0,0,0,52,305,1,0,0,0,54,307,1,0,0,0,56,321,1,0,0,
  	0,58,329,1,0,0,0,60,336,1,0,0,0,62,354,1,0,0,0,64,375,1,0,0,0,66,378,
  	1,0,0,0,68,390,1,0,0,0,70,72,3,8,4,0,71,70,1,0,0,0,71,72,1,0,0,0,72,76,
  	1,0,0,0,73,77,3,2,1,0,74,77,3,6,3,0,75,77,3,4,2,0,76,73,1,0,0,0,76,74,
  	1,0,0,0,76,75,1,0,0,0,77,1,1,0,0,0,78,81,3,30,15,0,79,81,3,32,16,0,80,
  	78,1,0,0,0,80,79,1,0,0,0,80,81,1,0,0,0,81,83,1,0,0,0,82,84,3,20,10,0,
  	83,82,1,0,0,0,84,85,1,0,0,0,85,83,1,0,0,0,85,86,1,0,0,0,86,87,1,0,0,0,
  	87,88,5,0,0,1,88,3,1,0,0,0,89,91,3,14,7,0,90,92,3,16,8,0,91,90,1,0,0,
  	0,91,92,1,0,0,0,92,96,1,0,0,0,93,95,3,30,15,0,94,93,1,0,0,0,95,98,1,0,
  	0,0,96,94,1,0,0,0,96,97,1,0,0,0,97,100,1,0,0,0,98,96,1,0,0,0,99,101,3,
  	18,9,0,100,99,1,0,0,0,101,102,1,0,0,0,102,100,1,0,0,0,102,103,1,0,0,0,
  	103,107,1,0,0,0,104,106,3,20,10,0,105,104,1,0,0,0,106,109,1,0,0,0,107,
  	105,1,0,0,0,107,108,1,0,0,0,108,110,1,0,0,0,109,107,1,0,0,0,110,111,5,
  	0,0,1,111,5,1,0,0,0,112,114,3,12,6,0,113,115,3,16,8,0,114,113,1,0,0,0,
  	114,115,1,0,0,0,115,119,1,0,0,0,116,118,3,30,15,0,117,116,1,0,0,0,118,
  	121,1,0,0,0,119,117,1,0,0,0,119,120,1,0,0,0,120,125,1,0,0,0,121,119,1,
  	0,0,0,122,124,3,20,10,0,123,122,1,0,0,0,124,127,1,0,0,0,125,123,1,0,0,
  	0,125,126,1,0,0,0,126,128,1,0,0,0,127,125,1,0,0,0,128,129,5,0,0,1,129,
  	7,1,0,0,0,130,131,5,31,0,0,131,135,5,4,0,0,132,134,3,10,5,0,133,132,1,
  	0,0,0,134,137,1,0,0,0,135,133,1,0,0,0,135,136,1,0,0,0,136,138,1,0,0,0,
  	137,135,1,0,0,0,138,139,5,5,0,0,139,9,1,0,0,0,140,145,5,46,0,0,141,142,
  	5,14,0,0,142,144,5,46,0,0,143,141,1,0,0,0,144,147,1,0,0,0,145,143,1,0,
  	0,0,145,146,1,0,0,0,146,11,1,0,0,0,147,145,1,0,0,0,148,149,5,27,0,0,149,
  	150,5,15,0,0,150,151,5,46,0,0,151,13,1,0,0,0,152,153,5,28,0,0,153,154,
  	5,15,0,0,154,155,5,46,0,0,155,15,1,0,0,0,156,157,5,30,0,0,157,158,5,15,
  	0,0,158,159,5,46,0,0,159,17,1,0,0,0,160,161,5,47,0,0,161,163,5,4,0,0,
  	162,164,3,28,14,0,163,162,1,0,0,0,163,164,1,0,0,0,164,165,1,0,0,0,165,
  	168,5,5,0,0,166,167,5,15,0,0,167,169,5,46,0,0,168,166,1,0,0,0,168,169,
  	1,0,0,0,169,19,1,0,0,0,170,171,3,18,9,0,171,172,3,22,11,0,172,21,1,0,
  	0,0,173,174,3,44,22,0,174,23,1,0,0,0,175,176,5,47,0,0,176,178,5,4,0,0,
  	177,179,3,36,18,0,178,177,1,0,0,0,178,179,1,0,0,0,179,180,1,0,0,0,180,
  	181,5,5,0,0,181,25,1,0,0,0,182,183,5,46,0,0,183,185,5,4,0,0,184,186,3,
  	36,18,0,185,184,1,0,0,0,185,186,1,0,0,0,186,187,1,0,0,0,187,188,5,5,0,
  	0,188,27,1,0,0,0,189,194,3,30,15,0,190,191,5,12,0,0,191,193,3,30,15,0,
  	192,190,1,0,0,0,193,196,1,0,0,0,194,192,1,0,0,0,194,195,1,0,0,0,195,198,
  	1,0,0,0,196,194,1,0,0,0,197,199,5,12,0,0,198,197,1,0,0,0,198,199,1,0,
  	0,0,199,29,1,0,0,0,200,201,5,47,0,0,201,202,5,15,0,0,202,205,5,46,0,0,
  	203,204,5,16,0,0,204,206,3,48,24,0,205,203,1,0,0,0,205,206,1,0,0,0,206,
  	209,1,0,0,0,207,209,3,40,20,0,208,200,1,0,0,0,208,207,1,0,0,0,209,31,
  	1,0,0,0,210,213,5,47,0,0,211,212,5,16,0,0,212,214,3,48,24,0,213,211,1,
  	0,0,0,213,214,1,0,0,0,214,33,1,0,0,0,215,216,5,47,0,0,216,218,5,16,0,
  	0,217,215,1,0,0,0,217,218,1,0,0,0,218,219,1,0,0,0,219,220,3,48,24,0,220,
  	35,1,0,0,0,221,226,3,34,17,0,222,223,5,12,0,0,223,225,3,34,17,0,224,222,
  	1,0,0,0,225,228,1,0,0,0,226,224,1,0,0,0,226,227,1,0,0,0,227,230,1,0,0,
  	0,228,226,1,0,0,0,229,231,5,12,0,0,230,229,1,0,0,0,230,231,1,0,0,0,231,
  	37,1,0,0,0,232,240,3,30,15,0,233,240,3,32,16,0,234,240,3,56,28,0,235,
  	240,3,64,32,0,236,240,3,68,34,0,237,240,3,40,20,0,238,240,3,24,12,0,239,
  	232,1,0,0,0,239,233,1,0,0,0,239,234,1,0,0,0,239,235,1,0,0,0,239,236,1,
  	0,0,0,239,237,1,0,0,0,239,238,1,0,0,0,240,39,1,0,0,0,241,242,5,29,0,0,
  	242,243,5,46,0,0,243,247,5,6,0,0,244,246,3,42,21,0,245,244,1,0,0,0,246,
  	249,1,0,0,0,247,245,1,0,0,0,247,248,1,0,0,0,248,250,1,0,0,0,249,247,1,
  	0,0,0,250,251,5,7,0,0,251,41,1,0,0,0,252,255,5,45,0,0,253,254,5,16,0,
  	0,254,256,5,48,0,0,255,253,1,0,0,0,255,256,1,0,0,0,256,43,1,0,0,0,257,
  	261,5,6,0,0,258,260,3,38,19,0,259,258,1,0,0,0,260,263,1,0,0,0,261,259,
  	1,0,0,0,261,262,1,0,0,0,262,264,1,0,0,0,263,261,1,0,0,0,264,265,5,7,0,
  	0,265,45,1,0,0,0,266,271,3,48,24,0,267,268,5,12,0,0,268,270,3,48,24,0,
  	269,267,1,0,0,0,270,273,1,0,0,0,271,269,1,0,0,0,271,272,1,0,0,0,272,275,
  	1,0,0,0,273,271,1,0,0,0,274,276,5,12,0,0,275,274,1,0,0,0,275,276,1,0,
  	0,0,276,47,1,0,0,0,277,278,6,24,-1,0,278,284,3,50,25,0,279,280,5,4,0,
  	0,280,281,3,48,24,0,281,282,5,5,0,0,282,284,1,0,0,0,283,277,1,0,0,0,283,
  	279,1,0,0,0,284,296,1,0,0,0,285,286,10,5,0,0,286,287,7,0,0,0,287,295,
  	3,48,24,6,288,289,10,4,0,0,289,290,7,1,0,0,290,295,3,48,24,5,291,292,
  	10,3,0,0,292,293,7,2,0,0,293,295,3,48,24,4,294,285,1,0,0,0,294,288,1,
  	0,0,0,294,291,1,0,0,0,295,298,1,0,0,0,296,294,1,0,0,0,296,297,1,0,0,0,
  	297,49,1,0,0,0,298,296,1,0,0,0,299,304,3,24,12,0,300,304,3,26,13,0,301,
  	304,3,52,26,0,302,304,5,47,0,0,303,299,1,0,0,0,303,300,1,0,0,0,303,301,
  	1,0,0,0,303,302,1,0,0,0,304,51,1,0,0,0,305,306,7,3,0,0,306,53,1,0,0,0,
  	307,312,3,50,25,0,308,309,5,14,0,0,309,311,3,50,25,0,310,308,1,0,0,0,
  	311,314,1,0,0,0,312,310,1,0,0,0,312,313,1,0,0,0,313,55,1,0,0,0,314,312,
  	1,0,0,0,315,316,5,32,0,0,316,317,3,48,24,0,317,318,3,44,22,0,318,319,
  	3,58,29,0,319,322,1,0,0,0,320,322,3,60,30,0,321,315,1,0,0,0,321,320,1,
  	0,0,0,322,57,1,0,0,0,323,324,5,33,0,0,324,325,3,48,24,0,325,326,3,44,
  	22,0,326,328,1,0,0,0,327,323,1,0,0,0,328,331,1,0,0,0,329,327,1,0,0,0,
  	329,330,1,0,0,0,330,334,1,0,0,0,331,329,1,0,0,0,332,333,5,33,0,0,333,
  	335,3,44,22,0,334,332,1,0,0,0,334,335,1,0,0,0,335,59,1,0,0,0,336,338,
  	5,32,0,0,337,339,3,48,24,0,338,337,1,0,0,0,338,339,1,0,0,0,339,340,1,
  	0,0,0,340,344,5,6,0,0,341,343,3,62,31,0,342,341,1,0,0,0,343,346,1,0,0,
  	0,344,342,1,0,0,0,344,345,1,0,0,0,345,350,1,0,0,0,346,344,1,0,0,0,347,
  	348,5,33,0,0,348,349,5,15,0,0,349,351,3,44,22,0,350,347,1,0,0,0,350,351,
  	1,0,0,0,351,352,1,0,0,0,352,353,5,7,0,0,353,61,1,0,0,0,354,355,3,48,24,
  	0,355,356,5,15,0,0,356,357,3,44,22,0,357,63,1,0,0,0,358,360,5,34,0,0,
  	359,361,3,48,24,0,360,359,1,0,0,0,360,361,1,0,0,0,361,362,1,0,0,0,362,
  	376,3,44,22,0,363,364,5,34,0,0,364,365,3,46,23,0,365,366,5,41,0,0,366,
  	367,3,48,24,0,367,368,3,44,22,0,368,376,1,0,0,0,369,370,5,34,0,0,370,
  	371,3,46,23,0,371,372,5,41,0,0,372,373,3,66,33,0,373,374,3,44,22,0,374,
  	376,1,0,0,0,375,358,1,0,0,0,375,363,1,0,0,0,375,369,1,0,0,0,376,65,1,
  	0,0,0,377,379,3,48,24,0,378,377,1,0,0,0,378,379,1,0,0,0,379,380,1,0,0,
  	0,380,381,5,13,0,0,381,382,3,48,24,0,382,67,1,0,0,0,383,384,5,35,0,0,
  	384,391,3,48,24,0,385,386,5,35,0,0,386,391,5,32,0,0,387,391,5,36,0,0,
  	388,389,5,37,0,0,389,391,3,48,24,0,390,383,1,0,0,0,390,385,1,0,0,0,390,
  	387,1,0,0,0,390,388,1,0,0,0,391,69,1,0,0,0,46,71,76,80,85,91,96,102,107,
  	114,119,125,135,145,163,168,178,185,194,198,205,208,213,217,226,230,239,
  	247,255,261,271,275,283,294,296,303,312,321,329,334,338,344,350,360,375,
  	378,390
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  logosParserStaticData = std::move(staticData);
}

}

LogosParser::LogosParser(TokenStream *input) : LogosParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

LogosParser::LogosParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  LogosParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *logosParserStaticData->atn, logosParserStaticData->decisionToDFA, logosParserStaticData->sharedContextCache, options);
}

LogosParser::~LogosParser() {
  delete _interpreter;
}

const atn::ATN& LogosParser::getATN() const {
  return *logosParserStaticData->atn;
}

std::string LogosParser::getGrammarFileName() const {
  return "Logos.g4";
}

const std::vector<std::string>& LogosParser::getRuleNames() const {
  return logosParserStaticData->ruleNames;
}

const dfa::Vocabulary& LogosParser::getVocabulary() const {
  return logosParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LogosParser::getSerializedATN() const {
  return logosParserStaticData->serializedATN;
}


//----------------- LogosFileContext ------------------------------------------------------------------

LogosParser::LogosFileContext::LogosFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::MainFileContext* LogosParser::LogosFileContext::mainFile() {
  return getRuleContext<LogosParser::MainFileContext>(0);
}

LogosParser::ObjectFileContext* LogosParser::LogosFileContext::objectFile() {
  return getRuleContext<LogosParser::ObjectFileContext>(0);
}

LogosParser::InterfaceFileContext* LogosParser::LogosFileContext::interfaceFile() {
  return getRuleContext<LogosParser::InterfaceFileContext>(0);
}

LogosParser::ImportStatementContext* LogosParser::LogosFileContext::importStatement() {
  return getRuleContext<LogosParser::ImportStatementContext>(0);
}


size_t LogosParser::LogosFileContext::getRuleIndex() const {
  return LogosParser::RuleLogosFile;
}


LogosParser::LogosFileContext* LogosParser::logosFile() {
  LogosFileContext *_localctx = _tracker.createInstance<LogosFileContext>(_ctx, getState());
  enterRule(_localctx, 0, LogosParser::RuleLogosFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPORT) {
      setState(70);
      importStatement();
    }
    setState(76);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::ENUM:
      case LogosParser::VARIABLE: {
        setState(73);
        mainFile();
        break;
      }

      case LogosParser::OBJECT: {
        setState(74);
        objectFile();
        break;
      }

      case LogosParser::INTERFACE: {
        setState(75);
        interfaceFile();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MainFileContext ------------------------------------------------------------------

LogosParser::MainFileContext::MainFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::MainFileContext::EOF() {
  return getToken(LogosParser::EOF, 0);
}

LogosParser::ExplicitVarDecContext* LogosParser::MainFileContext::explicitVarDec() {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(0);
}

LogosParser::ImplicitVarDecContext* LogosParser::MainFileContext::implicitVarDec() {
  return getRuleContext<LogosParser::ImplicitVarDecContext>(0);
}

std::vector<LogosParser::FuncImplementationContext *> LogosParser::MainFileContext::funcImplementation() {
  return getRuleContexts<LogosParser::FuncImplementationContext>();
}

LogosParser::FuncImplementationContext* LogosParser::MainFileContext::funcImplementation(size_t i) {
  return getRuleContext<LogosParser::FuncImplementationContext>(i);
}


size_t LogosParser::MainFileContext::getRuleIndex() const {
  return LogosParser::RuleMainFile;
}


LogosParser::MainFileContext* LogosParser::mainFile() {
  MainFileContext *_localctx = _tracker.createInstance<MainFileContext>(_ctx, getState());
  enterRule(_localctx, 2, LogosParser::RuleMainFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(78);
      explicitVarDec();
      break;
    }

    case 2: {
      setState(79);
      implicitVarDec();
      break;
    }

    default:
      break;
    }
    setState(83); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(82);
      funcImplementation();
      setState(85); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(87);
    match(LogosParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceFileContext ------------------------------------------------------------------

LogosParser::InterfaceFileContext::InterfaceFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::InterfaceDeclarationContext* LogosParser::InterfaceFileContext::interfaceDeclaration() {
  return getRuleContext<LogosParser::InterfaceDeclarationContext>(0);
}

tree::TerminalNode* LogosParser::InterfaceFileContext::EOF() {
  return getToken(LogosParser::EOF, 0);
}

LogosParser::ObjectImplementsContext* LogosParser::InterfaceFileContext::objectImplements() {
  return getRuleContext<LogosParser::ObjectImplementsContext>(0);
}

std::vector<LogosParser::ExplicitVarDecContext *> LogosParser::InterfaceFileContext::explicitVarDec() {
  return getRuleContexts<LogosParser::ExplicitVarDecContext>();
}

LogosParser::ExplicitVarDecContext* LogosParser::InterfaceFileContext::explicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(i);
}

std::vector<LogosParser::FuncSignatureContext *> LogosParser::InterfaceFileContext::funcSignature() {
  return getRuleContexts<LogosParser::FuncSignatureContext>();
}

LogosParser::FuncSignatureContext* LogosParser::InterfaceFileContext::funcSignature(size_t i) {
  return getRuleContext<LogosParser::FuncSignatureContext>(i);
}

std::vector<LogosParser::FuncImplementationContext *> LogosParser::InterfaceFileContext::funcImplementation() {
  return getRuleContexts<LogosParser::FuncImplementationContext>();
}

LogosParser::FuncImplementationContext* LogosParser::InterfaceFileContext::funcImplementation(size_t i) {
  return getRuleContext<LogosParser::FuncImplementationContext>(i);
}


size_t LogosParser::InterfaceFileContext::getRuleIndex() const {
  return LogosParser::RuleInterfaceFile;
}


LogosParser::InterfaceFileContext* LogosParser::interfaceFile() {
  InterfaceFileContext *_localctx = _tracker.createInstance<InterfaceFileContext>(_ctx, getState());
  enterRule(_localctx, 4, LogosParser::RuleInterfaceFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(89);
    interfaceDeclaration();
    setState(91);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(90);
      objectImplements();
    }
    setState(96);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(93);
        explicitVarDec(); 
      }
      setState(98);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
    setState(100); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(99);
              funcSignature();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(102); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(107);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(104);
      funcImplementation();
      setState(109);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(110);
    match(LogosParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectFileContext ------------------------------------------------------------------

LogosParser::ObjectFileContext::ObjectFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ObjectDeclarationContext* LogosParser::ObjectFileContext::objectDeclaration() {
  return getRuleContext<LogosParser::ObjectDeclarationContext>(0);
}

tree::TerminalNode* LogosParser::ObjectFileContext::EOF() {
  return getToken(LogosParser::EOF, 0);
}

LogosParser::ObjectImplementsContext* LogosParser::ObjectFileContext::objectImplements() {
  return getRuleContext<LogosParser::ObjectImplementsContext>(0);
}

std::vector<LogosParser::ExplicitVarDecContext *> LogosParser::ObjectFileContext::explicitVarDec() {
  return getRuleContexts<LogosParser::ExplicitVarDecContext>();
}

LogosParser::ExplicitVarDecContext* LogosParser::ObjectFileContext::explicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(i);
}

std::vector<LogosParser::FuncImplementationContext *> LogosParser::ObjectFileContext::funcImplementation() {
  return getRuleContexts<LogosParser::FuncImplementationContext>();
}

LogosParser::FuncImplementationContext* LogosParser::ObjectFileContext::funcImplementation(size_t i) {
  return getRuleContext<LogosParser::FuncImplementationContext>(i);
}


size_t LogosParser::ObjectFileContext::getRuleIndex() const {
  return LogosParser::RuleObjectFile;
}


LogosParser::ObjectFileContext* LogosParser::objectFile() {
  ObjectFileContext *_localctx = _tracker.createInstance<ObjectFileContext>(_ctx, getState());
  enterRule(_localctx, 6, LogosParser::RuleObjectFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(112);
    objectDeclaration();
    setState(114);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(113);
      objectImplements();
    }
    setState(119);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(116);
        explicitVarDec(); 
      }
      setState(121);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
    setState(125);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(122);
      funcImplementation();
      setState(127);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(128);
    match(LogosParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

LogosParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ImportStatementContext::IMPORT() {
  return getToken(LogosParser::IMPORT, 0);
}

tree::TerminalNode* LogosParser::ImportStatementContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::ImportStatementContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

std::vector<LogosParser::ImportPathContext *> LogosParser::ImportStatementContext::importPath() {
  return getRuleContexts<LogosParser::ImportPathContext>();
}

LogosParser::ImportPathContext* LogosParser::ImportStatementContext::importPath(size_t i) {
  return getRuleContext<LogosParser::ImportPathContext>(i);
}


size_t LogosParser::ImportStatementContext::getRuleIndex() const {
  return LogosParser::RuleImportStatement;
}


LogosParser::ImportStatementContext* LogosParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 8, LogosParser::RuleImportStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(130);
    match(LogosParser::IMPORT);
    setState(131);
    match(LogosParser::LPAREN);
    setState(135);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::TYPE) {
      setState(132);
      importPath();
      setState(137);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(138);
    match(LogosParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportPathContext ------------------------------------------------------------------

LogosParser::ImportPathContext::ImportPathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LogosParser::ImportPathContext::TYPE() {
  return getTokens(LogosParser::TYPE);
}

tree::TerminalNode* LogosParser::ImportPathContext::TYPE(size_t i) {
  return getToken(LogosParser::TYPE, i);
}

std::vector<tree::TerminalNode *> LogosParser::ImportPathContext::DOT() {
  return getTokens(LogosParser::DOT);
}

tree::TerminalNode* LogosParser::ImportPathContext::DOT(size_t i) {
  return getToken(LogosParser::DOT, i);
}


size_t LogosParser::ImportPathContext::getRuleIndex() const {
  return LogosParser::RuleImportPath;
}


LogosParser::ImportPathContext* LogosParser::importPath() {
  ImportPathContext *_localctx = _tracker.createInstance<ImportPathContext>(_ctx, getState());
  enterRule(_localctx, 10, LogosParser::RuleImportPath);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(140);
    match(LogosParser::TYPE);
    setState(145);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::DOT) {
      setState(141);
      match(LogosParser::DOT);
      setState(142);
      match(LogosParser::TYPE);
      setState(147);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectDeclarationContext ------------------------------------------------------------------

LogosParser::ObjectDeclarationContext::ObjectDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ObjectDeclarationContext::OBJECT() {
  return getToken(LogosParser::OBJECT, 0);
}

tree::TerminalNode* LogosParser::ObjectDeclarationContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::ObjectDeclarationContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}


size_t LogosParser::ObjectDeclarationContext::getRuleIndex() const {
  return LogosParser::RuleObjectDeclaration;
}


LogosParser::ObjectDeclarationContext* LogosParser::objectDeclaration() {
  ObjectDeclarationContext *_localctx = _tracker.createInstance<ObjectDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 12, LogosParser::RuleObjectDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    match(LogosParser::OBJECT);
    setState(149);
    match(LogosParser::COLON);
    setState(150);
    match(LogosParser::TYPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceDeclarationContext ------------------------------------------------------------------

LogosParser::InterfaceDeclarationContext::InterfaceDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::InterfaceDeclarationContext::INTERFACE() {
  return getToken(LogosParser::INTERFACE, 0);
}

tree::TerminalNode* LogosParser::InterfaceDeclarationContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::InterfaceDeclarationContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}


size_t LogosParser::InterfaceDeclarationContext::getRuleIndex() const {
  return LogosParser::RuleInterfaceDeclaration;
}


LogosParser::InterfaceDeclarationContext* LogosParser::interfaceDeclaration() {
  InterfaceDeclarationContext *_localctx = _tracker.createInstance<InterfaceDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 14, LogosParser::RuleInterfaceDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    match(LogosParser::INTERFACE);
    setState(153);
    match(LogosParser::COLON);
    setState(154);
    match(LogosParser::TYPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectImplementsContext ------------------------------------------------------------------

LogosParser::ObjectImplementsContext::ObjectImplementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ObjectImplementsContext::IMPLEMENTS() {
  return getToken(LogosParser::IMPLEMENTS, 0);
}

tree::TerminalNode* LogosParser::ObjectImplementsContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::ObjectImplementsContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}


size_t LogosParser::ObjectImplementsContext::getRuleIndex() const {
  return LogosParser::RuleObjectImplements;
}


LogosParser::ObjectImplementsContext* LogosParser::objectImplements() {
  ObjectImplementsContext *_localctx = _tracker.createInstance<ObjectImplementsContext>(_ctx, getState());
  enterRule(_localctx, 16, LogosParser::RuleObjectImplements);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    match(LogosParser::IMPLEMENTS);
    setState(157);
    match(LogosParser::COLON);
    setState(158);
    match(LogosParser::TYPE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncSignatureContext ------------------------------------------------------------------

LogosParser::FuncSignatureContext::FuncSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::FuncSignatureContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::FuncSignatureContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::FuncSignatureContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

LogosParser::ExplicitVarDecListContext* LogosParser::FuncSignatureContext::explicitVarDecList() {
  return getRuleContext<LogosParser::ExplicitVarDecListContext>(0);
}

tree::TerminalNode* LogosParser::FuncSignatureContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::FuncSignatureContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}


size_t LogosParser::FuncSignatureContext::getRuleIndex() const {
  return LogosParser::RuleFuncSignature;
}


LogosParser::FuncSignatureContext* LogosParser::funcSignature() {
  FuncSignatureContext *_localctx = _tracker.createInstance<FuncSignatureContext>(_ctx, getState());
  enterRule(_localctx, 18, LogosParser::RuleFuncSignature);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(LogosParser::VARIABLE);
    setState(161);
    match(LogosParser::LPAREN);
    setState(163);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ENUM

    || _la == LogosParser::VARIABLE) {
      setState(162);
      explicitVarDecList();
    }
    setState(165);
    match(LogosParser::RPAREN);
    setState(168);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(166);
      match(LogosParser::COLON);
      setState(167);
      match(LogosParser::TYPE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncImplementationContext ------------------------------------------------------------------

LogosParser::FuncImplementationContext::FuncImplementationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::FuncSignatureContext* LogosParser::FuncImplementationContext::funcSignature() {
  return getRuleContext<LogosParser::FuncSignatureContext>(0);
}

LogosParser::FuncBodyContext* LogosParser::FuncImplementationContext::funcBody() {
  return getRuleContext<LogosParser::FuncBodyContext>(0);
}


size_t LogosParser::FuncImplementationContext::getRuleIndex() const {
  return LogosParser::RuleFuncImplementation;
}


LogosParser::FuncImplementationContext* LogosParser::funcImplementation() {
  FuncImplementationContext *_localctx = _tracker.createInstance<FuncImplementationContext>(_ctx, getState());
  enterRule(_localctx, 20, LogosParser::RuleFuncImplementation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(170);
    funcSignature();
    setState(171);
    funcBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncBodyContext ------------------------------------------------------------------

LogosParser::FuncBodyContext::FuncBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::StatementsBlockContext* LogosParser::FuncBodyContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}


size_t LogosParser::FuncBodyContext::getRuleIndex() const {
  return LogosParser::RuleFuncBody;
}


LogosParser::FuncBodyContext* LogosParser::funcBody() {
  FuncBodyContext *_localctx = _tracker.createInstance<FuncBodyContext>(_ctx, getState());
  enterRule(_localctx, 22, LogosParser::RuleFuncBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(173);
    statementsBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncCallContext ------------------------------------------------------------------

LogosParser::FuncCallContext::FuncCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::FuncCallContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::FuncCallContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::FuncCallContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

LogosParser::FuncArgListContext* LogosParser::FuncCallContext::funcArgList() {
  return getRuleContext<LogosParser::FuncArgListContext>(0);
}


size_t LogosParser::FuncCallContext::getRuleIndex() const {
  return LogosParser::RuleFuncCall;
}


LogosParser::FuncCallContext* LogosParser::funcCall() {
  FuncCallContext *_localctx = _tracker.createInstance<FuncCallContext>(_ctx, getState());
  enterRule(_localctx, 24, LogosParser::RuleFuncCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    match(LogosParser::VARIABLE);
    setState(176);
    match(LogosParser::LPAREN);
    setState(178);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821392) != 0)) {
      setState(177);
      funcArgList();
    }
    setState(180);
    match(LogosParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructorCallContext ------------------------------------------------------------------

LogosParser::ConstructorCallContext::ConstructorCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ConstructorCallContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::ConstructorCallContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::ConstructorCallContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

LogosParser::FuncArgListContext* LogosParser::ConstructorCallContext::funcArgList() {
  return getRuleContext<LogosParser::FuncArgListContext>(0);
}


size_t LogosParser::ConstructorCallContext::getRuleIndex() const {
  return LogosParser::RuleConstructorCall;
}


LogosParser::ConstructorCallContext* LogosParser::constructorCall() {
  ConstructorCallContext *_localctx = _tracker.createInstance<ConstructorCallContext>(_ctx, getState());
  enterRule(_localctx, 26, LogosParser::RuleConstructorCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    match(LogosParser::TYPE);
    setState(183);
    match(LogosParser::LPAREN);
    setState(185);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821392) != 0)) {
      setState(184);
      funcArgList();
    }
    setState(187);
    match(LogosParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExplicitVarDecListContext ------------------------------------------------------------------

LogosParser::ExplicitVarDecListContext::ExplicitVarDecListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::ExplicitVarDecContext *> LogosParser::ExplicitVarDecListContext::explicitVarDec() {
  return getRuleContexts<LogosParser::ExplicitVarDecContext>();
}

LogosParser::ExplicitVarDecContext* LogosParser::ExplicitVarDecListContext::explicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::ExplicitVarDecListContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ExplicitVarDecListContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ExplicitVarDecListContext::getRuleIndex() const {
  return LogosParser::RuleExplicitVarDecList;
}


LogosParser::ExplicitVarDecListContext* LogosParser::explicitVarDecList() {
  ExplicitVarDecListContext *_localctx = _tracker.createInstance<ExplicitVarDecListContext>(_ctx, getState());
  enterRule(_localctx, 28, LogosParser::RuleExplicitVarDecList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(189);
    explicitVarDec();
    setState(194);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(190);
        match(LogosParser::COMMA);
        setState(191);
        explicitVarDec(); 
      }
      setState(196);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
    setState(198);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(197);
      match(LogosParser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExplicitVarDecContext ------------------------------------------------------------------

LogosParser::ExplicitVarDecContext::ExplicitVarDecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ExplicitVarDecContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::ExplicitVarDecContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::ExplicitVarDecContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::ExplicitVarDecContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::ExplicitVarDecContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

LogosParser::EnumDeclarationContext* LogosParser::ExplicitVarDecContext::enumDeclaration() {
  return getRuleContext<LogosParser::EnumDeclarationContext>(0);
}


size_t LogosParser::ExplicitVarDecContext::getRuleIndex() const {
  return LogosParser::RuleExplicitVarDec;
}


LogosParser::ExplicitVarDecContext* LogosParser::explicitVarDec() {
  ExplicitVarDecContext *_localctx = _tracker.createInstance<ExplicitVarDecContext>(_ctx, getState());
  enterRule(_localctx, 30, LogosParser::RuleExplicitVarDec);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(208);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::VARIABLE: {
        enterOuterAlt(_localctx, 1);
        setState(200);
        match(LogosParser::VARIABLE);
        setState(201);
        match(LogosParser::COLON);
        setState(202);
        match(LogosParser::TYPE);
        setState(205);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LogosParser::EQUAL) {
          setState(203);
          match(LogosParser::EQUAL);
          setState(204);
          expr(0);
        }
        break;
      }

      case LogosParser::ENUM: {
        enterOuterAlt(_localctx, 2);
        setState(207);
        enumDeclaration();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImplicitVarDecContext ------------------------------------------------------------------

LogosParser::ImplicitVarDecContext::ImplicitVarDecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ImplicitVarDecContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::ImplicitVarDecContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::ImplicitVarDecContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::ImplicitVarDecContext::getRuleIndex() const {
  return LogosParser::RuleImplicitVarDec;
}


LogosParser::ImplicitVarDecContext* LogosParser::implicitVarDec() {
  ImplicitVarDecContext *_localctx = _tracker.createInstance<ImplicitVarDecContext>(_ctx, getState());
  enterRule(_localctx, 32, LogosParser::RuleImplicitVarDec);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(210);
    match(LogosParser::VARIABLE);
    setState(213);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(211);
      match(LogosParser::EQUAL);
      setState(212);
      expr(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncArgContext ------------------------------------------------------------------

LogosParser::FuncArgContext::FuncArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ExprContext* LogosParser::FuncArgContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::FuncArgContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::FuncArgContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}


size_t LogosParser::FuncArgContext::getRuleIndex() const {
  return LogosParser::RuleFuncArg;
}


LogosParser::FuncArgContext* LogosParser::funcArg() {
  FuncArgContext *_localctx = _tracker.createInstance<FuncArgContext>(_ctx, getState());
  enterRule(_localctx, 34, LogosParser::RuleFuncArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(215);
      match(LogosParser::VARIABLE);
      setState(216);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(219);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncArgListContext ------------------------------------------------------------------

LogosParser::FuncArgListContext::FuncArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::FuncArgContext *> LogosParser::FuncArgListContext::funcArg() {
  return getRuleContexts<LogosParser::FuncArgContext>();
}

LogosParser::FuncArgContext* LogosParser::FuncArgListContext::funcArg(size_t i) {
  return getRuleContext<LogosParser::FuncArgContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::FuncArgListContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::FuncArgListContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::FuncArgListContext::getRuleIndex() const {
  return LogosParser::RuleFuncArgList;
}


LogosParser::FuncArgListContext* LogosParser::funcArgList() {
  FuncArgListContext *_localctx = _tracker.createInstance<FuncArgListContext>(_ctx, getState());
  enterRule(_localctx, 36, LogosParser::RuleFuncArgList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(221);
    funcArg();
    setState(226);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(222);
        match(LogosParser::COMMA);
        setState(223);
        funcArg(); 
      }
      setState(228);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
    setState(230);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(229);
      match(LogosParser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

LogosParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ExplicitVarDecContext* LogosParser::StatementContext::explicitVarDec() {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(0);
}

LogosParser::ImplicitVarDecContext* LogosParser::StatementContext::implicitVarDec() {
  return getRuleContext<LogosParser::ImplicitVarDecContext>(0);
}

LogosParser::IfStatementContext* LogosParser::StatementContext::ifStatement() {
  return getRuleContext<LogosParser::IfStatementContext>(0);
}

LogosParser::LoopStatementContext* LogosParser::StatementContext::loopStatement() {
  return getRuleContext<LogosParser::LoopStatementContext>(0);
}

LogosParser::ControlFlowStatementContext* LogosParser::StatementContext::controlFlowStatement() {
  return getRuleContext<LogosParser::ControlFlowStatementContext>(0);
}

LogosParser::EnumDeclarationContext* LogosParser::StatementContext::enumDeclaration() {
  return getRuleContext<LogosParser::EnumDeclarationContext>(0);
}

LogosParser::FuncCallContext* LogosParser::StatementContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}


size_t LogosParser::StatementContext::getRuleIndex() const {
  return LogosParser::RuleStatement;
}


LogosParser::StatementContext* LogosParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 38, LogosParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(239);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(232);
      explicitVarDec();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(233);
      implicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(234);
      ifStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(235);
      loopStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(236);
      controlFlowStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(237);
      enumDeclaration();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(238);
      funcCall();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumDeclarationContext ------------------------------------------------------------------

LogosParser::EnumDeclarationContext::EnumDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::EnumDeclarationContext::ENUM() {
  return getToken(LogosParser::ENUM, 0);
}

tree::TerminalNode* LogosParser::EnumDeclarationContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::EnumDeclarationContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

tree::TerminalNode* LogosParser::EnumDeclarationContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

std::vector<LogosParser::EnumFieldContext *> LogosParser::EnumDeclarationContext::enumField() {
  return getRuleContexts<LogosParser::EnumFieldContext>();
}

LogosParser::EnumFieldContext* LogosParser::EnumDeclarationContext::enumField(size_t i) {
  return getRuleContext<LogosParser::EnumFieldContext>(i);
}


size_t LogosParser::EnumDeclarationContext::getRuleIndex() const {
  return LogosParser::RuleEnumDeclaration;
}


LogosParser::EnumDeclarationContext* LogosParser::enumDeclaration() {
  EnumDeclarationContext *_localctx = _tracker.createInstance<EnumDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 40, LogosParser::RuleEnumDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(241);
    match(LogosParser::ENUM);
    setState(242);
    match(LogosParser::TYPE);
    setState(243);
    match(LogosParser::LBRACE);
    setState(247);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST) {
      setState(244);
      enumField();
      setState(249);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(250);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EnumFieldContext ------------------------------------------------------------------

LogosParser::EnumFieldContext::EnumFieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::EnumFieldContext::CONST() {
  return getToken(LogosParser::CONST, 0);
}

tree::TerminalNode* LogosParser::EnumFieldContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

tree::TerminalNode* LogosParser::EnumFieldContext::STRING() {
  return getToken(LogosParser::STRING, 0);
}


size_t LogosParser::EnumFieldContext::getRuleIndex() const {
  return LogosParser::RuleEnumField;
}


LogosParser::EnumFieldContext* LogosParser::enumField() {
  EnumFieldContext *_localctx = _tracker.createInstance<EnumFieldContext>(_ctx, getState());
  enterRule(_localctx, 42, LogosParser::RuleEnumField);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    match(LogosParser::CONST);
    setState(255);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(253);
      match(LogosParser::EQUAL);
      setState(254);
      match(LogosParser::STRING);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsBlockContext ------------------------------------------------------------------

LogosParser::StatementsBlockContext::StatementsBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::StatementsBlockContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

tree::TerminalNode* LogosParser::StatementsBlockContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

std::vector<LogosParser::StatementContext *> LogosParser::StatementsBlockContext::statement() {
  return getRuleContexts<LogosParser::StatementContext>();
}

LogosParser::StatementContext* LogosParser::StatementsBlockContext::statement(size_t i) {
  return getRuleContext<LogosParser::StatementContext>(i);
}


size_t LogosParser::StatementsBlockContext::getRuleIndex() const {
  return LogosParser::RuleStatementsBlock;
}


LogosParser::StatementsBlockContext* LogosParser::statementsBlock() {
  StatementsBlockContext *_localctx = _tracker.createInstance<StatementsBlockContext>(_ctx, getState());
  enterRule(_localctx, 44, LogosParser::RuleStatementsBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(257);
    match(LogosParser::LBRACE);
    setState(261);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 141000018231296) != 0)) {
      setState(258);
      statement();
      setState(263);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(264);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprListContext ------------------------------------------------------------------

LogosParser::ExprListContext::ExprListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::ExprContext *> LogosParser::ExprListContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::ExprListContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::ExprListContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ExprListContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ExprListContext::getRuleIndex() const {
  return LogosParser::RuleExprList;
}


LogosParser::ExprListContext* LogosParser::exprList() {
  ExprListContext *_localctx = _tracker.createInstance<ExprListContext>(_ctx, getState());
  enterRule(_localctx, 46, LogosParser::RuleExprList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(266);
    expr(0);
    setState(271);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(267);
        match(LogosParser::COMMA);
        setState(268);
        expr(0); 
      }
      setState(273);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    }
    setState(275);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(274);
      match(LogosParser::COMMA);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

LogosParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::UnaryExprContext* LogosParser::ExprContext::unaryExpr() {
  return getRuleContext<LogosParser::UnaryExprContext>(0);
}

tree::TerminalNode* LogosParser::ExprContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::ExprContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

std::vector<LogosParser::ExprContext *> LogosParser::ExprContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::ExprContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

tree::TerminalNode* LogosParser::ExprContext::STAR() {
  return getToken(LogosParser::STAR, 0);
}

tree::TerminalNode* LogosParser::ExprContext::SLASH() {
  return getToken(LogosParser::SLASH, 0);
}

tree::TerminalNode* LogosParser::ExprContext::PLUS() {
  return getToken(LogosParser::PLUS, 0);
}

tree::TerminalNode* LogosParser::ExprContext::MINUS() {
  return getToken(LogosParser::MINUS, 0);
}

tree::TerminalNode* LogosParser::ExprContext::DOUBLE_EQUAL() {
  return getToken(LogosParser::DOUBLE_EQUAL, 0);
}

tree::TerminalNode* LogosParser::ExprContext::LANGLE() {
  return getToken(LogosParser::LANGLE, 0);
}

tree::TerminalNode* LogosParser::ExprContext::RANGLE() {
  return getToken(LogosParser::RANGLE, 0);
}

tree::TerminalNode* LogosParser::ExprContext::GE() {
  return getToken(LogosParser::GE, 0);
}

tree::TerminalNode* LogosParser::ExprContext::LE() {
  return getToken(LogosParser::LE, 0);
}


size_t LogosParser::ExprContext::getRuleIndex() const {
  return LogosParser::RuleExpr;
}



LogosParser::ExprContext* LogosParser::expr() {
   return expr(0);
}

LogosParser::ExprContext* LogosParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LogosParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  LogosParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, LogosParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(283);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::INTEGER:
      case LogosParser::FLOAT:
      case LogosParser::BOOL:
      case LogosParser::TYPE:
      case LogosParser::VARIABLE:
      case LogosParser::STRING: {
        setState(278);
        unaryExpr();
        break;
      }

      case LogosParser::LPAREN: {
        setState(279);
        match(LogosParser::LPAREN);
        setState(280);
        antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
        setState(281);
        match(LogosParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(296);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(294);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(285);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(286);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == LogosParser::STAR

          || _la == LogosParser::SLASH)) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(287);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(288);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(289);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == LogosParser::MINUS

          || _la == LogosParser::PLUS)) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(290);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(291);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(292);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 3086) != 0))) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(293);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(298);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- UnaryExprContext ------------------------------------------------------------------

LogosParser::UnaryExprContext::UnaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::FuncCallContext* LogosParser::UnaryExprContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::ConstructorCallContext* LogosParser::UnaryExprContext::constructorCall() {
  return getRuleContext<LogosParser::ConstructorCallContext>(0);
}

LogosParser::ConstantContext* LogosParser::UnaryExprContext::constant() {
  return getRuleContext<LogosParser::ConstantContext>(0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}


size_t LogosParser::UnaryExprContext::getRuleIndex() const {
  return LogosParser::RuleUnaryExpr;
}


LogosParser::UnaryExprContext* LogosParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 50, LogosParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(303);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(299);
      funcCall();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(300);
      constructorCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(301);
      constant();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(302);
      match(LogosParser::VARIABLE);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

LogosParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ConstantContext::INTEGER() {
  return getToken(LogosParser::INTEGER, 0);
}

tree::TerminalNode* LogosParser::ConstantContext::FLOAT() {
  return getToken(LogosParser::FLOAT, 0);
}

tree::TerminalNode* LogosParser::ConstantContext::BOOL() {
  return getToken(LogosParser::BOOL, 0);
}

tree::TerminalNode* LogosParser::ConstantContext::STRING() {
  return getToken(LogosParser::STRING, 0);
}


size_t LogosParser::ConstantContext::getRuleIndex() const {
  return LogosParser::RuleConstant;
}


LogosParser::ConstantContext* LogosParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 52, LogosParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(305);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 312261302288384) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectionContext ------------------------------------------------------------------

LogosParser::SelectionContext::SelectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::UnaryExprContext *> LogosParser::SelectionContext::unaryExpr() {
  return getRuleContexts<LogosParser::UnaryExprContext>();
}

LogosParser::UnaryExprContext* LogosParser::SelectionContext::unaryExpr(size_t i) {
  return getRuleContext<LogosParser::UnaryExprContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::SelectionContext::DOT() {
  return getTokens(LogosParser::DOT);
}

tree::TerminalNode* LogosParser::SelectionContext::DOT(size_t i) {
  return getToken(LogosParser::DOT, i);
}


size_t LogosParser::SelectionContext::getRuleIndex() const {
  return LogosParser::RuleSelection;
}


LogosParser::SelectionContext* LogosParser::selection() {
  SelectionContext *_localctx = _tracker.createInstance<SelectionContext>(_ctx, getState());
  enterRule(_localctx, 54, LogosParser::RuleSelection);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(307);
    unaryExpr();
    setState(312);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::DOT) {
      setState(308);
      match(LogosParser::DOT);
      setState(309);
      unaryExpr();
      setState(314);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

LogosParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::IfStatementContext::IF() {
  return getToken(LogosParser::IF, 0);
}

LogosParser::ExprContext* LogosParser::IfStatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

LogosParser::StatementsBlockContext* LogosParser::IfStatementContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}

LogosParser::ElseStatementContext* LogosParser::IfStatementContext::elseStatement() {
  return getRuleContext<LogosParser::ElseStatementContext>(0);
}

LogosParser::PatternMatchingContext* LogosParser::IfStatementContext::patternMatching() {
  return getRuleContext<LogosParser::PatternMatchingContext>(0);
}


size_t LogosParser::IfStatementContext::getRuleIndex() const {
  return LogosParser::RuleIfStatement;
}


LogosParser::IfStatementContext* LogosParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, LogosParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(321);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(315);
      match(LogosParser::IF);
      setState(316);
      expr(0);
      setState(317);
      statementsBlock();
      setState(318);
      elseStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(320);
      patternMatching();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseStatementContext ------------------------------------------------------------------

LogosParser::ElseStatementContext::ElseStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LogosParser::ElseStatementContext::ELSE() {
  return getTokens(LogosParser::ELSE);
}

tree::TerminalNode* LogosParser::ElseStatementContext::ELSE(size_t i) {
  return getToken(LogosParser::ELSE, i);
}

std::vector<LogosParser::ExprContext *> LogosParser::ElseStatementContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::ElseStatementContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

std::vector<LogosParser::StatementsBlockContext *> LogosParser::ElseStatementContext::statementsBlock() {
  return getRuleContexts<LogosParser::StatementsBlockContext>();
}

LogosParser::StatementsBlockContext* LogosParser::ElseStatementContext::statementsBlock(size_t i) {
  return getRuleContext<LogosParser::StatementsBlockContext>(i);
}


size_t LogosParser::ElseStatementContext::getRuleIndex() const {
  return LogosParser::RuleElseStatement;
}


LogosParser::ElseStatementContext* LogosParser::elseStatement() {
  ElseStatementContext *_localctx = _tracker.createInstance<ElseStatementContext>(_ctx, getState());
  enterRule(_localctx, 58, LogosParser::RuleElseStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(329);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(323);
        match(LogosParser::ELSE);
        setState(324);
        expr(0);
        setState(325);
        statementsBlock(); 
      }
      setState(331);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    }
    setState(334);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(332);
      match(LogosParser::ELSE);
      setState(333);
      statementsBlock();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternMatchingContext ------------------------------------------------------------------

LogosParser::PatternMatchingContext::PatternMatchingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::PatternMatchingContext::IF() {
  return getToken(LogosParser::IF, 0);
}

tree::TerminalNode* LogosParser::PatternMatchingContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

tree::TerminalNode* LogosParser::PatternMatchingContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

LogosParser::ExprContext* LogosParser::PatternMatchingContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

std::vector<LogosParser::PatternContext *> LogosParser::PatternMatchingContext::pattern() {
  return getRuleContexts<LogosParser::PatternContext>();
}

LogosParser::PatternContext* LogosParser::PatternMatchingContext::pattern(size_t i) {
  return getRuleContext<LogosParser::PatternContext>(i);
}

tree::TerminalNode* LogosParser::PatternMatchingContext::ELSE() {
  return getToken(LogosParser::ELSE, 0);
}

tree::TerminalNode* LogosParser::PatternMatchingContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::StatementsBlockContext* LogosParser::PatternMatchingContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}


size_t LogosParser::PatternMatchingContext::getRuleIndex() const {
  return LogosParser::RulePatternMatching;
}


LogosParser::PatternMatchingContext* LogosParser::patternMatching() {
  PatternMatchingContext *_localctx = _tracker.createInstance<PatternMatchingContext>(_ctx, getState());
  enterRule(_localctx, 60, LogosParser::RulePatternMatching);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(336);
    match(LogosParser::IF);
    setState(338);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821392) != 0)) {
      setState(337);
      expr(0);
    }
    setState(340);
    match(LogosParser::LBRACE);
    setState(344);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821392) != 0)) {
      setState(341);
      pattern();
      setState(346);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(350);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(347);
      match(LogosParser::ELSE);
      setState(348);
      match(LogosParser::COLON);
      setState(349);
      statementsBlock();
    }
    setState(352);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternContext ------------------------------------------------------------------

LogosParser::PatternContext::PatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ExprContext* LogosParser::PatternContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::PatternContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::StatementsBlockContext* LogosParser::PatternContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}


size_t LogosParser::PatternContext::getRuleIndex() const {
  return LogosParser::RulePattern;
}


LogosParser::PatternContext* LogosParser::pattern() {
  PatternContext *_localctx = _tracker.createInstance<PatternContext>(_ctx, getState());
  enterRule(_localctx, 62, LogosParser::RulePattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(354);
    expr(0);
    setState(355);
    match(LogosParser::COLON);
    setState(356);
    statementsBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoopStatementContext ------------------------------------------------------------------

LogosParser::LoopStatementContext::LoopStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::LoopStatementContext::FOR() {
  return getToken(LogosParser::FOR, 0);
}

LogosParser::StatementsBlockContext* LogosParser::LoopStatementContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}

LogosParser::ExprContext* LogosParser::LoopStatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

LogosParser::ExprListContext* LogosParser::LoopStatementContext::exprList() {
  return getRuleContext<LogosParser::ExprListContext>(0);
}

tree::TerminalNode* LogosParser::LoopStatementContext::IN() {
  return getToken(LogosParser::IN, 0);
}

LogosParser::RangeContext* LogosParser::LoopStatementContext::range() {
  return getRuleContext<LogosParser::RangeContext>(0);
}


size_t LogosParser::LoopStatementContext::getRuleIndex() const {
  return LogosParser::RuleLoopStatement;
}


LogosParser::LoopStatementContext* LogosParser::loopStatement() {
  LoopStatementContext *_localctx = _tracker.createInstance<LoopStatementContext>(_ctx, getState());
  enterRule(_localctx, 64, LogosParser::RuleLoopStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(375);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(358);
      match(LogosParser::FOR);
      setState(360);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 523367534821392) != 0)) {
        setState(359);
        expr(0);
      }
      setState(362);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(363);
      match(LogosParser::FOR);
      setState(364);
      exprList();
      setState(365);
      match(LogosParser::IN);
      setState(366);
      expr(0);
      setState(367);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(369);
      match(LogosParser::FOR);
      setState(370);
      exprList();
      setState(371);
      match(LogosParser::IN);
      setState(372);
      range();
      setState(373);
      statementsBlock();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RangeContext ------------------------------------------------------------------

LogosParser::RangeContext::RangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::RangeContext::DOUBLE_DOT() {
  return getToken(LogosParser::DOUBLE_DOT, 0);
}

std::vector<LogosParser::ExprContext *> LogosParser::RangeContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::RangeContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}


size_t LogosParser::RangeContext::getRuleIndex() const {
  return LogosParser::RuleRange;
}


LogosParser::RangeContext* LogosParser::range() {
  RangeContext *_localctx = _tracker.createInstance<RangeContext>(_ctx, getState());
  enterRule(_localctx, 66, LogosParser::RuleRange);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(378);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821392) != 0)) {
      setState(377);
      expr(0);
    }
    setState(380);
    match(LogosParser::DOUBLE_DOT);
    setState(381);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ControlFlowStatementContext ------------------------------------------------------------------

LogosParser::ControlFlowStatementContext::ControlFlowStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ControlFlowStatementContext::BREAK() {
  return getToken(LogosParser::BREAK, 0);
}

LogosParser::ExprContext* LogosParser::ControlFlowStatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::ControlFlowStatementContext::IF() {
  return getToken(LogosParser::IF, 0);
}

tree::TerminalNode* LogosParser::ControlFlowStatementContext::CONTINUE() {
  return getToken(LogosParser::CONTINUE, 0);
}

tree::TerminalNode* LogosParser::ControlFlowStatementContext::RETURN() {
  return getToken(LogosParser::RETURN, 0);
}


size_t LogosParser::ControlFlowStatementContext::getRuleIndex() const {
  return LogosParser::RuleControlFlowStatement;
}


LogosParser::ControlFlowStatementContext* LogosParser::controlFlowStatement() {
  ControlFlowStatementContext *_localctx = _tracker.createInstance<ControlFlowStatementContext>(_ctx, getState());
  enterRule(_localctx, 68, LogosParser::RuleControlFlowStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(390);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(383);
      match(LogosParser::BREAK);
      setState(384);
      expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(385);
      match(LogosParser::BREAK);
      setState(386);
      match(LogosParser::IF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(387);
      match(LogosParser::CONTINUE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(388);
      match(LogosParser::RETURN);
      setState(389);
      expr(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool LogosParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 24: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LogosParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);
    case 2: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void LogosParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  logosParserInitialize();
#else
  ::antlr4::internal::call_once(logosParserOnceFlag, logosParserInitialize);
#endif
}
