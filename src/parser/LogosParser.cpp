
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
      "logosFile", "extern", "logosEnvFile", "logosAppFile", "mainFile", 
      "objectFile", "interfaceFile", "interface", "group", "groupTypesList", 
      "groupTargetList", "interfaceBody", "object", "objectBody", "field", 
      "interfaceField", "objectDeclaration", "implements", "funcSignatureHeader", 
      "funcSignature", "interfaceFuncSignature", "funcImpl", "anonnymosfuncSignature", 
      "anonnymosFunc", "methodImplementation", "funcBody", "param", "statement", 
      "statementsBlock", "assignment", "explicitVarDec", "implicitVarDec", 
      "ifStatement", "elseIfStatement", "elseStatement", "patternMatching", 
      "pattern", "loopStatement", "breakStmt", "returnStatement", "enumDeclaration", 
      "enumField", "expr", "unaryExpr", "prefixExpr", "postfixExpr", "arrayExpr", 
      "hashMap", "keyValue", "funcCall", "funcArgList", "funcArg", "constructor", 
      "constructorArgList", "constructorArg", "constant", "iterIndex", "index", 
      "selection", "firstSelectionElement", "innerSelectionElement", "range", 
      "type", "mapType", "arraySize", "funcType", "vector", "requireEnvVars", 
      "assignemntOp"
    },
    std::vector<std::string>{
      "", "'C'", "'require'", "'envs'", "'=='", "'!='", "'>='", "'<='", 
      "'('", "')'", "'{'", "'}'", "'['", "']'", "'->'", "'<'", "'>'", "','", 
      "'...'", "'..'", "':='", "'+='", "'-='", "'*='", "'/='", "'%='", "'&='", 
      "'|='", "'^='", "'<<='", "'>>='", "'++'", "'--'", "'.'", "':'", "'='", 
      "'+'", "'-'", "'*'", "'/'", "'#'", "'\\u003F'", "'!'", "'%'", "'$'", 
      "'&'", "'|'", "'^'", "'<<'", "'>>'", "'object'", "'single'", "'self'", 
      "'Self'", "'interface'", "'extern'", "'pub'", "'implements'", "'const'", 
      "'enum'", "'vec2'", "'vec3'", "'vec4'", "'if'", "'else'", "'for'", 
      "'break'", "'continue'", "'return'", "'and'", "'or'", "'not'", "'in'", 
      "", "", "", "'null'"
    },
    std::vector<std::string>{
      "", "", "", "", "DOUBLE_EQUAL", "NOT_EQUAL", "GE", "LE", "LPAREN", 
      "RPAREN", "LBRACE", "RBRACE", "LBRACK", "RBRACK", "ARROW", "LANGLE", 
      "RANGLE", "COMMA", "TRIPLE_DOT", "DOUBLE_DOT", "WALRUS", "EQUAL_PLUS", 
      "EQUAL_MINUS", "EQUAL_STAR", "EQUAL_SLASH", "EQUAL_PERCENT", "EQUAL_AMPERSAND", 
      "EQUAL_PIPE", "EQUAL_CARET", "EQUAL_DOUBLE_RANGLE", "EQUAL_DOUBLE_LANGLE", 
      "INC", "DEC", "DOT", "COLON", "EQUAL", "PLUS", "MINUS", "STAR", "SLASH", 
      "HASH", "QUEST_MARK", "EXCLA_MARK", "PERCENT", "DOLLAR", "AMPERSAND", 
      "PIPE", "CARET", "DOUBLE_RANGLE", "DOUBLE_LANGLE", "OBJECT", "SINGLETON", 
      "SELF_INSTANCE", "SELF_CLASS", "INTERFACE", "EXTERN", "VISIBILITY", 
      "IMPLEMENTS", "CONST", "ENUM", "VEC2", "VEC3", "VEC4", "IF", "ELSE", 
      "FOR", "BREAK", "CONTINUE", "RETURN", "AND", "OR", "NOT", "IN", "INTEGER", 
      "FLOAT", "BOOL", "NULL", "IDENTIFIER", "STRING", "TAG", "LINE_COMMENT", 
      "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,82,863,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,1,0,3,0,140,8,0,
  	1,0,1,0,1,0,3,0,145,8,0,1,1,1,1,1,1,1,1,5,1,151,8,1,10,1,12,1,154,9,1,
  	1,1,1,1,1,2,1,2,5,2,160,8,2,10,2,12,2,163,9,2,1,2,1,2,1,3,1,3,5,3,169,
  	8,3,10,3,12,3,172,9,3,1,3,3,3,175,8,3,1,3,1,3,1,4,1,4,1,4,1,4,5,4,183,
  	8,4,10,4,12,4,186,9,4,1,4,4,4,189,8,4,11,4,12,4,190,1,4,1,4,1,5,1,5,1,
  	5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,5,9,223,8,9,10,9,12,9,226,9,9,1,9,3,9,
  	229,8,9,1,10,1,10,1,10,5,10,234,8,10,10,10,12,10,237,9,10,1,10,3,10,240,
  	8,10,1,11,3,11,243,8,11,1,11,5,11,246,8,11,10,11,12,11,249,9,11,1,11,
  	5,11,252,8,11,10,11,12,11,255,9,11,1,11,5,11,258,8,11,10,11,12,11,261,
  	9,11,1,12,1,12,1,12,1,12,1,12,1,12,1,13,3,13,270,8,13,1,13,5,13,273,8,
  	13,10,13,12,13,276,9,13,1,13,5,13,279,8,13,10,13,12,13,282,9,13,1,14,
  	3,14,285,8,14,1,14,3,14,288,8,14,1,14,1,14,1,14,1,14,1,14,3,14,295,8,
  	14,1,15,3,15,298,8,15,1,15,1,15,3,15,302,8,15,1,15,1,15,1,15,1,15,3,15,
  	308,8,15,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,3,17,318,8,17,1,17,3,
  	17,321,8,17,1,18,1,18,1,18,1,18,1,18,5,18,328,8,18,10,18,12,18,331,9,
  	18,1,18,3,18,334,8,18,3,18,336,8,18,1,18,1,18,1,19,1,19,1,19,3,19,343,
  	8,19,1,20,1,20,3,20,347,8,20,1,20,1,20,3,20,351,8,20,1,21,1,21,1,21,1,
  	22,1,22,1,22,1,22,5,22,360,8,22,10,22,12,22,363,9,22,1,22,3,22,366,8,
  	22,3,22,368,8,22,1,22,1,22,1,22,3,22,373,8,22,1,23,1,23,1,23,1,24,3,24,
  	379,8,24,1,24,1,24,1,24,1,25,1,25,1,26,1,26,1,26,1,26,3,26,390,8,26,1,
  	26,1,26,3,26,394,8,26,1,26,1,26,3,26,398,8,26,1,27,1,27,1,27,1,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,412,8,27,1,28,1,28,5,28,416,8,
  	28,10,28,12,28,419,9,28,1,28,1,28,1,29,1,29,1,29,3,29,426,8,29,1,29,1,
  	29,1,29,1,30,3,30,432,8,30,1,30,1,30,1,30,1,30,1,30,3,30,439,8,30,1,31,
  	3,31,442,8,31,1,31,1,31,3,31,446,8,31,1,31,1,31,1,31,1,32,1,32,1,32,3,
  	32,454,8,32,1,32,1,32,5,32,458,8,32,10,32,12,32,461,9,32,1,32,3,32,464,
  	8,32,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,35,1,35,3,35,475,8,35,1,35,
  	1,35,5,35,479,8,35,10,35,12,35,482,9,35,1,35,1,35,1,35,3,35,487,8,35,
  	1,35,1,35,1,36,1,36,1,36,1,36,1,37,1,37,1,37,3,37,498,8,37,1,37,1,37,
  	1,37,1,37,1,37,1,37,1,37,1,37,5,37,508,8,37,10,37,12,37,511,9,37,1,37,
  	3,37,514,8,37,1,37,1,37,1,37,1,37,1,37,1,37,3,37,522,8,37,1,37,3,37,525,
  	8,37,1,38,1,38,3,38,529,8,38,1,39,1,39,3,39,533,8,39,1,40,1,40,1,40,1,
  	40,5,40,539,8,40,10,40,12,40,542,9,40,1,40,1,40,1,41,1,41,1,41,3,41,549,
  	8,41,1,42,1,42,1,42,1,42,1,42,1,42,3,42,557,8,42,1,42,1,42,1,42,3,42,
  	562,8,42,3,42,564,8,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,
  	42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,5,42,587,8,
  	42,10,42,12,42,590,9,42,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,
  	1,43,1,43,1,43,1,43,1,43,1,43,3,43,607,8,43,1,44,1,44,1,44,1,45,1,45,
  	1,45,1,45,1,45,3,45,617,8,45,1,45,1,45,1,46,1,46,1,46,1,46,5,46,625,8,
  	46,10,46,12,46,628,9,46,1,46,3,46,631,8,46,3,46,633,8,46,1,46,1,46,3,
  	46,637,8,46,1,47,1,47,1,47,1,47,5,47,643,8,47,10,47,12,47,646,9,47,1,
  	47,3,47,649,8,47,3,47,651,8,47,1,47,1,47,1,48,1,48,1,48,1,48,1,49,1,49,
  	1,49,3,49,662,8,49,1,49,3,49,665,8,49,1,49,3,49,668,8,49,1,49,1,49,1,
  	50,1,50,1,50,5,50,675,8,50,10,50,12,50,678,9,50,1,51,1,51,3,51,682,8,
  	51,1,51,1,51,1,52,1,52,1,52,3,52,689,8,52,1,52,1,52,1,53,1,53,1,53,5,
  	53,696,8,53,10,53,12,53,699,9,53,1,53,3,53,702,8,53,1,54,1,54,1,54,1,
  	54,1,55,1,55,1,56,1,56,3,56,712,8,56,1,56,4,56,715,8,56,11,56,12,56,716,
  	1,57,1,57,1,57,3,57,722,8,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,
  	1,57,1,57,1,57,1,57,1,57,3,57,737,8,57,1,58,1,58,3,58,741,8,58,1,58,1,
  	58,1,58,3,58,746,8,58,4,58,748,8,58,11,58,12,58,749,1,59,1,59,1,59,1,
  	59,1,59,1,59,1,59,3,59,759,8,59,1,60,1,60,1,60,3,60,764,8,60,1,61,1,61,
  	1,61,1,61,1,61,1,61,1,61,1,61,1,61,3,61,775,8,61,1,62,1,62,1,62,3,62,
  	780,8,62,1,62,1,62,1,62,3,62,785,8,62,1,62,1,62,4,62,789,8,62,11,62,12,
  	62,790,1,62,3,62,794,8,62,5,62,796,8,62,10,62,12,62,799,9,62,1,63,1,63,
  	1,63,1,63,1,63,1,63,1,64,1,64,3,64,809,8,64,1,64,1,64,1,65,1,65,1,65,
  	1,65,5,65,817,8,65,10,65,12,65,820,9,65,1,65,3,65,823,8,65,3,65,825,8,
  	65,1,65,1,65,1,65,1,65,1,66,1,66,1,66,1,66,1,66,5,66,836,8,66,10,66,12,
  	66,839,9,66,1,66,3,66,842,8,66,3,66,844,8,66,1,66,1,66,1,67,1,67,1,67,
  	1,67,1,67,1,67,5,67,854,8,67,10,67,12,67,857,9,67,1,67,1,67,1,68,1,68,
  	1,68,0,2,84,124,69,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,
  	38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,
  	84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,120,122,
  	124,126,128,130,132,134,136,0,13,1,0,50,51,2,0,38,39,43,43,1,0,36,37,
  	2,0,6,7,15,16,1,0,4,5,1,0,69,70,1,0,45,47,1,0,48,49,2,0,37,37,71,71,1,
  	0,31,32,2,0,73,75,78,78,1,0,60,62,1,0,20,30,950,0,139,1,0,0,0,2,146,1,
  	0,0,0,4,161,1,0,0,0,6,170,1,0,0,0,8,184,1,0,0,0,10,194,1,0,0,0,12,198,
  	1,0,0,0,14,203,1,0,0,0,16,209,1,0,0,0,18,219,1,0,0,0,20,230,1,0,0,0,22,
  	242,1,0,0,0,24,262,1,0,0,0,26,269,1,0,0,0,28,284,1,0,0,0,30,297,1,0,0,
  	0,32,309,1,0,0,0,34,312,1,0,0,0,36,322,1,0,0,0,38,339,1,0,0,0,40,344,
  	1,0,0,0,42,352,1,0,0,0,44,355,1,0,0,0,46,374,1,0,0,0,48,378,1,0,0,0,50,
  	383,1,0,0,0,52,397,1,0,0,0,54,411,1,0,0,0,56,413,1,0,0,0,58,425,1,0,0,
  	0,60,431,1,0,0,0,62,441,1,0,0,0,64,450,1,0,0,0,66,465,1,0,0,0,68,469,
  	1,0,0,0,70,472,1,0,0,0,72,490,1,0,0,0,74,524,1,0,0,0,76,526,1,0,0,0,78,
  	530,1,0,0,0,80,534,1,0,0,0,82,545,1,0,0,0,84,563,1,0,0,0,86,606,1,0,0,
  	0,88,608,1,0,0,0,90,616,1,0,0,0,92,620,1,0,0,0,94,638,1,0,0,0,96,654,
  	1,0,0,0,98,658,1,0,0,0,100,671,1,0,0,0,102,681,1,0,0,0,104,685,1,0,0,
  	0,106,692,1,0,0,0,108,703,1,0,0,0,110,707,1,0,0,0,112,711,1,0,0,0,114,
  	736,1,0,0,0,116,738,1,0,0,0,118,758,1,0,0,0,120,763,1,0,0,0,122,774,1,
  	0,0,0,124,784,1,0,0,0,126,800,1,0,0,0,128,806,1,0,0,0,130,812,1,0,0,0,
  	132,830,1,0,0,0,134,847,1,0,0,0,136,860,1,0,0,0,138,140,3,2,1,0,139,138,
  	1,0,0,0,139,140,1,0,0,0,140,144,1,0,0,0,141,145,3,8,4,0,142,145,3,10,
  	5,0,143,145,3,12,6,0,144,141,1,0,0,0,144,142,1,0,0,0,144,143,1,0,0,0,
  	145,1,1,0,0,0,146,147,5,55,0,0,147,148,5,1,0,0,148,152,5,10,0,0,149,151,
  	5,78,0,0,150,149,1,0,0,0,151,154,1,0,0,0,152,150,1,0,0,0,152,153,1,0,
  	0,0,153,155,1,0,0,0,154,152,1,0,0,0,155,156,5,11,0,0,156,3,1,0,0,0,157,
  	160,3,62,31,0,158,160,3,60,30,0,159,157,1,0,0,0,159,158,1,0,0,0,160,163,
  	1,0,0,0,161,159,1,0,0,0,161,162,1,0,0,0,162,164,1,0,0,0,163,161,1,0,0,
  	0,164,165,5,0,0,1,165,5,1,0,0,0,166,169,3,62,31,0,167,169,3,60,30,0,168,
  	166,1,0,0,0,168,167,1,0,0,0,169,172,1,0,0,0,170,168,1,0,0,0,170,171,1,
  	0,0,0,171,174,1,0,0,0,172,170,1,0,0,0,173,175,3,134,67,0,174,173,1,0,
  	0,0,174,175,1,0,0,0,175,176,1,0,0,0,176,177,5,0,0,1,177,7,1,0,0,0,178,
  	183,3,24,12,0,179,183,3,80,40,0,180,183,3,14,7,0,181,183,3,16,8,0,182,
  	178,1,0,0,0,182,179,1,0,0,0,182,180,1,0,0,0,182,181,1,0,0,0,183,186,1,
  	0,0,0,184,182,1,0,0,0,184,185,1,0,0,0,185,188,1,0,0,0,186,184,1,0,0,0,
  	187,189,3,42,21,0,188,187,1,0,0,0,189,190,1,0,0,0,190,188,1,0,0,0,190,
  	191,1,0,0,0,191,192,1,0,0,0,192,193,5,0,0,1,193,9,1,0,0,0,194,195,3,32,
  	16,0,195,196,3,26,13,0,196,197,5,0,0,1,197,11,1,0,0,0,198,199,5,54,0,
  	0,199,200,5,77,0,0,200,201,3,22,11,0,201,202,5,0,0,1,202,13,1,0,0,0,203,
  	204,5,54,0,0,204,205,5,77,0,0,205,206,5,10,0,0,206,207,3,22,11,0,207,
  	208,5,11,0,0,208,15,1,0,0,0,209,210,5,77,0,0,210,211,5,35,0,0,211,212,
  	5,10,0,0,212,213,3,18,9,0,213,214,5,11,0,0,214,215,5,14,0,0,215,216,5,
  	10,0,0,216,217,3,20,10,0,217,218,5,11,0,0,218,17,1,0,0,0,219,224,3,124,
  	62,0,220,221,5,17,0,0,221,223,3,124,62,0,222,220,1,0,0,0,223,226,1,0,
  	0,0,224,222,1,0,0,0,224,225,1,0,0,0,225,228,1,0,0,0,226,224,1,0,0,0,227,
  	229,5,17,0,0,228,227,1,0,0,0,228,229,1,0,0,0,229,19,1,0,0,0,230,235,5,
  	77,0,0,231,232,5,17,0,0,232,234,5,77,0,0,233,231,1,0,0,0,234,237,1,0,
  	0,0,235,233,1,0,0,0,235,236,1,0,0,0,236,239,1,0,0,0,237,235,1,0,0,0,238,
  	240,5,17,0,0,239,238,1,0,0,0,239,240,1,0,0,0,240,21,1,0,0,0,241,243,3,
  	34,17,0,242,241,1,0,0,0,242,243,1,0,0,0,243,247,1,0,0,0,244,246,3,30,
  	15,0,245,244,1,0,0,0,246,249,1,0,0,0,247,245,1,0,0,0,247,248,1,0,0,0,
  	248,253,1,0,0,0,249,247,1,0,0,0,250,252,3,40,20,0,251,250,1,0,0,0,252,
  	255,1,0,0,0,253,251,1,0,0,0,253,254,1,0,0,0,254,259,1,0,0,0,255,253,1,
  	0,0,0,256,258,3,42,21,0,257,256,1,0,0,0,258,261,1,0,0,0,259,257,1,0,0,
  	0,259,260,1,0,0,0,260,23,1,0,0,0,261,259,1,0,0,0,262,263,7,0,0,0,263,
  	264,5,77,0,0,264,265,5,10,0,0,265,266,3,26,13,0,266,267,5,11,0,0,267,
  	25,1,0,0,0,268,270,3,34,17,0,269,268,1,0,0,0,269,270,1,0,0,0,270,274,
  	1,0,0,0,271,273,3,28,14,0,272,271,1,0,0,0,273,276,1,0,0,0,274,272,1,0,
  	0,0,274,275,1,0,0,0,275,280,1,0,0,0,276,274,1,0,0,0,277,279,3,48,24,0,
  	278,277,1,0,0,0,279,282,1,0,0,0,280,278,1,0,0,0,280,281,1,0,0,0,281,27,
  	1,0,0,0,282,280,1,0,0,0,283,285,5,56,0,0,284,283,1,0,0,0,284,285,1,0,
  	0,0,285,287,1,0,0,0,286,288,5,58,0,0,287,286,1,0,0,0,287,288,1,0,0,0,
  	288,289,1,0,0,0,289,290,5,77,0,0,290,291,5,34,0,0,291,294,3,124,62,0,
  	292,293,5,35,0,0,293,295,3,84,42,0,294,292,1,0,0,0,294,295,1,0,0,0,295,
  	29,1,0,0,0,296,298,5,58,0,0,297,296,1,0,0,0,297,298,1,0,0,0,298,299,1,
  	0,0,0,299,301,5,77,0,0,300,302,5,41,0,0,301,300,1,0,0,0,301,302,1,0,0,
  	0,302,303,1,0,0,0,303,304,5,34,0,0,304,307,3,124,62,0,305,306,5,35,0,
  	0,306,308,3,84,42,0,307,305,1,0,0,0,307,308,1,0,0,0,308,31,1,0,0,0,309,
  	310,7,0,0,0,310,311,5,77,0,0,311,33,1,0,0,0,312,313,5,57,0,0,313,314,
  	5,34,0,0,314,317,5,77,0,0,315,316,5,17,0,0,316,318,5,77,0,0,317,315,1,
  	0,0,0,317,318,1,0,0,0,318,320,1,0,0,0,319,321,5,17,0,0,320,319,1,0,0,
  	0,320,321,1,0,0,0,321,35,1,0,0,0,322,323,5,77,0,0,323,335,5,8,0,0,324,
  	329,3,52,26,0,325,326,5,17,0,0,326,328,3,52,26,0,327,325,1,0,0,0,328,
  	331,1,0,0,0,329,327,1,0,0,0,329,330,1,0,0,0,330,333,1,0,0,0,331,329,1,
  	0,0,0,332,334,5,17,0,0,333,332,1,0,0,0,333,334,1,0,0,0,334,336,1,0,0,
  	0,335,324,1,0,0,0,335,336,1,0,0,0,336,337,1,0,0,0,337,338,5,9,0,0,338,
  	37,1,0,0,0,339,342,3,36,18,0,340,341,5,34,0,0,341,343,3,124,62,0,342,
  	340,1,0,0,0,342,343,1,0,0,0,343,39,1,0,0,0,344,346,3,36,18,0,345,347,
  	5,41,0,0,346,345,1,0,0,0,346,347,1,0,0,0,347,350,1,0,0,0,348,349,5,34,
  	0,0,349,351,3,124,62,0,350,348,1,0,0,0,350,351,1,0,0,0,351,41,1,0,0,0,
  	352,353,3,38,19,0,353,354,3,50,25,0,354,43,1,0,0,0,355,367,5,8,0,0,356,
  	361,3,52,26,0,357,358,5,17,0,0,358,360,3,52,26,0,359,357,1,0,0,0,360,
  	363,1,0,0,0,361,359,1,0,0,0,361,362,1,0,0,0,362,365,1,0,0,0,363,361,1,
  	0,0,0,364,366,5,17,0,0,365,364,1,0,0,0,365,366,1,0,0,0,366,368,1,0,0,
  	0,367,356,1,0,0,0,367,368,1,0,0,0,368,369,1,0,0,0,369,372,5,9,0,0,370,
  	371,5,34,0,0,371,373,3,124,62,0,372,370,1,0,0,0,372,373,1,0,0,0,373,45,
  	1,0,0,0,374,375,3,44,22,0,375,376,3,50,25,0,376,47,1,0,0,0,377,379,5,
  	56,0,0,378,377,1,0,0,0,378,379,1,0,0,0,379,380,1,0,0,0,380,381,3,38,19,
  	0,381,382,3,50,25,0,382,49,1,0,0,0,383,384,3,56,28,0,384,51,1,0,0,0,385,
  	386,5,77,0,0,386,387,5,34,0,0,387,389,3,124,62,0,388,390,5,18,0,0,389,
  	388,1,0,0,0,389,390,1,0,0,0,390,393,1,0,0,0,391,392,5,35,0,0,392,394,
  	3,84,42,0,393,391,1,0,0,0,393,394,1,0,0,0,394,398,1,0,0,0,395,396,5,77,
  	0,0,396,398,3,130,65,0,397,385,1,0,0,0,397,395,1,0,0,0,398,53,1,0,0,0,
  	399,412,3,58,29,0,400,412,3,60,30,0,401,412,3,62,31,0,402,412,3,64,32,
  	0,403,412,3,70,35,0,404,412,3,74,37,0,405,412,5,67,0,0,406,412,3,76,38,
  	0,407,412,3,78,39,0,408,412,3,98,49,0,409,412,3,116,58,0,410,412,3,90,
  	45,0,411,399,1,0,0,0,411,400,1,0,0,0,411,401,1,0,0,0,411,402,1,0,0,0,
  	411,403,1,0,0,0,411,404,1,0,0,0,411,405,1,0,0,0,411,406,1,0,0,0,411,407,
  	1,0,0,0,411,408,1,0,0,0,411,409,1,0,0,0,411,410,1,0,0,0,412,55,1,0,0,
  	0,413,417,5,10,0,0,414,416,3,54,27,0,415,414,1,0,0,0,416,419,1,0,0,0,
  	417,415,1,0,0,0,417,418,1,0,0,0,418,420,1,0,0,0,419,417,1,0,0,0,420,421,
  	5,11,0,0,421,57,1,0,0,0,422,426,5,77,0,0,423,426,3,112,56,0,424,426,3,
  	116,58,0,425,422,1,0,0,0,425,423,1,0,0,0,425,424,1,0,0,0,426,427,1,0,
  	0,0,427,428,3,136,68,0,428,429,3,84,42,0,429,59,1,0,0,0,430,432,5,58,
  	0,0,431,430,1,0,0,0,431,432,1,0,0,0,432,433,1,0,0,0,433,434,5,77,0,0,
  	434,435,5,34,0,0,435,438,3,124,62,0,436,437,5,35,0,0,437,439,3,84,42,
  	0,438,436,1,0,0,0,438,439,1,0,0,0,439,61,1,0,0,0,440,442,5,58,0,0,441,
  	440,1,0,0,0,441,442,1,0,0,0,442,443,1,0,0,0,443,445,5,77,0,0,444,446,
  	5,41,0,0,445,444,1,0,0,0,445,446,1,0,0,0,446,447,1,0,0,0,447,448,5,35,
  	0,0,448,449,3,84,42,0,449,63,1,0,0,0,450,451,5,63,0,0,451,453,3,84,42,
  	0,452,454,5,79,0,0,453,452,1,0,0,0,453,454,1,0,0,0,454,455,1,0,0,0,455,
  	459,3,56,28,0,456,458,3,66,33,0,457,456,1,0,0,0,458,461,1,0,0,0,459,457,
  	1,0,0,0,459,460,1,0,0,0,460,463,1,0,0,0,461,459,1,0,0,0,462,464,3,68,
  	34,0,463,462,1,0,0,0,463,464,1,0,0,0,464,65,1,0,0,0,465,466,5,64,0,0,
  	466,467,3,84,42,0,467,468,3,56,28,0,468,67,1,0,0,0,469,470,5,64,0,0,470,
  	471,3,56,28,0,471,69,1,0,0,0,472,474,5,63,0,0,473,475,3,84,42,0,474,473,
  	1,0,0,0,474,475,1,0,0,0,475,476,1,0,0,0,476,480,5,10,0,0,477,479,3,72,
  	36,0,478,477,1,0,0,0,479,482,1,0,0,0,480,478,1,0,0,0,480,481,1,0,0,0,
  	481,486,1,0,0,0,482,480,1,0,0,0,483,484,5,64,0,0,484,485,5,34,0,0,485,
  	487,3,56,28,0,486,483,1,0,0,0,486,487,1,0,0,0,487,488,1,0,0,0,488,489,
  	5,11,0,0,489,71,1,0,0,0,490,491,3,84,42,0,491,492,5,34,0,0,492,493,3,
  	56,28,0,493,73,1,0,0,0,494,495,5,65,0,0,495,497,5,77,0,0,496,498,5,17,
  	0,0,497,496,1,0,0,0,497,498,1,0,0,0,498,499,1,0,0,0,499,500,5,72,0,0,
  	500,501,3,122,61,0,501,502,3,56,28,0,502,525,1,0,0,0,503,504,5,65,0,0,
  	504,509,5,77,0,0,505,506,5,17,0,0,506,508,5,77,0,0,507,505,1,0,0,0,508,
  	511,1,0,0,0,509,507,1,0,0,0,509,510,1,0,0,0,510,513,1,0,0,0,511,509,1,
  	0,0,0,512,514,5,17,0,0,513,512,1,0,0,0,513,514,1,0,0,0,514,515,1,0,0,
  	0,515,516,5,72,0,0,516,517,3,86,43,0,517,518,3,56,28,0,518,525,1,0,0,
  	0,519,521,5,65,0,0,520,522,5,77,0,0,521,520,1,0,0,0,521,522,1,0,0,0,522,
  	523,1,0,0,0,523,525,3,56,28,0,524,494,1,0,0,0,524,503,1,0,0,0,524,519,
  	1,0,0,0,525,75,1,0,0,0,526,528,5,66,0,0,527,529,5,79,0,0,528,527,1,0,
  	0,0,528,529,1,0,0,0,529,77,1,0,0,0,530,532,5,68,0,0,531,533,3,84,42,0,
  	532,531,1,0,0,0,532,533,1,0,0,0,533,79,1,0,0,0,534,535,5,59,0,0,535,536,
  	5,77,0,0,536,540,5,10,0,0,537,539,3,82,41,0,538,537,1,0,0,0,539,542,1,
  	0,0,0,540,538,1,0,0,0,540,541,1,0,0,0,541,543,1,0,0,0,542,540,1,0,0,0,
  	543,544,5,11,0,0,544,81,1,0,0,0,545,548,5,77,0,0,546,547,5,35,0,0,547,
  	549,5,78,0,0,548,546,1,0,0,0,548,549,1,0,0,0,549,83,1,0,0,0,550,551,6,
  	42,-1,0,551,552,5,8,0,0,552,553,3,84,42,0,553,556,5,9,0,0,554,555,5,14,
  	0,0,555,557,3,124,62,0,556,554,1,0,0,0,556,557,1,0,0,0,557,564,1,0,0,
  	0,558,561,3,86,43,0,559,560,5,14,0,0,560,562,3,124,62,0,561,559,1,0,0,
  	0,561,562,1,0,0,0,562,564,1,0,0,0,563,550,1,0,0,0,563,558,1,0,0,0,564,
  	588,1,0,0,0,565,566,10,7,0,0,566,567,7,1,0,0,567,587,3,84,42,8,568,569,
  	10,6,0,0,569,570,7,2,0,0,570,587,3,84,42,7,571,572,10,5,0,0,572,573,7,
  	3,0,0,573,587,3,84,42,6,574,575,10,4,0,0,575,576,7,4,0,0,576,587,3,84,
  	42,5,577,578,10,3,0,0,578,579,7,5,0,0,579,587,3,84,42,4,580,581,10,2,
  	0,0,581,582,7,6,0,0,582,587,3,84,42,3,583,584,10,1,0,0,584,585,7,7,0,
  	0,585,587,3,84,42,2,586,565,1,0,0,0,586,568,1,0,0,0,586,571,1,0,0,0,586,
  	574,1,0,0,0,586,577,1,0,0,0,586,580,1,0,0,0,586,583,1,0,0,0,587,590,1,
  	0,0,0,588,586,1,0,0,0,588,589,1,0,0,0,589,85,1,0,0,0,590,588,1,0,0,0,
  	591,607,5,77,0,0,592,607,5,52,0,0,593,607,5,53,0,0,594,607,5,76,0,0,595,
  	607,3,88,44,0,596,607,3,90,45,0,597,607,3,98,49,0,598,607,3,46,23,0,599,
  	607,3,132,66,0,600,607,3,104,52,0,601,607,3,110,55,0,602,607,3,112,56,
  	0,603,607,3,116,58,0,604,607,3,92,46,0,605,607,3,94,47,0,606,591,1,0,
  	0,0,606,592,1,0,0,0,606,593,1,0,0,0,606,594,1,0,0,0,606,595,1,0,0,0,606,
  	596,1,0,0,0,606,597,1,0,0,0,606,598,1,0,0,0,606,599,1,0,0,0,606,600,1,
  	0,0,0,606,601,1,0,0,0,606,602,1,0,0,0,606,603,1,0,0,0,606,604,1,0,0,0,
  	606,605,1,0,0,0,607,87,1,0,0,0,608,609,7,8,0,0,609,610,3,84,42,0,610,
  	89,1,0,0,0,611,617,5,77,0,0,612,617,3,112,56,0,613,617,3,116,58,0,614,
  	617,3,98,49,0,615,617,3,110,55,0,616,611,1,0,0,0,616,612,1,0,0,0,616,
  	613,1,0,0,0,616,614,1,0,0,0,616,615,1,0,0,0,617,618,1,0,0,0,618,619,7,
  	9,0,0,619,91,1,0,0,0,620,632,5,12,0,0,621,626,3,84,42,0,622,623,5,17,
  	0,0,623,625,3,84,42,0,624,622,1,0,0,0,625,628,1,0,0,0,626,624,1,0,0,0,
  	626,627,1,0,0,0,627,630,1,0,0,0,628,626,1,0,0,0,629,631,5,17,0,0,630,
  	629,1,0,0,0,630,631,1,0,0,0,631,633,1,0,0,0,632,621,1,0,0,0,632,633,1,
  	0,0,0,633,634,1,0,0,0,634,636,5,13,0,0,635,637,5,42,0,0,636,635,1,0,0,
  	0,636,637,1,0,0,0,637,93,1,0,0,0,638,650,5,10,0,0,639,644,3,96,48,0,640,
  	641,5,17,0,0,641,643,3,96,48,0,642,640,1,0,0,0,643,646,1,0,0,0,644,642,
  	1,0,0,0,644,645,1,0,0,0,645,648,1,0,0,0,646,644,1,0,0,0,647,649,5,17,
  	0,0,648,647,1,0,0,0,648,649,1,0,0,0,649,651,1,0,0,0,650,639,1,0,0,0,650,
  	651,1,0,0,0,651,652,1,0,0,0,652,653,5,11,0,0,653,95,1,0,0,0,654,655,3,
  	84,42,0,655,656,5,34,0,0,656,657,3,84,42,0,657,97,1,0,0,0,658,659,5,77,
  	0,0,659,661,5,8,0,0,660,662,3,100,50,0,661,660,1,0,0,0,661,662,1,0,0,
  	0,662,664,1,0,0,0,663,665,5,18,0,0,664,663,1,0,0,0,664,665,1,0,0,0,665,
  	667,1,0,0,0,666,668,5,17,0,0,667,666,1,0,0,0,667,668,1,0,0,0,668,669,
  	1,0,0,0,669,670,5,9,0,0,670,99,1,0,0,0,671,676,3,102,51,0,672,673,5,17,
  	0,0,673,675,3,102,51,0,674,672,1,0,0,0,675,678,1,0,0,0,676,674,1,0,0,
  	0,676,677,1,0,0,0,677,101,1,0,0,0,678,676,1,0,0,0,679,680,5,77,0,0,680,
  	682,5,35,0,0,681,679,1,0,0,0,681,682,1,0,0,0,682,683,1,0,0,0,683,684,
  	3,84,42,0,684,103,1,0,0,0,685,686,5,77,0,0,686,688,5,10,0,0,687,689,3,
  	106,53,0,688,687,1,0,0,0,688,689,1,0,0,0,689,690,1,0,0,0,690,691,5,11,
  	0,0,691,105,1,0,0,0,692,697,3,108,54,0,693,694,5,17,0,0,694,696,3,108,
  	54,0,695,693,1,0,0,0,696,699,1,0,0,0,697,695,1,0,0,0,697,698,1,0,0,0,
  	698,701,1,0,0,0,699,697,1,0,0,0,700,702,5,17,0,0,701,700,1,0,0,0,701,
  	702,1,0,0,0,702,107,1,0,0,0,703,704,5,77,0,0,704,705,5,35,0,0,705,706,
  	3,84,42,0,706,109,1,0,0,0,707,708,7,10,0,0,708,111,1,0,0,0,709,712,3,
  	98,49,0,710,712,5,77,0,0,711,709,1,0,0,0,711,710,1,0,0,0,712,714,1,0,
  	0,0,713,715,3,114,57,0,714,713,1,0,0,0,715,716,1,0,0,0,716,714,1,0,0,
  	0,716,717,1,0,0,0,717,113,1,0,0,0,718,719,5,12,0,0,719,721,3,84,42,0,
  	720,722,5,34,0,0,721,720,1,0,0,0,721,722,1,0,0,0,722,723,1,0,0,0,723,
  	724,5,13,0,0,724,737,1,0,0,0,725,726,5,12,0,0,726,727,5,34,0,0,727,728,
  	3,84,42,0,728,729,5,13,0,0,729,737,1,0,0,0,730,731,5,12,0,0,731,732,3,
  	84,42,0,732,733,5,34,0,0,733,734,3,84,42,0,734,735,5,13,0,0,735,737,1,
  	0,0,0,736,718,1,0,0,0,736,725,1,0,0,0,736,730,1,0,0,0,737,115,1,0,0,0,
  	738,740,3,118,59,0,739,741,5,41,0,0,740,739,1,0,0,0,740,741,1,0,0,0,741,
  	747,1,0,0,0,742,743,5,33,0,0,743,745,3,120,60,0,744,746,5,41,0,0,745,
  	744,1,0,0,0,745,746,1,0,0,0,746,748,1,0,0,0,747,742,1,0,0,0,748,749,1,
  	0,0,0,749,747,1,0,0,0,749,750,1,0,0,0,750,117,1,0,0,0,751,759,5,77,0,
  	0,752,759,5,78,0,0,753,759,5,53,0,0,754,759,5,52,0,0,755,759,3,98,49,
  	0,756,759,3,104,52,0,757,759,3,112,56,0,758,751,1,0,0,0,758,752,1,0,0,
  	0,758,753,1,0,0,0,758,754,1,0,0,0,758,755,1,0,0,0,758,756,1,0,0,0,758,
  	757,1,0,0,0,759,119,1,0,0,0,760,764,5,77,0,0,761,764,3,98,49,0,762,764,
  	3,112,56,0,763,760,1,0,0,0,763,761,1,0,0,0,763,762,1,0,0,0,764,121,1,
  	0,0,0,765,766,3,84,42,0,766,767,5,19,0,0,767,768,3,84,42,0,768,775,1,
  	0,0,0,769,770,5,19,0,0,770,775,3,84,42,0,771,772,3,84,42,0,772,773,5,
  	19,0,0,773,775,1,0,0,0,774,765,1,0,0,0,774,769,1,0,0,0,774,771,1,0,0,
  	0,775,123,1,0,0,0,776,777,6,62,-1,0,777,779,5,77,0,0,778,780,5,41,0,0,
  	779,778,1,0,0,0,779,780,1,0,0,0,780,785,1,0,0,0,781,785,5,53,0,0,782,
  	785,3,126,63,0,783,785,3,130,65,0,784,776,1,0,0,0,784,781,1,0,0,0,784,
  	782,1,0,0,0,784,783,1,0,0,0,785,797,1,0,0,0,786,788,10,3,0,0,787,789,
  	3,128,64,0,788,787,1,0,0,0,789,790,1,0,0,0,790,788,1,0,0,0,790,791,1,
  	0,0,0,791,793,1,0,0,0,792,794,5,42,0,0,793,792,1,0,0,0,793,794,1,0,0,
  	0,794,796,1,0,0,0,795,786,1,0,0,0,796,799,1,0,0,0,797,795,1,0,0,0,797,
  	798,1,0,0,0,798,125,1,0,0,0,799,797,1,0,0,0,800,801,5,10,0,0,801,802,
  	3,124,62,0,802,803,5,34,0,0,803,804,3,124,62,0,804,805,5,11,0,0,805,127,
  	1,0,0,0,806,808,5,12,0,0,807,809,3,84,42,0,808,807,1,0,0,0,808,809,1,
  	0,0,0,809,810,1,0,0,0,810,811,5,13,0,0,811,129,1,0,0,0,812,824,5,8,0,
  	0,813,818,3,124,62,0,814,815,5,17,0,0,815,817,3,124,62,0,816,814,1,0,
  	0,0,817,820,1,0,0,0,818,816,1,0,0,0,818,819,1,0,0,0,819,822,1,0,0,0,820,
  	818,1,0,0,0,821,823,5,17,0,0,822,821,1,0,0,0,822,823,1,0,0,0,823,825,
  	1,0,0,0,824,813,1,0,0,0,824,825,1,0,0,0,825,826,1,0,0,0,826,827,5,9,0,
  	0,827,828,5,34,0,0,828,829,3,124,62,0,829,131,1,0,0,0,830,831,7,11,0,
  	0,831,843,5,8,0,0,832,837,3,84,42,0,833,834,5,17,0,0,834,836,3,84,42,
  	0,835,833,1,0,0,0,836,839,1,0,0,0,837,835,1,0,0,0,837,838,1,0,0,0,838,
  	841,1,0,0,0,839,837,1,0,0,0,840,842,5,17,0,0,841,840,1,0,0,0,841,842,
  	1,0,0,0,842,844,1,0,0,0,843,832,1,0,0,0,843,844,1,0,0,0,844,845,1,0,0,
  	0,845,846,5,9,0,0,846,133,1,0,0,0,847,848,5,2,0,0,848,849,5,3,0,0,849,
  	855,5,10,0,0,850,851,5,77,0,0,851,852,5,34,0,0,852,854,3,124,62,0,853,
  	850,1,0,0,0,854,857,1,0,0,0,855,853,1,0,0,0,855,856,1,0,0,0,856,858,1,
  	0,0,0,857,855,1,0,0,0,858,859,5,11,0,0,859,135,1,0,0,0,860,861,7,12,0,
  	0,861,137,1,0,0,0,111,139,144,152,159,161,168,170,174,182,184,190,224,
  	228,235,239,242,247,253,259,269,274,280,284,287,294,297,301,307,317,320,
  	329,333,335,342,346,350,361,365,367,372,378,389,393,397,411,417,425,431,
  	438,441,445,453,459,463,474,480,486,497,509,513,521,524,528,532,540,548,
  	556,561,563,586,588,606,616,626,630,632,636,644,648,650,661,664,667,676,
  	681,688,697,701,711,716,721,736,740,745,749,758,763,774,779,784,790,793,
  	797,808,818,822,824,837,841,843,855
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

LogosParser::ExternContext* LogosParser::LogosFileContext::extern_() {
  return getRuleContext<LogosParser::ExternContext>(0);
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
    setState(139);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EXTERN) {
      setState(138);
      extern_();
    }
    setState(144);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(141);
      mainFile();
      break;
    }

    case 2: {
      setState(142);
      objectFile();
      break;
    }

    case 3: {
      setState(143);
      interfaceFile();
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

//----------------- ExternContext ------------------------------------------------------------------

LogosParser::ExternContext::ExternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ExternContext::EXTERN() {
  return getToken(LogosParser::EXTERN, 0);
}

tree::TerminalNode* LogosParser::ExternContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

tree::TerminalNode* LogosParser::ExternContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> LogosParser::ExternContext::STRING() {
  return getTokens(LogosParser::STRING);
}

tree::TerminalNode* LogosParser::ExternContext::STRING(size_t i) {
  return getToken(LogosParser::STRING, i);
}


size_t LogosParser::ExternContext::getRuleIndex() const {
  return LogosParser::RuleExtern;
}


LogosParser::ExternContext* LogosParser::extern_() {
  ExternContext *_localctx = _tracker.createInstance<ExternContext>(_ctx, getState());
  enterRule(_localctx, 2, LogosParser::RuleExtern);
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
    match(LogosParser::EXTERN);
    setState(147);
    match(LogosParser::T__0);
    setState(148);
    match(LogosParser::LBRACE);
    setState(152);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::STRING) {
      setState(149);
      match(LogosParser::STRING);
      setState(154);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(155);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogosEnvFileContext ------------------------------------------------------------------

LogosParser::LogosEnvFileContext::LogosEnvFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::LogosEnvFileContext::EOF() {
  return getToken(LogosParser::EOF, 0);
}

std::vector<LogosParser::ImplicitVarDecContext *> LogosParser::LogosEnvFileContext::implicitVarDec() {
  return getRuleContexts<LogosParser::ImplicitVarDecContext>();
}

LogosParser::ImplicitVarDecContext* LogosParser::LogosEnvFileContext::implicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ImplicitVarDecContext>(i);
}

std::vector<LogosParser::ExplicitVarDecContext *> LogosParser::LogosEnvFileContext::explicitVarDec() {
  return getRuleContexts<LogosParser::ExplicitVarDecContext>();
}

LogosParser::ExplicitVarDecContext* LogosParser::LogosEnvFileContext::explicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(i);
}


