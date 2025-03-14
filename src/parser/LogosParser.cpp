
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
      "logosFile", "mainFile", "objectFile", "interfaceFile", "objectDeclaration", 
      "interfaceDeclaration", "objectImplements", "funcSignature", "funcImplementation", 
      "funcBody", "paramList", "statement", "statementsBlock", "assignment", 
      "explicitVarDec", "implicitVarDec", "ifStatement", "elseIfStatement", 
      "elseStatement", "patternMatching", "pattern", "loopStatement", "controlFlow", 
      "returnStatement", "enumDeclaration", "enumField", "expr", "exprList", 
      "unaryExpr", "array", "map", "funcCall", "constructor", "funcArgList", 
      "funcArg", "constant", "arrayIndex", "selection", "firstSelectionElement", 
      "innerSelectionElement", "range", "type"
    },
    std::vector<std::string>{
      "", "'=='", "'!='", "'>='", "'<='", "'('", "')'", "'{'", "'}'", "'['", 
      "']'", "'<'", "'>'", "','", "'..'", "'.'", "':'", "'='", "'-'", "'+'", 
      "'*'", "'/'", "'#'", "'\\u003F'", "'!'", "'%'", "'$'", "'&'", "'object'", 
      "'self'", "'interface'", "'enum'", "'implements'", "'import'", "'if'", 
      "'else'", "'for'", "'break'", "'continue'", "'return'", "'and'", "'or'", 
      "'not'", "'in'"
    },
    std::vector<std::string>{
      "", "DOUBLE_EQUAL", "NOT_EQUAL", "GE", "LE", "LPAREN", "RPAREN", "LBRACE", 
      "RBRACE", "LBRACK", "RBRACK", "LANGLE", "RANGLE", "COMMA", "DOUBLE_DOT", 
      "DOT", "COLON", "EQUAL", "MINUS", "PLUS", "STAR", "SLASH", "HASH", 
      "QUEST_MARK", "EXCLA_MARK", "PERCENT", "DOLLAR", "AMPERSAND", "OBJECT", 
      "SELF", "INTERFACE", "ENUM", "IMPLEMENTS", "IMPORT", "IF", "ELSE", 
      "FOR", "BREAK", "CONTINUE", "RETURN", "AND", "OR", "NOT", "IN", "INTEGER", 
      "FLOAT", "BOOL", "CONST", "TYPE", "VARIABLE", "STRING", "LINE_COMMENT", 
      "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,53,464,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,1,0,1,
  	0,1,0,3,0,88,8,0,1,1,4,1,91,8,1,11,1,12,1,92,1,1,1,1,1,2,1,2,3,2,99,8,
  	2,1,2,5,2,102,8,2,10,2,12,2,105,9,2,1,2,5,2,108,8,2,10,2,12,2,111,9,2,
  	1,2,1,2,1,3,1,3,3,3,117,8,3,1,3,5,3,120,8,3,10,3,12,3,123,9,3,1,3,4,3,
  	126,8,3,11,3,12,3,127,1,3,5,3,131,8,3,10,3,12,3,134,9,3,1,3,1,3,1,4,1,
  	4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,3,7,153,8,7,1,7,
  	1,7,1,7,3,7,158,8,7,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,10,5,10,168,8,10,
  	10,10,12,10,171,9,10,1,10,3,10,174,8,10,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,3,11,185,8,11,1,12,1,12,5,12,189,8,12,10,12,12,12,192,
  	9,12,1,12,1,12,1,13,1,13,1,13,3,13,199,8,13,1,13,1,13,1,13,1,13,1,14,
  	1,14,1,14,1,14,1,14,3,14,210,8,14,1,15,1,15,1,15,1,15,1,16,1,16,1,16,
  	1,16,5,16,220,8,16,10,16,12,16,223,9,16,1,16,3,16,226,8,16,1,16,3,16,
  	229,8,16,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,19,1,19,3,19,240,8,19,1,
  	19,1,19,5,19,244,8,19,10,19,12,19,247,9,19,1,19,1,19,1,19,3,19,252,8,
  	19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,21,3,21,262,8,21,1,21,1,21,1,
  	21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,277,8,21,1,
  	22,1,22,1,22,1,22,1,22,3,22,284,8,22,1,23,1,23,1,23,1,24,1,24,1,24,1,
  	24,5,24,293,8,24,10,24,12,24,296,9,24,1,24,1,24,1,25,1,25,1,25,3,25,303,
  	8,25,1,26,1,26,1,26,1,26,1,26,1,26,3,26,311,8,26,1,26,1,26,1,26,1,26,
  	1,26,1,26,1,26,1,26,1,26,5,26,322,8,26,10,26,12,26,325,9,26,1,27,1,27,
  	1,27,5,27,330,8,27,10,27,12,27,333,9,27,1,27,3,27,336,8,27,1,28,1,28,
  	1,28,1,28,1,28,1,28,1,28,1,28,1,28,3,28,347,8,28,1,29,1,29,1,29,1,29,
  	5,29,353,8,29,10,29,12,29,356,9,29,1,29,1,29,1,30,1,30,1,30,1,30,1,30,
  	3,30,365,8,30,5,30,367,8,30,10,30,12,30,370,9,30,1,30,1,30,1,31,1,31,
  	1,31,3,31,377,8,31,1,31,1,31,1,32,1,32,1,32,3,32,384,8,32,1,32,1,32,1,
  	33,1,33,1,33,5,33,391,8,33,10,33,12,33,394,9,33,1,33,3,33,397,8,33,1,
  	34,1,34,3,34,401,8,34,1,34,1,34,1,35,1,35,1,36,1,36,3,36,409,8,36,1,36,
  	1,36,1,36,1,36,4,36,415,8,36,11,36,12,36,416,1,37,1,37,1,37,4,37,422,
  	8,37,11,37,12,37,423,1,38,1,38,1,38,1,38,1,38,1,38,3,38,432,8,38,1,39,
  	1,39,1,39,3,39,437,8,39,1,40,3,40,440,8,40,1,40,1,40,1,40,1,41,1,41,1,
  	41,3,41,448,8,41,1,41,5,41,451,8,41,10,41,12,41,454,9,41,1,41,1,41,1,
  	41,1,41,1,41,1,41,3,41,462,8,41,1,41,0,1,52,42,0,2,4,6,8,10,12,14,16,
  	18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,
  	64,66,68,70,72,74,76,78,80,82,0,4,1,0,20,21,1,0,18,19,2,0,1,4,11,12,2,
  	0,44,46,50,50,496,0,87,1,0,0,0,2,90,1,0,0,0,4,96,1,0,0,0,6,114,1,0,0,
  	0,8,137,1,0,0,0,10,141,1,0,0,0,12,145,1,0,0,0,14,149,1,0,0,0,16,159,1,
  	0,0,0,18,162,1,0,0,0,20,164,1,0,0,0,22,184,1,0,0,0,24,186,1,0,0,0,26,
  	198,1,0,0,0,28,204,1,0,0,0,30,211,1,0,0,0,32,228,1,0,0,0,34,230,1,0,0,
  	0,36,234,1,0,0,0,38,237,1,0,0,0,40,255,1,0,0,0,42,276,1,0,0,0,44,283,
  	1,0,0,0,46,285,1,0,0,0,48,288,1,0,0,0,50,299,1,0,0,0,52,310,1,0,0,0,54,
  	326,1,0,0,0,56,346,1,0,0,0,58,348,1,0,0,0,60,359,1,0,0,0,62,373,1,0,0,
  	0,64,380,1,0,0,0,66,387,1,0,0,0,68,400,1,0,0,0,70,404,1,0,0,0,72,408,
  	1,0,0,0,74,418,1,0,0,0,76,431,1,0,0,0,78,436,1,0,0,0,80,439,1,0,0,0,82,
  	461,1,0,0,0,84,88,3,2,1,0,85,88,3,4,2,0,86,88,3,6,3,0,87,84,1,0,0,0,87,
  	85,1,0,0,0,87,86,1,0,0,0,88,1,1,0,0,0,89,91,3,16,8,0,90,89,1,0,0,0,91,
  	92,1,0,0,0,92,90,1,0,0,0,92,93,1,0,0,0,93,94,1,0,0,0,94,95,5,0,0,1,95,
  	3,1,0,0,0,96,98,3,8,4,0,97,99,3,12,6,0,98,97,1,0,0,0,98,99,1,0,0,0,99,
  	103,1,0,0,0,100,102,3,28,14,0,101,100,1,0,0,0,102,105,1,0,0,0,103,101,
  	1,0,0,0,103,104,1,0,0,0,104,109,1,0,0,0,105,103,1,0,0,0,106,108,3,16,
  	8,0,107,106,1,0,0,0,108,111,1,0,0,0,109,107,1,0,0,0,109,110,1,0,0,0,110,
  	112,1,0,0,0,111,109,1,0,0,0,112,113,5,0,0,1,113,5,1,0,0,0,114,116,3,10,
  	5,0,115,117,3,12,6,0,116,115,1,0,0,0,116,117,1,0,0,0,117,121,1,0,0,0,
  	118,120,3,28,14,0,119,118,1,0,0,0,120,123,1,0,0,0,121,119,1,0,0,0,121,
  	122,1,0,0,0,122,125,1,0,0,0,123,121,1,0,0,0,124,126,3,14,7,0,125,124,
  	1,0,0,0,126,127,1,0,0,0,127,125,1,0,0,0,127,128,1,0,0,0,128,132,1,0,0,
  	0,129,131,3,16,8,0,130,129,1,0,0,0,131,134,1,0,0,0,132,130,1,0,0,0,132,
  	133,1,0,0,0,133,135,1,0,0,0,134,132,1,0,0,0,135,136,5,0,0,1,136,7,1,0,
  	0,0,137,138,5,28,0,0,138,139,5,16,0,0,139,140,5,48,0,0,140,9,1,0,0,0,
  	141,142,5,30,0,0,142,143,5,16,0,0,143,144,5,48,0,0,144,11,1,0,0,0,145,
  	146,5,32,0,0,146,147,5,16,0,0,147,148,5,48,0,0,148,13,1,0,0,0,149,150,
  	5,49,0,0,150,152,5,5,0,0,151,153,3,20,10,0,152,151,1,0,0,0,152,153,1,
  	0,0,0,153,154,1,0,0,0,154,157,5,6,0,0,155,156,5,16,0,0,156,158,3,82,41,
  	0,157,155,1,0,0,0,157,158,1,0,0,0,158,15,1,0,0,0,159,160,3,14,7,0,160,
  	161,3,18,9,0,161,17,1,0,0,0,162,163,3,24,12,0,163,19,1,0,0,0,164,169,
  	3,28,14,0,165,166,5,13,0,0,166,168,3,28,14,0,167,165,1,0,0,0,168,171,
  	1,0,0,0,169,167,1,0,0,0,169,170,1,0,0,0,170,173,1,0,0,0,171,169,1,0,0,
  	0,172,174,5,13,0,0,173,172,1,0,0,0,173,174,1,0,0,0,174,21,1,0,0,0,175,
  	185,3,26,13,0,176,185,3,28,14,0,177,185,3,30,15,0,178,185,3,32,16,0,179,
  	185,3,42,21,0,180,185,3,44,22,0,181,185,3,46,23,0,182,185,3,48,24,0,183,
  	185,3,62,31,0,184,175,1,0,0,0,184,176,1,0,0,0,184,177,1,0,0,0,184,178,
  	1,0,0,0,184,179,1,0,0,0,184,180,1,0,0,0,184,181,1,0,0,0,184,182,1,0,0,
  	0,184,183,1,0,0,0,185,23,1,0,0,0,186,190,5,7,0,0,187,189,3,22,11,0,188,
  	187,1,0,0,0,189,192,1,0,0,0,190,188,1,0,0,0,190,191,1,0,0,0,191,193,1,
  	0,0,0,192,190,1,0,0,0,193,194,5,8,0,0,194,25,1,0,0,0,195,199,5,49,0,0,
  	196,199,3,72,36,0,197,199,3,74,37,0,198,195,1,0,0,0,198,196,1,0,0,0,198,
  	197,1,0,0,0,199,200,1,0,0,0,200,201,5,16,0,0,201,202,5,17,0,0,202,203,
  	3,52,26,0,203,27,1,0,0,0,204,205,5,49,0,0,205,206,5,16,0,0,206,209,3,
  	82,41,0,207,208,5,17,0,0,208,210,3,52,26,0,209,207,1,0,0,0,209,210,1,
  	0,0,0,210,29,1,0,0,0,211,212,5,49,0,0,212,213,5,17,0,0,213,214,3,52,26,
  	0,214,31,1,0,0,0,215,216,5,34,0,0,216,217,3,52,26,0,217,221,3,24,12,0,
  	218,220,3,34,17,0,219,218,1,0,0,0,220,223,1,0,0,0,221,219,1,0,0,0,221,
  	222,1,0,0,0,222,225,1,0,0,0,223,221,1,0,0,0,224,226,3,36,18,0,225,224,
  	1,0,0,0,225,226,1,0,0,0,226,229,1,0,0,0,227,229,3,38,19,0,228,215,1,0,
  	0,0,228,227,1,0,0,0,229,33,1,0,0,0,230,231,5,35,0,0,231,232,3,52,26,0,
  	232,233,3,24,12,0,233,35,1,0,0,0,234,235,5,35,0,0,235,236,3,24,12,0,236,
  	37,1,0,0,0,237,239,5,34,0,0,238,240,3,52,26,0,239,238,1,0,0,0,239,240,
  	1,0,0,0,240,241,1,0,0,0,241,245,5,7,0,0,242,244,3,40,20,0,243,242,1,0,
  	0,0,244,247,1,0,0,0,245,243,1,0,0,0,245,246,1,0,0,0,246,251,1,0,0,0,247,
  	245,1,0,0,0,248,249,5,35,0,0,249,250,5,16,0,0,250,252,3,24,12,0,251,248,
  	1,0,0,0,251,252,1,0,0,0,252,253,1,0,0,0,253,254,5,8,0,0,254,39,1,0,0,
  	0,255,256,3,52,26,0,256,257,5,16,0,0,257,258,3,24,12,0,258,41,1,0,0,0,
  	259,261,5,36,0,0,260,262,5,49,0,0,261,260,1,0,0,0,261,262,1,0,0,0,262,
  	263,1,0,0,0,263,277,3,24,12,0,264,265,5,36,0,0,265,266,5,49,0,0,266,267,
  	5,43,0,0,267,268,3,80,40,0,268,269,3,24,12,0,269,277,1,0,0,0,270,271,
  	5,36,0,0,271,272,3,54,27,0,272,273,5,43,0,0,273,274,3,52,26,0,274,275,
  	3,24,12,0,275,277,1,0,0,0,276,259,1,0,0,0,276,264,1,0,0,0,276,270,1,0,
  	0,0,277,43,1,0,0,0,278,279,5,37,0,0,279,284,3,52,26,0,280,281,5,37,0,
  	0,281,284,5,34,0,0,282,284,5,38,0,0,283,278,1,0,0,0,283,280,1,0,0,0,283,
  	282,1,0,0,0,284,45,1,0,0,0,285,286,5,39,0,0,286,287,3,52,26,0,287,47,
  	1,0,0,0,288,289,5,31,0,0,289,290,5,48,0,0,290,294,5,7,0,0,291,293,3,50,
  	25,0,292,291,1,0,0,0,293,296,1,0,0,0,294,292,1,0,0,0,294,295,1,0,0,0,
  	295,297,1,0,0,0,296,294,1,0,0,0,297,298,5,8,0,0,298,49,1,0,0,0,299,302,
  	5,47,0,0,300,301,5,17,0,0,301,303,5,50,0,0,302,300,1,0,0,0,302,303,1,
  	0,0,0,303,51,1,0,0,0,304,305,6,26,-1,0,305,311,3,56,28,0,306,307,5,5,
  	0,0,307,308,3,52,26,0,308,309,5,6,0,0,309,311,1,0,0,0,310,304,1,0,0,0,
  	310,306,1,0,0,0,311,323,1,0,0,0,312,313,10,5,0,0,313,314,7,0,0,0,314,
  	322,3,52,26,6,315,316,10,4,0,0,316,317,7,1,0,0,317,322,3,52,26,5,318,
  	319,10,3,0,0,319,320,7,2,0,0,320,322,3,52,26,4,321,312,1,0,0,0,321,315,
  	1,0,0,0,321,318,1,0,0,0,322,325,1,0,0,0,323,321,1,0,0,0,323,324,1,0,0,
  	0,324,53,1,0,0,0,325,323,1,0,0,0,326,331,3,52,26,0,327,328,5,13,0,0,328,
  	330,3,52,26,0,329,327,1,0,0,0,330,333,1,0,0,0,331,329,1,0,0,0,331,332,
  	1,0,0,0,332,335,1,0,0,0,333,331,1,0,0,0,334,336,5,13,0,0,335,334,1,0,
  	0,0,335,336,1,0,0,0,336,55,1,0,0,0,337,347,5,49,0,0,338,347,5,29,0,0,
  	339,347,3,62,31,0,340,347,3,64,32,0,341,347,3,70,35,0,342,347,3,58,29,
  	0,343,347,3,60,30,0,344,347,3,72,36,0,345,347,3,74,37,0,346,337,1,0,0,
  	0,346,338,1,0,0,0,346,339,1,0,0,0,346,340,1,0,0,0,346,341,1,0,0,0,346,
  	342,1,0,0,0,346,343,1,0,0,0,346,344,1,0,0,0,346,345,1,0,0,0,347,57,1,
  	0,0,0,348,349,5,9,0,0,349,354,3,52,26,0,350,351,5,13,0,0,351,353,3,52,
  	26,0,352,350,1,0,0,0,353,356,1,0,0,0,354,352,1,0,0,0,354,355,1,0,0,0,
  	355,357,1,0,0,0,356,354,1,0,0,0,357,358,5,10,0,0,358,59,1,0,0,0,359,368,
  	5,7,0,0,360,361,3,52,26,0,361,362,5,16,0,0,362,364,3,52,26,0,363,365,
  	5,13,0,0,364,363,1,0,0,0,364,365,1,0,0,0,365,367,1,0,0,0,366,360,1,0,
  	0,0,367,370,1,0,0,0,368,366,1,0,0,0,368,369,1,0,0,0,369,371,1,0,0,0,370,
  	368,1,0,0,0,371,372,5,8,0,0,372,61,1,0,0,0,373,374,5,49,0,0,374,376,5,
  	5,0,0,375,377,3,66,33,0,376,375,1,0,0,0,376,377,1,0,0,0,377,378,1,0,0,
  	0,378,379,5,6,0,0,379,63,1,0,0,0,380,381,5,48,0,0,381,383,5,5,0,0,382,
  	384,3,66,33,0,383,382,1,0,0,0,383,384,1,0,0,0,384,385,1,0,0,0,385,386,
  	5,6,0,0,386,65,1,0,0,0,387,392,3,68,34,0,388,389,5,13,0,0,389,391,3,68,
  	34,0,390,388,1,0,0,0,391,394,1,0,0,0,392,390,1,0,0,0,392,393,1,0,0,0,
  	393,396,1,0,0,0,394,392,1,0,0,0,395,397,5,13,0,0,396,395,1,0,0,0,396,
  	397,1,0,0,0,397,67,1,0,0,0,398,399,5,49,0,0,399,401,5,17,0,0,400,398,
  	1,0,0,0,400,401,1,0,0,0,401,402,1,0,0,0,402,403,3,52,26,0,403,69,1,0,
  	0,0,404,405,7,3,0,0,405,71,1,0,0,0,406,409,3,62,31,0,407,409,5,49,0,0,
  	408,406,1,0,0,0,408,407,1,0,0,0,409,414,1,0,0,0,410,411,5,9,0,0,411,412,
  	3,52,26,0,412,413,5,10,0,0,413,415,1,0,0,0,414,410,1,0,0,0,415,416,1,
  	0,0,0,416,414,1,0,0,0,416,417,1,0,0,0,417,73,1,0,0,0,418,421,3,76,38,
  	0,419,420,5,15,0,0,420,422,3,78,39,0,421,419,1,0,0,0,422,423,1,0,0,0,
  	423,421,1,0,0,0,423,424,1,0,0,0,424,75,1,0,0,0,425,432,5,49,0,0,426,432,
  	5,48,0,0,427,432,5,29,0,0,428,432,3,62,31,0,429,432,3,64,32,0,430,432,
  	3,72,36,0,431,425,1,0,0,0,431,426,1,0,0,0,431,427,1,0,0,0,431,428,1,0,
  	0,0,431,429,1,0,0,0,431,430,1,0,0,0,432,77,1,0,0,0,433,437,5,49,0,0,434,
  	437,3,62,31,0,435,437,3,72,36,0,436,433,1,0,0,0,436,434,1,0,0,0,436,435,
  	1,0,0,0,437,79,1,0,0,0,438,440,3,52,26,0,439,438,1,0,0,0,439,440,1,0,
  	0,0,440,441,1,0,0,0,441,442,5,14,0,0,442,443,3,52,26,0,443,81,1,0,0,0,
  	444,452,5,48,0,0,445,447,5,9,0,0,446,448,5,44,0,0,447,446,1,0,0,0,447,
  	448,1,0,0,0,448,449,1,0,0,0,449,451,5,10,0,0,450,445,1,0,0,0,451,454,
  	1,0,0,0,452,450,1,0,0,0,452,453,1,0,0,0,453,462,1,0,0,0,454,452,1,0,0,
  	0,455,456,5,7,0,0,456,457,3,82,41,0,457,458,5,16,0,0,458,459,3,82,41,
  	0,459,460,5,8,0,0,460,462,1,0,0,0,461,444,1,0,0,0,461,455,1,0,0,0,462,
  	83,1,0,0,0,51,87,92,98,103,109,116,121,127,132,152,157,169,173,184,190,
  	198,209,221,225,228,239,245,251,261,276,283,294,302,310,321,323,331,335,
  	346,354,364,368,376,383,392,396,400,408,416,423,431,436,439,447,452,461
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


size_t LogosParser::LogosFileContext::getRuleIndex() const {
  return LogosParser::RuleLogosFile;
}


LogosParser::LogosFileContext* LogosParser::logosFile() {
  LogosFileContext *_localctx = _tracker.createInstance<LogosFileContext>(_ctx, getState());
  enterRule(_localctx, 0, LogosParser::RuleLogosFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(87);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::VARIABLE: {
        enterOuterAlt(_localctx, 1);
        setState(84);
        mainFile();
        break;
      }

      case LogosParser::OBJECT: {
        enterOuterAlt(_localctx, 2);
        setState(85);
        objectFile();
        break;
      }

      case LogosParser::INTERFACE: {
        enterOuterAlt(_localctx, 3);
        setState(86);
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
    setState(90); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(89);
      funcImplementation();
      setState(92); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(94);
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
    setState(96);
    objectDeclaration();
    setState(98);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(97);
      objectImplements();
    }
    setState(103);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(100);
        explicitVarDec(); 
      }
      setState(105);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
    setState(109);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(106);
      funcImplementation();
      setState(111);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(112);
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
    setState(114);
    interfaceDeclaration();
    setState(116);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(115);
      objectImplements();
    }
    setState(121);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(118);
        explicitVarDec(); 
      }
      setState(123);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
    setState(125); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(124);
              funcSignature();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(127); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(132);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(129);
      funcImplementation();
      setState(134);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(135);
    match(LogosParser::EOF);
   
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
  enterRule(_localctx, 8, LogosParser::RuleObjectDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    match(LogosParser::OBJECT);
    setState(138);
    match(LogosParser::COLON);
    setState(139);
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
  enterRule(_localctx, 10, LogosParser::RuleInterfaceDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141);
    match(LogosParser::INTERFACE);
    setState(142);
    match(LogosParser::COLON);
    setState(143);
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
  enterRule(_localctx, 12, LogosParser::RuleObjectImplements);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(LogosParser::IMPLEMENTS);
    setState(146);
    match(LogosParser::COLON);
    setState(147);
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

LogosParser::TypeContext* LogosParser::FuncSignatureContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}


