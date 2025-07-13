
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
      "interfaceField", "objectDeclaration", "interfaceDeclaration", "objectImplements", 
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
  	4,1,82,875,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
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
  	5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,9,1,9,1,9,5,9,222,8,9,10,9,12,9,225,9,9,1,9,3,9,228,
  	8,9,1,10,1,10,1,10,5,10,233,8,10,10,10,12,10,236,9,10,1,10,3,10,239,8,
  	10,1,11,5,11,242,8,11,10,11,12,11,245,9,11,1,11,5,11,248,8,11,10,11,12,
  	11,251,9,11,1,11,5,11,254,8,11,10,11,12,11,257,9,11,1,12,1,12,1,12,1,
  	12,1,12,1,12,1,13,3,13,266,8,13,1,13,5,13,269,8,13,10,13,12,13,272,9,
  	13,1,13,5,13,275,8,13,10,13,12,13,278,9,13,1,14,3,14,281,8,14,1,14,3,
  	14,284,8,14,1,14,1,14,1,14,1,14,1,14,3,14,291,8,14,1,15,3,15,294,8,15,
  	1,15,1,15,3,15,298,8,15,1,15,1,15,1,15,1,15,3,15,304,8,15,1,16,1,16,1,
  	16,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,3,18,317,8,18,1,18,3,18,320,
  	8,18,1,19,1,19,1,19,1,19,1,19,5,19,327,8,19,10,19,12,19,330,9,19,1,19,
  	3,19,333,8,19,3,19,335,8,19,1,19,1,19,1,19,3,19,340,8,19,1,20,1,20,1,
  	20,1,20,1,20,5,20,347,8,20,10,20,12,20,350,9,20,1,20,3,20,353,8,20,3,
  	20,355,8,20,1,20,1,20,3,20,359,8,20,1,20,1,20,3,20,363,8,20,1,21,1,21,
  	1,21,1,22,1,22,1,22,1,22,5,22,372,8,22,10,22,12,22,375,9,22,1,22,3,22,
  	378,8,22,3,22,380,8,22,1,22,1,22,1,22,3,22,385,8,22,1,23,1,23,1,23,1,
  	24,3,24,391,8,24,1,24,1,24,1,24,1,25,1,25,1,26,1,26,1,26,1,26,3,26,402,
  	8,26,1,26,1,26,3,26,406,8,26,1,26,1,26,3,26,410,8,26,1,27,1,27,1,27,1,
  	27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,424,8,27,1,28,1,28,5,
  	28,428,8,28,10,28,12,28,431,9,28,1,28,1,28,1,29,1,29,1,29,3,29,438,8,
  	29,1,29,1,29,1,29,1,30,3,30,444,8,30,1,30,1,30,1,30,1,30,1,30,3,30,451,
  	8,30,1,31,3,31,454,8,31,1,31,1,31,3,31,458,8,31,1,31,1,31,1,31,1,32,1,
  	32,1,32,3,32,466,8,32,1,32,1,32,5,32,470,8,32,10,32,12,32,473,9,32,1,
  	32,3,32,476,8,32,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,35,1,35,3,35,487,
  	8,35,1,35,1,35,5,35,491,8,35,10,35,12,35,494,9,35,1,35,1,35,1,35,3,35,
  	499,8,35,1,35,1,35,1,36,1,36,1,36,1,36,1,37,1,37,1,37,3,37,510,8,37,1,
  	37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,5,37,520,8,37,10,37,12,37,523,9,
  	37,1,37,3,37,526,8,37,1,37,1,37,1,37,1,37,1,37,1,37,3,37,534,8,37,1,37,
  	3,37,537,8,37,1,38,1,38,3,38,541,8,38,1,39,1,39,3,39,545,8,39,1,40,1,
  	40,1,40,1,40,5,40,551,8,40,10,40,12,40,554,9,40,1,40,1,40,1,41,1,41,1,
  	41,3,41,561,8,41,1,42,1,42,1,42,1,42,1,42,1,42,3,42,569,8,42,1,42,1,42,
  	1,42,3,42,574,8,42,3,42,576,8,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,
  	42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,5,
  	42,599,8,42,10,42,12,42,602,9,42,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,
  	43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,3,43,619,8,43,1,44,1,44,1,44,1,
  	45,1,45,1,45,1,45,1,45,3,45,629,8,45,1,45,1,45,1,46,1,46,1,46,1,46,5,
  	46,637,8,46,10,46,12,46,640,9,46,1,46,3,46,643,8,46,3,46,645,8,46,1,46,
  	1,46,3,46,649,8,46,1,47,1,47,1,47,1,47,5,47,655,8,47,10,47,12,47,658,
  	9,47,1,47,3,47,661,8,47,3,47,663,8,47,1,47,1,47,1,48,1,48,1,48,1,48,1,
  	49,1,49,1,49,3,49,674,8,49,1,49,3,49,677,8,49,1,49,3,49,680,8,49,1,49,
  	1,49,1,50,1,50,1,50,5,50,687,8,50,10,50,12,50,690,9,50,1,51,1,51,3,51,
  	694,8,51,1,51,1,51,1,52,1,52,1,52,3,52,701,8,52,1,52,1,52,1,53,1,53,1,
  	53,5,53,708,8,53,10,53,12,53,711,9,53,1,53,3,53,714,8,53,1,54,1,54,1,
  	54,1,54,1,55,1,55,1,56,1,56,3,56,724,8,56,1,56,4,56,727,8,56,11,56,12,
  	56,728,1,57,1,57,1,57,3,57,734,8,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,
  	1,57,1,57,1,57,1,57,1,57,1,57,3,57,749,8,57,1,58,1,58,3,58,753,8,58,1,
  	58,1,58,1,58,3,58,758,8,58,4,58,760,8,58,11,58,12,58,761,1,59,1,59,1,
  	59,1,59,1,59,1,59,1,59,3,59,771,8,59,1,60,1,60,1,60,3,60,776,8,60,1,61,
  	1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,3,61,787,8,61,1,62,1,62,1,62,
  	3,62,792,8,62,1,62,1,62,1,62,3,62,797,8,62,1,62,1,62,4,62,801,8,62,11,
  	62,12,62,802,1,62,3,62,806,8,62,5,62,808,8,62,10,62,12,62,811,9,62,1,
  	63,1,63,1,63,1,63,1,63,1,63,1,64,1,64,3,64,821,8,64,1,64,1,64,1,65,1,
  	65,1,65,1,65,5,65,829,8,65,10,65,12,65,832,9,65,1,65,3,65,835,8,65,3,
  	65,837,8,65,1,65,1,65,1,65,1,65,1,66,1,66,1,66,1,66,1,66,5,66,848,8,66,
  	10,66,12,66,851,9,66,1,66,3,66,854,8,66,3,66,856,8,66,1,66,1,66,1,67,
  	1,67,1,67,1,67,1,67,1,67,5,67,866,8,67,10,67,12,67,869,9,67,1,67,1,67,
  	1,68,1,68,1,68,0,2,84,124,69,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,
  	76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,
  	118,120,122,124,126,128,130,132,134,136,0,13,1,0,50,51,2,0,38,39,43,43,
  	1,0,36,37,2,0,6,7,15,16,1,0,4,5,1,0,69,70,1,0,45,47,1,0,48,49,2,0,37,
  	37,71,71,1,0,31,32,2,0,73,75,78,78,1,0,60,62,1,0,20,30,964,0,139,1,0,
  	0,0,2,146,1,0,0,0,4,161,1,0,0,0,6,170,1,0,0,0,8,184,1,0,0,0,10,194,1,
  	0,0,0,12,198,1,0,0,0,14,202,1,0,0,0,16,208,1,0,0,0,18,218,1,0,0,0,20,
  	229,1,0,0,0,22,243,1,0,0,0,24,258,1,0,0,0,26,265,1,0,0,0,28,280,1,0,0,
  	0,30,293,1,0,0,0,32,305,1,0,0,0,34,308,1,0,0,0,36,311,1,0,0,0,38,321,
  	1,0,0,0,40,341,1,0,0,0,42,364,1,0,0,0,44,367,1,0,0,0,46,386,1,0,0,0,48,
  	390,1,0,0,0,50,395,1,0,0,0,52,409,1,0,0,0,54,423,1,0,0,0,56,425,1,0,0,
  	0,58,437,1,0,0,0,60,443,1,0,0,0,62,453,1,0,0,0,64,462,1,0,0,0,66,477,
  	1,0,0,0,68,481,1,0,0,0,70,484,1,0,0,0,72,502,1,0,0,0,74,536,1,0,0,0,76,
  	538,1,0,0,0,78,542,1,0,0,0,80,546,1,0,0,0,82,557,1,0,0,0,84,575,1,0,0,
  	0,86,618,1,0,0,0,88,620,1,0,0,0,90,628,1,0,0,0,92,632,1,0,0,0,94,650,
  	1,0,0,0,96,666,1,0,0,0,98,670,1,0,0,0,100,683,1,0,0,0,102,693,1,0,0,0,
  	104,697,1,0,0,0,106,704,1,0,0,0,108,715,1,0,0,0,110,719,1,0,0,0,112,723,
  	1,0,0,0,114,748,1,0,0,0,116,750,1,0,0,0,118,770,1,0,0,0,120,775,1,0,0,
  	0,122,786,1,0,0,0,124,796,1,0,0,0,126,812,1,0,0,0,128,818,1,0,0,0,130,
  	824,1,0,0,0,132,842,1,0,0,0,134,859,1,0,0,0,136,872,1,0,0,0,138,140,3,
  	2,1,0,139,138,1,0,0,0,139,140,1,0,0,0,140,144,1,0,0,0,141,145,3,8,4,0,
  	142,145,3,10,5,0,143,145,3,12,6,0,144,141,1,0,0,0,144,142,1,0,0,0,144,
  	143,1,0,0,0,145,1,1,0,0,0,146,147,5,55,0,0,147,148,5,1,0,0,148,152,5,
  	10,0,0,149,151,5,78,0,0,150,149,1,0,0,0,151,154,1,0,0,0,152,150,1,0,0,
  	0,152,153,1,0,0,0,153,155,1,0,0,0,154,152,1,0,0,0,155,156,5,11,0,0,156,
  	3,1,0,0,0,157,160,3,62,31,0,158,160,3,60,30,0,159,157,1,0,0,0,159,158,
  	1,0,0,0,160,163,1,0,0,0,161,159,1,0,0,0,161,162,1,0,0,0,162,164,1,0,0,
  	0,163,161,1,0,0,0,164,165,5,0,0,1,165,5,1,0,0,0,166,169,3,62,31,0,167,
  	169,3,60,30,0,168,166,1,0,0,0,168,167,1,0,0,0,169,172,1,0,0,0,170,168,
  	1,0,0,0,170,171,1,0,0,0,171,174,1,0,0,0,172,170,1,0,0,0,173,175,3,134,
  	67,0,174,173,1,0,0,0,174,175,1,0,0,0,175,176,1,0,0,0,176,177,5,0,0,1,
  	177,7,1,0,0,0,178,183,3,24,12,0,179,183,3,80,40,0,180,183,3,14,7,0,181,
  	183,3,16,8,0,182,178,1,0,0,0,182,179,1,0,0,0,182,180,1,0,0,0,182,181,
  	1,0,0,0,183,186,1,0,0,0,184,182,1,0,0,0,184,185,1,0,0,0,185,188,1,0,0,
  	0,186,184,1,0,0,0,187,189,3,42,21,0,188,187,1,0,0,0,189,190,1,0,0,0,190,
  	188,1,0,0,0,190,191,1,0,0,0,191,192,1,0,0,0,192,193,5,0,0,1,193,9,1,0,
  	0,0,194,195,3,32,16,0,195,196,3,26,13,0,196,197,5,0,0,1,197,11,1,0,0,
  	0,198,199,3,34,17,0,199,200,3,22,11,0,200,201,5,0,0,1,201,13,1,0,0,0,
  	202,203,5,54,0,0,203,204,5,77,0,0,204,205,5,10,0,0,205,206,3,22,11,0,
  	206,207,5,11,0,0,207,15,1,0,0,0,208,209,5,77,0,0,209,210,5,35,0,0,210,
  	211,5,10,0,0,211,212,3,18,9,0,212,213,5,11,0,0,213,214,5,14,0,0,214,215,
  	5,10,0,0,215,216,3,20,10,0,216,217,5,11,0,0,217,17,1,0,0,0,218,223,3,
  	124,62,0,219,220,5,17,0,0,220,222,3,124,62,0,221,219,1,0,0,0,222,225,
  	1,0,0,0,223,221,1,0,0,0,223,224,1,0,0,0,224,227,1,0,0,0,225,223,1,0,0,
  	0,226,228,5,17,0,0,227,226,1,0,0,0,227,228,1,0,0,0,228,19,1,0,0,0,229,
  	234,5,77,0,0,230,231,5,17,0,0,231,233,5,77,0,0,232,230,1,0,0,0,233,236,
  	1,0,0,0,234,232,1,0,0,0,234,235,1,0,0,0,235,238,1,0,0,0,236,234,1,0,0,
  	0,237,239,5,17,0,0,238,237,1,0,0,0,238,239,1,0,0,0,239,21,1,0,0,0,240,
  	242,3,30,15,0,241,240,1,0,0,0,242,245,1,0,0,0,243,241,1,0,0,0,243,244,
  	1,0,0,0,244,249,1,0,0,0,245,243,1,0,0,0,246,248,3,40,20,0,247,246,1,0,
  	0,0,248,251,1,0,0,0,249,247,1,0,0,0,249,250,1,0,0,0,250,255,1,0,0,0,251,
  	249,1,0,0,0,252,254,3,42,21,0,253,252,1,0,0,0,254,257,1,0,0,0,255,253,
  	1,0,0,0,255,256,1,0,0,0,256,23,1,0,0,0,257,255,1,0,0,0,258,259,7,0,0,
  	0,259,260,5,77,0,0,260,261,5,10,0,0,261,262,3,26,13,0,262,263,5,11,0,
  	0,263,25,1,0,0,0,264,266,3,36,18,0,265,264,1,0,0,0,265,266,1,0,0,0,266,
  	270,1,0,0,0,267,269,3,28,14,0,268,267,1,0,0,0,269,272,1,0,0,0,270,268,
  	1,0,0,0,270,271,1,0,0,0,271,276,1,0,0,0,272,270,1,0,0,0,273,275,3,48,
  	24,0,274,273,1,0,0,0,275,278,1,0,0,0,276,274,1,0,0,0,276,277,1,0,0,0,
  	277,27,1,0,0,0,278,276,1,0,0,0,279,281,5,56,0,0,280,279,1,0,0,0,280,281,
  	1,0,0,0,281,283,1,0,0,0,282,284,5,58,0,0,283,282,1,0,0,0,283,284,1,0,
  	0,0,284,285,1,0,0,0,285,286,5,77,0,0,286,287,5,34,0,0,287,290,3,124,62,
  	0,288,289,5,35,0,0,289,291,3,84,42,0,290,288,1,0,0,0,290,291,1,0,0,0,
  	291,29,1,0,0,0,292,294,5,58,0,0,293,292,1,0,0,0,293,294,1,0,0,0,294,295,
  	1,0,0,0,295,297,5,77,0,0,296,298,5,41,0,0,297,296,1,0,0,0,297,298,1,0,
  	0,0,298,299,1,0,0,0,299,300,5,34,0,0,300,303,3,124,62,0,301,302,5,35,
  	0,0,302,304,3,84,42,0,303,301,1,0,0,0,303,304,1,0,0,0,304,31,1,0,0,0,
  	305,306,7,0,0,0,306,307,5,77,0,0,307,33,1,0,0,0,308,309,5,54,0,0,309,
  	310,5,77,0,0,310,35,1,0,0,0,311,312,5,57,0,0,312,313,5,34,0,0,313,316,
  	5,77,0,0,314,315,5,17,0,0,315,317,5,77,0,0,316,314,1,0,0,0,316,317,1,
  	0,0,0,317,319,1,0,0,0,318,320,5,17,0,0,319,318,1,0,0,0,319,320,1,0,0,
  	0,320,37,1,0,0,0,321,322,5,77,0,0,322,334,5,8,0,0,323,328,3,52,26,0,324,
  	325,5,17,0,0,325,327,3,52,26,0,326,324,1,0,0,0,327,330,1,0,0,0,328,326,
  	1,0,0,0,328,329,1,0,0,0,329,332,1,0,0,0,330,328,1,0,0,0,331,333,5,17,
  	0,0,332,331,1,0,0,0,332,333,1,0,0,0,333,335,1,0,0,0,334,323,1,0,0,0,334,
  	335,1,0,0,0,335,336,1,0,0,0,336,339,5,9,0,0,337,338,5,34,0,0,338,340,
  	3,124,62,0,339,337,1,0,0,0,339,340,1,0,0,0,340,39,1,0,0,0,341,342,5,77,
  	0,0,342,354,5,8,0,0,343,348,3,52,26,0,344,345,5,17,0,0,345,347,3,52,26,
  	0,346,344,1,0,0,0,347,350,1,0,0,0,348,346,1,0,0,0,348,349,1,0,0,0,349,
  	352,1,0,0,0,350,348,1,0,0,0,351,353,5,17,0,0,352,351,1,0,0,0,352,353,
  	1,0,0,0,353,355,1,0,0,0,354,343,1,0,0,0,354,355,1,0,0,0,355,356,1,0,0,
  	0,356,358,5,9,0,0,357,359,5,41,0,0,358,357,1,0,0,0,358,359,1,0,0,0,359,
  	362,1,0,0,0,360,361,5,34,0,0,361,363,3,124,62,0,362,360,1,0,0,0,362,363,
  	1,0,0,0,363,41,1,0,0,0,364,365,3,38,19,0,365,366,3,50,25,0,366,43,1,0,
  	0,0,367,379,5,8,0,0,368,373,3,52,26,0,369,370,5,17,0,0,370,372,3,52,26,
  	0,371,369,1,0,0,0,372,375,1,0,0,0,373,371,1,0,0,0,373,374,1,0,0,0,374,
  	377,1,0,0,0,375,373,1,0,0,0,376,378,5,17,0,0,377,376,1,0,0,0,377,378,
  	1,0,0,0,378,380,1,0,0,0,379,368,1,0,0,0,379,380,1,0,0,0,380,381,1,0,0,
  	0,381,384,5,9,0,0,382,383,5,34,0,0,383,385,3,124,62,0,384,382,1,0,0,0,
  	384,385,1,0,0,0,385,45,1,0,0,0,386,387,3,44,22,0,387,388,3,50,25,0,388,
  	47,1,0,0,0,389,391,5,56,0,0,390,389,1,0,0,0,390,391,1,0,0,0,391,392,1,
  	0,0,0,392,393,3,38,19,0,393,394,3,50,25,0,394,49,1,0,0,0,395,396,3,56,
  	28,0,396,51,1,0,0,0,397,398,5,77,0,0,398,399,5,34,0,0,399,401,3,124,62,
  	0,400,402,5,18,0,0,401,400,1,0,0,0,401,402,1,0,0,0,402,405,1,0,0,0,403,
  	404,5,35,0,0,404,406,3,84,42,0,405,403,1,0,0,0,405,406,1,0,0,0,406,410,
  	1,0,0,0,407,408,5,77,0,0,408,410,3,130,65,0,409,397,1,0,0,0,409,407,1,
  	0,0,0,410,53,1,0,0,0,411,424,3,58,29,0,412,424,3,60,30,0,413,424,3,62,
  	31,0,414,424,3,64,32,0,415,424,3,70,35,0,416,424,3,74,37,0,417,424,5,
  	67,0,0,418,424,3,76,38,0,419,424,3,78,39,0,420,424,3,98,49,0,421,424,
  	3,116,58,0,422,424,3,90,45,0,423,411,1,0,0,0,423,412,1,0,0,0,423,413,
  	1,0,0,0,423,414,1,0,0,0,423,415,1,0,0,0,423,416,1,0,0,0,423,417,1,0,0,
  	0,423,418,1,0,0,0,423,419,1,0,0,0,423,420,1,0,0,0,423,421,1,0,0,0,423,
  	422,1,0,0,0,424,55,1,0,0,0,425,429,5,10,0,0,426,428,3,54,27,0,427,426,
  	1,0,0,0,428,431,1,0,0,0,429,427,1,0,0,0,429,430,1,0,0,0,430,432,1,0,0,
  	0,431,429,1,0,0,0,432,433,5,11,0,0,433,57,1,0,0,0,434,438,5,77,0,0,435,
  	438,3,112,56,0,436,438,3,116,58,0,437,434,1,0,0,0,437,435,1,0,0,0,437,
  	436,1,0,0,0,438,439,1,0,0,0,439,440,3,136,68,0,440,441,3,84,42,0,441,
  	59,1,0,0,0,442,444,5,58,0,0,443,442,1,0,0,0,443,444,1,0,0,0,444,445,1,
  	0,0,0,445,446,5,77,0,0,446,447,5,34,0,0,447,450,3,124,62,0,448,449,5,
  	35,0,0,449,451,3,84,42,0,450,448,1,0,0,0,450,451,1,0,0,0,451,61,1,0,0,
  	0,452,454,5,58,0,0,453,452,1,0,0,0,453,454,1,0,0,0,454,455,1,0,0,0,455,
  	457,5,77,0,0,456,458,5,41,0,0,457,456,1,0,0,0,457,458,1,0,0,0,458,459,
  	1,0,0,0,459,460,5,35,0,0,460,461,3,84,42,0,461,63,1,0,0,0,462,463,5,63,
  	0,0,463,465,3,84,42,0,464,466,5,79,0,0,465,464,1,0,0,0,465,466,1,0,0,
  	0,466,467,1,0,0,0,467,471,3,56,28,0,468,470,3,66,33,0,469,468,1,0,0,0,
  	470,473,1,0,0,0,471,469,1,0,0,0,471,472,1,0,0,0,472,475,1,0,0,0,473,471,
  	1,0,0,0,474,476,3,68,34,0,475,474,1,0,0,0,475,476,1,0,0,0,476,65,1,0,
  	0,0,477,478,5,64,0,0,478,479,3,84,42,0,479,480,3,56,28,0,480,67,1,0,0,
  	0,481,482,5,64,0,0,482,483,3,56,28,0,483,69,1,0,0,0,484,486,5,63,0,0,
  	485,487,3,84,42,0,486,485,1,0,0,0,486,487,1,0,0,0,487,488,1,0,0,0,488,
  	492,5,10,0,0,489,491,3,72,36,0,490,489,1,0,0,0,491,494,1,0,0,0,492,490,
  	1,0,0,0,492,493,1,0,0,0,493,498,1,0,0,0,494,492,1,0,0,0,495,496,5,64,
  	0,0,496,497,5,34,0,0,497,499,3,56,28,0,498,495,1,0,0,0,498,499,1,0,0,
  	0,499,500,1,0,0,0,500,501,5,11,0,0,501,71,1,0,0,0,502,503,3,84,42,0,503,
  	504,5,34,0,0,504,505,3,56,28,0,505,73,1,0,0,0,506,507,5,65,0,0,507,509,
  	5,77,0,0,508,510,5,17,0,0,509,508,1,0,0,0,509,510,1,0,0,0,510,511,1,0,
  	0,0,511,512,5,72,0,0,512,513,3,122,61,0,513,514,3,56,28,0,514,537,1,0,
  	0,0,515,516,5,65,0,0,516,521,5,77,0,0,517,518,5,17,0,0,518,520,5,77,0,
  	0,519,517,1,0,0,0,520,523,1,0,0,0,521,519,1,0,0,0,521,522,1,0,0,0,522,
  	525,1,0,0,0,523,521,1,0,0,0,524,526,5,17,0,0,525,524,1,0,0,0,525,526,
  	1,0,0,0,526,527,1,0,0,0,527,528,5,72,0,0,528,529,3,86,43,0,529,530,3,
  	56,28,0,530,537,1,0,0,0,531,533,5,65,0,0,532,534,5,77,0,0,533,532,1,0,
  	0,0,533,534,1,0,0,0,534,535,1,0,0,0,535,537,3,56,28,0,536,506,1,0,0,0,
  	536,515,1,0,0,0,536,531,1,0,0,0,537,75,1,0,0,0,538,540,5,66,0,0,539,541,
  	5,79,0,0,540,539,1,0,0,0,540,541,1,0,0,0,541,77,1,0,0,0,542,544,5,68,
  	0,0,543,545,3,84,42,0,544,543,1,0,0,0,544,545,1,0,0,0,545,79,1,0,0,0,
  	546,547,5,59,0,0,547,548,5,77,0,0,548,552,5,10,0,0,549,551,3,82,41,0,
  	550,549,1,0,0,0,551,554,1,0,0,0,552,550,1,0,0,0,552,553,1,0,0,0,553,555,
  	1,0,0,0,554,552,1,0,0,0,555,556,5,11,0,0,556,81,1,0,0,0,557,560,5,77,
  	0,0,558,559,5,35,0,0,559,561,5,78,0,0,560,558,1,0,0,0,560,561,1,0,0,0,
  	561,83,1,0,0,0,562,563,6,42,-1,0,563,564,5,8,0,0,564,565,3,84,42,0,565,
  	568,5,9,0,0,566,567,5,14,0,0,567,569,3,124,62,0,568,566,1,0,0,0,568,569,
  	1,0,0,0,569,576,1,0,0,0,570,573,3,86,43,0,571,572,5,14,0,0,572,574,3,
  	124,62,0,573,571,1,0,0,0,573,574,1,0,0,0,574,576,1,0,0,0,575,562,1,0,
  	0,0,575,570,1,0,0,0,576,600,1,0,0,0,577,578,10,7,0,0,578,579,7,1,0,0,
  	579,599,3,84,42,8,580,581,10,6,0,0,581,582,7,2,0,0,582,599,3,84,42,7,
  	583,584,10,5,0,0,584,585,7,3,0,0,585,599,3,84,42,6,586,587,10,4,0,0,587,
  	588,7,4,0,0,588,599,3,84,42,5,589,590,10,3,0,0,590,591,7,5,0,0,591,599,
  	3,84,42,4,592,593,10,2,0,0,593,594,7,6,0,0,594,599,3,84,42,3,595,596,
  	10,1,0,0,596,597,7,7,0,0,597,599,3,84,42,2,598,577,1,0,0,0,598,580,1,
  	0,0,0,598,583,1,0,0,0,598,586,1,0,0,0,598,589,1,0,0,0,598,592,1,0,0,0,
  	598,595,1,0,0,0,599,602,1,0,0,0,600,598,1,0,0,0,600,601,1,0,0,0,601,85,
  	1,0,0,0,602,600,1,0,0,0,603,619,5,77,0,0,604,619,5,52,0,0,605,619,5,53,
  	0,0,606,619,5,76,0,0,607,619,3,88,44,0,608,619,3,90,45,0,609,619,3,98,
  	49,0,610,619,3,46,23,0,611,619,3,132,66,0,612,619,3,104,52,0,613,619,
  	3,110,55,0,614,619,3,112,56,0,615,619,3,116,58,0,616,619,3,92,46,0,617,
  	619,3,94,47,0,618,603,1,0,0,0,618,604,1,0,0,0,618,605,1,0,0,0,618,606,
  	1,0,0,0,618,607,1,0,0,0,618,608,1,0,0,0,618,609,1,0,0,0,618,610,1,0,0,
  	0,618,611,1,0,0,0,618,612,1,0,0,0,618,613,1,0,0,0,618,614,1,0,0,0,618,
  	615,1,0,0,0,618,616,1,0,0,0,618,617,1,0,0,0,619,87,1,0,0,0,620,621,7,
  	8,0,0,621,622,3,84,42,0,622,89,1,0,0,0,623,629,5,77,0,0,624,629,3,112,
  	56,0,625,629,3,116,58,0,626,629,3,98,49,0,627,629,3,110,55,0,628,623,
  	1,0,0,0,628,624,1,0,0,0,628,625,1,0,0,0,628,626,1,0,0,0,628,627,1,0,0,
  	0,629,630,1,0,0,0,630,631,7,9,0,0,631,91,1,0,0,0,632,644,5,12,0,0,633,
  	638,3,84,42,0,634,635,5,17,0,0,635,637,3,84,42,0,636,634,1,0,0,0,637,
  	640,1,0,0,0,638,636,1,0,0,0,638,639,1,0,0,0,639,642,1,0,0,0,640,638,1,
  	0,0,0,641,643,5,17,0,0,642,641,1,0,0,0,642,643,1,0,0,0,643,645,1,0,0,
  	0,644,633,1,0,0,0,644,645,1,0,0,0,645,646,1,0,0,0,646,648,5,13,0,0,647,
  	649,5,42,0,0,648,647,1,0,0,0,648,649,1,0,0,0,649,93,1,0,0,0,650,662,5,
  	10,0,0,651,656,3,96,48,0,652,653,5,17,0,0,653,655,3,96,48,0,654,652,1,
  	0,0,0,655,658,1,0,0,0,656,654,1,0,0,0,656,657,1,0,0,0,657,660,1,0,0,0,
  	658,656,1,0,0,0,659,661,5,17,0,0,660,659,1,0,0,0,660,661,1,0,0,0,661,
  	663,1,0,0,0,662,651,1,0,0,0,662,663,1,0,0,0,663,664,1,0,0,0,664,665,5,
  	11,0,0,665,95,1,0,0,0,666,667,3,84,42,0,667,668,5,34,0,0,668,669,3,84,
  	42,0,669,97,1,0,0,0,670,671,5,77,0,0,671,673,5,8,0,0,672,674,3,100,50,
  	0,673,672,1,0,0,0,673,674,1,0,0,0,674,676,1,0,0,0,675,677,5,18,0,0,676,
  	675,1,0,0,0,676,677,1,0,0,0,677,679,1,0,0,0,678,680,5,17,0,0,679,678,
  	1,0,0,0,679,680,1,0,0,0,680,681,1,0,0,0,681,682,5,9,0,0,682,99,1,0,0,
  	0,683,688,3,102,51,0,684,685,5,17,0,0,685,687,3,102,51,0,686,684,1,0,
  	0,0,687,690,1,0,0,0,688,686,1,0,0,0,688,689,1,0,0,0,689,101,1,0,0,0,690,
  	688,1,0,0,0,691,692,5,77,0,0,692,694,5,35,0,0,693,691,1,0,0,0,693,694,
  	1,0,0,0,694,695,1,0,0,0,695,696,3,84,42,0,696,103,1,0,0,0,697,698,5,77,
  	0,0,698,700,5,10,0,0,699,701,3,106,53,0,700,699,1,0,0,0,700,701,1,0,0,
  	0,701,702,1,0,0,0,702,703,5,11,0,0,703,105,1,0,0,0,704,709,3,108,54,0,
  	705,706,5,17,0,0,706,708,3,108,54,0,707,705,1,0,0,0,708,711,1,0,0,0,709,
  	707,1,0,0,0,709,710,1,0,0,0,710,713,1,0,0,0,711,709,1,0,0,0,712,714,5,
  	17,0,0,713,712,1,0,0,0,713,714,1,0,0,0,714,107,1,0,0,0,715,716,5,77,0,
  	0,716,717,5,35,0,0,717,718,3,84,42,0,718,109,1,0,0,0,719,720,7,10,0,0,
  	720,111,1,0,0,0,721,724,3,98,49,0,722,724,5,77,0,0,723,721,1,0,0,0,723,
  	722,1,0,0,0,724,726,1,0,0,0,725,727,3,114,57,0,726,725,1,0,0,0,727,728,
  	1,0,0,0,728,726,1,0,0,0,728,729,1,0,0,0,729,113,1,0,0,0,730,731,5,12,
  	0,0,731,733,3,84,42,0,732,734,5,34,0,0,733,732,1,0,0,0,733,734,1,0,0,
  	0,734,735,1,0,0,0,735,736,5,13,0,0,736,749,1,0,0,0,737,738,5,12,0,0,738,
  	739,5,34,0,0,739,740,3,84,42,0,740,741,5,13,0,0,741,749,1,0,0,0,742,743,
  	5,12,0,0,743,744,3,84,42,0,744,745,5,34,0,0,745,746,3,84,42,0,746,747,
  	5,13,0,0,747,749,1,0,0,0,748,730,1,0,0,0,748,737,1,0,0,0,748,742,1,0,
  	0,0,749,115,1,0,0,0,750,752,3,118,59,0,751,753,5,41,0,0,752,751,1,0,0,
  	0,752,753,1,0,0,0,753,759,1,0,0,0,754,755,5,33,0,0,755,757,3,120,60,0,
  	756,758,5,41,0,0,757,756,1,0,0,0,757,758,1,0,0,0,758,760,1,0,0,0,759,
  	754,1,0,0,0,760,761,1,0,0,0,761,759,1,0,0,0,761,762,1,0,0,0,762,117,1,
  	0,0,0,763,771,5,77,0,0,764,771,5,78,0,0,765,771,5,53,0,0,766,771,5,52,
  	0,0,767,771,3,98,49,0,768,771,3,104,52,0,769,771,3,112,56,0,770,763,1,
  	0,0,0,770,764,1,0,0,0,770,765,1,0,0,0,770,766,1,0,0,0,770,767,1,0,0,0,
  	770,768,1,0,0,0,770,769,1,0,0,0,771,119,1,0,0,0,772,776,5,77,0,0,773,
  	776,3,98,49,0,774,776,3,112,56,0,775,772,1,0,0,0,775,773,1,0,0,0,775,
  	774,1,0,0,0,776,121,1,0,0,0,777,778,3,84,42,0,778,779,5,19,0,0,779,780,
  	3,84,42,0,780,787,1,0,0,0,781,782,5,19,0,0,782,787,3,84,42,0,783,784,
  	3,84,42,0,784,785,5,19,0,0,785,787,1,0,0,0,786,777,1,0,0,0,786,781,1,
  	0,0,0,786,783,1,0,0,0,787,123,1,0,0,0,788,789,6,62,-1,0,789,791,5,77,
  	0,0,790,792,5,41,0,0,791,790,1,0,0,0,791,792,1,0,0,0,792,797,1,0,0,0,
  	793,797,5,53,0,0,794,797,3,126,63,0,795,797,3,130,65,0,796,788,1,0,0,
  	0,796,793,1,0,0,0,796,794,1,0,0,0,796,795,1,0,0,0,797,809,1,0,0,0,798,
  	800,10,3,0,0,799,801,3,128,64,0,800,799,1,0,0,0,801,802,1,0,0,0,802,800,
  	1,0,0,0,802,803,1,0,0,0,803,805,1,0,0,0,804,806,5,42,0,0,805,804,1,0,
  	0,0,805,806,1,0,0,0,806,808,1,0,0,0,807,798,1,0,0,0,808,811,1,0,0,0,809,
  	807,1,0,0,0,809,810,1,0,0,0,810,125,1,0,0,0,811,809,1,0,0,0,812,813,5,
  	10,0,0,813,814,3,124,62,0,814,815,5,34,0,0,815,816,3,124,62,0,816,817,
  	5,11,0,0,817,127,1,0,0,0,818,820,5,12,0,0,819,821,3,84,42,0,820,819,1,
  	0,0,0,820,821,1,0,0,0,821,822,1,0,0,0,822,823,5,13,0,0,823,129,1,0,0,
  	0,824,836,5,8,0,0,825,830,3,124,62,0,826,827,5,17,0,0,827,829,3,124,62,
  	0,828,826,1,0,0,0,829,832,1,0,0,0,830,828,1,0,0,0,830,831,1,0,0,0,831,
  	834,1,0,0,0,832,830,1,0,0,0,833,835,5,17,0,0,834,833,1,0,0,0,834,835,
  	1,0,0,0,835,837,1,0,0,0,836,825,1,0,0,0,836,837,1,0,0,0,837,838,1,0,0,
  	0,838,839,5,9,0,0,839,840,5,34,0,0,840,841,3,124,62,0,841,131,1,0,0,0,
  	842,843,7,11,0,0,843,855,5,8,0,0,844,849,3,84,42,0,845,846,5,17,0,0,846,
  	848,3,84,42,0,847,845,1,0,0,0,848,851,1,0,0,0,849,847,1,0,0,0,849,850,
  	1,0,0,0,850,853,1,0,0,0,851,849,1,0,0,0,852,854,5,17,0,0,853,852,1,0,
  	0,0,853,854,1,0,0,0,854,856,1,0,0,0,855,844,1,0,0,0,855,856,1,0,0,0,856,
  	857,1,0,0,0,857,858,5,9,0,0,858,133,1,0,0,0,859,860,5,2,0,0,860,861,5,
  	3,0,0,861,867,5,10,0,0,862,863,5,77,0,0,863,864,5,34,0,0,864,866,3,124,
  	62,0,865,862,1,0,0,0,866,869,1,0,0,0,867,865,1,0,0,0,867,868,1,0,0,0,
  	868,870,1,0,0,0,869,867,1,0,0,0,870,871,5,11,0,0,871,135,1,0,0,0,872,
  	873,7,12,0,0,873,137,1,0,0,0,113,139,144,152,159,161,168,170,174,182,
  	184,190,223,227,234,238,243,249,255,265,270,276,280,283,290,293,297,303,
  	316,319,328,332,334,339,348,352,354,358,362,373,377,379,384,390,401,405,
  	409,423,429,437,443,450,453,457,465,471,475,486,492,498,509,521,525,533,
  	536,540,544,552,560,568,573,575,598,600,618,628,638,642,644,648,656,660,
  	662,673,676,679,688,693,700,709,713,723,728,733,748,752,757,761,770,775,
  	786,791,796,802,805,809,820,830,834,836,849,853,855,867
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