size_t LogosParser::LogosEnvFileContext::getRuleIndex() const {
  return LogosParser::RuleLogosEnvFile;
}


LogosParser::LogosEnvFileContext* LogosParser::logosEnvFile() {
  LogosEnvFileContext *_localctx = _tracker.createInstance<LogosEnvFileContext>(_ctx, getState());
  enterRule(_localctx, 4, LogosParser::RuleLogosEnvFile);
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
    setState(161);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST

    || _la == LogosParser::IDENTIFIER) {
      setState(159);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(157);
        implicitVarDec();
        break;
      }

      case 2: {
        setState(158);
        explicitVarDec();
        break;
      }

      default:
        break;
      }
      setState(163);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(164);
    match(LogosParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LogosAppFileContext ------------------------------------------------------------------

LogosParser::LogosAppFileContext::LogosAppFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::LogosAppFileContext::EOF() {
  return getToken(LogosParser::EOF, 0);
}

std::vector<LogosParser::ImplicitVarDecContext *> LogosParser::LogosAppFileContext::implicitVarDec() {
  return getRuleContexts<LogosParser::ImplicitVarDecContext>();
}

LogosParser::ImplicitVarDecContext* LogosParser::LogosAppFileContext::implicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ImplicitVarDecContext>(i);
}

