
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
      "innerSelectionElement", "range", "type", "vector"
    },
    std::vector<std::string>{
      "", "'=='", "'!='", "'>='", "'<='", "'('", "')'", "'{'", "'}'", "'['", 
      "']'", "'<'", "'>'", "','", "'..'", "'.'", "':'", "'='", "'-'", "'+'", 
      "'*'", "'/'", "'#'", "'\\u003F'", "'!'", "'%'", "'$'", "'&'", "'object'", 
      "'self'", "'Self'", "'interface'", "'enum'", "'vec'", "'vec2'", "'vec3'", 
      "'vec4'", "'implements'", "'import'", "'if'", "'else'", "'for'", "'break'", 
      "'continue'", "'return'", "'and'", "'or'", "'not'", "'in'", "", "", 
      "", "'null'"
    },
    std::vector<std::string>{
      "", "DOUBLE_EQUAL", "NOT_EQUAL", "GE", "LE", "LPAREN", "RPAREN", "LBRACE", 
      "RBRACE", "LBRACK", "RBRACK", "LANGLE", "RANGLE", "COMMA", "DOUBLE_DOT", 
      "DOT", "COLON", "EQUAL", "MINUS", "PLUS", "STAR", "SLASH", "HASH", 
      "QUEST_MARK", "EXCLA_MARK", "PERCENT", "DOLLAR", "AMPERSAND", "OBJECT", 
      "SELF_INSTANCE", "SELF_CLASS", "INTERFACE", "ENUM", "VEC", "VEC2", 
      "VEC3", "VEC4", "IMPLEMENTS", "IMPORT", "IF", "ELSE", "FOR", "BREAK", 
      "CONTINUE", "RETURN", "AND", "OR", "NOT", "IN", "INTEGER", "FLOAT", 
      "BOOL", "NULL", "CONST", "TYPE", "VARIABLE", "STRING", "LINE_COMMENT", 
      "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,59,489,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,1,0,1,0,1,0,3,0,90,8,0,1,1,1,1,4,1,94,8,1,11,1,12,1,95,1,1,1,1,1,2,
  	1,2,3,2,102,8,2,1,2,5,2,105,8,2,10,2,12,2,108,9,2,1,2,5,2,111,8,2,10,
  	2,12,2,114,9,2,1,2,1,2,1,3,1,3,3,3,120,8,3,1,3,5,3,123,8,3,10,3,12,3,
  	126,9,3,1,3,4,3,129,8,3,11,3,12,3,130,1,3,5,3,134,8,3,10,3,12,3,137,9,
  	3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,
  	3,7,156,8,7,1,7,1,7,1,7,3,7,161,8,7,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,10,
  	5,10,171,8,10,10,10,12,10,174,9,10,1,10,3,10,177,8,10,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,3,11,188,8,11,1,12,1,12,5,12,192,8,12,10,
  	12,12,12,195,9,12,1,12,1,12,1,13,1,13,1,13,3,13,202,8,13,1,13,1,13,1,
  	13,1,13,1,14,1,14,1,14,1,14,1,14,3,14,213,8,14,1,15,1,15,1,15,1,15,1,
  	16,1,16,1,16,1,16,5,16,223,8,16,10,16,12,16,226,9,16,1,16,3,16,229,8,
  	16,1,16,3,16,232,8,16,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,19,1,19,3,
  	19,243,8,19,1,19,1,19,5,19,247,8,19,10,19,12,19,250,9,19,1,19,1,19,1,
  	19,3,19,255,8,19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,5,
  	21,267,8,21,10,21,12,21,270,9,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,
  	21,5,21,280,8,21,10,21,12,21,283,9,21,1,21,1,21,1,21,1,21,1,21,1,21,3,
  	21,291,8,21,1,21,3,21,294,8,21,1,22,1,22,1,22,1,22,1,22,3,22,301,8,22,
  	1,23,1,23,1,23,1,24,1,24,1,24,1,24,5,24,310,8,24,10,24,12,24,313,9,24,
  	1,24,1,24,1,25,1,25,1,25,3,25,320,8,25,1,26,1,26,1,26,1,26,1,26,1,26,
  	3,26,328,8,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,5,26,339,8,
  	26,10,26,12,26,342,9,26,1,27,1,27,1,27,5,27,347,8,27,10,27,12,27,350,
  	9,27,1,27,3,27,353,8,27,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,1,28,
  	1,28,1,28,3,28,366,8,28,1,29,1,29,1,29,1,29,5,29,372,8,29,10,29,12,29,
  	375,9,29,1,29,3,29,378,8,29,1,29,1,29,1,30,1,30,1,30,1,30,1,30,3,30,387,
  	8,30,5,30,389,8,30,10,30,12,30,392,9,30,1,30,1,30,1,31,1,31,1,31,3,31,
  	399,8,31,1,31,1,31,1,32,1,32,1,32,3,32,406,8,32,1,32,1,32,1,33,1,33,1,
  	33,5,33,413,8,33,10,33,12,33,416,9,33,1,33,3,33,419,8,33,1,34,1,34,3,
  	34,423,8,34,1,34,1,34,1,35,1,35,1,36,1,36,3,36,431,8,36,1,36,1,36,1,36,
  	1,36,4,36,437,8,36,11,36,12,36,438,1,37,1,37,1,37,4,37,444,8,37,11,37,
  	12,37,445,1,38,1,38,1,38,1,38,1,38,1,38,1,38,3,38,455,8,38,1,39,1,39,
  	1,39,3,39,460,8,39,1,40,3,40,463,8,40,1,40,1,40,1,40,1,41,1,41,1,41,1,
  	41,3,41,472,8,41,1,41,4,41,475,8,41,11,41,12,41,476,1,41,1,41,1,41,1,
  	41,1,41,1,41,3,41,485,8,41,1,42,1,42,1,42,0,1,52,43,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,
  	62,64,66,68,70,72,74,76,78,80,82,84,0,5,1,0,20,21,1,0,18,19,2,0,1,4,11,
  	12,2,0,49,51,56,56,1,0,33,36,527,0,89,1,0,0,0,2,91,1,0,0,0,4,99,1,0,0,
  	0,6,117,1,0,0,0,8,140,1,0,0,0,10,144,1,0,0,0,12,148,1,0,0,0,14,152,1,
  	0,0,0,16,162,1,0,0,0,18,165,1,0,0,0,20,167,1,0,0,0,22,187,1,0,0,0,24,
  	189,1,0,0,0,26,201,1,0,0,0,28,207,1,0,0,0,30,214,1,0,0,0,32,231,1,0,0,
  	0,34,233,1,0,0,0,36,237,1,0,0,0,38,240,1,0,0,0,40,258,1,0,0,0,42,293,
  	1,0,0,0,44,300,1,0,0,0,46,302,1,0,0,0,48,305,1,0,0,0,50,316,1,0,0,0,52,
  	327,1,0,0,0,54,343,1,0,0,0,56,365,1,0,0,0,58,367,1,0,0,0,60,381,1,0,0,
  	0,62,395,1,0,0,0,64,402,1,0,0,0,66,409,1,0,0,0,68,422,1,0,0,0,70,426,
  	1,0,0,0,72,430,1,0,0,0,74,440,1,0,0,0,76,454,1,0,0,0,78,459,1,0,0,0,80,
  	462,1,0,0,0,82,484,1,0,0,0,84,486,1,0,0,0,86,90,3,2,1,0,87,90,3,4,2,0,
  	88,90,3,6,3,0,89,86,1,0,0,0,89,87,1,0,0,0,89,88,1,0,0,0,90,1,1,0,0,0,
  	91,93,3,48,24,0,92,94,3,16,8,0,93,92,1,0,0,0,94,95,1,0,0,0,95,93,1,0,
  	0,0,95,96,1,0,0,0,96,97,1,0,0,0,97,98,5,0,0,1,98,3,1,0,0,0,99,101,3,8,
  	4,0,100,102,3,12,6,0,101,100,1,0,0,0,101,102,1,0,0,0,102,106,1,0,0,0,
  	103,105,3,28,14,0,104,103,1,0,0,0,105,108,1,0,0,0,106,104,1,0,0,0,106,
  	107,1,0,0,0,107,112,1,0,0,0,108,106,1,0,0,0,109,111,3,16,8,0,110,109,
  	1,0,0,0,111,114,1,0,0,0,112,110,1,0,0,0,112,113,1,0,0,0,113,115,1,0,0,
  	0,114,112,1,0,0,0,115,116,5,0,0,1,116,5,1,0,0,0,117,119,3,10,5,0,118,
  	120,3,12,6,0,119,118,1,0,0,0,119,120,1,0,0,0,120,124,1,0,0,0,121,123,
  	3,28,14,0,122,121,1,0,0,0,123,126,1,0,0,0,124,122,1,0,0,0,124,125,1,0,
  	0,0,125,128,1,0,0,0,126,124,1,0,0,0,127,129,3,14,7,0,128,127,1,0,0,0,
  	129,130,1,0,0,0,130,128,1,0,0,0,130,131,1,0,0,0,131,135,1,0,0,0,132,134,
  	3,16,8,0,133,132,1,0,0,0,134,137,1,0,0,0,135,133,1,0,0,0,135,136,1,0,
  	0,0,136,138,1,0,0,0,137,135,1,0,0,0,138,139,5,0,0,1,139,7,1,0,0,0,140,
  	141,5,28,0,0,141,142,5,16,0,0,142,143,5,54,0,0,143,9,1,0,0,0,144,145,
  	5,31,0,0,145,146,5,16,0,0,146,147,5,54,0,0,147,11,1,0,0,0,148,149,5,37,
  	0,0,149,150,5,16,0,0,150,151,5,54,0,0,151,13,1,0,0,0,152,153,5,55,0,0,
  	153,155,5,5,0,0,154,156,3,20,10,0,155,154,1,0,0,0,155,156,1,0,0,0,156,
  	157,1,0,0,0,157,160,5,6,0,0,158,159,5,16,0,0,159,161,3,82,41,0,160,158,
  	1,0,0,0,160,161,1,0,0,0,161,15,1,0,0,0,162,163,3,14,7,0,163,164,3,18,
  	9,0,164,17,1,0,0,0,165,166,3,24,12,0,166,19,1,0,0,0,167,172,3,28,14,0,
  	168,169,5,13,0,0,169,171,3,28,14,0,170,168,1,0,0,0,171,174,1,0,0,0,172,
  	170,1,0,0,0,172,173,1,0,0,0,173,176,1,0,0,0,174,172,1,0,0,0,175,177,5,
  	13,0,0,176,175,1,0,0,0,176,177,1,0,0,0,177,21,1,0,0,0,178,188,3,26,13,
  	0,179,188,3,28,14,0,180,188,3,30,15,0,181,188,3,32,16,0,182,188,3,42,
  	21,0,183,188,3,44,22,0,184,188,3,46,23,0,185,188,3,48,24,0,186,188,3,
  	62,31,0,187,178,1,0,0,0,187,179,1,0,0,0,187,180,1,0,0,0,187,181,1,0,0,
  	0,187,182,1,0,0,0,187,183,1,0,0,0,187,184,1,0,0,0,187,185,1,0,0,0,187,
  	186,1,0,0,0,188,23,1,0,0,0,189,193,5,7,0,0,190,192,3,22,11,0,191,190,
  	1,0,0,0,192,195,1,0,0,0,193,191,1,0,0,0,193,194,1,0,0,0,194,196,1,0,0,
  	0,195,193,1,0,0,0,196,197,5,8,0,0,197,25,1,0,0,0,198,202,5,55,0,0,199,
  	202,3,72,36,0,200,202,3,74,37,0,201,198,1,0,0,0,201,199,1,0,0,0,201,200,
  	1,0,0,0,202,203,1,0,0,0,203,204,5,16,0,0,204,205,5,17,0,0,205,206,3,52,
  	26,0,206,27,1,0,0,0,207,208,5,55,0,0,208,209,5,16,0,0,209,212,3,82,41,
  	0,210,211,5,17,0,0,211,213,3,52,26,0,212,210,1,0,0,0,212,213,1,0,0,0,
  	213,29,1,0,0,0,214,215,5,55,0,0,215,216,5,17,0,0,216,217,3,52,26,0,217,
  	31,1,0,0,0,218,219,5,39,0,0,219,220,3,52,26,0,220,224,3,24,12,0,221,223,
  	3,34,17,0,222,221,1,0,0,0,223,226,1,0,0,0,224,222,1,0,0,0,224,225,1,0,
  	0,0,225,228,1,0,0,0,226,224,1,0,0,0,227,229,3,36,18,0,228,227,1,0,0,0,
  	228,229,1,0,0,0,229,232,1,0,0,0,230,232,3,38,19,0,231,218,1,0,0,0,231,
  	230,1,0,0,0,232,33,1,0,0,0,233,234,5,40,0,0,234,235,3,52,26,0,235,236,
  	3,24,12,0,236,35,1,0,0,0,237,238,5,40,0,0,238,239,3,24,12,0,239,37,1,
  	0,0,0,240,242,5,39,0,0,241,243,3,52,26,0,242,241,1,0,0,0,242,243,1,0,
  	0,0,243,244,1,0,0,0,244,248,5,7,0,0,245,247,3,40,20,0,246,245,1,0,0,0,
  	247,250,1,0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,254,1,0,0,0,250,248,
  	1,0,0,0,251,252,5,40,0,0,252,253,5,16,0,0,253,255,3,24,12,0,254,251,1,
  	0,0,0,254,255,1,0,0,0,255,256,1,0,0,0,256,257,5,8,0,0,257,39,1,0,0,0,
  	258,259,3,52,26,0,259,260,5,16,0,0,260,261,3,24,12,0,261,41,1,0,0,0,262,
  	263,5,41,0,0,263,268,5,55,0,0,264,265,5,13,0,0,265,267,5,55,0,0,266,264,
  	1,0,0,0,267,270,1,0,0,0,268,266,1,0,0,0,268,269,1,0,0,0,269,271,1,0,0,
  	0,270,268,1,0,0,0,271,272,5,48,0,0,272,273,3,80,40,0,273,274,3,24,12,
  	0,274,294,1,0,0,0,275,276,5,41,0,0,276,281,5,55,0,0,277,278,5,13,0,0,
  	278,280,5,55,0,0,279,277,1,0,0,0,280,283,1,0,0,0,281,279,1,0,0,0,281,
  	282,1,0,0,0,282,284,1,0,0,0,283,281,1,0,0,0,284,285,5,48,0,0,285,286,
  	3,56,28,0,286,287,3,24,12,0,287,294,1,0,0,0,288,290,5,41,0,0,289,291,
  	5,55,0,0,290,289,1,0,0,0,290,291,1,0,0,0,291,292,1,0,0,0,292,294,3,24,
  	12,0,293,262,1,0,0,0,293,275,1,0,0,0,293,288,1,0,0,0,294,43,1,0,0,0,295,
  	296,5,42,0,0,296,301,3,52,26,0,297,298,5,42,0,0,298,301,5,39,0,0,299,
  	301,5,43,0,0,300,295,1,0,0,0,300,297,1,0,0,0,300,299,1,0,0,0,301,45,1,
  	0,0,0,302,303,5,44,0,0,303,304,3,52,26,0,304,47,1,0,0,0,305,306,5,32,
  	0,0,306,307,5,54,0,0,307,311,5,7,0,0,308,310,3,50,25,0,309,308,1,0,0,
  	0,310,313,1,0,0,0,311,309,1,0,0,0,311,312,1,0,0,0,312,314,1,0,0,0,313,
  	311,1,0,0,0,314,315,5,8,0,0,315,49,1,0,0,0,316,319,5,53,0,0,317,318,5,
  	17,0,0,318,320,5,56,0,0,319,317,1,0,0,0,319,320,1,0,0,0,320,51,1,0,0,
  	0,321,322,6,26,-1,0,322,328,3,56,28,0,323,324,5,5,0,0,324,325,3,52,26,
  	0,325,326,5,6,0,0,326,328,1,0,0,0,327,321,1,0,0,0,327,323,1,0,0,0,328,
  	340,1,0,0,0,329,330,10,5,0,0,330,331,7,0,0,0,331,339,3,52,26,6,332,333,
  	10,4,0,0,333,334,7,1,0,0,334,339,3,52,26,5,335,336,10,3,0,0,336,337,7,
  	2,0,0,337,339,3,52,26,4,338,329,1,0,0,0,338,332,1,0,0,0,338,335,1,0,0,
  	0,339,342,1,0,0,0,340,338,1,0,0,0,340,341,1,0,0,0,341,53,1,0,0,0,342,
  	340,1,0,0,0,343,348,3,52,26,0,344,345,5,13,0,0,345,347,3,52,26,0,346,
  	344,1,0,0,0,347,350,1,0,0,0,348,346,1,0,0,0,348,349,1,0,0,0,349,352,1,
  	0,0,0,350,348,1,0,0,0,351,353,5,13,0,0,352,351,1,0,0,0,352,353,1,0,0,
  	0,353,55,1,0,0,0,354,366,5,55,0,0,355,366,5,29,0,0,356,366,5,30,0,0,357,
  	366,5,52,0,0,358,366,3,62,31,0,359,366,3,64,32,0,360,366,3,70,35,0,361,
  	366,3,58,29,0,362,366,3,60,30,0,363,366,3,72,36,0,364,366,3,74,37,0,365,
  	354,1,0,0,0,365,355,1,0,0,0,365,356,1,0,0,0,365,357,1,0,0,0,365,358,1,
  	0,0,0,365,359,1,0,0,0,365,360,1,0,0,0,365,361,1,0,0,0,365,362,1,0,0,0,
  	365,363,1,0,0,0,365,364,1,0,0,0,366,57,1,0,0,0,367,368,5,9,0,0,368,373,
  	3,52,26,0,369,370,5,13,0,0,370,372,3,52,26,0,371,369,1,0,0,0,372,375,
  	1,0,0,0,373,371,1,0,0,0,373,374,1,0,0,0,374,377,1,0,0,0,375,373,1,0,0,
  	0,376,378,5,13,0,0,377,376,1,0,0,0,377,378,1,0,0,0,378,379,1,0,0,0,379,
  	380,5,10,0,0,380,59,1,0,0,0,381,390,5,7,0,0,382,383,3,52,26,0,383,384,
  	5,16,0,0,384,386,3,52,26,0,385,387,5,13,0,0,386,385,1,0,0,0,386,387,1,
  	0,0,0,387,389,1,0,0,0,388,382,1,0,0,0,389,392,1,0,0,0,390,388,1,0,0,0,
  	390,391,1,0,0,0,391,393,1,0,0,0,392,390,1,0,0,0,393,394,5,8,0,0,394,61,
  	1,0,0,0,395,396,5,55,0,0,396,398,5,5,0,0,397,399,3,66,33,0,398,397,1,
  	0,0,0,398,399,1,0,0,0,399,400,1,0,0,0,400,401,5,6,0,0,401,63,1,0,0,0,
  	402,403,5,54,0,0,403,405,5,5,0,0,404,406,3,66,33,0,405,404,1,0,0,0,405,
  	406,1,0,0,0,406,407,1,0,0,0,407,408,5,6,0,0,408,65,1,0,0,0,409,414,3,
  	68,34,0,410,411,5,13,0,0,411,413,3,68,34,0,412,410,1,0,0,0,413,416,1,
  	0,0,0,414,412,1,0,0,0,414,415,1,0,0,0,415,418,1,0,0,0,416,414,1,0,0,0,
  	417,419,5,13,0,0,418,417,1,0,0,0,418,419,1,0,0,0,419,67,1,0,0,0,420,421,
  	5,55,0,0,421,423,5,17,0,0,422,420,1,0,0,0,422,423,1,0,0,0,423,424,1,0,
  	0,0,424,425,3,52,26,0,425,69,1,0,0,0,426,427,7,3,0,0,427,71,1,0,0,0,428,
  	431,3,62,31,0,429,431,5,55,0,0,430,428,1,0,0,0,430,429,1,0,0,0,431,436,
  	1,0,0,0,432,433,5,9,0,0,433,434,3,52,26,0,434,435,5,10,0,0,435,437,1,
  	0,0,0,436,432,1,0,0,0,437,438,1,0,0,0,438,436,1,0,0,0,438,439,1,0,0,0,
  	439,73,1,0,0,0,440,443,3,76,38,0,441,442,5,15,0,0,442,444,3,78,39,0,443,
  	441,1,0,0,0,444,445,1,0,0,0,445,443,1,0,0,0,445,446,1,0,0,0,446,75,1,
  	0,0,0,447,455,5,55,0,0,448,455,5,54,0,0,449,455,5,30,0,0,450,455,5,29,
  	0,0,451,455,3,62,31,0,452,455,3,64,32,0,453,455,3,72,36,0,454,447,1,0,
  	0,0,454,448,1,0,0,0,454,449,1,0,0,0,454,450,1,0,0,0,454,451,1,0,0,0,454,
  	452,1,0,0,0,454,453,1,0,0,0,455,77,1,0,0,0,456,460,5,55,0,0,457,460,3,
  	62,31,0,458,460,3,72,36,0,459,456,1,0,0,0,459,457,1,0,0,0,459,458,1,0,
  	0,0,460,79,1,0,0,0,461,463,3,52,26,0,462,461,1,0,0,0,462,463,1,0,0,0,
  	463,464,1,0,0,0,464,465,5,14,0,0,465,466,3,52,26,0,466,81,1,0,0,0,467,
  	485,5,54,0,0,468,474,5,54,0,0,469,471,5,9,0,0,470,472,5,49,0,0,471,470,
  	1,0,0,0,471,472,1,0,0,0,472,473,1,0,0,0,473,475,5,10,0,0,474,469,1,0,
  	0,0,475,476,1,0,0,0,476,474,1,0,0,0,476,477,1,0,0,0,477,485,1,0,0,0,478,
  	479,5,7,0,0,479,480,3,82,41,0,480,481,5,16,0,0,481,482,3,82,41,0,482,
  	483,5,8,0,0,483,485,1,0,0,0,484,467,1,0,0,0,484,468,1,0,0,0,484,478,1,
  	0,0,0,485,83,1,0,0,0,486,487,7,4,0,0,487,85,1,0,0,0,54,89,95,101,106,
  	112,119,124,130,135,155,160,172,176,187,193,201,212,224,228,231,242,248,
  	254,268,281,290,293,300,311,319,327,338,340,348,352,365,373,377,386,390,
  	398,405,414,418,422,430,438,445,454,459,462,471,476,484
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
    setState(89);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::ENUM: {
        enterOuterAlt(_localctx, 1);
        setState(86);
        mainFile();
        break;
      }

      case LogosParser::OBJECT: {
        enterOuterAlt(_localctx, 2);
        setState(87);
        objectFile();
        break;
      }

      case LogosParser::INTERFACE: {
        enterOuterAlt(_localctx, 3);
        setState(88);
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

LogosParser::EnumDeclarationContext* LogosParser::MainFileContext::enumDeclaration() {
  return getRuleContext<LogosParser::EnumDeclarationContext>(0);
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
    setState(91);
    enumDeclaration();
    setState(93); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(92);
      funcImplementation();
      setState(95); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(97);
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
    setState(99);
    objectDeclaration();
    setState(101);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(100);
      objectImplements();
    }
    setState(106);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(103);
        explicitVarDec(); 
      }
      setState(108);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
    setState(112);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(109);
      funcImplementation();
      setState(114);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(115);
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
    setState(117);
    interfaceDeclaration();
    setState(119);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(118);
      objectImplements();
    }
    setState(124);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(121);
        explicitVarDec(); 
      }
      setState(126);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
    setState(128); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(127);
              funcSignature();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(130); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(135);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(132);
      funcImplementation();
      setState(137);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(138);
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
    setState(140);
    match(LogosParser::OBJECT);
    setState(141);
    match(LogosParser::COLON);
    setState(142);
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
    setState(144);
    match(LogosParser::INTERFACE);
    setState(145);
    match(LogosParser::COLON);
    setState(146);
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
    setState(148);
    match(LogosParser::IMPLEMENTS);
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
    setState(152);
    match(LogosParser::VARIABLE);
    setState(153);
    match(LogosParser::LPAREN);
    setState(155);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(154);
      paramList();
    }
    setState(157);
    match(LogosParser::RPAREN);
    setState(160);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(158);
      match(LogosParser::COLON);
      setState(159);
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
    setState(162);
    funcSignature();
    setState(163);
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
    setState(165);
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
    setState(167);
    explicitVarDec();
    setState(172);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(168);
        match(LogosParser::COMMA);
        setState(169);
        explicitVarDec(); 
      }
      setState(174);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
    setState(176);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(175);
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
    setState(187);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(178);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(179);
      explicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(180);
      implicitVarDec();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(181);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(182);
      loopStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(183);
      controlFlow();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(184);
      returnStatement();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(185);
      enumDeclaration();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(186);
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
    setState(189);
    match(LogosParser::LBRACE);
    setState(193);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 54076736538673152) != 0)) {
      setState(190);
      statement();
      setState(195);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(196);
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
    setState(201);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(198);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      setState(199);
      arrayIndex();
      break;
    }

    case 3: {
      setState(200);
      selection();
      break;
    }

    default:
      break;
    }
    setState(203);
    match(LogosParser::COLON);
    setState(204);
    match(LogosParser::EQUAL);
    setState(205);
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
    setState(207);
    match(LogosParser::VARIABLE);
    setState(208);
    match(LogosParser::COLON);
    setState(209);
    type();
    setState(212);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(210);
      match(LogosParser::EQUAL);
      setState(211);
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
    setState(214);
    match(LogosParser::VARIABLE);
    setState(215);
    match(LogosParser::EQUAL);
    setState(216);
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
    setState(231);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(218);
      match(LogosParser::IF);
      setState(219);
      expr(0);
      setState(220);
      statementsBlock();
      setState(224);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(221);
          elseIfStatement(); 
        }
        setState(226);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
      }
      setState(228);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::ELSE) {
        setState(227);
        elseStatement();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(230);
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
    setState(233);
    match(LogosParser::ELSE);
    setState(234);
    expr(0);
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
    setState(237);
    match(LogosParser::ELSE);
    setState(238);
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
    setState(240);
    match(LogosParser::IF);
    setState(242);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      setState(241);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(244);
    match(LogosParser::LBRACE);
    setState(248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 134545040478306976) != 0)) {
      setState(245);
      pattern();
      setState(250);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(254);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(251);
      match(LogosParser::ELSE);
      setState(252);
      match(LogosParser::COLON);
      setState(253);
      statementsBlock();
    }
    setState(256);
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
    setState(258);
    expr(0);
    setState(259);
    match(LogosParser::COLON);
    setState(260);
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

