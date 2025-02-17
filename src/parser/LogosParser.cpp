
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
      "logosFile", "mainFile", "objectFile", "interfaceFile", "importStatement", 
      "importPath", "objectDeclaration", "interfaceDeclaration", "objectImplements", 
      "funcSignature", "funcImplementation", "funcBody", "paramList", "explicitVarDec", 
      "implicitVarDec", "fieldDef", "funcArg", "funcArgList", "statement", 
      "enumDeclaration", "enumField", "statementsBlock", "exprList", "expr", 
      "unaryExpr", "funcCall", "array", "constructor", "constant", "arrayIndex", 
      "selectionElement", "selection", "ifStatement", "elseStatement", "patternMatching", 
      "pattern", "loopStatement", "controlFlow", "returnStatement", "range"
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
  	4,1,51,441,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,1,0,3,0,82,8,0,1,0,1,0,1,0,
  	3,0,87,8,0,1,1,4,1,90,8,1,11,1,12,1,91,1,1,1,1,1,2,1,2,3,2,98,8,2,1,2,
  	5,2,101,8,2,10,2,12,2,104,9,2,1,2,5,2,107,8,2,10,2,12,2,110,9,2,1,2,1,
  	2,1,3,1,3,3,3,116,8,3,1,3,5,3,119,8,3,10,3,12,3,122,9,3,1,3,4,3,125,8,
  	3,11,3,12,3,126,1,3,5,3,130,8,3,10,3,12,3,133,9,3,1,3,1,3,1,4,1,4,1,4,
  	5,4,140,8,4,10,4,12,4,143,9,4,1,4,1,4,1,5,1,5,1,5,5,5,150,8,5,10,5,12,
  	5,153,9,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,9,1,9,1,9,
  	3,9,170,8,9,1,9,1,9,1,9,3,9,175,8,9,1,10,1,10,1,10,1,11,1,11,1,12,1,12,
  	1,12,5,12,185,8,12,10,12,12,12,188,9,12,1,12,3,12,191,8,12,1,13,1,13,
  	1,13,1,13,1,13,3,13,198,8,13,1,14,1,14,1,14,1,14,1,15,1,15,1,15,5,15,
  	207,8,15,10,15,12,15,210,9,15,1,15,1,15,1,15,1,16,1,16,3,16,217,8,16,
  	1,16,1,16,1,17,1,17,1,17,5,17,224,8,17,10,17,12,17,227,9,17,1,17,3,17,
  	230,8,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,3,18,241,8,18,1,
  	19,1,19,1,19,1,19,5,19,247,8,19,10,19,12,19,250,9,19,1,19,1,19,1,20,1,
  	20,1,20,3,20,257,8,20,1,21,1,21,5,21,261,8,21,10,21,12,21,264,9,21,1,
  	21,1,21,1,22,1,22,1,22,5,22,271,8,22,10,22,12,22,274,9,22,1,22,3,22,277,
  	8,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,3,23,286,8,23,1,23,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,5,23,297,8,23,10,23,12,23,300,9,23,1,24,
  	1,24,1,24,1,24,1,24,1,24,3,24,308,8,24,1,25,1,25,1,25,3,25,313,8,25,1,
  	25,1,25,1,26,1,26,1,26,1,26,5,26,321,8,26,10,26,12,26,324,9,26,1,26,1,
  	26,1,27,1,27,1,27,3,27,331,8,27,1,27,1,27,1,28,1,28,1,29,1,29,3,29,339,
  	8,29,1,29,1,29,1,29,1,29,4,29,345,8,29,11,29,12,29,346,1,30,1,30,1,30,
  	1,30,3,30,353,8,30,1,31,1,31,1,31,5,31,358,8,31,10,31,12,31,361,9,31,
  	1,32,1,32,1,32,1,32,1,32,1,32,3,32,369,8,32,1,33,1,33,1,33,1,33,5,33,
  	375,8,33,10,33,12,33,378,9,33,1,33,1,33,3,33,382,8,33,1,34,1,34,3,34,
  	386,8,34,1,34,1,34,5,34,390,8,34,10,34,12,34,393,9,34,1,34,1,34,1,34,
  	3,34,398,8,34,1,34,1,34,1,35,1,35,1,35,1,35,1,36,1,36,3,36,408,8,36,1,
  	36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,423,
  	8,36,1,37,1,37,1,37,1,37,1,37,3,37,430,8,37,1,38,1,38,1,38,1,39,3,39,
  	436,8,39,1,39,1,39,1,39,1,39,0,1,46,40,0,2,4,6,8,10,12,14,16,18,20,22,
  	24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,
  	70,72,74,76,78,0,4,1,0,19,20,1,0,17,18,2,0,1,3,10,11,2,0,42,44,48,48,
  	466,0,86,1,0,0,0,2,89,1,0,0,0,4,95,1,0,0,0,6,113,1,0,0,0,8,136,1,0,0,
  	0,10,146,1,0,0,0,12,154,1,0,0,0,14,158,1,0,0,0,16,162,1,0,0,0,18,166,
  	1,0,0,0,20,176,1,0,0,0,22,179,1,0,0,0,24,181,1,0,0,0,26,192,1,0,0,0,28,
  	199,1,0,0,0,30,203,1,0,0,0,32,216,1,0,0,0,34,220,1,0,0,0,36,240,1,0,0,
  	0,38,242,1,0,0,0,40,253,1,0,0,0,42,258,1,0,0,0,44,267,1,0,0,0,46,285,
  	1,0,0,0,48,307,1,0,0,0,50,309,1,0,0,0,52,316,1,0,0,0,54,327,1,0,0,0,56,
  	334,1,0,0,0,58,338,1,0,0,0,60,352,1,0,0,0,62,354,1,0,0,0,64,368,1,0,0,
  	0,66,376,1,0,0,0,68,383,1,0,0,0,70,401,1,0,0,0,72,422,1,0,0,0,74,429,
  	1,0,0,0,76,431,1,0,0,0,78,435,1,0,0,0,80,82,3,8,4,0,81,80,1,0,0,0,81,
  	82,1,0,0,0,82,83,1,0,0,0,83,87,3,2,1,0,84,87,3,4,2,0,85,87,3,6,3,0,86,
  	81,1,0,0,0,86,84,1,0,0,0,86,85,1,0,0,0,87,1,1,0,0,0,88,90,3,20,10,0,89,
  	88,1,0,0,0,90,91,1,0,0,0,91,89,1,0,0,0,91,92,1,0,0,0,92,93,1,0,0,0,93,
  	94,5,0,0,1,94,3,1,0,0,0,95,97,3,12,6,0,96,98,3,16,8,0,97,96,1,0,0,0,97,
  	98,1,0,0,0,98,102,1,0,0,0,99,101,3,26,13,0,100,99,1,0,0,0,101,104,1,0,
  	0,0,102,100,1,0,0,0,102,103,1,0,0,0,103,108,1,0,0,0,104,102,1,0,0,0,105,
  	107,3,20,10,0,106,105,1,0,0,0,107,110,1,0,0,0,108,106,1,0,0,0,108,109,
  	1,0,0,0,109,111,1,0,0,0,110,108,1,0,0,0,111,112,5,0,0,1,112,5,1,0,0,0,
  	113,115,3,14,7,0,114,116,3,16,8,0,115,114,1,0,0,0,115,116,1,0,0,0,116,
  	120,1,0,0,0,117,119,3,26,13,0,118,117,1,0,0,0,119,122,1,0,0,0,120,118,
  	1,0,0,0,120,121,1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,0,123,125,3,18,
  	9,0,124,123,1,0,0,0,125,126,1,0,0,0,126,124,1,0,0,0,126,127,1,0,0,0,127,
  	131,1,0,0,0,128,130,3,20,10,0,129,128,1,0,0,0,130,133,1,0,0,0,131,129,
  	1,0,0,0,131,132,1,0,0,0,132,134,1,0,0,0,133,131,1,0,0,0,134,135,5,0,0,
  	1,135,7,1,0,0,0,136,137,5,31,0,0,137,141,5,4,0,0,138,140,3,10,5,0,139,
  	138,1,0,0,0,140,143,1,0,0,0,141,139,1,0,0,0,141,142,1,0,0,0,142,144,1,
  	0,0,0,143,141,1,0,0,0,144,145,5,5,0,0,145,9,1,0,0,0,146,151,5,46,0,0,
  	147,148,5,14,0,0,148,150,5,46,0,0,149,147,1,0,0,0,150,153,1,0,0,0,151,
  	149,1,0,0,0,151,152,1,0,0,0,152,11,1,0,0,0,153,151,1,0,0,0,154,155,5,
  	27,0,0,155,156,5,15,0,0,156,157,5,46,0,0,157,13,1,0,0,0,158,159,5,28,
  	0,0,159,160,5,15,0,0,160,161,5,46,0,0,161,15,1,0,0,0,162,163,5,30,0,0,
  	163,164,5,15,0,0,164,165,5,46,0,0,165,17,1,0,0,0,166,167,5,47,0,0,167,
  	169,5,4,0,0,168,170,3,24,12,0,169,168,1,0,0,0,169,170,1,0,0,0,170,171,
  	1,0,0,0,171,174,5,5,0,0,172,173,5,15,0,0,173,175,5,46,0,0,174,172,1,0,
  	0,0,174,175,1,0,0,0,175,19,1,0,0,0,176,177,3,18,9,0,177,178,3,22,11,0,
  	178,21,1,0,0,0,179,180,3,42,21,0,180,23,1,0,0,0,181,186,3,26,13,0,182,
  	183,5,12,0,0,183,185,3,26,13,0,184,182,1,0,0,0,185,188,1,0,0,0,186,184,
  	1,0,0,0,186,187,1,0,0,0,187,190,1,0,0,0,188,186,1,0,0,0,189,191,5,12,
  	0,0,190,189,1,0,0,0,190,191,1,0,0,0,191,25,1,0,0,0,192,193,5,47,0,0,193,
  	194,5,15,0,0,194,197,5,46,0,0,195,196,5,16,0,0,196,198,3,46,23,0,197,
  	195,1,0,0,0,197,198,1,0,0,0,198,27,1,0,0,0,199,200,5,47,0,0,200,201,5,
  	16,0,0,201,202,3,46,23,0,202,29,1,0,0,0,203,204,5,47,0,0,204,208,5,14,
  	0,0,205,207,5,47,0,0,206,205,1,0,0,0,207,210,1,0,0,0,208,206,1,0,0,0,
  	208,209,1,0,0,0,209,211,1,0,0,0,210,208,1,0,0,0,211,212,5,16,0,0,212,
  	213,3,46,23,0,213,31,1,0,0,0,214,215,5,47,0,0,215,217,5,16,0,0,216,214,
  	1,0,0,0,216,217,1,0,0,0,217,218,1,0,0,0,218,219,3,46,23,0,219,33,1,0,
  	0,0,220,225,3,32,16,0,221,222,5,12,0,0,222,224,3,32,16,0,223,221,1,0,
  	0,0,224,227,1,0,0,0,225,223,1,0,0,0,225,226,1,0,0,0,226,229,1,0,0,0,227,
  	225,1,0,0,0,228,230,5,12,0,0,229,228,1,0,0,0,229,230,1,0,0,0,230,35,1,
  	0,0,0,231,241,3,30,15,0,232,241,3,26,13,0,233,241,3,28,14,0,234,241,3,
  	64,32,0,235,241,3,72,36,0,236,241,3,74,37,0,237,241,3,76,38,0,238,241,
  	3,38,19,0,239,241,3,50,25,0,240,231,1,0,0,0,240,232,1,0,0,0,240,233,1,
  	0,0,0,240,234,1,0,0,0,240,235,1,0,0,0,240,236,1,0,0,0,240,237,1,0,0,0,
  	240,238,1,0,0,0,240,239,1,0,0,0,241,37,1,0,0,0,242,243,5,29,0,0,243,244,
  	5,46,0,0,244,248,5,6,0,0,245,247,3,40,20,0,246,245,1,0,0,0,247,250,1,
  	0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,251,1,0,0,0,250,248,1,0,0,0,
  	251,252,5,7,0,0,252,39,1,0,0,0,253,256,5,45,0,0,254,255,5,16,0,0,255,
  	257,5,48,0,0,256,254,1,0,0,0,256,257,1,0,0,0,257,41,1,0,0,0,258,262,5,
  	6,0,0,259,261,3,36,18,0,260,259,1,0,0,0,261,264,1,0,0,0,262,260,1,0,0,
  	0,262,263,1,0,0,0,263,265,1,0,0,0,264,262,1,0,0,0,265,266,5,7,0,0,266,
  	43,1,0,0,0,267,272,3,46,23,0,268,269,5,12,0,0,269,271,3,46,23,0,270,268,
  	1,0,0,0,271,274,1,0,0,0,272,270,1,0,0,0,272,273,1,0,0,0,273,276,1,0,0,
  	0,274,272,1,0,0,0,275,277,5,12,0,0,276,275,1,0,0,0,276,277,1,0,0,0,277,
  	45,1,0,0,0,278,279,6,23,-1,0,279,286,3,48,24,0,280,286,3,52,26,0,281,
  	282,5,4,0,0,282,283,3,46,23,0,283,284,5,5,0,0,284,286,1,0,0,0,285,278,
  	1,0,0,0,285,280,1,0,0,0,285,281,1,0,0,0,286,298,1,0,0,0,287,288,10,6,
  	0,0,288,289,7,0,0,0,289,297,3,46,23,7,290,291,10,5,0,0,291,292,7,1,0,
  	0,292,297,3,46,23,6,293,294,10,4,0,0,294,295,7,2,0,0,295,297,3,46,23,
  	5,296,287,1,0,0,0,296,290,1,0,0,0,296,293,1,0,0,0,297,300,1,0,0,0,298,
  	296,1,0,0,0,298,299,1,0,0,0,299,47,1,0,0,0,300,298,1,0,0,0,301,308,3,
  	50,25,0,302,308,3,54,27,0,303,308,3,56,28,0,304,308,3,58,29,0,305,308,
  	3,62,31,0,306,308,5,47,0,0,307,301,1,0,0,0,307,302,1,0,0,0,307,303,1,
  	0,0,0,307,304,1,0,0,0,307,305,1,0,0,0,307,306,1,0,0,0,308,49,1,0,0,0,
  	309,310,5,47,0,0,310,312,5,4,0,0,311,313,3,34,17,0,312,311,1,0,0,0,312,
  	313,1,0,0,0,313,314,1,0,0,0,314,315,5,5,0,0,315,51,1,0,0,0,316,317,5,
  	8,0,0,317,322,3,46,23,0,318,319,5,12,0,0,319,321,3,46,23,0,320,318,1,
  	0,0,0,321,324,1,0,0,0,322,320,1,0,0,0,322,323,1,0,0,0,323,325,1,0,0,0,
  	324,322,1,0,0,0,325,326,5,9,0,0,326,53,1,0,0,0,327,328,5,46,0,0,328,330,
  	5,4,0,0,329,331,3,34,17,0,330,329,1,0,0,0,330,331,1,0,0,0,331,332,1,0,
  	0,0,332,333,5,5,0,0,333,55,1,0,0,0,334,335,7,3,0,0,335,57,1,0,0,0,336,
  	339,5,47,0,0,337,339,3,50,25,0,338,336,1,0,0,0,338,337,1,0,0,0,339,344,
  	1,0,0,0,340,341,5,8,0,0,341,342,3,46,23,0,342,343,5,9,0,0,343,345,1,0,
  	0,0,344,340,1,0,0,0,345,346,1,0,0,0,346,344,1,0,0,0,346,347,1,0,0,0,347,
  	59,1,0,0,0,348,353,5,47,0,0,349,353,3,50,25,0,350,353,3,54,27,0,351,353,
  	3,58,29,0,352,348,1,0,0,0,352,349,1,0,0,0,352,350,1,0,0,0,352,351,1,0,
  	0,0,353,61,1,0,0,0,354,359,3,60,30,0,355,356,5,14,0,0,356,358,3,60,30,
  	0,357,355,1,0,0,0,358,361,1,0,0,0,359,357,1,0,0,0,359,360,1,0,0,0,360,
  	63,1,0,0,0,361,359,1,0,0,0,362,363,5,32,0,0,363,364,3,46,23,0,364,365,
  	3,42,21,0,365,366,3,66,33,0,366,369,1,0,0,0,367,369,3,68,34,0,368,362,
  	1,0,0,0,368,367,1,0,0,0,369,65,1,0,0,0,370,371,5,33,0,0,371,372,3,46,
  	23,0,372,373,3,42,21,0,373,375,1,0,0,0,374,370,1,0,0,0,375,378,1,0,0,
  	0,376,374,1,0,0,0,376,377,1,0,0,0,377,381,1,0,0,0,378,376,1,0,0,0,379,
  	380,5,33,0,0,380,382,3,42,21,0,381,379,1,0,0,0,381,382,1,0,0,0,382,67,
  	1,0,0,0,383,385,5,32,0,0,384,386,3,46,23,0,385,384,1,0,0,0,385,386,1,
  	0,0,0,386,387,1,0,0,0,387,391,5,6,0,0,388,390,3,70,35,0,389,388,1,0,0,
  	0,390,393,1,0,0,0,391,389,1,0,0,0,391,392,1,0,0,0,392,397,1,0,0,0,393,
  	391,1,0,0,0,394,395,5,33,0,0,395,396,5,15,0,0,396,398,3,42,21,0,397,394,
  	1,0,0,0,397,398,1,0,0,0,398,399,1,0,0,0,399,400,5,7,0,0,400,69,1,0,0,
  	0,401,402,3,46,23,0,402,403,5,15,0,0,403,404,3,42,21,0,404,71,1,0,0,0,
  	405,407,5,34,0,0,406,408,3,46,23,0,407,406,1,0,0,0,407,408,1,0,0,0,408,
  	409,1,0,0,0,409,423,3,42,21,0,410,411,5,34,0,0,411,412,3,44,22,0,412,
  	413,5,41,0,0,413,414,3,46,23,0,414,415,3,42,21,0,415,423,1,0,0,0,416,
  	417,5,34,0,0,417,418,3,44,22,0,418,419,5,41,0,0,419,420,3,78,39,0,420,
  	421,3,42,21,0,421,423,1,0,0,0,422,405,1,0,0,0,422,410,1,0,0,0,422,416,
  	1,0,0,0,423,73,1,0,0,0,424,425,5,35,0,0,425,430,3,46,23,0,426,427,5,35,
  	0,0,427,430,5,32,0,0,428,430,5,36,0,0,429,424,1,0,0,0,429,426,1,0,0,0,
  	429,428,1,0,0,0,430,75,1,0,0,0,431,432,5,37,0,0,432,433,3,46,23,0,433,
  	77,1,0,0,0,434,436,3,46,23,0,435,434,1,0,0,0,435,436,1,0,0,0,436,437,
  	1,0,0,0,437,438,5,13,0,0,438,439,3,46,23,0,439,79,1,0,0,0,48,81,86,91,
  	97,102,108,115,120,126,131,141,151,169,174,186,190,197,208,216,225,229,
  	240,248,256,262,272,276,285,296,298,307,312,322,330,338,346,352,359,368,
  	376,381,385,391,397,407,422,429,435
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