std::vector<LogosParser::ExplicitVarDecContext *> LogosParser::LogosAppFileContext::explicitVarDec() {
  return getRuleContexts<LogosParser::ExplicitVarDecContext>();
}

LogosParser::ExplicitVarDecContext* LogosParser::LogosAppFileContext::explicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(i);
}

LogosParser::RequireEnvVarsContext* LogosParser::LogosAppFileContext::requireEnvVars() {
  return getRuleContext<LogosParser::RequireEnvVarsContext>(0);
}


size_t LogosParser::LogosAppFileContext::getRuleIndex() const {
  return LogosParser::RuleLogosAppFile;
}


LogosParser::LogosAppFileContext* LogosParser::logosAppFile() {
  LogosAppFileContext *_localctx = _tracker.createInstance<LogosAppFileContext>(_ctx, getState());
  enterRule(_localctx, 6, LogosParser::RuleLogosAppFile);
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
    setState(170);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST

    || _la == LogosParser::IDENTIFIER) {
      setState(168);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(166);
        implicitVarDec();
        break;
      }

      case 2: {
        setState(167);
        explicitVarDec();
        break;
      }

      default:
        break;
      }
      setState(172);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(174);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::T__1) {
      setState(173);
      requireEnvVars();
    }
    setState(176);
    match(LogosParser::EOF);
   
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