size_t LogosParser::FuncSignatureContext::getRuleIndex() const {
  return LogosParser::RuleFuncSignature;
}


LogosParser::FuncSignatureContext* LogosParser::funcSignature() {
  FuncSignatureContext *_localctx = _tracker.createInstance<FuncSignatureContext>(_ctx, getState());
  enterRule(_localctx, 14, LogosParser::RuleFuncSignature);
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
    setState(149);
    match(LogosParser::VARIABLE);
    setState(150);
    match(LogosParser::LPAREN);
    setState(152);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(151);
      paramList();
    }
    setState(154);
    match(LogosParser::RPAREN);
    setState(157);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(155);
      match(LogosParser::COLON);
      setState(156);
      type();
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
  enterRule(_localctx, 16, LogosParser::RuleFuncImplementation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    funcSignature();
    setState(160);
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
  enterRule(_localctx, 18, LogosParser::RuleFuncBody);

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
  enterRule(_localctx, 20, LogosParser::RuleParamList);
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
    setState(164);
    explicitVarDec();
    setState(169);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(165);
        match(LogosParser::COMMA);
        setState(166);
        explicitVarDec(); 
      }
      setState(171);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
    setState(173);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(172);
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

LogosParser::AssignmentContext* LogosParser::StatementContext::assignment() {
  return getRuleContext<LogosParser::AssignmentContext>(0);
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
  enterRule(_localctx, 22, LogosParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(184);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(175);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(176);
      explicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(177);
      implicitVarDec();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(178);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(179);
      loopStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(180);
      controlFlow();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(181);
      returnStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(182);
      enumDeclaration();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(183);
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
  enterRule(_localctx, 24, LogosParser::RuleStatementsBlock);
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
    setState(186);
    match(LogosParser::LBRACE);
    setState(190);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 845475586506752) != 0)) {
      setState(187);
      statement();
      setState(192);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(193);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

LogosParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::AssignmentContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::AssignmentContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::AssignmentContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::AssignmentContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

LogosParser::ArrayIndexContext* LogosParser::AssignmentContext::arrayIndex() {
  return getRuleContext<LogosParser::ArrayIndexContext>(0);
}

LogosParser::SelectionContext* LogosParser::AssignmentContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}