LogosParser::ImportStatementContext* LogosParser::LogosFileContext::importStatement() {
  return getRuleContext<LogosParser::ImportStatementContext>(0);
}

LogosParser::ObjectFileContext* LogosParser::LogosFileContext::objectFile() {
  return getRuleContext<LogosParser::ObjectFileContext>(0);
}

LogosParser::InterfaceFileContext* LogosParser::LogosFileContext::interfaceFile() {
  return getRuleContext<LogosParser::InterfaceFileContext>(0);
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
    setState(86);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::IMPORT:
      case LogosParser::VARIABLE: {
        enterOuterAlt(_localctx, 1);
        setState(81);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LogosParser::IMPORT) {
          setState(80);
          importStatement();
        }
        setState(83);
        mainFile();
        break;
      }

      case LogosParser::OBJECT: {
        enterOuterAlt(_localctx, 2);
        setState(84);
        objectFile();
        break;
      }

      case LogosParser::INTERFACE: {
        enterOuterAlt(_localctx, 3);
        setState(85);
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
    setState(89); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(88);
      funcImplementation();
      setState(91); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(93);
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
  enterRule(_localctx, 4, LogosParser::RuleObjectFile);
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
    setState(95);
    objectDeclaration();
    setState(97);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(96);
      objectImplements();
    }
    setState(102);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(99);
        explicitVarDec(); 
      }
      setState(104);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
    setState(108);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(105);
      funcImplementation();
      setState(110);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(111);
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
  enterRule(_localctx, 6, LogosParser::RuleInterfaceFile);
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
    setState(113);
    interfaceDeclaration();
    setState(115);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(114);
      objectImplements();
    }
    setState(120);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(117);
        explicitVarDec(); 
      }
      setState(122);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
    setState(124); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(123);
              funcSignature();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(126); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(131);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(128);
      funcImplementation();
      setState(133);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(134);
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
    setState(136);
    match(LogosParser::IMPORT);
    setState(137);
    match(LogosParser::LPAREN);
    setState(141);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::TYPE) {
      setState(138);
      importPath();
      setState(143);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(144);
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
    setState(146);
    match(LogosParser::TYPE);
    setState(151);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::DOT) {
      setState(147);
      match(LogosParser::DOT);
      setState(148);
      match(LogosParser::TYPE);
      setState(153);
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
    setState(154);
    match(LogosParser::OBJECT);
    setState(155);
    match(LogosParser::COLON);
    setState(156);
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
    setState(158);
    match(LogosParser::INTERFACE);
    setState(159);
    match(LogosParser::COLON);
    setState(160);
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
    setState(162);
    match(LogosParser::IMPLEMENTS);
    setState(163);
    match(LogosParser::COLON);
    setState(164);
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

LogosParser::ParamListContext* LogosParser::FuncSignatureContext::paramList() {
  return getRuleContext<LogosParser::ParamListContext>(0);
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
    setState(166);
    match(LogosParser::VARIABLE);
    setState(167);
    match(LogosParser::LPAREN);
    setState(169);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(168);
      paramList();
    }
    setState(171);
    match(LogosParser::RPAREN);
    setState(174);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(172);
      match(LogosParser::COLON);
      setState(173);
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
    setState(176);
    funcSignature();
    setState(177);
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
    setState(179);
    statementsBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamListContext ------------------------------------------------------------------

LogosParser::ParamListContext::ParamListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::ExplicitVarDecContext *> LogosParser::ParamListContext::explicitVarDec() {
  return getRuleContexts<LogosParser::ExplicitVarDecContext>();
}

LogosParser::ExplicitVarDecContext* LogosParser::ParamListContext::explicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::ParamListContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ParamListContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ParamListContext::getRuleIndex() const {
  return LogosParser::RuleParamList;
}


LogosParser::ParamListContext* LogosParser::paramList() {
  ParamListContext *_localctx = _tracker.createInstance<ParamListContext>(_ctx, getState());
  enterRule(_localctx, 24, LogosParser::RuleParamList);
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
    setState(181);
    explicitVarDec();
    setState(186);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(182);
        match(LogosParser::COMMA);
        setState(183);
        explicitVarDec(); 
      }
      setState(188);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    }
    setState(190);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(189);
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