LogosParser::InterfaceDeclarationContext* LogosParser::InterfaceFileContext::interfaceDeclaration() {
  return getRuleContext<LogosParser::InterfaceDeclarationContext>(0);
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
    interfaceDeclaration();
    setState(199);
    interfaceBody();
    setState(200);
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
    setState(202);
    match(LogosParser::INTERFACE);
    setState(203);
    match(LogosParser::IDENTIFIER);
    setState(204);
    match(LogosParser::LBRACE);
    setState(205);
    interfaceBody();
    setState(206);
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
    setState(208);
    match(LogosParser::IDENTIFIER);
    setState(209);
    match(LogosParser::EQUAL);
    setState(210);
    match(LogosParser::LBRACE);
    setState(211);
    groupTypesList();
    setState(212);
    match(LogosParser::RBRACE);
    setState(213);
    match(LogosParser::ARROW);
    setState(214);
    match(LogosParser::LBRACE);
    setState(215);
    groupTargetList();
    setState(216);
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
    setState(218);
    type(0);
    setState(223);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(219);
        match(LogosParser::COMMA);
        setState(220);
        type(0); 
      }
      setState(225);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
    setState(227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(226);
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
    setState(229);
    match(LogosParser::IDENTIFIER);
    setState(234);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(230);
        match(LogosParser::COMMA);
        setState(231);
        match(LogosParser::IDENTIFIER); 
      }
      setState(236);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
    setState(238);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(237);
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
    setState(243);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(240);
        interfaceField(); 
      }
      setState(245);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    }
    setState(249);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(246);
        interfaceFuncSignature(); 
      }
      setState(251);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
    setState(255);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(252);
      funcImpl();
      setState(257);
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
    setState(258);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(259);
    match(LogosParser::IDENTIFIER);
    setState(260);
    match(LogosParser::LBRACE);
    setState(261);
    objectBody();
    setState(262);
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