size_t LogosParser::AssignmentContext::getRuleIndex() const {
  return LogosParser::RuleAssignment;
}


LogosParser::AssignmentContext* LogosParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 26, LogosParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(198);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(195);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      setState(196);
      arrayIndex();
      break;
    }

    case 3: {
      setState(197);
      selection();
      break;
    }

    default:
      break;
    }
    setState(200);
    match(LogosParser::COLON);
    setState(201);
    match(LogosParser::EQUAL);
    setState(202);
    expr(0);
   
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

LogosParser::TypeContext* LogosParser::ExplicitVarDecContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
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
  enterRule(_localctx, 28, LogosParser::RuleExplicitVarDec);
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
    setState(204);
    match(LogosParser::VARIABLE);
    setState(205);
    match(LogosParser::COLON);
    setState(206);
    type();
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(207);
      match(LogosParser::EQUAL);
      setState(208);
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
  enterRule(_localctx, 30, LogosParser::RuleImplicitVarDec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(211);
    match(LogosParser::VARIABLE);
    setState(212);
    match(LogosParser::EQUAL);
    setState(213);
    expr(0);
   
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

std::vector<LogosParser::ElseIfStatementContext *> LogosParser::IfStatementContext::elseIfStatement() {
  return getRuleContexts<LogosParser::ElseIfStatementContext>();
}

LogosParser::ElseIfStatementContext* LogosParser::IfStatementContext::elseIfStatement(size_t i) {
  return getRuleContext<LogosParser::ElseIfStatementContext>(i);
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
  enterRule(_localctx, 32, LogosParser::RuleIfStatement);
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
    setState(228);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(215);
      match(LogosParser::IF);
      setState(216);
      expr(0);
      setState(217);
      statementsBlock();
      setState(221);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(218);
          elseIfStatement(); 
        }
        setState(223);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
      }
      setState(225);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::ELSE) {
        setState(224);
        elseStatement();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(227);
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

//----------------- ElseIfStatementContext ------------------------------------------------------------------

LogosParser::ElseIfStatementContext::ElseIfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ElseIfStatementContext::ELSE() {
  return getToken(LogosParser::ELSE, 0);
}

LogosParser::ExprContext* LogosParser::ElseIfStatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

LogosParser::StatementsBlockContext* LogosParser::ElseIfStatementContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}