size_t LogosParser::ExplicitVarDecContext::getRuleIndex() const {
  return LogosParser::RuleExplicitVarDec;
}


LogosParser::ExplicitVarDecContext* LogosParser::explicitVarDec() {
  ExplicitVarDecContext *_localctx = _tracker.createInstance<ExplicitVarDecContext>(_ctx, getState());
  enterRule(_localctx, 26, LogosParser::RuleExplicitVarDec);
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
    setState(192);
    match(LogosParser::VARIABLE);
    setState(193);
    match(LogosParser::COLON);
    setState(194);
    match(LogosParser::TYPE);
    setState(197);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(195);
      match(LogosParser::EQUAL);
      setState(196);
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
  enterRule(_localctx, 28, LogosParser::RuleImplicitVarDec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(199);
    match(LogosParser::VARIABLE);
    setState(200);
    match(LogosParser::EQUAL);
    setState(201);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldDefContext ------------------------------------------------------------------

LogosParser::FieldDefContext::FieldDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LogosParser::FieldDefContext::VARIABLE() {
  return getTokens(LogosParser::VARIABLE);
}

tree::TerminalNode* LogosParser::FieldDefContext::VARIABLE(size_t i) {
  return getToken(LogosParser::VARIABLE, i);
}

tree::TerminalNode* LogosParser::FieldDefContext::DOT() {
  return getToken(LogosParser::DOT, 0);
}

tree::TerminalNode* LogosParser::FieldDefContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::FieldDefContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::FieldDefContext::getRuleIndex() const {
  return LogosParser::RuleFieldDef;
}


LogosParser::FieldDefContext* LogosParser::fieldDef() {
  FieldDefContext *_localctx = _tracker.createInstance<FieldDefContext>(_ctx, getState());
  enterRule(_localctx, 30, LogosParser::RuleFieldDef);
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
    setState(203);
    match(LogosParser::VARIABLE);
    setState(204);
    match(LogosParser::DOT);
    setState(208);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(205);
      match(LogosParser::VARIABLE);
      setState(210);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(211);
    match(LogosParser::EQUAL);
    setState(212);
    expr(0);
   
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
  enterRule(_localctx, 32, LogosParser::RuleFuncArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(216);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(214);
      match(LogosParser::VARIABLE);
      setState(215);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(218);
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
  enterRule(_localctx, 34, LogosParser::RuleFuncArgList);
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
    setState(220);
    funcArg();
    setState(225);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(221);
        match(LogosParser::COMMA);
        setState(222);
        funcArg(); 
      }
      setState(227);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
    setState(229);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(228);
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

LogosParser::FieldDefContext* LogosParser::StatementContext::fieldDef() {
  return getRuleContext<LogosParser::FieldDefContext>(0);
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

LogosParser::ControlFlowContext* LogosParser::StatementContext::controlFlow() {
  return getRuleContext<LogosParser::ControlFlowContext>(0);
}

LogosParser::ReturnStatementContext* LogosParser::StatementContext::returnStatement() {
  return getRuleContext<LogosParser::ReturnStatementContext>(0);
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
  enterRule(_localctx, 36, LogosParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(240);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(231);
      fieldDef();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(232);
      explicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(233);
      implicitVarDec();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(234);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(235);
      loopStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(236);
      controlFlow();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(237);
      returnStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(238);
      enumDeclaration();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(239);
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
  enterRule(_localctx, 38, LogosParser::RuleEnumDeclaration);
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
    setState(242);
    match(LogosParser::ENUM);
    setState(243);
    match(LogosParser::TYPE);
    setState(244);
    match(LogosParser::LBRACE);
    setState(248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST) {
      setState(245);
      enumField();
      setState(250);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(251);
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
  enterRule(_localctx, 40, LogosParser::RuleEnumField);
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
    setState(253);
    match(LogosParser::CONST);
    setState(256);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(254);
      match(LogosParser::EQUAL);
      setState(255);
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
  enterRule(_localctx, 42, LogosParser::RuleStatementsBlock);
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
    setState(258);
    match(LogosParser::LBRACE);
    setState(262);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 141000018231296) != 0)) {
      setState(259);
      statement();
      setState(264);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(265);
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
  enterRule(_localctx, 44, LogosParser::RuleExprList);
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
    setState(267);
    expr(0);
    setState(272);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(268);
        match(LogosParser::COMMA);
        setState(269);
        expr(0); 
      }
      setState(274);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }
    setState(276);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(275);
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

LogosParser::ArrayContext* LogosParser::ExprContext::array() {
  return getRuleContext<LogosParser::ArrayContext>(0);
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
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, LogosParser::RuleExpr, precedence);

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
    setState(285);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::INTEGER:
      case LogosParser::FLOAT:
      case LogosParser::BOOL:
      case LogosParser::TYPE:
      case LogosParser::VARIABLE:
      case LogosParser::STRING: {
        setState(279);
        unaryExpr();
        break;
      }

      case LogosParser::LBRACK: {
        setState(280);
        array();
        break;
      }

      case LogosParser::LPAREN: {
        setState(281);
        match(LogosParser::LPAREN);
        setState(282);
        antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
        setState(283);
        match(LogosParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(298);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(296);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(287);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(288);
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
          setState(289);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(290);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(291);
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
          setState(292);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(293);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(294);
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
          setState(295);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        default:
          break;
        } 
      }
      setState(300);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
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

LogosParser::ConstructorContext* LogosParser::UnaryExprContext::constructor() {
  return getRuleContext<LogosParser::ConstructorContext>(0);
}

LogosParser::ConstantContext* LogosParser::UnaryExprContext::constant() {
  return getRuleContext<LogosParser::ConstantContext>(0);
}

LogosParser::ArrayIndexContext* LogosParser::UnaryExprContext::arrayIndex() {
  return getRuleContext<LogosParser::ArrayIndexContext>(0);
}

LogosParser::SelectionContext* LogosParser::UnaryExprContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}


size_t LogosParser::UnaryExprContext::getRuleIndex() const {
  return LogosParser::RuleUnaryExpr;
}


LogosParser::UnaryExprContext* LogosParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 48, LogosParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(307);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(301);
      funcCall();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(302);
      constructor();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(303);
      constant();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(304);
      arrayIndex();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(305);
      selection();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(306);
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
  enterRule(_localctx, 50, LogosParser::RuleFuncCall);
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
    setState(309);
    match(LogosParser::VARIABLE);
    setState(310);
    match(LogosParser::LPAREN);
    setState(312);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821648) != 0)) {
      setState(311);
      funcArgList();
    }
    setState(314);
    match(LogosParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayContext ------------------------------------------------------------------

LogosParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ArrayContext::LBRACK() {
  return getToken(LogosParser::LBRACK, 0);
}

std::vector<LogosParser::ExprContext *> LogosParser::ArrayContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::ArrayContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

tree::TerminalNode* LogosParser::ArrayContext::RBRACK() {
  return getToken(LogosParser::RBRACK, 0);
}

std::vector<tree::TerminalNode *> LogosParser::ArrayContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ArrayContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ArrayContext::getRuleIndex() const {
  return LogosParser::RuleArray;
}


LogosParser::ArrayContext* LogosParser::array() {
  ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, getState());
  enterRule(_localctx, 52, LogosParser::RuleArray);
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
    setState(316);
    match(LogosParser::LBRACK);
    setState(317);
    expr(0);
    setState(322);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::COMMA) {
      setState(318);
      match(LogosParser::COMMA);
      setState(319);
      expr(0);
      setState(324);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(325);
    match(LogosParser::RBRACK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructorContext ------------------------------------------------------------------

LogosParser::ConstructorContext::ConstructorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ConstructorContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::ConstructorContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::ConstructorContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

LogosParser::FuncArgListContext* LogosParser::ConstructorContext::funcArgList() {
  return getRuleContext<LogosParser::FuncArgListContext>(0);
}


size_t LogosParser::ConstructorContext::getRuleIndex() const {
  return LogosParser::RuleConstructor;
}


LogosParser::ConstructorContext* LogosParser::constructor() {
  ConstructorContext *_localctx = _tracker.createInstance<ConstructorContext>(_ctx, getState());
  enterRule(_localctx, 54, LogosParser::RuleConstructor);
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
    setState(327);
    match(LogosParser::TYPE);
    setState(328);
    match(LogosParser::LPAREN);
    setState(330);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821648) != 0)) {
      setState(329);
      funcArgList();
    }
    setState(332);
    match(LogosParser::RPAREN);
   
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
  enterRule(_localctx, 56, LogosParser::RuleConstant);
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
    setState(334);
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