LogosParser::ObjectImplementsContext* LogosParser::ObjectBodyContext::objectImplements() {
  return getRuleContext<LogosParser::ObjectImplementsContext>(0);
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
    setState(265);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(264);
      objectImplements();
    }
    setState(270);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(267);
        field(); 
      }
      setState(272);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
    setState(276);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VISIBILITY

    || _la == LogosParser::IDENTIFIER) {
      setState(273);
      methodImplementation();
      setState(278);
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
    setState(280);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(279);
      match(LogosParser::VISIBILITY);
    }
    setState(283);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(282);
      match(LogosParser::CONST);
    }
    setState(285);
    match(LogosParser::IDENTIFIER);
    setState(286);
    match(LogosParser::COLON);
    setState(287);
    type(0);
    setState(290);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(288);
      match(LogosParser::EQUAL);
      setState(289);
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
    setState(293);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(292);
      match(LogosParser::CONST);
    }
    setState(295);
    match(LogosParser::IDENTIFIER);
    setState(297);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(296);
      match(LogosParser::QUEST_MARK);
    }
    setState(299);
    match(LogosParser::COLON);
    setState(300);
    type(0);
    setState(303);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(301);
      match(LogosParser::EQUAL);
      setState(302);
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
    setState(305);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(306);
    match(LogosParser::IDENTIFIER);
   
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