std::vector<LogosParser::ObjectContext *> LogosParser::MainFileContext::object() {
  return getRuleContexts<LogosParser::ObjectContext>();
}

LogosParser::ObjectContext* LogosParser::MainFileContext::object(size_t i) {
  return getRuleContext<LogosParser::ObjectContext>(i);
}

std::vector<LogosParser::EnumDeclarationContext *> LogosParser::MainFileContext::enumDeclaration() {
  return getRuleContexts<LogosParser::EnumDeclarationContext>();
}

LogosParser::EnumDeclarationContext* LogosParser::MainFileContext::enumDeclaration(size_t i) {
  return getRuleContext<LogosParser::EnumDeclarationContext>(i);
}

std::vector<LogosParser::InterfaceContext *> LogosParser::MainFileContext::interface() {
  return getRuleContexts<LogosParser::InterfaceContext>();
}

LogosParser::InterfaceContext* LogosParser::MainFileContext::interface(size_t i) {
  return getRuleContext<LogosParser::InterfaceContext>(i);
}

std::vector<LogosParser::GroupContext *> LogosParser::MainFileContext::group() {
  return getRuleContexts<LogosParser::GroupContext>();
}

LogosParser::GroupContext* LogosParser::MainFileContext::group(size_t i) {
  return getRuleContext<LogosParser::GroupContext>(i);
}

std::vector<LogosParser::FuncImplContext *> LogosParser::MainFileContext::funcImpl() {
  return getRuleContexts<LogosParser::FuncImplContext>();
}

LogosParser::FuncImplContext* LogosParser::MainFileContext::funcImpl(size_t i) {
  return getRuleContext<LogosParser::FuncImplContext>(i);
}


size_t LogosParser::MainFileContext::getRuleIndex() const {
  return LogosParser::RuleMainFile;
}


LogosParser::MainFileContext* LogosParser::mainFile() {
  MainFileContext *_localctx = _tracker.createInstance<MainFileContext>(_ctx, getState());
  enterRule(_localctx, 8, LogosParser::RuleMainFile);
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
    setState(184);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(182);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case LogosParser::OBJECT:
          case LogosParser::SINGLETON: {
            setState(178);
            object();
            break;
          }

          case LogosParser::ENUM: {
            setState(179);
            enumDeclaration();
            break;
          }

          case LogosParser::INTERFACE: {
            setState(180);
            interface();
            break;
          }

          case LogosParser::IDENTIFIER: {
            setState(181);
            group();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(186);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
    setState(188); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(187);
      funcImpl();
      setState(190); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::IDENTIFIER);
    setState(192);
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

LogosParser::ObjectBodyContext* LogosParser::ObjectFileContext::objectBody() {
  return getRuleContext<LogosParser::ObjectBodyContext>(0);
}

tree::TerminalNode* LogosParser::ObjectFileContext::EOF() {
  return getToken(LogosParser::EOF, 0);
}


size_t LogosParser::ObjectFileContext::getRuleIndex() const {
  return LogosParser::RuleObjectFile;
}


LogosParser::ObjectFileContext* LogosParser::objectFile() {
  ObjectFileContext *_localctx = _tracker.createInstance<ObjectFileContext>(_ctx, getState());
  enterRule(_localctx, 10, LogosParser::RuleObjectFile);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(194);
    objectDeclaration();
    setState(195);
    objectBody();
    setState(196);
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

tree::TerminalNode* LogosParser::InterfaceFileContext::INTERFACE() {
  return getToken(LogosParser::INTERFACE, 0);
}

tree::TerminalNode* LogosParser::InterfaceFileContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

LogosParser::InterfaceBodyContext* LogosParser::InterfaceFileContext::interfaceBody() {
  return getRuleContext<LogosParser::InterfaceBodyContext>(0);
}

tree::TerminalNode* LogosParser::InterfaceFileContext::EOF() {
  return getToken(LogosParser::EOF, 0);
}


size_t LogosParser::InterfaceFileContext::getRuleIndex() const {
  return LogosParser::RuleInterfaceFile;
}


LogosParser::InterfaceFileContext* LogosParser::interfaceFile() {
  InterfaceFileContext *_localctx = _tracker.createInstance<InterfaceFileContext>(_ctx, getState());
  enterRule(_localctx, 12, LogosParser::RuleInterfaceFile);

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
    match(LogosParser::INTERFACE);
    setState(199);
    match(LogosParser::IDENTIFIER);
    setState(200);
    interfaceBody();
    setState(201);
    match(LogosParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceContext ------------------------------------------------------------------

LogosParser::InterfaceContext::InterfaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::InterfaceContext::INTERFACE() {
  return getToken(LogosParser::INTERFACE, 0);
}

tree::TerminalNode* LogosParser::InterfaceContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::InterfaceContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

LogosParser::InterfaceBodyContext* LogosParser::InterfaceContext::interfaceBody() {
  return getRuleContext<LogosParser::InterfaceBodyContext>(0);
}

tree::TerminalNode* LogosParser::InterfaceContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}


size_t LogosParser::InterfaceContext::getRuleIndex() const {
  return LogosParser::RuleInterface;
}


LogosParser::InterfaceContext* LogosParser::interface() {
  InterfaceContext *_localctx = _tracker.createInstance<InterfaceContext>(_ctx, getState());
  enterRule(_localctx, 14, LogosParser::RuleInterface);

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
    match(LogosParser::INTERFACE);
    setState(204);
    match(LogosParser::IDENTIFIER);
    setState(205);
    match(LogosParser::LBRACE);
    setState(206);
    interfaceBody();
    setState(207);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupContext ------------------------------------------------------------------

LogosParser::GroupContext::GroupContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::GroupContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::GroupContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

std::vector<tree::TerminalNode *> LogosParser::GroupContext::LBRACE() {
  return getTokens(LogosParser::LBRACE);
}

tree::TerminalNode* LogosParser::GroupContext::LBRACE(size_t i) {
  return getToken(LogosParser::LBRACE, i);
}

LogosParser::GroupTypesListContext* LogosParser::GroupContext::groupTypesList() {
  return getRuleContext<LogosParser::GroupTypesListContext>(0);
}

std::vector<tree::TerminalNode *> LogosParser::GroupContext::RBRACE() {
  return getTokens(LogosParser::RBRACE);
}

tree::TerminalNode* LogosParser::GroupContext::RBRACE(size_t i) {
  return getToken(LogosParser::RBRACE, i);
}

tree::TerminalNode* LogosParser::GroupContext::ARROW() {
  return getToken(LogosParser::ARROW, 0);
}

LogosParser::GroupTargetListContext* LogosParser::GroupContext::groupTargetList() {
  return getRuleContext<LogosParser::GroupTargetListContext>(0);
}


size_t LogosParser::GroupContext::getRuleIndex() const {
  return LogosParser::RuleGroup;
}


LogosParser::GroupContext* LogosParser::group() {
  GroupContext *_localctx = _tracker.createInstance<GroupContext>(_ctx, getState());
  enterRule(_localctx, 16, LogosParser::RuleGroup);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    match(LogosParser::IDENTIFIER);
    setState(210);
    match(LogosParser::EQUAL);
    setState(211);
    match(LogosParser::LBRACE);
    setState(212);
    groupTypesList();
    setState(213);
    match(LogosParser::RBRACE);
    setState(214);
    match(LogosParser::ARROW);
    setState(215);
    match(LogosParser::LBRACE);
    setState(216);
    groupTargetList();
    setState(217);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupTypesListContext ------------------------------------------------------------------

LogosParser::GroupTypesListContext::GroupTypesListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::TypeContext *> LogosParser::GroupTypesListContext::type() {
  return getRuleContexts<LogosParser::TypeContext>();
}

LogosParser::TypeContext* LogosParser::GroupTypesListContext::type(size_t i) {
  return getRuleContext<LogosParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::GroupTypesListContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::GroupTypesListContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::GroupTypesListContext::getRuleIndex() const {
  return LogosParser::RuleGroupTypesList;
}


LogosParser::GroupTypesListContext* LogosParser::groupTypesList() {
  GroupTypesListContext *_localctx = _tracker.createInstance<GroupTypesListContext>(_ctx, getState());
  enterRule(_localctx, 18, LogosParser::RuleGroupTypesList);
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
    setState(219);
    type(0);
    setState(224);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(220);
        match(LogosParser::COMMA);
        setState(221);
        type(0); 
      }
      setState(226);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
    setState(228);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(227);
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

//----------------- GroupTargetListContext ------------------------------------------------------------------

LogosParser::GroupTargetListContext::GroupTargetListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LogosParser::GroupTargetListContext::IDENTIFIER() {
  return getTokens(LogosParser::IDENTIFIER);
}

tree::TerminalNode* LogosParser::GroupTargetListContext::IDENTIFIER(size_t i) {
  return getToken(LogosParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> LogosParser::GroupTargetListContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::GroupTargetListContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::GroupTargetListContext::getRuleIndex() const {
  return LogosParser::RuleGroupTargetList;
}


LogosParser::GroupTargetListContext* LogosParser::groupTargetList() {
  GroupTargetListContext *_localctx = _tracker.createInstance<GroupTargetListContext>(_ctx, getState());
  enterRule(_localctx, 20, LogosParser::RuleGroupTargetList);
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
    setState(230);
    match(LogosParser::IDENTIFIER);
    setState(235);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(231);
        match(LogosParser::COMMA);
        setState(232);
        match(LogosParser::IDENTIFIER); 
      }
      setState(237);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
    setState(239);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(238);
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

//----------------- InterfaceBodyContext ------------------------------------------------------------------

LogosParser::InterfaceBodyContext::InterfaceBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ImplementsContext* LogosParser::InterfaceBodyContext::implements() {
  return getRuleContext<LogosParser::ImplementsContext>(0);
}

std::vector<LogosParser::InterfaceFieldContext *> LogosParser::InterfaceBodyContext::interfaceField() {
  return getRuleContexts<LogosParser::InterfaceFieldContext>();
}

LogosParser::InterfaceFieldContext* LogosParser::InterfaceBodyContext::interfaceField(size_t i) {
  return getRuleContext<LogosParser::InterfaceFieldContext>(i);
}

std::vector<LogosParser::InterfaceFuncSignatureContext *> LogosParser::InterfaceBodyContext::interfaceFuncSignature() {
  return getRuleContexts<LogosParser::InterfaceFuncSignatureContext>();
}

LogosParser::InterfaceFuncSignatureContext* LogosParser::InterfaceBodyContext::interfaceFuncSignature(size_t i) {
  return getRuleContext<LogosParser::InterfaceFuncSignatureContext>(i);
}

std::vector<LogosParser::FuncImplContext *> LogosParser::InterfaceBodyContext::funcImpl() {
  return getRuleContexts<LogosParser::FuncImplContext>();
}

LogosParser::FuncImplContext* LogosParser::InterfaceBodyContext::funcImpl(size_t i) {
  return getRuleContext<LogosParser::FuncImplContext>(i);
}


size_t LogosParser::InterfaceBodyContext::getRuleIndex() const {
  return LogosParser::RuleInterfaceBody;
}


LogosParser::InterfaceBodyContext* LogosParser::interfaceBody() {
  InterfaceBodyContext *_localctx = _tracker.createInstance<InterfaceBodyContext>(_ctx, getState());
  enterRule(_localctx, 22, LogosParser::RuleInterfaceBody);
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
    setState(242);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(241);
      implements();
    }
    setState(247);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(244);
        interfaceField(); 
      }
      setState(249);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
    setState(253);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(250);
        interfaceFuncSignature(); 
      }
      setState(255);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
    setState(259);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(256);
      funcImpl();
      setState(261);
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

//----------------- ObjectContext ------------------------------------------------------------------

LogosParser::ObjectContext::ObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ObjectContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::ObjectContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

LogosParser::ObjectBodyContext* LogosParser::ObjectContext::objectBody() {
  return getRuleContext<LogosParser::ObjectBodyContext>(0);
}

tree::TerminalNode* LogosParser::ObjectContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

tree::TerminalNode* LogosParser::ObjectContext::OBJECT() {
  return getToken(LogosParser::OBJECT, 0);
}

tree::TerminalNode* LogosParser::ObjectContext::SINGLETON() {
  return getToken(LogosParser::SINGLETON, 0);
}


size_t LogosParser::ObjectContext::getRuleIndex() const {
  return LogosParser::RuleObject;
}


LogosParser::ObjectContext* LogosParser::object() {
  ObjectContext *_localctx = _tracker.createInstance<ObjectContext>(_ctx, getState());
  enterRule(_localctx, 24, LogosParser::RuleObject);
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
    setState(262);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(263);
    match(LogosParser::IDENTIFIER);
    setState(264);
    match(LogosParser::LBRACE);
    setState(265);
    objectBody();
    setState(266);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectBodyContext ------------------------------------------------------------------

LogosParser::ObjectBodyContext::ObjectBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ImplementsContext* LogosParser::ObjectBodyContext::implements() {
  return getRuleContext<LogosParser::ImplementsContext>(0);
}

std::vector<LogosParser::FieldContext *> LogosParser::ObjectBodyContext::field() {
  return getRuleContexts<LogosParser::FieldContext>();
}

LogosParser::FieldContext* LogosParser::ObjectBodyContext::field(size_t i) {
  return getRuleContext<LogosParser::FieldContext>(i);
}

std::vector<LogosParser::MethodImplementationContext *> LogosParser::ObjectBodyContext::methodImplementation() {
  return getRuleContexts<LogosParser::MethodImplementationContext>();
}

LogosParser::MethodImplementationContext* LogosParser::ObjectBodyContext::methodImplementation(size_t i) {
  return getRuleContext<LogosParser::MethodImplementationContext>(i);
}


size_t LogosParser::ObjectBodyContext::getRuleIndex() const {
  return LogosParser::RuleObjectBody;
}


LogosParser::ObjectBodyContext* LogosParser::objectBody() {
  ObjectBodyContext *_localctx = _tracker.createInstance<ObjectBodyContext>(_ctx, getState());
  enterRule(_localctx, 26, LogosParser::RuleObjectBody);
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
    setState(269);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(268);
      implements();
    }
    setState(274);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(271);
        field(); 
      }
      setState(276);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    }
    setState(280);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VISIBILITY

    || _la == LogosParser::IDENTIFIER) {
      setState(277);
      methodImplementation();
      setState(282);
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

//----------------- FieldContext ------------------------------------------------------------------

LogosParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::FieldContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::FieldContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::TypeContext* LogosParser::FieldContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}

tree::TerminalNode* LogosParser::FieldContext::VISIBILITY() {
  return getToken(LogosParser::VISIBILITY, 0);
}

tree::TerminalNode* LogosParser::FieldContext::CONST() {
  return getToken(LogosParser::CONST, 0);
}

tree::TerminalNode* LogosParser::FieldContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::FieldContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::FieldContext::getRuleIndex() const {
  return LogosParser::RuleField;
}


LogosParser::FieldContext* LogosParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 28, LogosParser::RuleField);
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
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(283);
      match(LogosParser::VISIBILITY);
    }
    setState(287);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(286);
      match(LogosParser::CONST);
    }
    setState(289);
    match(LogosParser::IDENTIFIER);
    setState(290);
    match(LogosParser::COLON);
    setState(291);
    type(0);
    setState(294);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(292);
      match(LogosParser::EQUAL);
      setState(293);
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

//----------------- InterfaceFieldContext ------------------------------------------------------------------

LogosParser::InterfaceFieldContext::InterfaceFieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::InterfaceFieldContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::InterfaceFieldContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::TypeContext* LogosParser::InterfaceFieldContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}