//----------------- ArrayIndexContext ------------------------------------------------------------------

LogosParser::ArrayIndexContext::ArrayIndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ArrayIndexContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

LogosParser::FuncCallContext* LogosParser::ArrayIndexContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

std::vector<tree::TerminalNode *> LogosParser::ArrayIndexContext::LBRACK() {
  return getTokens(LogosParser::LBRACK);
}

tree::TerminalNode* LogosParser::ArrayIndexContext::LBRACK(size_t i) {
  return getToken(LogosParser::LBRACK, i);
}

std::vector<LogosParser::ExprContext *> LogosParser::ArrayIndexContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::ArrayIndexContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::ArrayIndexContext::RBRACK() {
  return getTokens(LogosParser::RBRACK);
}

tree::TerminalNode* LogosParser::ArrayIndexContext::RBRACK(size_t i) {
  return getToken(LogosParser::RBRACK, i);
}


size_t LogosParser::ArrayIndexContext::getRuleIndex() const {
  return LogosParser::RuleArrayIndex;
}


LogosParser::ArrayIndexContext* LogosParser::arrayIndex() {
  ArrayIndexContext *_localctx = _tracker.createInstance<ArrayIndexContext>(_ctx, getState());
  enterRule(_localctx, 58, LogosParser::RuleArrayIndex);

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
    setState(338);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(336);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      setState(337);
      funcCall();
      break;
    }

    default:
      break;
    }
    setState(344); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(340);
              match(LogosParser::LBRACK);
              setState(341);
              expr(0);
              setState(342);
              match(LogosParser::RBRACK);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(346); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectionElementContext ------------------------------------------------------------------