std::vector<tree::TerminalNode *> LogosParser::LoopStatementContext::VARIABLE() {
  return getTokens(LogosParser::VARIABLE);
}

tree::TerminalNode* LogosParser::LoopStatementContext::VARIABLE(size_t i) {
  return getToken(LogosParser::VARIABLE, i);
}

tree::TerminalNode* LogosParser::LoopStatementContext::IN() {
  return getToken(LogosParser::IN, 0);
}

LogosParser::StatementsBlockContext* LogosParser::LoopStatementContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}

LogosParser::RangeContext* LogosParser::LoopStatementContext::range() {
  return getRuleContext<LogosParser::RangeContext>(0);
}

std::vector<tree::TerminalNode *> LogosParser::LoopStatementContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::LoopStatementContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}

LogosParser::UnaryExprContext* LogosParser::LoopStatementContext::unaryExpr() {
  return getRuleContext<LogosParser::UnaryExprContext>(0);
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
    setState(293);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(262);
      match(LogosParser::FOR);
      setState(263);
      match(LogosParser::VARIABLE);
      setState(268);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LogosParser::COMMA) {
        setState(264);
        match(LogosParser::COMMA);
        setState(265);
        match(LogosParser::VARIABLE);
        setState(270);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(271);
      match(LogosParser::IN);
      setState(272);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(273);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(275);
      match(LogosParser::FOR);
      setState(276);
      match(LogosParser::VARIABLE);
      setState(281);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LogosParser::COMMA) {
        setState(277);
        match(LogosParser::COMMA);
        setState(278);
        match(LogosParser::VARIABLE);
        setState(283);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(284);
      match(LogosParser::IN);
      setState(285);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = unaryExpr();
      setState(286);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(288);
      match(LogosParser::FOR);
      setState(290);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::VARIABLE) {
        setState(289);
        match(LogosParser::VARIABLE);
      }
      setState(292);
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
    setState(300);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(295);
      match(LogosParser::BREAK);
      setState(296);
      expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(297);
      match(LogosParser::BREAK);
      setState(298);
      match(LogosParser::IF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(299);
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
    setState(302);
    match(LogosParser::RETURN);
    setState(303);
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
    setState(305);
    match(LogosParser::ENUM);
    setState(306);
    match(LogosParser::TYPE);
    setState(307);
    match(LogosParser::LBRACE);
    setState(311);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST) {
      setState(308);
      enumField();
      setState(313);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(314);
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
    setState(316);
    match(LogosParser::CONST);
    setState(319);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(317);
      match(LogosParser::EQUAL);
      setState(318);
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
    setState(327);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::LBRACE:
      case LogosParser::LBRACK:
      case LogosParser::SELF_INSTANCE:
      case LogosParser::SELF_CLASS:
      case LogosParser::INTEGER:
      case LogosParser::FLOAT:
      case LogosParser::BOOL:
      case LogosParser::NULL_:
      case LogosParser::TYPE:
      case LogosParser::VARIABLE:
      case LogosParser::STRING: {
        setState(322);
        unaryExpr();
        break;
      }

      case LogosParser::LPAREN: {
        setState(323);
        match(LogosParser::LPAREN);
        setState(324);
        antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
        setState(325);
        match(LogosParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(340);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(338);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(329);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(330);
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
          setState(331);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(332);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(333);
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
          setState(334);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(335);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(336);
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
          setState(337);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(342);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
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
    setState(343);
    expr(0);
    setState(348);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(344);
        match(LogosParser::COMMA);
        setState(345);
        expr(0); 
      }
      setState(350);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
    setState(352);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(351);
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

tree::TerminalNode* LogosParser::UnaryExprContext::SELF_INSTANCE() {
  return getToken(LogosParser::SELF_INSTANCE, 0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::SELF_CLASS() {
  return getToken(LogosParser::SELF_CLASS, 0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::NULL_() {
  return getToken(LogosParser::NULL_, 0);
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
    setState(365);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(354);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(355);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(356);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(357);
      match(LogosParser::NULL_);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(358);
      funcCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(359);
      constructor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(360);
      constant();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(361);
      array();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(362);
      map();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(363);
      arrayIndex();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(364);
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
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(367);
    match(LogosParser::LBRACK);
    setState(368);
    expr(0);
    setState(373);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(369);
        match(LogosParser::COMMA);
        setState(370);
        expr(0); 
      }
      setState(375);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    }
    setState(377);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(376);
      match(LogosParser::COMMA);
    }
    setState(379);
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
    setState(381);
    match(LogosParser::LBRACE);
    setState(390);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 134545040478306976) != 0)) {
      setState(382);
      expr(0);
      setState(383);
      match(LogosParser::COLON);
      setState(384);
      expr(0);
      setState(386);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(385);
        match(LogosParser::COMMA);
      }
      setState(392);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(393);
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
    setState(395);
    match(LogosParser::VARIABLE);
    setState(396);
    match(LogosParser::LPAREN);
    setState(398);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 134545040478306976) != 0)) {
      setState(397);
      funcArgList();
    }
    setState(400);
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
    setState(402);
    match(LogosParser::TYPE);
    setState(403);
    match(LogosParser::LPAREN);
    setState(405);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 134545040478306976) != 0)) {
      setState(404);
      funcArgList();
    }
    setState(407);
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
    setState(409);
    funcArg();
    setState(414);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(410);
        match(LogosParser::COMMA);
        setState(411);
        funcArg(); 
      }
      setState(416);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx);
    }
    setState(418);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(417);
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
    setState(422);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      setState(420);
      match(LogosParser::VARIABLE);
      setState(421);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(424);
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
    setState(426);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 75998243711877120) != 0))) {
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
    setState(430);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      setState(428);
      funcCall();
      break;
    }

    case 2: {
      setState(429);
      match(LogosParser::VARIABLE);
      break;
    }

    default:
      break;
    }
    setState(436); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(432);
              match(LogosParser::LBRACK);
              setState(433);
              expr(0);
              setState(434);
              match(LogosParser::RBRACK);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(438); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
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
    setState(440);
    firstSelectionElement();
    setState(443); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(441);
              match(LogosParser::DOT);
              setState(442);
              innerSelectionElement();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(445); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
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