tree::TerminalNode* LogosParser::InterfaceFieldContext::CONST() {
  return getToken(LogosParser::CONST, 0);
}

tree::TerminalNode* LogosParser::InterfaceFieldContext::QUEST_MARK() {
  return getToken(LogosParser::QUEST_MARK, 0);
}

tree::TerminalNode* LogosParser::InterfaceFieldContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::InterfaceFieldContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::InterfaceFieldContext::getRuleIndex() const {
  return LogosParser::RuleInterfaceField;
}


LogosParser::InterfaceFieldContext* LogosParser::interfaceField() {
  InterfaceFieldContext *_localctx = _tracker.createInstance<InterfaceFieldContext>(_ctx, getState());
  enterRule(_localctx, 30, LogosParser::RuleInterfaceField);
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
    setState(297);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(296);
      match(LogosParser::CONST);
    }
    setState(299);
    match(LogosParser::IDENTIFIER);
    setState(301);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(300);
      match(LogosParser::QUEST_MARK);
    }
    setState(303);
    match(LogosParser::COLON);
    setState(304);
    type(0);
    setState(307);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(305);
      match(LogosParser::EQUAL);
      setState(306);
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

//----------------- ObjectDeclarationContext ------------------------------------------------------------------

LogosParser::ObjectDeclarationContext::ObjectDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ObjectDeclarationContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::ObjectDeclarationContext::OBJECT() {
  return getToken(LogosParser::OBJECT, 0);
}

tree::TerminalNode* LogosParser::ObjectDeclarationContext::SINGLETON() {
  return getToken(LogosParser::SINGLETON, 0);
}


size_t LogosParser::ObjectDeclarationContext::getRuleIndex() const {
  return LogosParser::RuleObjectDeclaration;
}


LogosParser::ObjectDeclarationContext* LogosParser::objectDeclaration() {
  ObjectDeclarationContext *_localctx = _tracker.createInstance<ObjectDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 32, LogosParser::RuleObjectDeclaration);
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
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(310);
    match(LogosParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImplementsContext ------------------------------------------------------------------

LogosParser::ImplementsContext::ImplementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ImplementsContext::IMPLEMENTS() {
  return getToken(LogosParser::IMPLEMENTS, 0);
}

tree::TerminalNode* LogosParser::ImplementsContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

std::vector<tree::TerminalNode *> LogosParser::ImplementsContext::IDENTIFIER() {
  return getTokens(LogosParser::IDENTIFIER);
}

tree::TerminalNode* LogosParser::ImplementsContext::IDENTIFIER(size_t i) {
  return getToken(LogosParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> LogosParser::ImplementsContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ImplementsContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ImplementsContext::getRuleIndex() const {
  return LogosParser::RuleImplements;
}


LogosParser::ImplementsContext* LogosParser::implements() {
  ImplementsContext *_localctx = _tracker.createInstance<ImplementsContext>(_ctx, getState());
  enterRule(_localctx, 34, LogosParser::RuleImplements);
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
    setState(312);
    match(LogosParser::IMPLEMENTS);
    setState(313);
    match(LogosParser::COLON);
    setState(314);
    match(LogosParser::IDENTIFIER);
    setState(317);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      setState(315);
      match(LogosParser::COMMA);
      setState(316);
      match(LogosParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    setState(320);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(319);
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

//----------------- FuncSignatureHeaderContext ------------------------------------------------------------------

LogosParser::FuncSignatureHeaderContext::FuncSignatureHeaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::FuncSignatureHeaderContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::FuncSignatureHeaderContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::FuncSignatureHeaderContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

std::vector<LogosParser::ParamContext *> LogosParser::FuncSignatureHeaderContext::param() {
  return getRuleContexts<LogosParser::ParamContext>();
}

LogosParser::ParamContext* LogosParser::FuncSignatureHeaderContext::param(size_t i) {
  return getRuleContext<LogosParser::ParamContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::FuncSignatureHeaderContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::FuncSignatureHeaderContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::FuncSignatureHeaderContext::getRuleIndex() const {
  return LogosParser::RuleFuncSignatureHeader;
}


LogosParser::FuncSignatureHeaderContext* LogosParser::funcSignatureHeader() {
  FuncSignatureHeaderContext *_localctx = _tracker.createInstance<FuncSignatureHeaderContext>(_ctx, getState());
  enterRule(_localctx, 36, LogosParser::RuleFuncSignatureHeader);
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
    setState(322);
    match(LogosParser::IDENTIFIER);
    setState(323);
    match(LogosParser::LPAREN);
    setState(335);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(324);
      param();
      setState(329);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(325);
          match(LogosParser::COMMA);
          setState(326);
          param(); 
        }
        setState(331);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
      }
      setState(333);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(332);
        match(LogosParser::COMMA);
      }
    }
    setState(337);
    match(LogosParser::RPAREN);
   
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

LogosParser::FuncSignatureHeaderContext* LogosParser::FuncSignatureContext::funcSignatureHeader() {
  return getRuleContext<LogosParser::FuncSignatureHeaderContext>(0);
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
  enterRule(_localctx, 38, LogosParser::RuleFuncSignature);
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
    setState(339);
    funcSignatureHeader();
    setState(342);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(340);
      match(LogosParser::COLON);
      setState(341);
      type(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InterfaceFuncSignatureContext ------------------------------------------------------------------

LogosParser::InterfaceFuncSignatureContext::InterfaceFuncSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::FuncSignatureHeaderContext* LogosParser::InterfaceFuncSignatureContext::funcSignatureHeader() {
  return getRuleContext<LogosParser::FuncSignatureHeaderContext>(0);
}

tree::TerminalNode* LogosParser::InterfaceFuncSignatureContext::QUEST_MARK() {
  return getToken(LogosParser::QUEST_MARK, 0);
}

tree::TerminalNode* LogosParser::InterfaceFuncSignatureContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::TypeContext* LogosParser::InterfaceFuncSignatureContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}


size_t LogosParser::InterfaceFuncSignatureContext::getRuleIndex() const {
  return LogosParser::RuleInterfaceFuncSignature;
}


LogosParser::InterfaceFuncSignatureContext* LogosParser::interfaceFuncSignature() {
  InterfaceFuncSignatureContext *_localctx = _tracker.createInstance<InterfaceFuncSignatureContext>(_ctx, getState());
  enterRule(_localctx, 40, LogosParser::RuleInterfaceFuncSignature);
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
    setState(344);
    funcSignatureHeader();
    setState(346);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(345);
      match(LogosParser::QUEST_MARK);
    }
    setState(350);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(348);
      match(LogosParser::COLON);
      setState(349);
      type(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncImplContext ------------------------------------------------------------------

LogosParser::FuncImplContext::FuncImplContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::FuncSignatureContext* LogosParser::FuncImplContext::funcSignature() {
  return getRuleContext<LogosParser::FuncSignatureContext>(0);
}

LogosParser::FuncBodyContext* LogosParser::FuncImplContext::funcBody() {
  return getRuleContext<LogosParser::FuncBodyContext>(0);
}


size_t LogosParser::FuncImplContext::getRuleIndex() const {
  return LogosParser::RuleFuncImpl;
}


LogosParser::FuncImplContext* LogosParser::funcImpl() {
  FuncImplContext *_localctx = _tracker.createInstance<FuncImplContext>(_ctx, getState());
  enterRule(_localctx, 42, LogosParser::RuleFuncImpl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    funcSignature();
    setState(353);
    funcBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnonnymosfuncSignatureContext ------------------------------------------------------------------

LogosParser::AnonnymosfuncSignatureContext::AnonnymosfuncSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::AnonnymosfuncSignatureContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::AnonnymosfuncSignatureContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

std::vector<LogosParser::ParamContext *> LogosParser::AnonnymosfuncSignatureContext::param() {
  return getRuleContexts<LogosParser::ParamContext>();
}

LogosParser::ParamContext* LogosParser::AnonnymosfuncSignatureContext::param(size_t i) {
  return getRuleContext<LogosParser::ParamContext>(i);
}

tree::TerminalNode* LogosParser::AnonnymosfuncSignatureContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::TypeContext* LogosParser::AnonnymosfuncSignatureContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> LogosParser::AnonnymosfuncSignatureContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::AnonnymosfuncSignatureContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::AnonnymosfuncSignatureContext::getRuleIndex() const {
  return LogosParser::RuleAnonnymosfuncSignature;
}


LogosParser::AnonnymosfuncSignatureContext* LogosParser::anonnymosfuncSignature() {
  AnonnymosfuncSignatureContext *_localctx = _tracker.createInstance<AnonnymosfuncSignatureContext>(_ctx, getState());
  enterRule(_localctx, 44, LogosParser::RuleAnonnymosfuncSignature);
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
    setState(355);
    match(LogosParser::LPAREN);
    setState(367);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(356);
      param();
      setState(361);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(357);
          match(LogosParser::COMMA);
          setState(358);
          param(); 
        }
        setState(363);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
      }
      setState(365);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(364);
        match(LogosParser::COMMA);
      }
    }
    setState(369);
    match(LogosParser::RPAREN);
    setState(372);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(370);
      match(LogosParser::COLON);
      setState(371);
      type(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnonnymosFuncContext ------------------------------------------------------------------

LogosParser::AnonnymosFuncContext::AnonnymosFuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::AnonnymosfuncSignatureContext* LogosParser::AnonnymosFuncContext::anonnymosfuncSignature() {
  return getRuleContext<LogosParser::AnonnymosfuncSignatureContext>(0);
}

LogosParser::FuncBodyContext* LogosParser::AnonnymosFuncContext::funcBody() {
  return getRuleContext<LogosParser::FuncBodyContext>(0);
}


size_t LogosParser::AnonnymosFuncContext::getRuleIndex() const {
  return LogosParser::RuleAnonnymosFunc;
}


LogosParser::AnonnymosFuncContext* LogosParser::anonnymosFunc() {
  AnonnymosFuncContext *_localctx = _tracker.createInstance<AnonnymosFuncContext>(_ctx, getState());
  enterRule(_localctx, 46, LogosParser::RuleAnonnymosFunc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(374);
    anonnymosfuncSignature();
    setState(375);
    funcBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MethodImplementationContext ------------------------------------------------------------------

LogosParser::MethodImplementationContext::MethodImplementationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::FuncSignatureContext* LogosParser::MethodImplementationContext::funcSignature() {
  return getRuleContext<LogosParser::FuncSignatureContext>(0);
}

LogosParser::FuncBodyContext* LogosParser::MethodImplementationContext::funcBody() {
  return getRuleContext<LogosParser::FuncBodyContext>(0);
}

tree::TerminalNode* LogosParser::MethodImplementationContext::VISIBILITY() {
  return getToken(LogosParser::VISIBILITY, 0);
}


size_t LogosParser::MethodImplementationContext::getRuleIndex() const {
  return LogosParser::RuleMethodImplementation;
}


LogosParser::MethodImplementationContext* LogosParser::methodImplementation() {
  MethodImplementationContext *_localctx = _tracker.createInstance<MethodImplementationContext>(_ctx, getState());
  enterRule(_localctx, 48, LogosParser::RuleMethodImplementation);
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
    if (_la == LogosParser::VISIBILITY) {
      setState(377);
      match(LogosParser::VISIBILITY);
    }
    setState(380);
    funcSignature();
    setState(381);
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
  enterRule(_localctx, 50, LogosParser::RuleFuncBody);

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
    statementsBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

LogosParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ParamContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::ParamContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::TypeContext* LogosParser::ParamContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}

tree::TerminalNode* LogosParser::ParamContext::TRIPLE_DOT() {
  return getToken(LogosParser::TRIPLE_DOT, 0);
}

tree::TerminalNode* LogosParser::ParamContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::ParamContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

LogosParser::FuncTypeContext* LogosParser::ParamContext::funcType() {
  return getRuleContext<LogosParser::FuncTypeContext>(0);
}


size_t LogosParser::ParamContext::getRuleIndex() const {
  return LogosParser::RuleParam;
}


LogosParser::ParamContext* LogosParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 52, LogosParser::RuleParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(397);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(385);
      match(LogosParser::IDENTIFIER);
      setState(386);
      match(LogosParser::COLON);
      setState(387);
      type(0);
      setState(389);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::TRIPLE_DOT) {
        setState(388);
        match(LogosParser::TRIPLE_DOT);
      }
      setState(393);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::EQUAL) {
        setState(391);
        match(LogosParser::EQUAL);
        setState(392);
        expr(0);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(395);
      match(LogosParser::IDENTIFIER);
      setState(396);
      funcType();
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

LogosParser::PatternMatchingContext* LogosParser::StatementContext::patternMatching() {
  return getRuleContext<LogosParser::PatternMatchingContext>(0);
}

LogosParser::LoopStatementContext* LogosParser::StatementContext::loopStatement() {
  return getRuleContext<LogosParser::LoopStatementContext>(0);
}

tree::TerminalNode* LogosParser::StatementContext::CONTINUE() {
  return getToken(LogosParser::CONTINUE, 0);
}

LogosParser::BreakStmtContext* LogosParser::StatementContext::breakStmt() {
  return getRuleContext<LogosParser::BreakStmtContext>(0);
}

LogosParser::ReturnStatementContext* LogosParser::StatementContext::returnStatement() {
  return getRuleContext<LogosParser::ReturnStatementContext>(0);
}

LogosParser::FuncCallContext* LogosParser::StatementContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::SelectionContext* LogosParser::StatementContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}

LogosParser::PostfixExprContext* LogosParser::StatementContext::postfixExpr() {
  return getRuleContext<LogosParser::PostfixExprContext>(0);
}


size_t LogosParser::StatementContext::getRuleIndex() const {
  return LogosParser::RuleStatement;
}


LogosParser::StatementContext* LogosParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 54, LogosParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(411);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(399);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(400);
      explicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(401);
      implicitVarDec();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(402);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(403);
      patternMatching();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(404);
      loopStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(405);
      match(LogosParser::CONTINUE);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(406);
      breakStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(407);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(408);
      funcCall();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(409);
      selection();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(410);
      postfixExpr();
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
  enterRule(_localctx, 56, LogosParser::RuleStatementsBlock);
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
    setState(413);
    match(LogosParser::LBRACE);
    setState(417);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 52) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 52)) & 115468355) != 0)) {
      setState(414);
      statement();
      setState(419);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(420);
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

LogosParser::AssignemntOpContext* LogosParser::AssignmentContext::assignemntOp() {
  return getRuleContext<LogosParser::AssignemntOpContext>(0);
}

LogosParser::ExprContext* LogosParser::AssignmentContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::AssignmentContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

LogosParser::IterIndexContext* LogosParser::AssignmentContext::iterIndex() {
  return getRuleContext<LogosParser::IterIndexContext>(0);
}

LogosParser::SelectionContext* LogosParser::AssignmentContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}