size_t LogosParser::ElseIfStatementContext::getRuleIndex() const {
  return LogosParser::RuleElseIfStatement;
}


LogosParser::ElseIfStatementContext* LogosParser::elseIfStatement() {
  ElseIfStatementContext *_localctx = _tracker.createInstance<ElseIfStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, LogosParser::RuleElseIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(230);
    match(LogosParser::ELSE);
    setState(231);
    expr(0);
    setState(232);
    statementsBlock();
   
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

tree::TerminalNode* LogosParser::ElseStatementContext::ELSE() {
  return getToken(LogosParser::ELSE, 0);
}

LogosParser::StatementsBlockContext* LogosParser::ElseStatementContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}


size_t LogosParser::ElseStatementContext::getRuleIndex() const {
  return LogosParser::RuleElseStatement;
}


LogosParser::ElseStatementContext* LogosParser::elseStatement() {
  ElseStatementContext *_localctx = _tracker.createInstance<ElseStatementContext>(_ctx, getState());
  enterRule(_localctx, 36, LogosParser::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    match(LogosParser::ELSE);
    setState(235);
    statementsBlock();
   
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
  enterRule(_localctx, 38, LogosParser::RulePatternMatching);
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
    setState(237);
    match(LogosParser::IF);
    setState(239);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(238);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(241);
    match(LogosParser::LBRACE);
    setState(245);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2093470676157088) != 0)) {
      setState(242);
      pattern();
      setState(247);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(251);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(248);
      match(LogosParser::ELSE);
      setState(249);
      match(LogosParser::COLON);
      setState(250);
      statementsBlock();
    }
    setState(253);
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
  enterRule(_localctx, 40, LogosParser::RulePattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(255);
    expr(0);
    setState(256);
    match(LogosParser::COLON);
    setState(257);
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

tree::TerminalNode* LogosParser::LoopStatementContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::LoopStatementContext::IN() {
  return getToken(LogosParser::IN, 0);
}

LogosParser::RangeContext* LogosParser::LoopStatementContext::range() {
  return getRuleContext<LogosParser::RangeContext>(0);
}

LogosParser::ExprListContext* LogosParser::LoopStatementContext::exprList() {
  return getRuleContext<LogosParser::ExprListContext>(0);
}

LogosParser::ExprContext* LogosParser::LoopStatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::LoopStatementContext::getRuleIndex() const {
  return LogosParser::RuleLoopStatement;
}


LogosParser::LoopStatementContext* LogosParser::loopStatement() {
  LoopStatementContext *_localctx = _tracker.createInstance<LoopStatementContext>(_ctx, getState());
  enterRule(_localctx, 42, LogosParser::RuleLoopStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(276);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(259);
      match(LogosParser::FOR);
      setState(261);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::VARIABLE) {
        setState(260);
        match(LogosParser::VARIABLE);
      }
      setState(263);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(264);
      match(LogosParser::FOR);
      setState(265);
      match(LogosParser::VARIABLE);
      setState(266);
      match(LogosParser::IN);
      setState(267);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(268);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(270);
      match(LogosParser::FOR);
      setState(271);
      exprList();
      setState(272);
      match(LogosParser::IN);
      setState(273);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = expr(0);
      setState(274);
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
  enterRule(_localctx, 44, LogosParser::RuleControlFlow);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(283);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(278);
      match(LogosParser::BREAK);
      setState(279);
      expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(280);
      match(LogosParser::BREAK);
      setState(281);
      match(LogosParser::IF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(282);
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
  enterRule(_localctx, 46, LogosParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(285);
    match(LogosParser::RETURN);
    setState(286);
    expr(0);
   
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
  enterRule(_localctx, 48, LogosParser::RuleEnumDeclaration);
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
    setState(288);
    match(LogosParser::ENUM);
    setState(289);
    match(LogosParser::TYPE);
    setState(290);
    match(LogosParser::LBRACE);
    setState(294);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST) {
      setState(291);
      enumField();
      setState(296);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(297);
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
  enterRule(_localctx, 50, LogosParser::RuleEnumField);
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
    setState(299);
    match(LogosParser::CONST);
    setState(302);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(300);
      match(LogosParser::EQUAL);
      setState(301);
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

tree::TerminalNode* LogosParser::ExprContext::NOT_EQUAL() {
  return getToken(LogosParser::NOT_EQUAL, 0);
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
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, LogosParser::RuleExpr, precedence);

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
    setState(310);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::LBRACE:
      case LogosParser::LBRACK:
      case LogosParser::SELF:
      case LogosParser::INTEGER:
      case LogosParser::FLOAT:
      case LogosParser::BOOL:
      case LogosParser::TYPE:
      case LogosParser::VARIABLE:
      case LogosParser::STRING: {
        setState(305);
        unaryExpr();
        break;
      }

      case LogosParser::LPAREN: {
        setState(306);
        match(LogosParser::LPAREN);
        setState(307);
        antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
        setState(308);
        match(LogosParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(323);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(321);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(312);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(313);
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
          setState(314);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(315);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(316);
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
          setState(317);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(318);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(319);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 6174) != 0))) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(320);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(325);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
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
  enterRule(_localctx, 54, LogosParser::RuleExprList);
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
    setState(326);
    expr(0);
    setState(331);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(327);
        match(LogosParser::COMMA);
        setState(328);
        expr(0); 
      }
      setState(333);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
    setState(335);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(334);
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

//----------------- UnaryExprContext ------------------------------------------------------------------

LogosParser::UnaryExprContext::UnaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::UnaryExprContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::SELF() {
  return getToken(LogosParser::SELF, 0);
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

LogosParser::ArrayContext* LogosParser::UnaryExprContext::array() {
  return getRuleContext<LogosParser::ArrayContext>(0);
}

LogosParser::MapContext* LogosParser::UnaryExprContext::map() {
  return getRuleContext<LogosParser::MapContext>(0);
}

LogosParser::ArrayIndexContext* LogosParser::UnaryExprContext::arrayIndex() {
  return getRuleContext<LogosParser::ArrayIndexContext>(0);
}

LogosParser::SelectionContext* LogosParser::UnaryExprContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}


size_t LogosParser::UnaryExprContext::getRuleIndex() const {
  return LogosParser::RuleUnaryExpr;
}


LogosParser::UnaryExprContext* LogosParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 56, LogosParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(346);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(337);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(338);
      match(LogosParser::SELF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(339);
      funcCall();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(340);
      constructor();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(341);
      constant();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(342);
      array();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(343);
      map();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(344);
      arrayIndex();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(345);
      selection();
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
  enterRule(_localctx, 58, LogosParser::RuleArray);
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
    setState(348);
    match(LogosParser::LBRACK);
    setState(349);
    expr(0);
    setState(354);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::COMMA) {
      setState(350);
      match(LogosParser::COMMA);
      setState(351);
      expr(0);
      setState(356);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(357);
    match(LogosParser::RBRACK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MapContext ------------------------------------------------------------------

LogosParser::MapContext::MapContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::MapContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

tree::TerminalNode* LogosParser::MapContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

std::vector<LogosParser::ExprContext *> LogosParser::MapContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::MapContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::MapContext::COLON() {
  return getTokens(LogosParser::COLON);
}

tree::TerminalNode* LogosParser::MapContext::COLON(size_t i) {
  return getToken(LogosParser::COLON, i);
}

std::vector<tree::TerminalNode *> LogosParser::MapContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::MapContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::MapContext::getRuleIndex() const {
  return LogosParser::RuleMap;
}


LogosParser::MapContext* LogosParser::map() {
  MapContext *_localctx = _tracker.createInstance<MapContext>(_ctx, getState());
  enterRule(_localctx, 60, LogosParser::RuleMap);
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
    setState(359);
    match(LogosParser::LBRACE);
    setState(368);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2093470676157088) != 0)) {
      setState(360);
      expr(0);
      setState(361);
      match(LogosParser::COLON);
      setState(362);
      expr(0);
      setState(364);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(363);
        match(LogosParser::COMMA);
      }
      setState(370);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(371);
    match(LogosParser::RBRACE);
   
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
  enterRule(_localctx, 62, LogosParser::RuleFuncCall);
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
    setState(373);
    match(LogosParser::VARIABLE);
    setState(374);
    match(LogosParser::LPAREN);
    setState(376);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2093470676157088) != 0)) {
      setState(375);
      funcArgList();
    }
    setState(378);
    match(LogosParser::RPAREN);
   
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
  enterRule(_localctx, 64, LogosParser::RuleConstructor);
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
    setState(380);
    match(LogosParser::TYPE);
    setState(381);
    match(LogosParser::LPAREN);
    setState(383);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2093470676157088) != 0)) {
      setState(382);
      funcArgList();
    }
    setState(385);
    match(LogosParser::RPAREN);
   
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
  enterRule(_localctx, 66, LogosParser::RuleFuncArgList);
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
    setState(387);
    funcArg();
    setState(392);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(388);
        match(LogosParser::COMMA);
        setState(389);
        funcArg(); 
      }
      setState(394);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    }
    setState(396);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(395);
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
  enterRule(_localctx, 68, LogosParser::RuleFuncArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(400);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      setState(398);
      match(LogosParser::VARIABLE);
      setState(399);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(402);
    expr(0);
   
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
  enterRule(_localctx, 70, LogosParser::RuleConstant);
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
    setState(404);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1249045209153536) != 0))) {
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

LogosParser::FuncCallContext* LogosParser::ArrayIndexContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

tree::TerminalNode* LogosParser::ArrayIndexContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
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
  enterRule(_localctx, 72, LogosParser::RuleArrayIndex);

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
    setState(408);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(406);
      funcCall();
      break;
    }

    case 2: {
      setState(407);
      match(LogosParser::VARIABLE);
      break;
    }

    default:
      break;
    }
    setState(414); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(410);
              match(LogosParser::LBRACK);
              setState(411);
              expr(0);
              setState(412);
              match(LogosParser::RBRACK);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(416); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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