LogosParser::SelectionElementContext::SelectionElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::SelectionElementContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

LogosParser::FuncCallContext* LogosParser::SelectionElementContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::ConstructorContext* LogosParser::SelectionElementContext::constructor() {
  return getRuleContext<LogosParser::ConstructorContext>(0);
}

LogosParser::ArrayIndexContext* LogosParser::SelectionElementContext::arrayIndex() {
  return getRuleContext<LogosParser::ArrayIndexContext>(0);
}


size_t LogosParser::SelectionElementContext::getRuleIndex() const {
  return LogosParser::RuleSelectionElement;
}


LogosParser::SelectionElementContext* LogosParser::selectionElement() {
  SelectionElementContext *_localctx = _tracker.createInstance<SelectionElementContext>(_ctx, getState());
  enterRule(_localctx, 60, LogosParser::RuleSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(352);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(348);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(349);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(350);
      constructor();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(351);
      arrayIndex();
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

//----------------- SelectionContext ------------------------------------------------------------------

LogosParser::SelectionContext::SelectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::SelectionElementContext *> LogosParser::SelectionContext::selectionElement() {
  return getRuleContexts<LogosParser::SelectionElementContext>();
}

LogosParser::SelectionElementContext* LogosParser::SelectionContext::selectionElement(size_t i) {
  return getRuleContext<LogosParser::SelectionElementContext>(i);
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
  enterRule(_localctx, 62, LogosParser::RuleSelection);

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
    setState(354);
    selectionElement();
    setState(359);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(355);
        match(LogosParser::DOT);
        setState(356);
        selectionElement(); 
      }
      setState(361);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
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
  enterRule(_localctx, 64, LogosParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(368);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(362);
      match(LogosParser::IF);
      setState(363);
      expr(0);
      setState(364);
      statementsBlock();
      setState(365);
      elseStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(367);
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
  enterRule(_localctx, 66, LogosParser::RuleElseStatement);
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
    setState(376);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(370);
        match(LogosParser::ELSE);
        setState(371);
        expr(0);
        setState(372);
        statementsBlock(); 
      }
      setState(378);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    }
    setState(381);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(379);
      match(LogosParser::ELSE);
      setState(380);
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
  enterRule(_localctx, 68, LogosParser::RulePatternMatching);
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
    setState(383);
    match(LogosParser::IF);
    setState(385);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821648) != 0)) {
      setState(384);
      expr(0);
    }
    setState(387);
    match(LogosParser::LBRACE);
    setState(391);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821648) != 0)) {
      setState(388);
      pattern();
      setState(393);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(397);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(394);
      match(LogosParser::ELSE);
      setState(395);
      match(LogosParser::COLON);
      setState(396);
      statementsBlock();
    }
    setState(399);
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
  enterRule(_localctx, 70, LogosParser::RulePattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(401);
    expr(0);
    setState(402);
    match(LogosParser::COLON);
    setState(403);
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
  enterRule(_localctx, 72, LogosParser::RuleLoopStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(422);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(405);
      match(LogosParser::FOR);
      setState(407);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 523367534821648) != 0)) {
        setState(406);
        expr(0);
      }
      setState(409);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(410);
      match(LogosParser::FOR);
      setState(411);
      exprList();
      setState(412);
      match(LogosParser::IN);
      setState(413);
      expr(0);
      setState(414);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(416);
      match(LogosParser::FOR);
      setState(417);
      exprList();
      setState(418);
      match(LogosParser::IN);
      setState(419);
      range();
      setState(420);
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