size_t LogosParser::AssignmentContext::getRuleIndex() const {
  return LogosParser::RuleAssignment;
}


LogosParser::AssignmentContext* LogosParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 58, LogosParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(425);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      setState(422);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(423);
      iterIndex();
      break;
    }

    case 3: {
      setState(424);
      selection();
      break;
    }

    default:
      break;
    }
    setState(427);
    assignemntOp();
    setState(428);
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

tree::TerminalNode* LogosParser::ExplicitVarDecContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::ExplicitVarDecContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::TypeContext* LogosParser::ExplicitVarDecContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}

tree::TerminalNode* LogosParser::ExplicitVarDecContext::CONST() {
  return getToken(LogosParser::CONST, 0);
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
  enterRule(_localctx, 60, LogosParser::RuleExplicitVarDec);
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
    setState(431);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(430);
      match(LogosParser::CONST);
    }
    setState(433);
    match(LogosParser::IDENTIFIER);
    setState(434);
    match(LogosParser::COLON);
    setState(435);
    type(0);
    setState(438);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(436);
      match(LogosParser::EQUAL);
      setState(437);
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

tree::TerminalNode* LogosParser::ImplicitVarDecContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::ImplicitVarDecContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::ImplicitVarDecContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::ImplicitVarDecContext::CONST() {
  return getToken(LogosParser::CONST, 0);
}

tree::TerminalNode* LogosParser::ImplicitVarDecContext::QUEST_MARK() {
  return getToken(LogosParser::QUEST_MARK, 0);
}


size_t LogosParser::ImplicitVarDecContext::getRuleIndex() const {
  return LogosParser::RuleImplicitVarDec;
}


LogosParser::ImplicitVarDecContext* LogosParser::implicitVarDec() {
  ImplicitVarDecContext *_localctx = _tracker.createInstance<ImplicitVarDecContext>(_ctx, getState());
  enterRule(_localctx, 62, LogosParser::RuleImplicitVarDec);
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
    setState(441);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(440);
      match(LogosParser::CONST);
    }
    setState(443);
    match(LogosParser::IDENTIFIER);
    setState(445);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(444);
      match(LogosParser::QUEST_MARK);
    }
    setState(447);
    match(LogosParser::EQUAL);
    setState(448);
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

tree::TerminalNode* LogosParser::IfStatementContext::TAG() {
  return getToken(LogosParser::TAG, 0);
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


size_t LogosParser::IfStatementContext::getRuleIndex() const {
  return LogosParser::RuleIfStatement;
}


LogosParser::IfStatementContext* LogosParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 64, LogosParser::RuleIfStatement);
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
    setState(450);
    match(LogosParser::IF);
    setState(451);
    expr(0);
    setState(453);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TAG) {
      setState(452);
      match(LogosParser::TAG);
    }
    setState(455);
    statementsBlock();
    setState(459);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(456);
        elseIfStatement(); 
      }
      setState(461);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    }
    setState(463);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(462);
      elseStatement();
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
  enterRule(_localctx, 66, LogosParser::RuleElseIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(465);
    match(LogosParser::ELSE);
    setState(466);
    expr(0);
    setState(467);
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
  enterRule(_localctx, 68, LogosParser::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(469);
    match(LogosParser::ELSE);
    setState(470);
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
  enterRule(_localctx, 70, LogosParser::RulePatternMatching);
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
    setState(472);
    match(LogosParser::IF);
    setState(474);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      setState(473);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(476);
    match(LogosParser::LBRACE);
    setState(480);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(477);
      pattern();
      setState(482);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(486);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(483);
      match(LogosParser::ELSE);
      setState(484);
      match(LogosParser::COLON);
      setState(485);
      statementsBlock();
    }
    setState(488);
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
  enterRule(_localctx, 72, LogosParser::RulePattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(490);
    expr(0);
    setState(491);
    match(LogosParser::COLON);
    setState(492);
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

std::vector<tree::TerminalNode *> LogosParser::LoopStatementContext::IDENTIFIER() {
  return getTokens(LogosParser::IDENTIFIER);
}

tree::TerminalNode* LogosParser::LoopStatementContext::IDENTIFIER(size_t i) {
  return getToken(LogosParser::IDENTIFIER, i);
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
  enterRule(_localctx, 74, LogosParser::RuleLoopStatement);
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
    setState(524);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(494);
      match(LogosParser::FOR);
      setState(495);
      match(LogosParser::IDENTIFIER);
      setState(497);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(496);
        match(LogosParser::COMMA);
      }
      setState(499);
      match(LogosParser::IN);
      setState(500);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(501);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(503);
      match(LogosParser::FOR);
      setState(504);
      match(LogosParser::IDENTIFIER);
      setState(509);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(505);
          match(LogosParser::COMMA);
          setState(506);
          match(LogosParser::IDENTIFIER); 
        }
        setState(511);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
      }
      setState(513);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(512);
        match(LogosParser::COMMA);
      }
      setState(515);
      match(LogosParser::IN);
      setState(516);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = unaryExpr();
      setState(517);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(519);
      match(LogosParser::FOR);
      setState(521);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::IDENTIFIER) {
        setState(520);
        match(LogosParser::IDENTIFIER);
      }
      setState(523);
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

//----------------- BreakStmtContext ------------------------------------------------------------------

LogosParser::BreakStmtContext::BreakStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::BreakStmtContext::BREAK() {
  return getToken(LogosParser::BREAK, 0);
}

tree::TerminalNode* LogosParser::BreakStmtContext::TAG() {
  return getToken(LogosParser::TAG, 0);
}


size_t LogosParser::BreakStmtContext::getRuleIndex() const {
  return LogosParser::RuleBreakStmt;
}


LogosParser::BreakStmtContext* LogosParser::breakStmt() {
  BreakStmtContext *_localctx = _tracker.createInstance<BreakStmtContext>(_ctx, getState());
  enterRule(_localctx, 76, LogosParser::RuleBreakStmt);
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
    setState(526);
    match(LogosParser::BREAK);
    setState(528);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TAG) {
      setState(527);
      match(LogosParser::TAG);
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
  enterRule(_localctx, 78, LogosParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(530);
    match(LogosParser::RETURN);
    setState(532);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      setState(531);
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

//----------------- EnumDeclarationContext ------------------------------------------------------------------

LogosParser::EnumDeclarationContext::EnumDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::EnumDeclarationContext::ENUM() {
  return getToken(LogosParser::ENUM, 0);
}

tree::TerminalNode* LogosParser::EnumDeclarationContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
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
  enterRule(_localctx, 80, LogosParser::RuleEnumDeclaration);
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
    setState(534);
    match(LogosParser::ENUM);
    setState(535);
    match(LogosParser::IDENTIFIER);
    setState(536);
    match(LogosParser::LBRACE);
    setState(540);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(537);
      enumField();
      setState(542);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(543);
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

tree::TerminalNode* LogosParser::EnumFieldContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
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
  enterRule(_localctx, 82, LogosParser::RuleEnumField);
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
    setState(545);
    match(LogosParser::IDENTIFIER);
    setState(548);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(546);
      match(LogosParser::EQUAL);
      setState(547);
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

tree::TerminalNode* LogosParser::ExprContext::ARROW() {
  return getToken(LogosParser::ARROW, 0);
}

LogosParser::TypeContext* LogosParser::ExprContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}

LogosParser::UnaryExprContext* LogosParser::ExprContext::unaryExpr() {
  return getRuleContext<LogosParser::UnaryExprContext>(0);
}

tree::TerminalNode* LogosParser::ExprContext::STAR() {
  return getToken(LogosParser::STAR, 0);
}

tree::TerminalNode* LogosParser::ExprContext::SLASH() {
  return getToken(LogosParser::SLASH, 0);
}

tree::TerminalNode* LogosParser::ExprContext::PERCENT() {
  return getToken(LogosParser::PERCENT, 0);
}

tree::TerminalNode* LogosParser::ExprContext::PLUS() {
  return getToken(LogosParser::PLUS, 0);
}

tree::TerminalNode* LogosParser::ExprContext::MINUS() {
  return getToken(LogosParser::MINUS, 0);
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

tree::TerminalNode* LogosParser::ExprContext::DOUBLE_EQUAL() {
  return getToken(LogosParser::DOUBLE_EQUAL, 0);
}

tree::TerminalNode* LogosParser::ExprContext::NOT_EQUAL() {
  return getToken(LogosParser::NOT_EQUAL, 0);
}

tree::TerminalNode* LogosParser::ExprContext::AND() {
  return getToken(LogosParser::AND, 0);
}

tree::TerminalNode* LogosParser::ExprContext::OR() {
  return getToken(LogosParser::OR, 0);
}

tree::TerminalNode* LogosParser::ExprContext::AMPERSAND() {
  return getToken(LogosParser::AMPERSAND, 0);
}

tree::TerminalNode* LogosParser::ExprContext::CARET() {
  return getToken(LogosParser::CARET, 0);
}

tree::TerminalNode* LogosParser::ExprContext::PIPE() {
  return getToken(LogosParser::PIPE, 0);
}

tree::TerminalNode* LogosParser::ExprContext::DOUBLE_LANGLE() {
  return getToken(LogosParser::DOUBLE_LANGLE, 0);
}

tree::TerminalNode* LogosParser::ExprContext::DOUBLE_RANGLE() {
  return getToken(LogosParser::DOUBLE_RANGLE, 0);
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
  size_t startState = 84;
  enterRecursionRule(_localctx, 84, LogosParser::RuleExpr, precedence);

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
    setState(563);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
    case 1: {
      setState(551);
      match(LogosParser::LPAREN);
      setState(552);
      antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
      setState(553);
      match(LogosParser::RPAREN);
      setState(556);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
      case 1: {
        setState(554);
        match(LogosParser::ARROW);
        setState(555);
        type(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      setState(558);
      unaryExpr();
      setState(561);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
      case 1: {
        setState(559);
        match(LogosParser::ARROW);
        setState(560);
        antlrcpp::downCast<ExprContext *>(_localctx)->cast = type(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(588);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(586);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(565);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(566);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 9620726743040) != 0))) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(567);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(568);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(569);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == LogosParser::PLUS

          || _la == LogosParser::MINUS)) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(570);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(571);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(572);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 98496) != 0))) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(573);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(574);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(575);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == LogosParser::DOUBLE_EQUAL

          || _la == LogosParser::NOT_EQUAL)) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(576);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(577);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(578);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == LogosParser::AND

          || _la == LogosParser::OR)) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(579);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(580);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(581);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 246290604621824) != 0))) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(582);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(583);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(584);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == LogosParser::DOUBLE_RANGLE

          || _la == LogosParser::DOUBLE_LANGLE)) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(585);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(590);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx);
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

tree::TerminalNode* LogosParser::UnaryExprContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
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