LogosParser::FirstSelectionElementContext* LogosParser::SelectionContext::firstSelectionElement() {
  return getRuleContext<LogosParser::FirstSelectionElementContext>(0);
}

std::vector<tree::TerminalNode *> LogosParser::SelectionContext::DOT() {
  return getTokens(LogosParser::DOT);
}

tree::TerminalNode* LogosParser::SelectionContext::DOT(size_t i) {
  return getToken(LogosParser::DOT, i);
}

std::vector<LogosParser::InnerSelectionElementContext *> LogosParser::SelectionContext::innerSelectionElement() {
  return getRuleContexts<LogosParser::InnerSelectionElementContext>();
}

LogosParser::InnerSelectionElementContext* LogosParser::SelectionContext::innerSelectionElement(size_t i) {
  return getRuleContext<LogosParser::InnerSelectionElementContext>(i);
}


size_t LogosParser::SelectionContext::getRuleIndex() const {
  return LogosParser::RuleSelection;
}


LogosParser::SelectionContext* LogosParser::selection() {
  SelectionContext *_localctx = _tracker.createInstance<SelectionContext>(_ctx, getState());
  enterRule(_localctx, 74, LogosParser::RuleSelection);

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
    setState(418);
    firstSelectionElement();
    setState(421); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(419);
              match(LogosParser::DOT);
              setState(420);
              innerSelectionElement();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(423); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FirstSelectionElementContext ------------------------------------------------------------------

LogosParser::FirstSelectionElementContext::FirstSelectionElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::FirstSelectionElementContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::FirstSelectionElementContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::FirstSelectionElementContext::SELF() {
  return getToken(LogosParser::SELF, 0);
}

LogosParser::FuncCallContext* LogosParser::FirstSelectionElementContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::ConstructorContext* LogosParser::FirstSelectionElementContext::constructor() {
  return getRuleContext<LogosParser::ConstructorContext>(0);
}

LogosParser::ArrayIndexContext* LogosParser::FirstSelectionElementContext::arrayIndex() {
  return getRuleContext<LogosParser::ArrayIndexContext>(0);
}


size_t LogosParser::FirstSelectionElementContext::getRuleIndex() const {
  return LogosParser::RuleFirstSelectionElement;
}


LogosParser::FirstSelectionElementContext* LogosParser::firstSelectionElement() {
  FirstSelectionElementContext *_localctx = _tracker.createInstance<FirstSelectionElementContext>(_ctx, getState());
  enterRule(_localctx, 76, LogosParser::RuleFirstSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(431);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(425);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(426);
      match(LogosParser::TYPE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(427);
      match(LogosParser::SELF);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(428);
      funcCall();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(429);
      constructor();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(430);
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

//----------------- InnerSelectionElementContext ------------------------------------------------------------------

LogosParser::InnerSelectionElementContext::InnerSelectionElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::InnerSelectionElementContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

LogosParser::FuncCallContext* LogosParser::InnerSelectionElementContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::ArrayIndexContext* LogosParser::InnerSelectionElementContext::arrayIndex() {
  return getRuleContext<LogosParser::ArrayIndexContext>(0);
}


size_t LogosParser::InnerSelectionElementContext::getRuleIndex() const {
  return LogosParser::RuleInnerSelectionElement;
}


LogosParser::InnerSelectionElementContext* LogosParser::innerSelectionElement() {
  InnerSelectionElementContext *_localctx = _tracker.createInstance<InnerSelectionElementContext>(_ctx, getState());
  enterRule(_localctx, 78, LogosParser::RuleInnerSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(436);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(433);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(434);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(435);
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
  enterRule(_localctx, 80, LogosParser::RuleRange);
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
    setState(439);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2093470676157088) != 0)) {
      setState(438);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
    }
    setState(441);
    match(LogosParser::DOUBLE_DOT);
    setState(442);
    antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

LogosParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::TypeContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

std::vector<tree::TerminalNode *> LogosParser::TypeContext::LBRACK() {
  return getTokens(LogosParser::LBRACK);
}

tree::TerminalNode* LogosParser::TypeContext::LBRACK(size_t i) {
  return getToken(LogosParser::LBRACK, i);
}

std::vector<tree::TerminalNode *> LogosParser::TypeContext::RBRACK() {
  return getTokens(LogosParser::RBRACK);
}

tree::TerminalNode* LogosParser::TypeContext::RBRACK(size_t i) {
  return getToken(LogosParser::RBRACK, i);
}

std::vector<tree::TerminalNode *> LogosParser::TypeContext::INTEGER() {
  return getTokens(LogosParser::INTEGER);
}

tree::TerminalNode* LogosParser::TypeContext::INTEGER(size_t i) {
  return getToken(LogosParser::INTEGER, i);
}

tree::TerminalNode* LogosParser::TypeContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

std::vector<LogosParser::TypeContext *> LogosParser::TypeContext::type() {
  return getRuleContexts<LogosParser::TypeContext>();
}

LogosParser::TypeContext* LogosParser::TypeContext::type(size_t i) {
  return getRuleContext<LogosParser::TypeContext>(i);
}

tree::TerminalNode* LogosParser::TypeContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::TypeContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}


size_t LogosParser::TypeContext::getRuleIndex() const {
  return LogosParser::RuleType;
}


LogosParser::TypeContext* LogosParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 82, LogosParser::RuleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(461);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(444);
        match(LogosParser::TYPE);
        setState(452);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == LogosParser::LBRACK) {
          setState(445);
          match(LogosParser::LBRACK);
          setState(447);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == LogosParser::INTEGER) {
            setState(446);
            match(LogosParser::INTEGER);
          }
          setState(449);
          match(LogosParser::RBRACK);
          setState(454);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case LogosParser::LBRACE: {
        enterOuterAlt(_localctx, 2);
        setState(455);
        match(LogosParser::LBRACE);
        setState(456);
        type();
        setState(457);
        match(LogosParser::COLON);
        setState(458);
        type();
        setState(459);
        match(LogosParser::RBRACE);
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

bool LogosParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 26: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

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