//----------------- ControlFlowContext ------------------------------------------------------------------

LogosParser::ControlFlowContext::ControlFlowContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ControlFlowContext::BREAK() {
  return getToken(LogosParser::BREAK, 0);
}

LogosParser::ExprContext* LogosParser::ControlFlowContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::ControlFlowContext::IF() {
  return getToken(LogosParser::IF, 0);
}

tree::TerminalNode* LogosParser::ControlFlowContext::CONTINUE() {
  return getToken(LogosParser::CONTINUE, 0);
}


size_t LogosParser::ControlFlowContext::getRuleIndex() const {
  return LogosParser::RuleControlFlow;
}


LogosParser::ControlFlowContext* LogosParser::controlFlow() {
  ControlFlowContext *_localctx = _tracker.createInstance<ControlFlowContext>(_ctx, getState());
  enterRule(_localctx, 74, LogosParser::RuleControlFlow);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(429);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(424);
      match(LogosParser::BREAK);
      setState(425);
      expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(426);
      match(LogosParser::BREAK);
      setState(427);
      match(LogosParser::IF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(428);
      match(LogosParser::CONTINUE);
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

//----------------- ReturnStatementContext ------------------------------------------------------------------

LogosParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ReturnStatementContext::RETURN() {
  return getToken(LogosParser::RETURN, 0);
}

LogosParser::ExprContext* LogosParser::ReturnStatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::ReturnStatementContext::getRuleIndex() const {
  return LogosParser::RuleReturnStatement;
}


LogosParser::ReturnStatementContext* LogosParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 76, LogosParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(431);
    match(LogosParser::RETURN);
    setState(432);
    expr(0);
   
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
  enterRule(_localctx, 78, LogosParser::RuleRange);
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
    setState(435);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821648) != 0)) {
      setState(434);
      expr(0);
    }
    setState(437);
    match(LogosParser::DOUBLE_DOT);
    setState(438);
    expr(0);
   
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
    case 23: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LogosParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 6);
    case 1: return precpred(_ctx, 5);
    case 2: return precpred(_ctx, 4);

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