tree::TerminalNode* LogosParser::InterfaceDeclarationContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}


size_t LogosParser::InterfaceDeclarationContext::getRuleIndex() const {
  return LogosParser::RuleInterfaceDeclaration;
}


LogosParser::InterfaceDeclarationContext* LogosParser::interfaceDeclaration() {
  InterfaceDeclarationContext *_localctx = _tracker.createInstance<InterfaceDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 34, LogosParser::RuleInterfaceDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(308);
    match(LogosParser::INTERFACE);
    setState(309);
    match(LogosParser::IDENTIFIER);
   
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

std::vector<tree::TerminalNode *> LogosParser::ObjectImplementsContext::IDENTIFIER() {
  return getTokens(LogosParser::IDENTIFIER);
}

tree::TerminalNode* LogosParser::ObjectImplementsContext::IDENTIFIER(size_t i) {
  return getToken(LogosParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> LogosParser::ObjectImplementsContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ObjectImplementsContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ObjectImplementsContext::getRuleIndex() const {
  return LogosParser::RuleObjectImplements;
}


LogosParser::ObjectImplementsContext* LogosParser::objectImplements() {
  ObjectImplementsContext *_localctx = _tracker.createInstance<ObjectImplementsContext>(_ctx, getState());
  enterRule(_localctx, 36, LogosParser::RuleObjectImplements);
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
    setState(311);
    match(LogosParser::IMPLEMENTS);
    setState(312);
    match(LogosParser::COLON);
    setState(313);
    match(LogosParser::IDENTIFIER);
    setState(316);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      setState(314);
      match(LogosParser::COMMA);
      setState(315);
      match(LogosParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    setState(319);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(318);
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

//----------------- FuncSignatureContext ------------------------------------------------------------------

LogosParser::FuncSignatureContext::FuncSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::FuncSignatureContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::FuncSignatureContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::FuncSignatureContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

std::vector<LogosParser::ParamContext *> LogosParser::FuncSignatureContext::param() {
  return getRuleContexts<LogosParser::ParamContext>();
}

LogosParser::ParamContext* LogosParser::FuncSignatureContext::param(size_t i) {
  return getRuleContext<LogosParser::ParamContext>(i);
}

tree::TerminalNode* LogosParser::FuncSignatureContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::TypeContext* LogosParser::FuncSignatureContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> LogosParser::FuncSignatureContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::FuncSignatureContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
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
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(321);
    match(LogosParser::IDENTIFIER);
    setState(322);
    match(LogosParser::LPAREN);
    setState(334);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(323);
      param();
      setState(328);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(324);
          match(LogosParser::COMMA);
          setState(325);
          param(); 
        }
        setState(330);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
      }
      setState(332);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(331);
        match(LogosParser::COMMA);
      }
    }
    setState(336);
    match(LogosParser::RPAREN);
    setState(339);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(337);
      match(LogosParser::COLON);
      setState(338);
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

tree::TerminalNode* LogosParser::InterfaceFuncSignatureContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::InterfaceFuncSignatureContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::InterfaceFuncSignatureContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

std::vector<LogosParser::ParamContext *> LogosParser::InterfaceFuncSignatureContext::param() {
  return getRuleContexts<LogosParser::ParamContext>();
}

LogosParser::ParamContext* LogosParser::InterfaceFuncSignatureContext::param(size_t i) {
  return getRuleContext<LogosParser::ParamContext>(i);
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

std::vector<tree::TerminalNode *> LogosParser::InterfaceFuncSignatureContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::InterfaceFuncSignatureContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
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
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(341);
    match(LogosParser::IDENTIFIER);
    setState(342);
    match(LogosParser::LPAREN);
    setState(354);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(343);
      param();
      setState(348);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(344);
          match(LogosParser::COMMA);
          setState(345);
          param(); 
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
    setState(356);
    match(LogosParser::RPAREN);
    setState(358);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(357);
      match(LogosParser::QUEST_MARK);
    }
    setState(362);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(360);
      match(LogosParser::COLON);
      setState(361);
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
    setState(364);
    funcSignature();
    setState(365);
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
    setState(367);
    match(LogosParser::LPAREN);
    setState(379);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(368);
      param();
      setState(373);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(369);
          match(LogosParser::COMMA);
          setState(370);
          param(); 
        }
        setState(375);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
      }
      setState(377);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(376);
        match(LogosParser::COMMA);
      }
    }
    setState(381);
    match(LogosParser::RPAREN);
    setState(384);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(382);
      match(LogosParser::COLON);
      setState(383);
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
    setState(386);
    anonnymosfuncSignature();
    setState(387);
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
    setState(390);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(389);
      match(LogosParser::VISIBILITY);
    }
    setState(392);
    funcSignature();
    setState(393);
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
    setState(395);
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
    setState(409);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(397);
      match(LogosParser::IDENTIFIER);
      setState(398);
      match(LogosParser::COLON);
      setState(399);
      type(0);
      setState(401);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::TRIPLE_DOT) {
        setState(400);
        match(LogosParser::TRIPLE_DOT);
      }
      setState(405);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::EQUAL) {
        setState(403);
        match(LogosParser::EQUAL);
        setState(404);
        expr(0);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(407);
      match(LogosParser::IDENTIFIER);
      setState(408);
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
    setState(423);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(411);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(412);
      explicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(413);
      implicitVarDec();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(414);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(415);
      patternMatching();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(416);
      loopStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(417);
      match(LogosParser::CONTINUE);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(418);
      breakStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(419);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(420);
      funcCall();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(421);
      selection();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(422);
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
    setState(425);
    match(LogosParser::LBRACE);
    setState(429);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 52) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 52)) & 115468355) != 0)) {
      setState(426);
      statement();
      setState(431);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(432);
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
    setState(437);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      setState(434);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(435);
      iterIndex();
      break;
    }

    case 3: {
      setState(436);
      selection();
      break;
    }

    default:
      break;
    }
    setState(439);
    assignemntOp();
    setState(440);
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
    setState(443);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(442);
      match(LogosParser::CONST);
    }
    setState(445);
    match(LogosParser::IDENTIFIER);
    setState(446);
    match(LogosParser::COLON);
    setState(447);
    type(0);
    setState(450);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(448);
      match(LogosParser::EQUAL);
      setState(449);
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
    setState(453);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(452);
      match(LogosParser::CONST);
    }
    setState(455);
    match(LogosParser::IDENTIFIER);
    setState(457);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(456);
      match(LogosParser::QUEST_MARK);
    }
    setState(459);
    match(LogosParser::EQUAL);
    setState(460);
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
    setState(462);
    match(LogosParser::IF);
    setState(463);
    expr(0);
    setState(465);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TAG) {
      setState(464);
      match(LogosParser::TAG);
    }
    setState(467);
    statementsBlock();
    setState(471);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(468);
        elseIfStatement(); 
      }
      setState(473);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    }
    setState(475);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(474);
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
    setState(477);
    match(LogosParser::ELSE);
    setState(478);
    expr(0);
    setState(479);
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
    setState(481);
    match(LogosParser::ELSE);
    setState(482);
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
    setState(484);
    match(LogosParser::IF);
    setState(486);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      setState(485);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(488);
    match(LogosParser::LBRACE);
    setState(492);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(489);
      pattern();
      setState(494);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(498);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(495);
      match(LogosParser::ELSE);
      setState(496);
      match(LogosParser::COLON);
      setState(497);
      statementsBlock();
    }
    setState(500);
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
    setState(502);
    expr(0);
    setState(503);
    match(LogosParser::COLON);
    setState(504);
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
    setState(536);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(506);
      match(LogosParser::FOR);
      setState(507);
      match(LogosParser::IDENTIFIER);
      setState(509);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(508);
        match(LogosParser::COMMA);
      }
      setState(511);
      match(LogosParser::IN);
      setState(512);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(513);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(515);
      match(LogosParser::FOR);
      setState(516);
      match(LogosParser::IDENTIFIER);
      setState(521);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(517);
          match(LogosParser::COMMA);
          setState(518);
          match(LogosParser::IDENTIFIER); 
        }
        setState(523);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx);
      }
      setState(525);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(524);
        match(LogosParser::COMMA);
      }
      setState(527);
      match(LogosParser::IN);
      setState(528);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = unaryExpr();
      setState(529);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(531);
      match(LogosParser::FOR);
      setState(533);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::IDENTIFIER) {
        setState(532);
        match(LogosParser::IDENTIFIER);
      }
      setState(535);
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
    setState(538);
    match(LogosParser::BREAK);
    setState(540);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TAG) {
      setState(539);
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
    setState(542);
    match(LogosParser::RETURN);
    setState(544);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
    case 1: {
      setState(543);
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
    setState(546);
    match(LogosParser::ENUM);
    setState(547);
    match(LogosParser::IDENTIFIER);
    setState(548);
    match(LogosParser::LBRACE);
    setState(552);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(549);
      enumField();
      setState(554);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(555);
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
    setState(557);
    match(LogosParser::IDENTIFIER);
    setState(560);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(558);
      match(LogosParser::EQUAL);
      setState(559);
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
    setState(575);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
    case 1: {
      setState(563);
      match(LogosParser::LPAREN);
      setState(564);
      antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
      setState(565);
      match(LogosParser::RPAREN);
      setState(568);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
      case 1: {
        setState(566);
        match(LogosParser::ARROW);
        setState(567);
        type(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      setState(570);
      unaryExpr();
      setState(573);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
      case 1: {
        setState(571);
        match(LogosParser::ARROW);
        setState(572);
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
    setState(600);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(598);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(577);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(578);
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
          setState(579);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(580);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(581);
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
          setState(582);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(583);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(584);
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
          setState(585);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(586);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(587);
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
          setState(588);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(589);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(590);
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
          setState(591);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(592);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(593);
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
          setState(594);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(595);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(596);
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
          setState(597);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(602);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx);
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
    setState(618);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(603);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(604);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(605);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(606);
      match(LogosParser::NULL_);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(607);
      prefixExpr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(608);
      postfixExpr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(609);
      funcCall();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(610);
      anonnymosFunc();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(611);
      vector();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(612);
      constructor();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(613);
      constant();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(614);
      iterIndex();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(615);
      selection();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(616);
      arrayExpr();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(617);
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
    setState(620);
    _la = _input->LA(1);
    if (!(_la == LogosParser::MINUS

    || _la == LogosParser::NOT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(621);
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
    setState(628);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      setState(623);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(624);
      iterIndex();
      break;
    }

    case 3: {
      setState(625);
      selection();
      break;
    }

    case 4: {
      setState(626);
      funcCall();
      break;
    }

    case 5: {
      setState(627);
      constant();
      break;
    }

    default:
      break;
    }
    setState(630);
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
    setState(632);
    match(LogosParser::LBRACK);
    setState(644);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(633);
      expr(0);
      setState(638);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(634);
          match(LogosParser::COMMA);
          setState(635);
          expr(0); 
        }
        setState(640);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx);
      }
      setState(642);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(641);
        match(LogosParser::COMMA);
      }
    }
    setState(646);
    match(LogosParser::RBRACK);
    setState(648);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      setState(647);
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
    setState(650);
    match(LogosParser::LBRACE);
    setState(662);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(651);
      keyValue();
      setState(656);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(652);
          match(LogosParser::COMMA);
          setState(653);
          keyValue(); 
        }
        setState(658);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
      }
      setState(660);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(659);
        match(LogosParser::COMMA);
      }
    }
    setState(664);
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
    setState(666);
    antlrcpp::downCast<KeyValueContext *>(_localctx)->key = expr(0);
    setState(667);
    match(LogosParser::COLON);
    setState(668);
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
    setState(670);
    match(LogosParser::IDENTIFIER);
    setState(671);
    match(LogosParser::LPAREN);
    setState(673);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(672);
      funcArgList();
    }
    setState(676);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TRIPLE_DOT) {
      setState(675);
      match(LogosParser::TRIPLE_DOT);
    }
    setState(679);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(678);
      match(LogosParser::COMMA);
    }
    setState(681);
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
    setState(683);
    funcArg();
    setState(688);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(684);
        match(LogosParser::COMMA);
        setState(685);
        funcArg(); 
      }
      setState(690);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx);
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
    setState(693);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx)) {
    case 1: {
      setState(691);
      match(LogosParser::IDENTIFIER);
      setState(692);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(695);
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
    setState(697);
    match(LogosParser::IDENTIFIER);
    setState(698);
    match(LogosParser::LBRACE);
    setState(700);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(699);
      constructorArgList();
    }
    setState(702);
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
    setState(704);
    constructorArg();
    setState(709);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(705);
        match(LogosParser::COMMA);
        setState(706);
        constructorArg(); 
      }
      setState(711);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx);
    }
    setState(713);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(712);
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
    setState(715);
    match(LogosParser::IDENTIFIER);
    setState(716);
    match(LogosParser::EQUAL);
    setState(717);
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
    setState(719);
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
    setState(723);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 90, _ctx)) {
    case 1: {
      setState(721);
      funcCall();
      break;
    }

    case 2: {
      setState(722);
      match(LogosParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    setState(726); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(725);
              index();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(728); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx);
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
    setState(748);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(730);
      match(LogosParser::LBRACK);
      setState(731);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(733);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COLON) {
        setState(732);
        match(LogosParser::COLON);
      }
      setState(735);
      match(LogosParser::RBRACK);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(737);
      match(LogosParser::LBRACK);
      setState(738);
      match(LogosParser::COLON);
      setState(739);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(740);
      match(LogosParser::RBRACK);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(742);
      match(LogosParser::LBRACK);
      setState(743);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(744);
      match(LogosParser::COLON);
      setState(745);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(746);
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
    setState(750);
    firstSelectionElement();
    setState(752);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(751);
      match(LogosParser::QUEST_MARK);
    }
    setState(759); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(754);
              match(LogosParser::DOT);
              setState(755);
              innerSelectionElement();
              setState(757);
              _errHandler->sync(this);

              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 95, _ctx)) {
              case 1: {
                setState(756);
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
      setState(761); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx);
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
    setState(770);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(763);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(764);
      match(LogosParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(765);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(766);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(767);
      funcCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(768);
      constructor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(769);
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
    setState(775);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(772);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(773);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(774);
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
    setState(786);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 99, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(777);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(778);
      match(LogosParser::DOUBLE_DOT);
      setState(779);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(781);
      match(LogosParser::DOUBLE_DOT);
      setState(782);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(783);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(784);
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
    setState(796);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::IDENTIFIER: {
        setState(789);
        match(LogosParser::IDENTIFIER);
        setState(791);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx)) {
        case 1: {
          setState(790);
          match(LogosParser::QUEST_MARK);
          break;
        }

        default:
          break;
        }
        break;
      }

      case LogosParser::SELF_CLASS: {
        setState(793);
        match(LogosParser::SELF_CLASS);
        break;
      }

      case LogosParser::LBRACE: {
        setState(794);
        mapType();
        break;
      }

      case LogosParser::LPAREN: {
        setState(795);
        funcType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(809);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        _localctx->baseType = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(798);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(800); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(799);
                  arraySize();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(802); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        setState(805);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 103, _ctx)) {
        case 1: {
          setState(804);
          match(LogosParser::EXCLA_MARK);
          break;
        }

        default:
          break;
        } 
      }
      setState(811);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx);
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
    setState(812);
    match(LogosParser::LBRACE);
    setState(813);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->key = type(0);
    setState(814);
    match(LogosParser::COLON);
    setState(815);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->value = type(0);
    setState(816);
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
    setState(818);
    match(LogosParser::LBRACK);
    setState(820);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(819);
      expr(0);
    }
    setState(822);
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
    setState(824);
    match(LogosParser::LPAREN);
    setState(836);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 9007199254742272) != 0) || _la == LogosParser::IDENTIFIER) {
      setState(825);
      type(0);
      setState(830);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 106, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(826);
          match(LogosParser::COMMA);
          setState(827);
          type(0); 
        }
        setState(832);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 106, _ctx);
      }
      setState(834);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(833);
        match(LogosParser::COMMA);
      }
    }
    setState(838);
    match(LogosParser::RPAREN);
    setState(839);
    match(LogosParser::COLON);
    setState(840);
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
    setState(842);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8070450532247928832) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(843);
    match(LogosParser::LPAREN);
    setState(855);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(844);
      expr(0);
      setState(849);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 109, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(845);
          match(LogosParser::COMMA);
          setState(846);
          expr(0); 
        }
        setState(851);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 109, _ctx);
      }
      setState(853);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(852);
        match(LogosParser::COMMA);
      }
    }
    setState(857);
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
    setState(859);
    match(LogosParser::T__1);
    setState(860);
    match(LogosParser::T__2);
    setState(861);
    match(LogosParser::LBRACE);
    setState(867);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(862);
      match(LogosParser::IDENTIFIER);
      setState(863);
      match(LogosParser::COLON);
      setState(864);
      type(0);
      setState(869);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(870);
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
    setState(872);
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