LogosParser::PrefixExprContext* LogosParser::UnaryExprContext::prefixExpr() {
  return getRuleContext<LogosParser::PrefixExprContext>(0);
}

LogosParser::PostfixExprContext* LogosParser::UnaryExprContext::postfixExpr() {
  return getRuleContext<LogosParser::PostfixExprContext>(0);
}

LogosParser::FuncCallContext* LogosParser::UnaryExprContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::AnonnymosFuncContext* LogosParser::UnaryExprContext::anonnymosFunc() {
  return getRuleContext<LogosParser::AnonnymosFuncContext>(0);
}

LogosParser::VectorContext* LogosParser::UnaryExprContext::vector() {
  return getRuleContext<LogosParser::VectorContext>(0);
}

LogosParser::ConstructorContext* LogosParser::UnaryExprContext::constructor() {
  return getRuleContext<LogosParser::ConstructorContext>(0);
}

LogosParser::ConstantContext* LogosParser::UnaryExprContext::constant() {
  return getRuleContext<LogosParser::ConstantContext>(0);
}

LogosParser::IterIndexContext* LogosParser::UnaryExprContext::iterIndex() {
  return getRuleContext<LogosParser::IterIndexContext>(0);
}

LogosParser::SelectionContext* LogosParser::UnaryExprContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}

LogosParser::ArrayExprContext* LogosParser::UnaryExprContext::arrayExpr() {
  return getRuleContext<LogosParser::ArrayExprContext>(0);
}

LogosParser::HashMapContext* LogosParser::UnaryExprContext::hashMap() {
  return getRuleContext<LogosParser::HashMapContext>(0);
}


size_t LogosParser::UnaryExprContext::getRuleIndex() const {
  return LogosParser::RuleUnaryExpr;
}


LogosParser::UnaryExprContext* LogosParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 86, LogosParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(606);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(591);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(592);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(593);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(594);
      match(LogosParser::NULL_);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(595);
      prefixExpr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(596);
      postfixExpr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(597);
      funcCall();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(598);
      anonnymosFunc();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(599);
      vector();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(600);
      constructor();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(601);
      constant();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(602);
      iterIndex();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(603);
      selection();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(604);
      arrayExpr();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(605);
      hashMap();
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

//----------------- PrefixExprContext ------------------------------------------------------------------

LogosParser::PrefixExprContext::PrefixExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ExprContext* LogosParser::PrefixExprContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::PrefixExprContext::NOT() {
  return getToken(LogosParser::NOT, 0);
}

tree::TerminalNode* LogosParser::PrefixExprContext::MINUS() {
  return getToken(LogosParser::MINUS, 0);
}


size_t LogosParser::PrefixExprContext::getRuleIndex() const {
  return LogosParser::RulePrefixExpr;
}


LogosParser::PrefixExprContext* LogosParser::prefixExpr() {
  PrefixExprContext *_localctx = _tracker.createInstance<PrefixExprContext>(_ctx, getState());
  enterRule(_localctx, 88, LogosParser::RulePrefixExpr);
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
    setState(608);
    _la = _input->LA(1);
    if (!(_la == LogosParser::MINUS

    || _la == LogosParser::NOT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(609);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PostfixExprContext ------------------------------------------------------------------

LogosParser::PostfixExprContext::PostfixExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::PostfixExprContext::INC() {
  return getToken(LogosParser::INC, 0);
}

tree::TerminalNode* LogosParser::PostfixExprContext::DEC() {
  return getToken(LogosParser::DEC, 0);
}

tree::TerminalNode* LogosParser::PostfixExprContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

LogosParser::IterIndexContext* LogosParser::PostfixExprContext::iterIndex() {
  return getRuleContext<LogosParser::IterIndexContext>(0);
}

LogosParser::SelectionContext* LogosParser::PostfixExprContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}

LogosParser::FuncCallContext* LogosParser::PostfixExprContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::ConstantContext* LogosParser::PostfixExprContext::constant() {
  return getRuleContext<LogosParser::ConstantContext>(0);
}


size_t LogosParser::PostfixExprContext::getRuleIndex() const {
  return LogosParser::RulePostfixExpr;
}


LogosParser::PostfixExprContext* LogosParser::postfixExpr() {
  PostfixExprContext *_localctx = _tracker.createInstance<PostfixExprContext>(_ctx, getState());
  enterRule(_localctx, 90, LogosParser::RulePostfixExpr);
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
    setState(616);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      setState(611);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(612);
      iterIndex();
      break;
    }

    case 3: {
      setState(613);
      selection();
      break;
    }

    case 4: {
      setState(614);
      funcCall();
      break;
    }

    case 5: {
      setState(615);
      constant();
      break;
    }

    default:
      break;
    }
    setState(618);
    _la = _input->LA(1);
    if (!(_la == LogosParser::INC

    || _la == LogosParser::DEC)) {
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

//----------------- ArrayExprContext ------------------------------------------------------------------

LogosParser::ArrayExprContext::ArrayExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ArrayExprContext::LBRACK() {
  return getToken(LogosParser::LBRACK, 0);
}

tree::TerminalNode* LogosParser::ArrayExprContext::RBRACK() {
  return getToken(LogosParser::RBRACK, 0);
}

std::vector<LogosParser::ExprContext *> LogosParser::ArrayExprContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::ArrayExprContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

tree::TerminalNode* LogosParser::ArrayExprContext::EXCLA_MARK() {
  return getToken(LogosParser::EXCLA_MARK, 0);
}

std::vector<tree::TerminalNode *> LogosParser::ArrayExprContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ArrayExprContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ArrayExprContext::getRuleIndex() const {
  return LogosParser::RuleArrayExpr;
}


LogosParser::ArrayExprContext* LogosParser::arrayExpr() {
  ArrayExprContext *_localctx = _tracker.createInstance<ArrayExprContext>(_ctx, getState());
  enterRule(_localctx, 92, LogosParser::RuleArrayExpr);
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
    setState(620);
    match(LogosParser::LBRACK);
    setState(632);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(621);
      expr(0);
      setState(626);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(622);
          match(LogosParser::COMMA);
          setState(623);
          expr(0); 
        }
        setState(628);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
      }
      setState(630);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(629);
        match(LogosParser::COMMA);
      }
    }
    setState(634);
    match(LogosParser::RBRACK);
    setState(636);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx)) {
    case 1: {
      setState(635);
      match(LogosParser::EXCLA_MARK);
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

//----------------- HashMapContext ------------------------------------------------------------------

LogosParser::HashMapContext::HashMapContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::HashMapContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

tree::TerminalNode* LogosParser::HashMapContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

std::vector<LogosParser::KeyValueContext *> LogosParser::HashMapContext::keyValue() {
  return getRuleContexts<LogosParser::KeyValueContext>();
}

LogosParser::KeyValueContext* LogosParser::HashMapContext::keyValue(size_t i) {
  return getRuleContext<LogosParser::KeyValueContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::HashMapContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::HashMapContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::HashMapContext::getRuleIndex() const {
  return LogosParser::RuleHashMap;
}


LogosParser::HashMapContext* LogosParser::hashMap() {
  HashMapContext *_localctx = _tracker.createInstance<HashMapContext>(_ctx, getState());
  enterRule(_localctx, 94, LogosParser::RuleHashMap);
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
    setState(638);
    match(LogosParser::LBRACE);
    setState(650);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(639);
      keyValue();
      setState(644);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(640);
          match(LogosParser::COMMA);
          setState(641);
          keyValue(); 
        }
        setState(646);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx);
      }
      setState(648);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(647);
        match(LogosParser::COMMA);
      }
    }
    setState(652);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyValueContext ------------------------------------------------------------------

LogosParser::KeyValueContext::KeyValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::KeyValueContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

std::vector<LogosParser::ExprContext *> LogosParser::KeyValueContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::KeyValueContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}


size_t LogosParser::KeyValueContext::getRuleIndex() const {
  return LogosParser::RuleKeyValue;
}


LogosParser::KeyValueContext* LogosParser::keyValue() {
  KeyValueContext *_localctx = _tracker.createInstance<KeyValueContext>(_ctx, getState());
  enterRule(_localctx, 96, LogosParser::RuleKeyValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(654);
    antlrcpp::downCast<KeyValueContext *>(_localctx)->key = expr(0);
    setState(655);
    match(LogosParser::COLON);
    setState(656);
    antlrcpp::downCast<KeyValueContext *>(_localctx)->value = expr(0);
   
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

tree::TerminalNode* LogosParser::FuncCallContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
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

tree::TerminalNode* LogosParser::FuncCallContext::TRIPLE_DOT() {
  return getToken(LogosParser::TRIPLE_DOT, 0);
}

tree::TerminalNode* LogosParser::FuncCallContext::COMMA() {
  return getToken(LogosParser::COMMA, 0);
}


size_t LogosParser::FuncCallContext::getRuleIndex() const {
  return LogosParser::RuleFuncCall;
}


LogosParser::FuncCallContext* LogosParser::funcCall() {
  FuncCallContext *_localctx = _tracker.createInstance<FuncCallContext>(_ctx, getState());
  enterRule(_localctx, 98, LogosParser::RuleFuncCall);
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
    setState(658);
    match(LogosParser::IDENTIFIER);
    setState(659);
    match(LogosParser::LPAREN);
    setState(661);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(660);
      funcArgList();
    }
    setState(664);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TRIPLE_DOT) {
      setState(663);
      match(LogosParser::TRIPLE_DOT);
    }
    setState(667);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(666);
      match(LogosParser::COMMA);
    }
    setState(669);
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
  enterRule(_localctx, 100, LogosParser::RuleFuncArgList);

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
    setState(671);
    funcArg();
    setState(676);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(672);
        match(LogosParser::COMMA);
        setState(673);
        funcArg(); 
      }
      setState(678);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx);
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

tree::TerminalNode* LogosParser::FuncArgContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::FuncArgContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}


size_t LogosParser::FuncArgContext::getRuleIndex() const {
  return LogosParser::RuleFuncArg;
}