tree::TerminalNode* LogosParser::FirstSelectionElementContext::SELF_CLASS() {
  return getToken(LogosParser::SELF_CLASS, 0);
}

tree::TerminalNode* LogosParser::FirstSelectionElementContext::SELF_INSTANCE() {
  return getToken(LogosParser::SELF_INSTANCE, 0);
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
    setState(454);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(447);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(448);
      match(LogosParser::TYPE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(449);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(450);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(451);
      funcCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(452);
      constructor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(453);
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
    setState(459);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(456);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(457);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(458);
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
    setState(462);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 134545040478306976) != 0)) {
      setState(461);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
    }
    setState(464);
    match(LogosParser::DOUBLE_DOT);
    setState(465);
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
    setState(484);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(467);
      match(LogosParser::TYPE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(468);
      match(LogosParser::TYPE);
      setState(474); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(469);
        match(LogosParser::LBRACK);
        setState(471);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LogosParser::INTEGER) {
          setState(470);
          match(LogosParser::INTEGER);
        }
        setState(473);
        match(LogosParser::RBRACK);
        setState(476); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == LogosParser::LBRACK);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(478);
      match(LogosParser::LBRACE);
      setState(479);
      type();
      setState(480);
      match(LogosParser::COLON);
      setState(481);
      type();
      setState(482);
      match(LogosParser::RBRACE);
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

//----------------- VectorContext ------------------------------------------------------------------

LogosParser::VectorContext::VectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::VectorContext::VEC() {
  return getToken(LogosParser::VEC, 0);
}

tree::TerminalNode* LogosParser::VectorContext::VEC2() {
  return getToken(LogosParser::VEC2, 0);
}

tree::TerminalNode* LogosParser::VectorContext::VEC3() {
  return getToken(LogosParser::VEC3, 0);
}

tree::TerminalNode* LogosParser::VectorContext::VEC4() {
  return getToken(LogosParser::VEC4, 0);
}


size_t LogosParser::VectorContext::getRuleIndex() const {
  return LogosParser::RuleVector;
}


LogosParser::VectorContext* LogosParser::vector() {
  VectorContext *_localctx = _tracker.createInstance<VectorContext>(_ctx, getState());
  enterRule(_localctx, 84, LogosParser::RuleVector);
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
    setState(486);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 128849018880) != 0))) {
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