LogosParser::FuncArgContext* LogosParser::funcArg() {
  FuncArgContext *_localctx = _tracker.createInstance<FuncArgContext>(_ctx, getState());
  enterRule(_localctx, 102, LogosParser::RuleFuncArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(681);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx)) {
    case 1: {
      setState(679);
      match(LogosParser::IDENTIFIER);
      setState(680);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(683);
    expr(0);
   
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

tree::TerminalNode* LogosParser::ConstructorContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::ConstructorContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

tree::TerminalNode* LogosParser::ConstructorContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

LogosParser::ConstructorArgListContext* LogosParser::ConstructorContext::constructorArgList() {
  return getRuleContext<LogosParser::ConstructorArgListContext>(0);
}


size_t LogosParser::ConstructorContext::getRuleIndex() const {
  return LogosParser::RuleConstructor;
}


LogosParser::ConstructorContext* LogosParser::constructor() {
  ConstructorContext *_localctx = _tracker.createInstance<ConstructorContext>(_ctx, getState());
  enterRule(_localctx, 104, LogosParser::RuleConstructor);
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
    setState(685);
    match(LogosParser::IDENTIFIER);
    setState(686);
    match(LogosParser::LBRACE);
    setState(688);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(687);
      constructorArgList();
    }
    setState(690);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructorArgListContext ------------------------------------------------------------------

LogosParser::ConstructorArgListContext::ConstructorArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::ConstructorArgContext *> LogosParser::ConstructorArgListContext::constructorArg() {
  return getRuleContexts<LogosParser::ConstructorArgContext>();
}

LogosParser::ConstructorArgContext* LogosParser::ConstructorArgListContext::constructorArg(size_t i) {
  return getRuleContext<LogosParser::ConstructorArgContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::ConstructorArgListContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ConstructorArgListContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ConstructorArgListContext::getRuleIndex() const {
  return LogosParser::RuleConstructorArgList;
}


LogosParser::ConstructorArgListContext* LogosParser::constructorArgList() {
  ConstructorArgListContext *_localctx = _tracker.createInstance<ConstructorArgListContext>(_ctx, getState());
  enterRule(_localctx, 106, LogosParser::RuleConstructorArgList);
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
    setState(692);
    constructorArg();
    setState(697);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(693);
        match(LogosParser::COMMA);
        setState(694);
        constructorArg(); 
      }
      setState(699);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx);
    }
    setState(701);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(700);
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

//----------------- ConstructorArgContext ------------------------------------------------------------------

LogosParser::ConstructorArgContext::ConstructorArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ConstructorArgContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::ConstructorArgContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::ConstructorArgContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::ConstructorArgContext::getRuleIndex() const {
  return LogosParser::RuleConstructorArg;
}


LogosParser::ConstructorArgContext* LogosParser::constructorArg() {
  ConstructorArgContext *_localctx = _tracker.createInstance<ConstructorArgContext>(_ctx, getState());
  enterRule(_localctx, 108, LogosParser::RuleConstructorArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(703);
    match(LogosParser::IDENTIFIER);
    setState(704);
    match(LogosParser::EQUAL);
    setState(705);
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
  enterRule(_localctx, 110, LogosParser::RuleConstant);
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
    setState(707);
    _la = _input->LA(1);
    if (!(((((_la - 73) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 73)) & 39) != 0))) {
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

//----------------- IterIndexContext ------------------------------------------------------------------

LogosParser::IterIndexContext::IterIndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::FuncCallContext* LogosParser::IterIndexContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

tree::TerminalNode* LogosParser::IterIndexContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

std::vector<LogosParser::IndexContext *> LogosParser::IterIndexContext::index() {
  return getRuleContexts<LogosParser::IndexContext>();
}

LogosParser::IndexContext* LogosParser::IterIndexContext::index(size_t i) {
  return getRuleContext<LogosParser::IndexContext>(i);
}


size_t LogosParser::IterIndexContext::getRuleIndex() const {
  return LogosParser::RuleIterIndex;
}


LogosParser::IterIndexContext* LogosParser::iterIndex() {
  IterIndexContext *_localctx = _tracker.createInstance<IterIndexContext>(_ctx, getState());
  enterRule(_localctx, 112, LogosParser::RuleIterIndex);

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
    setState(711);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx)) {
    case 1: {
      setState(709);
      funcCall();
      break;
    }

    case 2: {
      setState(710);
      match(LogosParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    setState(714); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(713);
              index();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(716); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 89, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IndexContext ------------------------------------------------------------------

LogosParser::IndexContext::IndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::IndexContext::LBRACK() {
  return getToken(LogosParser::LBRACK, 0);
}

tree::TerminalNode* LogosParser::IndexContext::RBRACK() {
  return getToken(LogosParser::RBRACK, 0);
}

std::vector<LogosParser::ExprContext *> LogosParser::IndexContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::IndexContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

tree::TerminalNode* LogosParser::IndexContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}


size_t LogosParser::IndexContext::getRuleIndex() const {
  return LogosParser::RuleIndex;
}


LogosParser::IndexContext* LogosParser::index() {
  IndexContext *_localctx = _tracker.createInstance<IndexContext>(_ctx, getState());
  enterRule(_localctx, 114, LogosParser::RuleIndex);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(736);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(718);
      match(LogosParser::LBRACK);
      setState(719);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(721);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COLON) {
        setState(720);
        match(LogosParser::COLON);
      }
      setState(723);
      match(LogosParser::RBRACK);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(725);
      match(LogosParser::LBRACK);
      setState(726);
      match(LogosParser::COLON);
      setState(727);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(728);
      match(LogosParser::RBRACK);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(730);
      match(LogosParser::LBRACK);
      setState(731);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(732);
      match(LogosParser::COLON);
      setState(733);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(734);
      match(LogosParser::RBRACK);
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

LogosParser::FirstSelectionElementContext* LogosParser::SelectionContext::firstSelectionElement() {
  return getRuleContext<LogosParser::FirstSelectionElementContext>(0);
}

std::vector<tree::TerminalNode *> LogosParser::SelectionContext::QUEST_MARK() {
  return getTokens(LogosParser::QUEST_MARK);
}

tree::TerminalNode* LogosParser::SelectionContext::QUEST_MARK(size_t i) {
  return getToken(LogosParser::QUEST_MARK, i);
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
  enterRule(_localctx, 116, LogosParser::RuleSelection);
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
    setState(738);
    firstSelectionElement();
    setState(740);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(739);
      match(LogosParser::QUEST_MARK);
    }
    setState(747); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(742);
              match(LogosParser::DOT);
              setState(743);
              innerSelectionElement();
              setState(745);
              _errHandler->sync(this);

              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
              case 1: {
                setState(744);
                match(LogosParser::QUEST_MARK);
                break;
              }

              default:
                break;
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(749); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 94, _ctx);
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

tree::TerminalNode* LogosParser::FirstSelectionElementContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::FirstSelectionElementContext::STRING() {
  return getToken(LogosParser::STRING, 0);
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

LogosParser::IterIndexContext* LogosParser::FirstSelectionElementContext::iterIndex() {
  return getRuleContext<LogosParser::IterIndexContext>(0);
}


size_t LogosParser::FirstSelectionElementContext::getRuleIndex() const {
  return LogosParser::RuleFirstSelectionElement;
}


LogosParser::FirstSelectionElementContext* LogosParser::firstSelectionElement() {
  FirstSelectionElementContext *_localctx = _tracker.createInstance<FirstSelectionElementContext>(_ctx, getState());
  enterRule(_localctx, 118, LogosParser::RuleFirstSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(758);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 95, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(751);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(752);
      match(LogosParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(753);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(754);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(755);
      funcCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(756);
      constructor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(757);
      iterIndex();
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

tree::TerminalNode* LogosParser::InnerSelectionElementContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

LogosParser::FuncCallContext* LogosParser::InnerSelectionElementContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::IterIndexContext* LogosParser::InnerSelectionElementContext::iterIndex() {
  return getRuleContext<LogosParser::IterIndexContext>(0);
}


size_t LogosParser::InnerSelectionElementContext::getRuleIndex() const {
  return LogosParser::RuleInnerSelectionElement;
}


LogosParser::InnerSelectionElementContext* LogosParser::innerSelectionElement() {
  InnerSelectionElementContext *_localctx = _tracker.createInstance<InnerSelectionElementContext>(_ctx, getState());
  enterRule(_localctx, 120, LogosParser::RuleInnerSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(763);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(760);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(761);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(762);
      iterIndex();
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
  enterRule(_localctx, 122, LogosParser::RuleRange);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(774);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(765);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(766);
      match(LogosParser::DOUBLE_DOT);
      setState(767);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(769);
      match(LogosParser::DOUBLE_DOT);
      setState(770);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(771);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(772);
      match(LogosParser::DOUBLE_DOT);
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

//----------------- TypeContext ------------------------------------------------------------------

LogosParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::TypeContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::TypeContext::QUEST_MARK() {
  return getToken(LogosParser::QUEST_MARK, 0);
}

tree::TerminalNode* LogosParser::TypeContext::SELF_CLASS() {
  return getToken(LogosParser::SELF_CLASS, 0);
}

LogosParser::MapTypeContext* LogosParser::TypeContext::mapType() {
  return getRuleContext<LogosParser::MapTypeContext>(0);
}

LogosParser::FuncTypeContext* LogosParser::TypeContext::funcType() {
  return getRuleContext<LogosParser::FuncTypeContext>(0);
}

LogosParser::TypeContext* LogosParser::TypeContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}

std::vector<LogosParser::ArraySizeContext *> LogosParser::TypeContext::arraySize() {
  return getRuleContexts<LogosParser::ArraySizeContext>();
}

LogosParser::ArraySizeContext* LogosParser::TypeContext::arraySize(size_t i) {
  return getRuleContext<LogosParser::ArraySizeContext>(i);
}

tree::TerminalNode* LogosParser::TypeContext::EXCLA_MARK() {
  return getToken(LogosParser::EXCLA_MARK, 0);
}


size_t LogosParser::TypeContext::getRuleIndex() const {
  return LogosParser::RuleType;
}



LogosParser::TypeContext* LogosParser::type() {
   return type(0);
}

LogosParser::TypeContext* LogosParser::type(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  LogosParser::TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, parentState);
  LogosParser::TypeContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 124;
  enterRecursionRule(_localctx, 124, LogosParser::RuleType, precedence);

    

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
    setState(784);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::IDENTIFIER: {
        setState(777);
        match(LogosParser::IDENTIFIER);
        setState(779);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx)) {
        case 1: {
          setState(778);
          match(LogosParser::QUEST_MARK);
          break;
        }

        default:
          break;
        }
        break;
      }

      case LogosParser::SELF_CLASS: {
        setState(781);
        match(LogosParser::SELF_CLASS);
        break;
      }

      case LogosParser::LBRACE: {
        setState(782);
        mapType();
        break;
      }

      case LogosParser::LPAREN: {
        setState(783);
        funcType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(797);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        _localctx->baseType = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(786);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(788); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(787);
                  arraySize();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(790); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        setState(793);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 101, _ctx)) {
        case 1: {
          setState(792);
          match(LogosParser::EXCLA_MARK);
          break;
        }

        default:
          break;
        } 
      }
      setState(799);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MapTypeContext ------------------------------------------------------------------

LogosParser::MapTypeContext::MapTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::MapTypeContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

tree::TerminalNode* LogosParser::MapTypeContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::MapTypeContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

std::vector<LogosParser::TypeContext *> LogosParser::MapTypeContext::type() {
  return getRuleContexts<LogosParser::TypeContext>();
}

LogosParser::TypeContext* LogosParser::MapTypeContext::type(size_t i) {
  return getRuleContext<LogosParser::TypeContext>(i);
}


size_t LogosParser::MapTypeContext::getRuleIndex() const {
  return LogosParser::RuleMapType;
}


LogosParser::MapTypeContext* LogosParser::mapType() {
  MapTypeContext *_localctx = _tracker.createInstance<MapTypeContext>(_ctx, getState());
  enterRule(_localctx, 126, LogosParser::RuleMapType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(800);
    match(LogosParser::LBRACE);
    setState(801);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->key = type(0);
    setState(802);
    match(LogosParser::COLON);
    setState(803);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->value = type(0);
    setState(804);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArraySizeContext ------------------------------------------------------------------

LogosParser::ArraySizeContext::ArraySizeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ArraySizeContext::LBRACK() {
  return getToken(LogosParser::LBRACK, 0);
}

tree::TerminalNode* LogosParser::ArraySizeContext::RBRACK() {
  return getToken(LogosParser::RBRACK, 0);
}

LogosParser::ExprContext* LogosParser::ArraySizeContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::ArraySizeContext::getRuleIndex() const {
  return LogosParser::RuleArraySize;
}


LogosParser::ArraySizeContext* LogosParser::arraySize() {
  ArraySizeContext *_localctx = _tracker.createInstance<ArraySizeContext>(_ctx, getState());
  enterRule(_localctx, 128, LogosParser::RuleArraySize);
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
    setState(806);
    match(LogosParser::LBRACK);
    setState(808);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(807);
      expr(0);
    }
    setState(810);
    match(LogosParser::RBRACK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

LogosParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::FuncTypeContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::FuncTypeContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

tree::TerminalNode* LogosParser::FuncTypeContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

std::vector<LogosParser::TypeContext *> LogosParser::FuncTypeContext::type() {
  return getRuleContexts<LogosParser::TypeContext>();
}

LogosParser::TypeContext* LogosParser::FuncTypeContext::type(size_t i) {
  return getRuleContext<LogosParser::TypeContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::FuncTypeContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::FuncTypeContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::FuncTypeContext::getRuleIndex() const {
  return LogosParser::RuleFuncType;
}


LogosParser::FuncTypeContext* LogosParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 130, LogosParser::RuleFuncType);
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
    setState(812);
    match(LogosParser::LPAREN);
    setState(824);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 9007199254742272) != 0) || _la == LogosParser::IDENTIFIER) {
      setState(813);
      type(0);
      setState(818);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(814);
          match(LogosParser::COMMA);
          setState(815);
          type(0); 
        }
        setState(820);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx);
      }
      setState(822);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(821);
        match(LogosParser::COMMA);
      }
    }
    setState(826);
    match(LogosParser::RPAREN);
    setState(827);
    match(LogosParser::COLON);
    setState(828);
    antlrcpp::downCast<FuncTypeContext *>(_localctx)->rt = type(0);
   
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

tree::TerminalNode* LogosParser::VectorContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::VectorContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
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

std::vector<LogosParser::ExprContext *> LogosParser::VectorContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::VectorContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::VectorContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::VectorContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::VectorContext::getRuleIndex() const {
  return LogosParser::RuleVector;
}


LogosParser::VectorContext* LogosParser::vector() {
  VectorContext *_localctx = _tracker.createInstance<VectorContext>(_ctx, getState());
  enterRule(_localctx, 132, LogosParser::RuleVector);
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
    setState(830);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8070450532247928832) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(831);
    match(LogosParser::LPAREN);
    setState(843);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(832);
      expr(0);
      setState(837);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 107, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(833);
          match(LogosParser::COMMA);
          setState(834);
          expr(0); 
        }
        setState(839);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 107, _ctx);
      }
      setState(841);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(840);
        match(LogosParser::COMMA);
      }
    }
    setState(845);
    match(LogosParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RequireEnvVarsContext ------------------------------------------------------------------

LogosParser::RequireEnvVarsContext::RequireEnvVarsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::RequireEnvVarsContext::LBRACE() {
  return getToken(LogosParser::LBRACE, 0);
}

tree::TerminalNode* LogosParser::RequireEnvVarsContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

std::vector<tree::TerminalNode *> LogosParser::RequireEnvVarsContext::IDENTIFIER() {
  return getTokens(LogosParser::IDENTIFIER);
}

tree::TerminalNode* LogosParser::RequireEnvVarsContext::IDENTIFIER(size_t i) {
  return getToken(LogosParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> LogosParser::RequireEnvVarsContext::COLON() {
  return getTokens(LogosParser::COLON);
}

tree::TerminalNode* LogosParser::RequireEnvVarsContext::COLON(size_t i) {
  return getToken(LogosParser::COLON, i);
}

std::vector<LogosParser::TypeContext *> LogosParser::RequireEnvVarsContext::type() {
  return getRuleContexts<LogosParser::TypeContext>();
}

LogosParser::TypeContext* LogosParser::RequireEnvVarsContext::type(size_t i) {
  return getRuleContext<LogosParser::TypeContext>(i);
}


size_t LogosParser::RequireEnvVarsContext::getRuleIndex() const {
  return LogosParser::RuleRequireEnvVars;
}


LogosParser::RequireEnvVarsContext* LogosParser::requireEnvVars() {
  RequireEnvVarsContext *_localctx = _tracker.createInstance<RequireEnvVarsContext>(_ctx, getState());
  enterRule(_localctx, 134, LogosParser::RuleRequireEnvVars);
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
    setState(847);
    match(LogosParser::T__1);
    setState(848);
    match(LogosParser::T__2);
    setState(849);
    match(LogosParser::LBRACE);
    setState(855);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(850);
      match(LogosParser::IDENTIFIER);
      setState(851);
      match(LogosParser::COLON);
      setState(852);
      type(0);
      setState(857);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(858);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignemntOpContext ------------------------------------------------------------------

LogosParser::AssignemntOpContext::AssignemntOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::AssignemntOpContext::WALRUS() {
  return getToken(LogosParser::WALRUS, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_PLUS() {
  return getToken(LogosParser::EQUAL_PLUS, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_MINUS() {
  return getToken(LogosParser::EQUAL_MINUS, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_STAR() {
  return getToken(LogosParser::EQUAL_STAR, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_SLASH() {
  return getToken(LogosParser::EQUAL_SLASH, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_PERCENT() {
  return getToken(LogosParser::EQUAL_PERCENT, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_AMPERSAND() {
  return getToken(LogosParser::EQUAL_AMPERSAND, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_PIPE() {
  return getToken(LogosParser::EQUAL_PIPE, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_CARET() {
  return getToken(LogosParser::EQUAL_CARET, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_DOUBLE_RANGLE() {
  return getToken(LogosParser::EQUAL_DOUBLE_RANGLE, 0);
}

tree::TerminalNode* LogosParser::AssignemntOpContext::EQUAL_DOUBLE_LANGLE() {
  return getToken(LogosParser::EQUAL_DOUBLE_LANGLE, 0);
}


size_t LogosParser::AssignemntOpContext::getRuleIndex() const {
  return LogosParser::RuleAssignemntOp;
}


LogosParser::AssignemntOpContext* LogosParser::assignemntOp() {
  AssignemntOpContext *_localctx = _tracker.createInstance<AssignemntOpContext>(_ctx, getState());
  enterRule(_localctx, 136, LogosParser::RuleAssignemntOp);
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
    setState(860);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2146435072) != 0))) {
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
    case 42: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);
    case 62: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool LogosParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 7);
    case 1: return precpred(_ctx, 6);
    case 2: return precpred(_ctx, 5);
    case 3: return precpred(_ctx, 4);
    case 4: return precpred(_ctx, 3);
    case 5: return precpred(_ctx, 2);
    case 6: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool LogosParser::typeSempred(TypeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 7: return precpred(_ctx, 3);

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
