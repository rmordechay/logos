
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
      "interfaceField", "implements", "funcSignatureHeader", "funcSignature", 
      "interfaceFuncSignature", "funcImpl", "anonymosFuncSignature", "anonnymosFunc", 
      "methodImplementation", "param", "anonymousParam", "statement", "statementsBlock", 
      "assignment", "explicitVarDec", "implicitVarDec", "ifStatement", "elseIfStatement", 
      "elseStatement", "patternMatching", "pattern", "loopStatement", "breakStmt", 
      "returnStatement", "enumDeclaration", "enumField", "coroutine", "expr", 
      "unaryExpr", "prefixExpr", "postfixExpr", "arrayExpr", "hashMap", 
      "keyValue", "funcCall", "funcArgList", "funcArg", "constructor", "constructorArgList", 
      "constructorArg", "constant", "iterIndex", "index", "selection", "firstSelectionElement", 
      "innerSelectionElement", "range", "type", "mapType", "arraySize", 
      "funcType", "vector", "requireEnvVars", "assignemntOp"
    },
    std::vector<std::string>{
      "", "'C'", "'require'", "'envs'", "'=='", "'!='", "'>='", "'<='", 
      "'('", "')'", "'{'", "'}'", "'['", "']'", "'->'", "'<'", "'>'", "','", 
      "'...'", "'..'", "':='", "'+='", "'-='", "'*='", "'/='", "'%='", "'&='", 
      "'|='", "'^='", "'<<='", "'>>='", "'++'", "'--'", "'.'", "':'", "'='", 
      "'+'", "'-'", "'*'", "'/'", "'#'", "'\\u003F'", "'!'", "'%'", "'$'", 
      "'&'", "'|'", "'^'", "'<<'", "'>>'", "'object'", "'single'", "'self'", 
      "'Self'", "'interface'", "'extern'", "'pub'", "'implements'", "'const'", 
      "'enum'", "'go'", "'vec2'", "'vec3'", "'vec4'", "'if'", "'else'", 
      "'for'", "'break'", "'continue'", "'return'", "'and'", "'or'", "'not'", 
      "'in'", "", "", "", "'null'"
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
      "IMPLEMENTS", "CONST", "ENUM", "GO", "VEC2", "VEC3", "VEC4", "IF", 
      "ELSE", "FOR", "BREAK", "CONTINUE", "RETURN", "AND", "OR", "NOT", 
      "IN", "INTEGER", "FLOAT", "BOOL", "NULL", "IDENTIFIER", "STRING", 
      "TAG", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,83,870,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
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
  	5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,5,9,224,8,9,10,9,12,9,227,9,9,1,9,
  	3,9,230,8,9,1,10,1,10,1,10,5,10,235,8,10,10,10,12,10,238,9,10,1,10,3,
  	10,241,8,10,1,11,3,11,244,8,11,1,11,5,11,247,8,11,10,11,12,11,250,9,11,
  	1,11,5,11,253,8,11,10,11,12,11,256,9,11,1,11,5,11,259,8,11,10,11,12,11,
  	262,9,11,1,12,1,12,1,12,1,12,1,12,1,12,1,13,3,13,271,8,13,1,13,5,13,274,
  	8,13,10,13,12,13,277,9,13,1,13,5,13,280,8,13,10,13,12,13,283,9,13,1,14,
  	3,14,286,8,14,1,14,3,14,289,8,14,1,14,1,14,1,14,1,14,1,14,3,14,296,8,
  	14,1,15,3,15,299,8,15,1,15,1,15,3,15,303,8,15,1,15,1,15,1,15,1,15,3,15,
  	309,8,15,1,16,1,16,1,16,1,16,1,16,3,16,316,8,16,1,16,3,16,319,8,16,1,
  	17,1,17,1,17,1,17,1,17,5,17,326,8,17,10,17,12,17,329,9,17,1,17,3,17,332,
  	8,17,3,17,334,8,17,1,17,1,17,1,18,1,18,1,18,3,18,341,8,18,1,19,1,19,3,
  	19,345,8,19,1,19,1,19,3,19,349,8,19,1,20,1,20,1,20,1,21,1,21,1,21,1,21,
  	5,21,358,8,21,10,21,12,21,361,9,21,1,21,3,21,364,8,21,3,21,366,8,21,1,
  	21,1,21,1,21,3,21,371,8,21,1,22,1,22,1,22,1,23,3,23,377,8,23,1,23,1,23,
  	1,23,1,24,1,24,1,24,1,24,1,24,3,24,387,8,24,1,24,1,24,3,24,391,8,24,3,
  	24,393,8,24,1,25,1,25,1,25,3,25,398,8,25,1,26,1,26,1,26,1,26,1,26,1,26,
  	1,26,1,26,1,26,1,26,1,26,1,26,1,26,3,26,413,8,26,1,27,1,27,5,27,417,8,
  	27,10,27,12,27,420,9,27,1,27,1,27,1,28,1,28,1,28,3,28,427,8,28,1,28,1,
  	28,1,28,1,29,3,29,433,8,29,1,29,1,29,1,29,1,29,1,29,3,29,440,8,29,1,30,
  	3,30,443,8,30,1,30,1,30,3,30,447,8,30,1,30,1,30,1,30,1,31,1,31,1,31,3,
  	31,455,8,31,1,31,1,31,5,31,459,8,31,10,31,12,31,462,9,31,1,31,3,31,465,
  	8,31,1,32,1,32,1,32,1,32,1,33,1,33,1,33,1,34,1,34,3,34,476,8,34,1,34,
  	1,34,5,34,480,8,34,10,34,12,34,483,9,34,1,34,1,34,1,34,3,34,488,8,34,
  	1,34,1,34,1,35,1,35,1,35,1,35,1,36,1,36,1,36,3,36,499,8,36,1,36,1,36,
  	1,36,1,36,1,36,1,36,1,36,1,36,5,36,509,8,36,10,36,12,36,512,9,36,1,36,
  	3,36,515,8,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,523,8,36,1,36,3,36,526,
  	8,36,1,37,1,37,3,37,530,8,37,1,38,1,38,3,38,534,8,38,1,39,1,39,1,39,1,
  	39,5,39,540,8,39,10,39,12,39,543,9,39,1,39,1,39,1,40,1,40,1,40,3,40,550,
  	8,40,1,41,1,41,1,41,1,41,3,41,556,8,41,1,42,1,42,1,42,1,42,1,42,1,42,
  	3,42,564,8,42,1,42,1,42,1,42,3,42,569,8,42,3,42,571,8,42,1,42,1,42,1,
  	42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,
  	42,1,42,1,42,1,42,1,42,5,42,594,8,42,10,42,12,42,597,9,42,1,43,1,43,1,
  	43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,3,43,614,
  	8,43,1,44,1,44,1,44,1,45,1,45,1,45,1,45,1,45,3,45,624,8,45,1,45,1,45,
  	1,46,1,46,1,46,1,46,5,46,632,8,46,10,46,12,46,635,9,46,1,46,3,46,638,
  	8,46,3,46,640,8,46,1,46,1,46,3,46,644,8,46,1,47,1,47,1,47,1,47,5,47,650,
  	8,47,10,47,12,47,653,9,47,1,47,3,47,656,8,47,3,47,658,8,47,1,47,1,47,
  	1,48,1,48,1,48,1,48,1,49,1,49,1,49,3,49,669,8,49,1,49,3,49,672,8,49,1,
  	49,3,49,675,8,49,1,49,1,49,1,50,1,50,1,50,5,50,682,8,50,10,50,12,50,685,
  	9,50,1,51,1,51,3,51,689,8,51,1,51,1,51,1,52,1,52,1,52,3,52,696,8,52,1,
  	52,1,52,1,53,1,53,1,53,5,53,703,8,53,10,53,12,53,706,9,53,1,53,3,53,709,
  	8,53,1,54,1,54,1,54,1,54,1,55,1,55,1,56,1,56,3,56,719,8,56,1,56,4,56,
  	722,8,56,11,56,12,56,723,1,57,1,57,1,57,3,57,729,8,57,1,57,1,57,1,57,
  	1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,3,57,744,8,57,1,58,
  	1,58,3,58,748,8,58,1,58,1,58,1,58,3,58,753,8,58,4,58,755,8,58,11,58,12,
  	58,756,1,59,1,59,1,59,1,59,1,59,1,59,1,59,3,59,766,8,59,1,60,1,60,1,60,
  	3,60,771,8,60,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,3,61,782,8,
  	61,1,62,1,62,1,62,3,62,787,8,62,1,62,1,62,1,62,3,62,792,8,62,1,62,1,62,
  	4,62,796,8,62,11,62,12,62,797,1,62,3,62,801,8,62,5,62,803,8,62,10,62,
  	12,62,806,9,62,1,63,1,63,1,63,1,63,1,63,1,63,1,64,1,64,3,64,816,8,64,
  	1,64,1,64,1,65,1,65,1,65,1,65,5,65,824,8,65,10,65,12,65,827,9,65,1,65,
  	3,65,830,8,65,3,65,832,8,65,1,65,1,65,1,65,1,65,1,66,1,66,1,66,1,66,1,
  	66,5,66,843,8,66,10,66,12,66,846,9,66,1,66,3,66,849,8,66,3,66,851,8,66,
  	1,66,1,66,1,67,1,67,1,67,1,67,1,67,1,67,5,67,861,8,67,10,67,12,67,864,
  	9,67,1,67,1,67,1,68,1,68,1,68,0,2,84,124,69,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,
  	66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,
  	110,112,114,116,118,120,122,124,126,128,130,132,134,136,0,13,1,0,50,51,
  	2,0,38,39,43,43,1,0,36,37,2,0,6,7,15,16,1,0,4,5,1,0,70,71,1,0,45,47,1,
  	0,48,49,2,0,37,37,72,72,1,0,31,32,2,0,74,76,79,79,1,0,61,63,1,0,20,30,
  	961,0,139,1,0,0,0,2,146,1,0,0,0,4,161,1,0,0,0,6,170,1,0,0,0,8,184,1,0,
  	0,0,10,194,1,0,0,0,12,199,1,0,0,0,14,204,1,0,0,0,16,210,1,0,0,0,18,220,
  	1,0,0,0,20,231,1,0,0,0,22,243,1,0,0,0,24,263,1,0,0,0,26,270,1,0,0,0,28,
  	285,1,0,0,0,30,298,1,0,0,0,32,310,1,0,0,0,34,320,1,0,0,0,36,337,1,0,0,
  	0,38,342,1,0,0,0,40,350,1,0,0,0,42,353,1,0,0,0,44,372,1,0,0,0,46,376,
  	1,0,0,0,48,381,1,0,0,0,50,394,1,0,0,0,52,412,1,0,0,0,54,414,1,0,0,0,56,
  	426,1,0,0,0,58,432,1,0,0,0,60,442,1,0,0,0,62,451,1,0,0,0,64,466,1,0,0,
  	0,66,470,1,0,0,0,68,473,1,0,0,0,70,491,1,0,0,0,72,525,1,0,0,0,74,527,
  	1,0,0,0,76,531,1,0,0,0,78,535,1,0,0,0,80,546,1,0,0,0,82,551,1,0,0,0,84,
  	570,1,0,0,0,86,613,1,0,0,0,88,615,1,0,0,0,90,623,1,0,0,0,92,627,1,0,0,
  	0,94,645,1,0,0,0,96,661,1,0,0,0,98,665,1,0,0,0,100,678,1,0,0,0,102,688,
  	1,0,0,0,104,692,1,0,0,0,106,699,1,0,0,0,108,710,1,0,0,0,110,714,1,0,0,
  	0,112,718,1,0,0,0,114,743,1,0,0,0,116,745,1,0,0,0,118,765,1,0,0,0,120,
  	770,1,0,0,0,122,781,1,0,0,0,124,791,1,0,0,0,126,807,1,0,0,0,128,813,1,
  	0,0,0,130,819,1,0,0,0,132,837,1,0,0,0,134,854,1,0,0,0,136,867,1,0,0,0,
  	138,140,3,2,1,0,139,138,1,0,0,0,139,140,1,0,0,0,140,144,1,0,0,0,141,145,
  	3,8,4,0,142,145,3,10,5,0,143,145,3,12,6,0,144,141,1,0,0,0,144,142,1,0,
  	0,0,144,143,1,0,0,0,145,1,1,0,0,0,146,147,5,55,0,0,147,148,5,1,0,0,148,
  	152,5,10,0,0,149,151,5,79,0,0,150,149,1,0,0,0,151,154,1,0,0,0,152,150,
  	1,0,0,0,152,153,1,0,0,0,153,155,1,0,0,0,154,152,1,0,0,0,155,156,5,11,
  	0,0,156,3,1,0,0,0,157,160,3,60,30,0,158,160,3,58,29,0,159,157,1,0,0,0,
  	159,158,1,0,0,0,160,163,1,0,0,0,161,159,1,0,0,0,161,162,1,0,0,0,162,164,
  	1,0,0,0,163,161,1,0,0,0,164,165,5,0,0,1,165,5,1,0,0,0,166,169,3,60,30,
  	0,167,169,3,58,29,0,168,166,1,0,0,0,168,167,1,0,0,0,169,172,1,0,0,0,170,
  	168,1,0,0,0,170,171,1,0,0,0,171,174,1,0,0,0,172,170,1,0,0,0,173,175,3,
  	134,67,0,174,173,1,0,0,0,174,175,1,0,0,0,175,176,1,0,0,0,176,177,5,0,
  	0,1,177,7,1,0,0,0,178,183,3,24,12,0,179,183,3,78,39,0,180,183,3,14,7,
  	0,181,183,3,16,8,0,182,178,1,0,0,0,182,179,1,0,0,0,182,180,1,0,0,0,182,
  	181,1,0,0,0,183,186,1,0,0,0,184,182,1,0,0,0,184,185,1,0,0,0,185,188,1,
  	0,0,0,186,184,1,0,0,0,187,189,3,40,20,0,188,187,1,0,0,0,189,190,1,0,0,
  	0,190,188,1,0,0,0,190,191,1,0,0,0,191,192,1,0,0,0,192,193,5,0,0,1,193,
  	9,1,0,0,0,194,195,7,0,0,0,195,196,5,78,0,0,196,197,3,26,13,0,197,198,
  	5,0,0,1,198,11,1,0,0,0,199,200,5,54,0,0,200,201,5,78,0,0,201,202,3,22,
  	11,0,202,203,5,0,0,1,203,13,1,0,0,0,204,205,5,54,0,0,205,206,5,78,0,0,
  	206,207,5,10,0,0,207,208,3,22,11,0,208,209,5,11,0,0,209,15,1,0,0,0,210,
  	211,5,78,0,0,211,212,5,35,0,0,212,213,5,10,0,0,213,214,3,18,9,0,214,215,
  	5,11,0,0,215,216,5,14,0,0,216,217,5,10,0,0,217,218,3,20,10,0,218,219,
  	5,11,0,0,219,17,1,0,0,0,220,225,3,124,62,0,221,222,5,17,0,0,222,224,3,
  	124,62,0,223,221,1,0,0,0,224,227,1,0,0,0,225,223,1,0,0,0,225,226,1,0,
  	0,0,226,229,1,0,0,0,227,225,1,0,0,0,228,230,5,17,0,0,229,228,1,0,0,0,
  	229,230,1,0,0,0,230,19,1,0,0,0,231,236,5,78,0,0,232,233,5,17,0,0,233,
  	235,5,78,0,0,234,232,1,0,0,0,235,238,1,0,0,0,236,234,1,0,0,0,236,237,
  	1,0,0,0,237,240,1,0,0,0,238,236,1,0,0,0,239,241,5,17,0,0,240,239,1,0,
  	0,0,240,241,1,0,0,0,241,21,1,0,0,0,242,244,3,32,16,0,243,242,1,0,0,0,
  	243,244,1,0,0,0,244,248,1,0,0,0,245,247,3,30,15,0,246,245,1,0,0,0,247,
  	250,1,0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,254,1,0,0,0,250,248,1,
  	0,0,0,251,253,3,38,19,0,252,251,1,0,0,0,253,256,1,0,0,0,254,252,1,0,0,
  	0,254,255,1,0,0,0,255,260,1,0,0,0,256,254,1,0,0,0,257,259,3,40,20,0,258,
  	257,1,0,0,0,259,262,1,0,0,0,260,258,1,0,0,0,260,261,1,0,0,0,261,23,1,
  	0,0,0,262,260,1,0,0,0,263,264,7,0,0,0,264,265,5,78,0,0,265,266,5,10,0,
  	0,266,267,3,26,13,0,267,268,5,11,0,0,268,25,1,0,0,0,269,271,3,32,16,0,
  	270,269,1,0,0,0,270,271,1,0,0,0,271,275,1,0,0,0,272,274,3,28,14,0,273,
  	272,1,0,0,0,274,277,1,0,0,0,275,273,1,0,0,0,275,276,1,0,0,0,276,281,1,
  	0,0,0,277,275,1,0,0,0,278,280,3,46,23,0,279,278,1,0,0,0,280,283,1,0,0,
  	0,281,279,1,0,0,0,281,282,1,0,0,0,282,27,1,0,0,0,283,281,1,0,0,0,284,
  	286,5,56,0,0,285,284,1,0,0,0,285,286,1,0,0,0,286,288,1,0,0,0,287,289,
  	5,58,0,0,288,287,1,0,0,0,288,289,1,0,0,0,289,290,1,0,0,0,290,291,5,78,
  	0,0,291,292,5,34,0,0,292,295,3,124,62,0,293,294,5,35,0,0,294,296,3,84,
  	42,0,295,293,1,0,0,0,295,296,1,0,0,0,296,29,1,0,0,0,297,299,5,58,0,0,
  	298,297,1,0,0,0,298,299,1,0,0,0,299,300,1,0,0,0,300,302,5,78,0,0,301,
  	303,5,41,0,0,302,301,1,0,0,0,302,303,1,0,0,0,303,304,1,0,0,0,304,305,
  	5,34,0,0,305,308,3,124,62,0,306,307,5,35,0,0,307,309,3,84,42,0,308,306,
  	1,0,0,0,308,309,1,0,0,0,309,31,1,0,0,0,310,311,5,57,0,0,311,312,5,34,
  	0,0,312,315,5,78,0,0,313,314,5,17,0,0,314,316,5,78,0,0,315,313,1,0,0,
  	0,315,316,1,0,0,0,316,318,1,0,0,0,317,319,5,17,0,0,318,317,1,0,0,0,318,
  	319,1,0,0,0,319,33,1,0,0,0,320,321,5,78,0,0,321,333,5,8,0,0,322,327,3,
  	48,24,0,323,324,5,17,0,0,324,326,3,48,24,0,325,323,1,0,0,0,326,329,1,
  	0,0,0,327,325,1,0,0,0,327,328,1,0,0,0,328,331,1,0,0,0,329,327,1,0,0,0,
  	330,332,5,17,0,0,331,330,1,0,0,0,331,332,1,0,0,0,332,334,1,0,0,0,333,
  	322,1,0,0,0,333,334,1,0,0,0,334,335,1,0,0,0,335,336,5,9,0,0,336,35,1,
  	0,0,0,337,340,3,34,17,0,338,339,5,34,0,0,339,341,3,124,62,0,340,338,1,
  	0,0,0,340,341,1,0,0,0,341,37,1,0,0,0,342,344,3,34,17,0,343,345,5,41,0,
  	0,344,343,1,0,0,0,344,345,1,0,0,0,345,348,1,0,0,0,346,347,5,34,0,0,347,
  	349,3,124,62,0,348,346,1,0,0,0,348,349,1,0,0,0,349,39,1,0,0,0,350,351,
  	3,36,18,0,351,352,3,54,27,0,352,41,1,0,0,0,353,365,5,8,0,0,354,359,3,
  	50,25,0,355,356,5,17,0,0,356,358,3,50,25,0,357,355,1,0,0,0,358,361,1,
  	0,0,0,359,357,1,0,0,0,359,360,1,0,0,0,360,363,1,0,0,0,361,359,1,0,0,0,
  	362,364,5,17,0,0,363,362,1,0,0,0,363,364,1,0,0,0,364,366,1,0,0,0,365,
  	354,1,0,0,0,365,366,1,0,0,0,366,367,1,0,0,0,367,370,5,9,0,0,368,369,5,
  	34,0,0,369,371,3,124,62,0,370,368,1,0,0,0,370,371,1,0,0,0,371,43,1,0,
  	0,0,372,373,3,42,21,0,373,374,3,54,27,0,374,45,1,0,0,0,375,377,5,56,0,
  	0,376,375,1,0,0,0,376,377,1,0,0,0,377,378,1,0,0,0,378,379,3,36,18,0,379,
  	380,3,54,27,0,380,47,1,0,0,0,381,382,5,78,0,0,382,392,5,34,0,0,383,393,
  	3,130,65,0,384,386,3,124,62,0,385,387,5,18,0,0,386,385,1,0,0,0,386,387,
  	1,0,0,0,387,390,1,0,0,0,388,389,5,35,0,0,389,391,3,84,42,0,390,388,1,
  	0,0,0,390,391,1,0,0,0,391,393,1,0,0,0,392,383,1,0,0,0,392,384,1,0,0,0,
  	393,49,1,0,0,0,394,397,5,78,0,0,395,396,5,34,0,0,396,398,3,124,62,0,397,
  	395,1,0,0,0,397,398,1,0,0,0,398,51,1,0,0,0,399,413,3,56,28,0,400,413,
  	3,58,29,0,401,413,3,60,30,0,402,413,3,62,31,0,403,413,3,68,34,0,404,413,
  	3,72,36,0,405,413,5,68,0,0,406,413,3,74,37,0,407,413,3,76,38,0,408,413,
  	3,98,49,0,409,413,3,116,58,0,410,413,3,82,41,0,411,413,3,90,45,0,412,
  	399,1,0,0,0,412,400,1,0,0,0,412,401,1,0,0,0,412,402,1,0,0,0,412,403,1,
  	0,0,0,412,404,1,0,0,0,412,405,1,0,0,0,412,406,1,0,0,0,412,407,1,0,0,0,
  	412,408,1,0,0,0,412,409,1,0,0,0,412,410,1,0,0,0,412,411,1,0,0,0,413,53,
  	1,0,0,0,414,418,5,10,0,0,415,417,3,52,26,0,416,415,1,0,0,0,417,420,1,
  	0,0,0,418,416,1,0,0,0,418,419,1,0,0,0,419,421,1,0,0,0,420,418,1,0,0,0,
  	421,422,5,11,0,0,422,55,1,0,0,0,423,427,5,78,0,0,424,427,3,112,56,0,425,
  	427,3,116,58,0,426,423,1,0,0,0,426,424,1,0,0,0,426,425,1,0,0,0,427,428,
  	1,0,0,0,428,429,3,136,68,0,429,430,3,84,42,0,430,57,1,0,0,0,431,433,5,
  	58,0,0,432,431,1,0,0,0,432,433,1,0,0,0,433,434,1,0,0,0,434,435,5,78,0,
  	0,435,436,5,34,0,0,436,439,3,124,62,0,437,438,5,35,0,0,438,440,3,84,42,
  	0,439,437,1,0,0,0,439,440,1,0,0,0,440,59,1,0,0,0,441,443,5,58,0,0,442,
  	441,1,0,0,0,442,443,1,0,0,0,443,444,1,0,0,0,444,446,5,78,0,0,445,447,
  	5,41,0,0,446,445,1,0,0,0,446,447,1,0,0,0,447,448,1,0,0,0,448,449,5,35,
  	0,0,449,450,3,84,42,0,450,61,1,0,0,0,451,452,5,64,0,0,452,454,3,84,42,
  	0,453,455,5,80,0,0,454,453,1,0,0,0,454,455,1,0,0,0,455,456,1,0,0,0,456,
  	460,3,54,27,0,457,459,3,64,32,0,458,457,1,0,0,0,459,462,1,0,0,0,460,458,
  	1,0,0,0,460,461,1,0,0,0,461,464,1,0,0,0,462,460,1,0,0,0,463,465,3,66,
  	33,0,464,463,1,0,0,0,464,465,1,0,0,0,465,63,1,0,0,0,466,467,5,65,0,0,
  	467,468,3,84,42,0,468,469,3,54,27,0,469,65,1,0,0,0,470,471,5,65,0,0,471,
  	472,3,54,27,0,472,67,1,0,0,0,473,475,5,64,0,0,474,476,3,84,42,0,475,474,
  	1,0,0,0,475,476,1,0,0,0,476,477,1,0,0,0,477,481,5,10,0,0,478,480,3,70,
  	35,0,479,478,1,0,0,0,480,483,1,0,0,0,481,479,1,0,0,0,481,482,1,0,0,0,
  	482,487,1,0,0,0,483,481,1,0,0,0,484,485,5,65,0,0,485,486,5,34,0,0,486,
  	488,3,54,27,0,487,484,1,0,0,0,487,488,1,0,0,0,488,489,1,0,0,0,489,490,
  	5,11,0,0,490,69,1,0,0,0,491,492,3,84,42,0,492,493,5,34,0,0,493,494,3,
  	54,27,0,494,71,1,0,0,0,495,496,5,66,0,0,496,498,5,78,0,0,497,499,5,17,
  	0,0,498,497,1,0,0,0,498,499,1,0,0,0,499,500,1,0,0,0,500,501,5,73,0,0,
  	501,502,3,122,61,0,502,503,3,54,27,0,503,526,1,0,0,0,504,505,5,66,0,0,
  	505,510,5,78,0,0,506,507,5,17,0,0,507,509,5,78,0,0,508,506,1,0,0,0,509,
  	512,1,0,0,0,510,508,1,0,0,0,510,511,1,0,0,0,511,514,1,0,0,0,512,510,1,
  	0,0,0,513,515,5,17,0,0,514,513,1,0,0,0,514,515,1,0,0,0,515,516,1,0,0,
  	0,516,517,5,73,0,0,517,518,3,86,43,0,518,519,3,54,27,0,519,526,1,0,0,
  	0,520,522,5,66,0,0,521,523,5,78,0,0,522,521,1,0,0,0,522,523,1,0,0,0,523,
  	524,1,0,0,0,524,526,3,54,27,0,525,495,1,0,0,0,525,504,1,0,0,0,525,520,
  	1,0,0,0,526,73,1,0,0,0,527,529,5,67,0,0,528,530,5,80,0,0,529,528,1,0,
  	0,0,529,530,1,0,0,0,530,75,1,0,0,0,531,533,5,69,0,0,532,534,3,84,42,0,
  	533,532,1,0,0,0,533,534,1,0,0,0,534,77,1,0,0,0,535,536,5,59,0,0,536,537,
  	5,78,0,0,537,541,5,10,0,0,538,540,3,80,40,0,539,538,1,0,0,0,540,543,1,
  	0,0,0,541,539,1,0,0,0,541,542,1,0,0,0,542,544,1,0,0,0,543,541,1,0,0,0,
  	544,545,5,11,0,0,545,79,1,0,0,0,546,549,5,78,0,0,547,548,5,35,0,0,548,
  	550,5,79,0,0,549,547,1,0,0,0,549,550,1,0,0,0,550,81,1,0,0,0,551,555,5,
  	60,0,0,552,556,3,98,49,0,553,556,3,116,58,0,554,556,3,54,27,0,555,552,
  	1,0,0,0,555,553,1,0,0,0,555,554,1,0,0,0,556,83,1,0,0,0,557,558,6,42,-1,
  	0,558,559,5,8,0,0,559,560,3,84,42,0,560,563,5,9,0,0,561,562,5,14,0,0,
  	562,564,3,124,62,0,563,561,1,0,0,0,563,564,1,0,0,0,564,571,1,0,0,0,565,
  	568,3,86,43,0,566,567,5,14,0,0,567,569,3,124,62,0,568,566,1,0,0,0,568,
  	569,1,0,0,0,569,571,1,0,0,0,570,557,1,0,0,0,570,565,1,0,0,0,571,595,1,
  	0,0,0,572,573,10,7,0,0,573,574,7,1,0,0,574,594,3,84,42,8,575,576,10,6,
  	0,0,576,577,7,2,0,0,577,594,3,84,42,7,578,579,10,5,0,0,579,580,7,3,0,
  	0,580,594,3,84,42,6,581,582,10,4,0,0,582,583,7,4,0,0,583,594,3,84,42,
  	5,584,585,10,3,0,0,585,586,7,5,0,0,586,594,3,84,42,4,587,588,10,2,0,0,
  	588,589,7,6,0,0,589,594,3,84,42,3,590,591,10,1,0,0,591,592,7,7,0,0,592,
  	594,3,84,42,2,593,572,1,0,0,0,593,575,1,0,0,0,593,578,1,0,0,0,593,581,
  	1,0,0,0,593,584,1,0,0,0,593,587,1,0,0,0,593,590,1,0,0,0,594,597,1,0,0,
  	0,595,593,1,0,0,0,595,596,1,0,0,0,596,85,1,0,0,0,597,595,1,0,0,0,598,
  	614,5,78,0,0,599,614,5,52,0,0,600,614,5,53,0,0,601,614,5,77,0,0,602,614,
  	3,88,44,0,603,614,3,90,45,0,604,614,3,98,49,0,605,614,3,44,22,0,606,614,
  	3,132,66,0,607,614,3,104,52,0,608,614,3,110,55,0,609,614,3,112,56,0,610,
  	614,3,116,58,0,611,614,3,92,46,0,612,614,3,94,47,0,613,598,1,0,0,0,613,
  	599,1,0,0,0,613,600,1,0,0,0,613,601,1,0,0,0,613,602,1,0,0,0,613,603,1,
  	0,0,0,613,604,1,0,0,0,613,605,1,0,0,0,613,606,1,0,0,0,613,607,1,0,0,0,
  	613,608,1,0,0,0,613,609,1,0,0,0,613,610,1,0,0,0,613,611,1,0,0,0,613,612,
  	1,0,0,0,614,87,1,0,0,0,615,616,7,8,0,0,616,617,3,84,42,0,617,89,1,0,0,
  	0,618,624,5,78,0,0,619,624,3,112,56,0,620,624,3,116,58,0,621,624,3,98,
  	49,0,622,624,3,110,55,0,623,618,1,0,0,0,623,619,1,0,0,0,623,620,1,0,0,
  	0,623,621,1,0,0,0,623,622,1,0,0,0,624,625,1,0,0,0,625,626,7,9,0,0,626,
  	91,1,0,0,0,627,639,5,12,0,0,628,633,3,84,42,0,629,630,5,17,0,0,630,632,
  	3,84,42,0,631,629,1,0,0,0,632,635,1,0,0,0,633,631,1,0,0,0,633,634,1,0,
  	0,0,634,637,1,0,0,0,635,633,1,0,0,0,636,638,5,17,0,0,637,636,1,0,0,0,
  	637,638,1,0,0,0,638,640,1,0,0,0,639,628,1,0,0,0,639,640,1,0,0,0,640,641,
  	1,0,0,0,641,643,5,13,0,0,642,644,5,42,0,0,643,642,1,0,0,0,643,644,1,0,
  	0,0,644,93,1,0,0,0,645,657,5,10,0,0,646,651,3,96,48,0,647,648,5,17,0,
  	0,648,650,3,96,48,0,649,647,1,0,0,0,650,653,1,0,0,0,651,649,1,0,0,0,651,
  	652,1,0,0,0,652,655,1,0,0,0,653,651,1,0,0,0,654,656,5,17,0,0,655,654,
  	1,0,0,0,655,656,1,0,0,0,656,658,1,0,0,0,657,646,1,0,0,0,657,658,1,0,0,
  	0,658,659,1,0,0,0,659,660,5,11,0,0,660,95,1,0,0,0,661,662,3,84,42,0,662,
  	663,5,34,0,0,663,664,3,84,42,0,664,97,1,0,0,0,665,666,5,78,0,0,666,668,
  	5,8,0,0,667,669,3,100,50,0,668,667,1,0,0,0,668,669,1,0,0,0,669,671,1,
  	0,0,0,670,672,5,18,0,0,671,670,1,0,0,0,671,672,1,0,0,0,672,674,1,0,0,
  	0,673,675,5,17,0,0,674,673,1,0,0,0,674,675,1,0,0,0,675,676,1,0,0,0,676,
  	677,5,9,0,0,677,99,1,0,0,0,678,683,3,102,51,0,679,680,5,17,0,0,680,682,
  	3,102,51,0,681,679,1,0,0,0,682,685,1,0,0,0,683,681,1,0,0,0,683,684,1,
  	0,0,0,684,101,1,0,0,0,685,683,1,0,0,0,686,687,5,78,0,0,687,689,5,35,0,
  	0,688,686,1,0,0,0,688,689,1,0,0,0,689,690,1,0,0,0,690,691,3,84,42,0,691,
  	103,1,0,0,0,692,693,5,78,0,0,693,695,5,10,0,0,694,696,3,106,53,0,695,
  	694,1,0,0,0,695,696,1,0,0,0,696,697,1,0,0,0,697,698,5,11,0,0,698,105,
  	1,0,0,0,699,704,3,108,54,0,700,701,5,17,0,0,701,703,3,108,54,0,702,700,
  	1,0,0,0,703,706,1,0,0,0,704,702,1,0,0,0,704,705,1,0,0,0,705,708,1,0,0,
  	0,706,704,1,0,0,0,707,709,5,17,0,0,708,707,1,0,0,0,708,709,1,0,0,0,709,
  	107,1,0,0,0,710,711,5,78,0,0,711,712,5,35,0,0,712,713,3,84,42,0,713,109,
  	1,0,0,0,714,715,7,10,0,0,715,111,1,0,0,0,716,719,3,98,49,0,717,719,5,
  	78,0,0,718,716,1,0,0,0,718,717,1,0,0,0,719,721,1,0,0,0,720,722,3,114,
  	57,0,721,720,1,0,0,0,722,723,1,0,0,0,723,721,1,0,0,0,723,724,1,0,0,0,
  	724,113,1,0,0,0,725,726,5,12,0,0,726,728,3,84,42,0,727,729,5,34,0,0,728,
  	727,1,0,0,0,728,729,1,0,0,0,729,730,1,0,0,0,730,731,5,13,0,0,731,744,
  	1,0,0,0,732,733,5,12,0,0,733,734,5,34,0,0,734,735,3,84,42,0,735,736,5,
  	13,0,0,736,744,1,0,0,0,737,738,5,12,0,0,738,739,3,84,42,0,739,740,5,34,
  	0,0,740,741,3,84,42,0,741,742,5,13,0,0,742,744,1,0,0,0,743,725,1,0,0,
  	0,743,732,1,0,0,0,743,737,1,0,0,0,744,115,1,0,0,0,745,747,3,118,59,0,
  	746,748,5,41,0,0,747,746,1,0,0,0,747,748,1,0,0,0,748,754,1,0,0,0,749,
  	750,5,33,0,0,750,752,3,120,60,0,751,753,5,41,0,0,752,751,1,0,0,0,752,
  	753,1,0,0,0,753,755,1,0,0,0,754,749,1,0,0,0,755,756,1,0,0,0,756,754,1,
  	0,0,0,756,757,1,0,0,0,757,117,1,0,0,0,758,766,5,78,0,0,759,766,5,79,0,
  	0,760,766,5,53,0,0,761,766,5,52,0,0,762,766,3,98,49,0,763,766,3,104,52,
  	0,764,766,3,112,56,0,765,758,1,0,0,0,765,759,1,0,0,0,765,760,1,0,0,0,
  	765,761,1,0,0,0,765,762,1,0,0,0,765,763,1,0,0,0,765,764,1,0,0,0,766,119,
  	1,0,0,0,767,771,5,78,0,0,768,771,3,98,49,0,769,771,3,112,56,0,770,767,
  	1,0,0,0,770,768,1,0,0,0,770,769,1,0,0,0,771,121,1,0,0,0,772,773,3,84,
  	42,0,773,774,5,19,0,0,774,775,3,84,42,0,775,782,1,0,0,0,776,777,5,19,
  	0,0,777,782,3,84,42,0,778,779,3,84,42,0,779,780,5,19,0,0,780,782,1,0,
  	0,0,781,772,1,0,0,0,781,776,1,0,0,0,781,778,1,0,0,0,782,123,1,0,0,0,783,
  	784,6,62,-1,0,784,786,5,78,0,0,785,787,5,41,0,0,786,785,1,0,0,0,786,787,
  	1,0,0,0,787,792,1,0,0,0,788,792,5,53,0,0,789,792,3,126,63,0,790,792,3,
  	130,65,0,791,783,1,0,0,0,791,788,1,0,0,0,791,789,1,0,0,0,791,790,1,0,
  	0,0,792,804,1,0,0,0,793,795,10,3,0,0,794,796,3,128,64,0,795,794,1,0,0,
  	0,796,797,1,0,0,0,797,795,1,0,0,0,797,798,1,0,0,0,798,800,1,0,0,0,799,
  	801,5,42,0,0,800,799,1,0,0,0,800,801,1,0,0,0,801,803,1,0,0,0,802,793,
  	1,0,0,0,803,806,1,0,0,0,804,802,1,0,0,0,804,805,1,0,0,0,805,125,1,0,0,
  	0,806,804,1,0,0,0,807,808,5,10,0,0,808,809,3,124,62,0,809,810,5,34,0,
  	0,810,811,3,124,62,0,811,812,5,11,0,0,812,127,1,0,0,0,813,815,5,12,0,
  	0,814,816,3,84,42,0,815,814,1,0,0,0,815,816,1,0,0,0,816,817,1,0,0,0,817,
  	818,5,13,0,0,818,129,1,0,0,0,819,831,5,8,0,0,820,825,3,124,62,0,821,822,
  	5,17,0,0,822,824,3,124,62,0,823,821,1,0,0,0,824,827,1,0,0,0,825,823,1,
  	0,0,0,825,826,1,0,0,0,826,829,1,0,0,0,827,825,1,0,0,0,828,830,5,17,0,
  	0,829,828,1,0,0,0,829,830,1,0,0,0,830,832,1,0,0,0,831,820,1,0,0,0,831,
  	832,1,0,0,0,832,833,1,0,0,0,833,834,5,9,0,0,834,835,5,34,0,0,835,836,
  	3,124,62,0,836,131,1,0,0,0,837,838,7,11,0,0,838,850,5,8,0,0,839,844,3,
  	84,42,0,840,841,5,17,0,0,841,843,3,84,42,0,842,840,1,0,0,0,843,846,1,
  	0,0,0,844,842,1,0,0,0,844,845,1,0,0,0,845,848,1,0,0,0,846,844,1,0,0,0,
  	847,849,5,17,0,0,848,847,1,0,0,0,848,849,1,0,0,0,849,851,1,0,0,0,850,
  	839,1,0,0,0,850,851,1,0,0,0,851,852,1,0,0,0,852,853,5,9,0,0,853,133,1,
  	0,0,0,854,855,5,2,0,0,855,856,5,3,0,0,856,862,5,10,0,0,857,858,5,78,0,
  	0,858,859,5,34,0,0,859,861,3,124,62,0,860,857,1,0,0,0,861,864,1,0,0,0,
  	862,860,1,0,0,0,862,863,1,0,0,0,863,865,1,0,0,0,864,862,1,0,0,0,865,866,
  	5,11,0,0,866,135,1,0,0,0,867,868,7,12,0,0,868,137,1,0,0,0,113,139,144,
  	152,159,161,168,170,174,182,184,190,225,229,236,240,243,248,254,260,270,
  	275,281,285,288,295,298,302,308,315,318,327,331,333,340,344,348,359,363,
  	365,370,376,386,390,392,397,412,418,426,432,439,442,446,454,460,464,475,
  	481,487,498,510,514,522,525,529,533,541,549,555,563,568,570,593,595,613,
  	623,633,637,639,643,651,655,657,668,671,674,683,688,695,704,708,718,723,
  	728,743,747,752,756,765,770,781,786,791,797,800,804,815,825,829,831,844,
  	848,850,862
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

tree::TerminalNode* LogosParser::ObjectFileContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

LogosParser::ObjectBodyContext* LogosParser::ObjectFileContext::objectBody() {
  return getRuleContext<LogosParser::ObjectBodyContext>(0);
}

tree::TerminalNode* LogosParser::ObjectFileContext::EOF() {
  return getToken(LogosParser::EOF, 0);
}

tree::TerminalNode* LogosParser::ObjectFileContext::OBJECT() {
  return getToken(LogosParser::OBJECT, 0);
}

tree::TerminalNode* LogosParser::ObjectFileContext::SINGLETON() {
  return getToken(LogosParser::SINGLETON, 0);
}


size_t LogosParser::ObjectFileContext::getRuleIndex() const {
  return LogosParser::RuleObjectFile;
}


LogosParser::ObjectFileContext* LogosParser::objectFile() {
  ObjectFileContext *_localctx = _tracker.createInstance<ObjectFileContext>(_ctx, getState());
  enterRule(_localctx, 10, LogosParser::RuleObjectFile);
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
    setState(194);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(195);
    match(LogosParser::IDENTIFIER);
    setState(196);
    objectBody();
    setState(197);
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
    setState(199);
    match(LogosParser::INTERFACE);
    setState(200);
    match(LogosParser::IDENTIFIER);
    setState(201);
    interfaceBody();
    setState(202);
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
    setState(204);
    match(LogosParser::INTERFACE);
    setState(205);
    match(LogosParser::IDENTIFIER);
    setState(206);
    match(LogosParser::LBRACE);
    setState(207);
    interfaceBody();
    setState(208);
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
    setState(210);
    match(LogosParser::IDENTIFIER);
    setState(211);
    match(LogosParser::EQUAL);
    setState(212);
    match(LogosParser::LBRACE);
    setState(213);
    groupTypesList();
    setState(214);
    match(LogosParser::RBRACE);
    setState(215);
    match(LogosParser::ARROW);
    setState(216);
    match(LogosParser::LBRACE);
    setState(217);
    groupTargetList();
    setState(218);
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
    setState(220);
    type(0);
    setState(225);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(221);
        match(LogosParser::COMMA);
        setState(222);
        type(0); 
      }
      setState(227);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
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
    setState(231);
    match(LogosParser::IDENTIFIER);
    setState(236);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(232);
        match(LogosParser::COMMA);
        setState(233);
        match(LogosParser::IDENTIFIER); 
      }
      setState(238);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
    setState(240);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(239);
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
    setState(243);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(242);
      implements();
    }
    setState(248);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(245);
        interfaceField(); 
      }
      setState(250);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
    setState(254);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(251);
        interfaceFuncSignature(); 
      }
      setState(256);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
    setState(260);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(257);
      funcImpl();
      setState(262);
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
    setState(263);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(264);
    match(LogosParser::IDENTIFIER);
    setState(265);
    match(LogosParser::LBRACE);
    setState(266);
    objectBody();
    setState(267);
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
    setState(270);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(269);
      implements();
    }
    setState(275);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(272);
        field(); 
      }
      setState(277);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    }
    setState(281);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VISIBILITY

    || _la == LogosParser::IDENTIFIER) {
      setState(278);
      methodImplementation();
      setState(283);
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
    setState(285);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(284);
      match(LogosParser::VISIBILITY);
    }
    setState(288);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(287);
      match(LogosParser::CONST);
    }
    setState(290);
    match(LogosParser::IDENTIFIER);
    setState(291);
    match(LogosParser::COLON);
    setState(292);
    type(0);
    setState(295);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(293);
      match(LogosParser::EQUAL);
      setState(294);
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
    setState(298);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(297);
      match(LogosParser::CONST);
    }
    setState(300);
    match(LogosParser::IDENTIFIER);
    setState(302);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(301);
      match(LogosParser::QUEST_MARK);
    }
    setState(304);
    match(LogosParser::COLON);
    setState(305);
    type(0);
    setState(308);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(306);
      match(LogosParser::EQUAL);
      setState(307);
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
  enterRule(_localctx, 32, LogosParser::RuleImplements);
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
    setState(310);
    match(LogosParser::IMPLEMENTS);
    setState(311);
    match(LogosParser::COLON);
    setState(312);
    match(LogosParser::IDENTIFIER);
    setState(315);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      setState(313);
      match(LogosParser::COMMA);
      setState(314);
      match(LogosParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    setState(318);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(317);
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
  enterRule(_localctx, 34, LogosParser::RuleFuncSignatureHeader);
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
    setState(320);
    match(LogosParser::IDENTIFIER);
    setState(321);
    match(LogosParser::LPAREN);
    setState(333);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(322);
      param();
      setState(327);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(323);
          match(LogosParser::COMMA);
          setState(324);
          param(); 
        }
        setState(329);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
      }
      setState(331);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(330);
        match(LogosParser::COMMA);
      }
    }
    setState(335);
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
  enterRule(_localctx, 36, LogosParser::RuleFuncSignature);
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
    setState(337);
    funcSignatureHeader();
    setState(340);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(338);
      match(LogosParser::COLON);
      setState(339);
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
  enterRule(_localctx, 38, LogosParser::RuleInterfaceFuncSignature);
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
    setState(342);
    funcSignatureHeader();
    setState(344);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(343);
      match(LogosParser::QUEST_MARK);
    }
    setState(348);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(346);
      match(LogosParser::COLON);
      setState(347);
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

LogosParser::StatementsBlockContext* LogosParser::FuncImplContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}


size_t LogosParser::FuncImplContext::getRuleIndex() const {
  return LogosParser::RuleFuncImpl;
}


LogosParser::FuncImplContext* LogosParser::funcImpl() {
  FuncImplContext *_localctx = _tracker.createInstance<FuncImplContext>(_ctx, getState());
  enterRule(_localctx, 40, LogosParser::RuleFuncImpl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(350);
    funcSignature();
    setState(351);
    statementsBlock();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AnonymosFuncSignatureContext ------------------------------------------------------------------

LogosParser::AnonymosFuncSignatureContext::AnonymosFuncSignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::AnonymosFuncSignatureContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::AnonymosFuncSignatureContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

std::vector<LogosParser::AnonymousParamContext *> LogosParser::AnonymosFuncSignatureContext::anonymousParam() {
  return getRuleContexts<LogosParser::AnonymousParamContext>();
}

LogosParser::AnonymousParamContext* LogosParser::AnonymosFuncSignatureContext::anonymousParam(size_t i) {
  return getRuleContext<LogosParser::AnonymousParamContext>(i);
}

tree::TerminalNode* LogosParser::AnonymosFuncSignatureContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::TypeContext* LogosParser::AnonymosFuncSignatureContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}

std::vector<tree::TerminalNode *> LogosParser::AnonymosFuncSignatureContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::AnonymosFuncSignatureContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::AnonymosFuncSignatureContext::getRuleIndex() const {
  return LogosParser::RuleAnonymosFuncSignature;
}


LogosParser::AnonymosFuncSignatureContext* LogosParser::anonymosFuncSignature() {
  AnonymosFuncSignatureContext *_localctx = _tracker.createInstance<AnonymosFuncSignatureContext>(_ctx, getState());
  enterRule(_localctx, 42, LogosParser::RuleAnonymosFuncSignature);
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
    setState(353);
    match(LogosParser::LPAREN);
    setState(365);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(354);
      anonymousParam();
      setState(359);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(355);
          match(LogosParser::COMMA);
          setState(356);
          anonymousParam(); 
        }
        setState(361);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
      }
      setState(363);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(362);
        match(LogosParser::COMMA);
      }
    }
    setState(367);
    match(LogosParser::RPAREN);
    setState(370);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(368);
      match(LogosParser::COLON);
      setState(369);
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

LogosParser::AnonymosFuncSignatureContext* LogosParser::AnonnymosFuncContext::anonymosFuncSignature() {
  return getRuleContext<LogosParser::AnonymosFuncSignatureContext>(0);
}

LogosParser::StatementsBlockContext* LogosParser::AnonnymosFuncContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}


size_t LogosParser::AnonnymosFuncContext::getRuleIndex() const {
  return LogosParser::RuleAnonnymosFunc;
}


LogosParser::AnonnymosFuncContext* LogosParser::anonnymosFunc() {
  AnonnymosFuncContext *_localctx = _tracker.createInstance<AnonnymosFuncContext>(_ctx, getState());
  enterRule(_localctx, 44, LogosParser::RuleAnonnymosFunc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(372);
    anonymosFuncSignature();
    setState(373);
    statementsBlock();
   
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

LogosParser::StatementsBlockContext* LogosParser::MethodImplementationContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}

tree::TerminalNode* LogosParser::MethodImplementationContext::VISIBILITY() {
  return getToken(LogosParser::VISIBILITY, 0);
}


size_t LogosParser::MethodImplementationContext::getRuleIndex() const {
  return LogosParser::RuleMethodImplementation;
}


LogosParser::MethodImplementationContext* LogosParser::methodImplementation() {
  MethodImplementationContext *_localctx = _tracker.createInstance<MethodImplementationContext>(_ctx, getState());
  enterRule(_localctx, 46, LogosParser::RuleMethodImplementation);
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
    setState(376);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(375);
      match(LogosParser::VISIBILITY);
    }
    setState(378);
    funcSignature();
    setState(379);
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

LogosParser::FuncTypeContext* LogosParser::ParamContext::funcType() {
  return getRuleContext<LogosParser::FuncTypeContext>(0);
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


size_t LogosParser::ParamContext::getRuleIndex() const {
  return LogosParser::RuleParam;
}


LogosParser::ParamContext* LogosParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 48, LogosParser::RuleParam);
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
    match(LogosParser::IDENTIFIER);
    setState(382);
    match(LogosParser::COLON);
    setState(392);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      setState(383);
      funcType();
      break;
    }

    case 2: {
      setState(384);
      type(0);
      setState(386);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::TRIPLE_DOT) {
        setState(385);
        match(LogosParser::TRIPLE_DOT);
      }
      setState(390);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::EQUAL) {
        setState(388);
        match(LogosParser::EQUAL);
        setState(389);
        expr(0);
      }
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

//----------------- AnonymousParamContext ------------------------------------------------------------------

LogosParser::AnonymousParamContext::AnonymousParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::AnonymousParamContext::IDENTIFIER() {
  return getToken(LogosParser::IDENTIFIER, 0);
}

tree::TerminalNode* LogosParser::AnonymousParamContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::TypeContext* LogosParser::AnonymousParamContext::type() {
  return getRuleContext<LogosParser::TypeContext>(0);
}


size_t LogosParser::AnonymousParamContext::getRuleIndex() const {
  return LogosParser::RuleAnonymousParam;
}


LogosParser::AnonymousParamContext* LogosParser::anonymousParam() {
  AnonymousParamContext *_localctx = _tracker.createInstance<AnonymousParamContext>(_ctx, getState());
  enterRule(_localctx, 50, LogosParser::RuleAnonymousParam);
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
    setState(394);
    match(LogosParser::IDENTIFIER);
    setState(397);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(395);
      match(LogosParser::COLON);
      setState(396);
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

LogosParser::CoroutineContext* LogosParser::StatementContext::coroutine() {
  return getRuleContext<LogosParser::CoroutineContext>(0);
}

LogosParser::PostfixExprContext* LogosParser::StatementContext::postfixExpr() {
  return getRuleContext<LogosParser::PostfixExprContext>(0);
}


size_t LogosParser::StatementContext::getRuleIndex() const {
  return LogosParser::RuleStatement;
}


LogosParser::StatementContext* LogosParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 52, LogosParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(412);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
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
      coroutine();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(411);
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
  enterRule(_localctx, 54, LogosParser::RuleStatementsBlock);
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
    setState(414);
    match(LogosParser::LBRACE);
    setState(418);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 52) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 52)) & 230936899) != 0)) {
      setState(415);
      statement();
      setState(420);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(421);
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
  enterRule(_localctx, 56, LogosParser::RuleAssignment);

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
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      setState(423);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(424);
      iterIndex();
      break;
    }

    case 3: {
      setState(425);
      selection();
      break;
    }

    default:
      break;
    }
    setState(428);
    assignemntOp();
    setState(429);
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
  enterRule(_localctx, 58, LogosParser::RuleExplicitVarDec);
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
    setState(432);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(431);
      match(LogosParser::CONST);
    }
    setState(434);
    match(LogosParser::IDENTIFIER);
    setState(435);
    match(LogosParser::COLON);
    setState(436);
    type(0);
    setState(439);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(437);
      match(LogosParser::EQUAL);
      setState(438);
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
  enterRule(_localctx, 60, LogosParser::RuleImplicitVarDec);
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
    setState(442);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(441);
      match(LogosParser::CONST);
    }
    setState(444);
    match(LogosParser::IDENTIFIER);
    setState(446);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(445);
      match(LogosParser::QUEST_MARK);
    }
    setState(448);
    match(LogosParser::EQUAL);
    setState(449);
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
  enterRule(_localctx, 62, LogosParser::RuleIfStatement);
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
    setState(451);
    match(LogosParser::IF);
    setState(452);
    expr(0);
    setState(454);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TAG) {
      setState(453);
      match(LogosParser::TAG);
    }
    setState(456);
    statementsBlock();
    setState(460);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(457);
        elseIfStatement(); 
      }
      setState(462);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
    }
    setState(464);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(463);
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
  enterRule(_localctx, 64, LogosParser::RuleElseIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(466);
    match(LogosParser::ELSE);
    setState(467);
    expr(0);
    setState(468);
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
  enterRule(_localctx, 66, LogosParser::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(470);
    match(LogosParser::ELSE);
    setState(471);
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
    setState(473);
    match(LogosParser::IF);
    setState(475);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      setState(474);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(477);
    match(LogosParser::LBRACE);
    setState(481);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -2292332072892623616) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & 253) != 0)) {
      setState(478);
      pattern();
      setState(483);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(487);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(484);
      match(LogosParser::ELSE);
      setState(485);
      match(LogosParser::COLON);
      setState(486);
      statementsBlock();
    }
    setState(489);
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
    setState(491);
    expr(0);
    setState(492);
    match(LogosParser::COLON);
    setState(493);
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
    size_t alt;
    setState(525);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(495);
      match(LogosParser::FOR);
      setState(496);
      match(LogosParser::IDENTIFIER);
      setState(498);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(497);
        match(LogosParser::COMMA);
      }
      setState(500);
      match(LogosParser::IN);
      setState(501);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(502);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(504);
      match(LogosParser::FOR);
      setState(505);
      match(LogosParser::IDENTIFIER);
      setState(510);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(506);
          match(LogosParser::COMMA);
          setState(507);
          match(LogosParser::IDENTIFIER); 
        }
        setState(512);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
      }
      setState(514);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(513);
        match(LogosParser::COMMA);
      }
      setState(516);
      match(LogosParser::IN);
      setState(517);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = unaryExpr();
      setState(518);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(520);
      match(LogosParser::FOR);
      setState(522);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::IDENTIFIER) {
        setState(521);
        match(LogosParser::IDENTIFIER);
      }
      setState(524);
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
  enterRule(_localctx, 74, LogosParser::RuleBreakStmt);
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
    setState(527);
    match(LogosParser::BREAK);
    setState(529);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TAG) {
      setState(528);
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
    setState(531);
    match(LogosParser::RETURN);
    setState(533);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      setState(532);
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
  enterRule(_localctx, 78, LogosParser::RuleEnumDeclaration);
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
    setState(535);
    match(LogosParser::ENUM);
    setState(536);
    match(LogosParser::IDENTIFIER);
    setState(537);
    match(LogosParser::LBRACE);
    setState(541);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(538);
      enumField();
      setState(543);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(544);
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
  enterRule(_localctx, 80, LogosParser::RuleEnumField);
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
    match(LogosParser::IDENTIFIER);
    setState(549);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(547);
      match(LogosParser::EQUAL);
      setState(548);
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

//----------------- CoroutineContext ------------------------------------------------------------------

LogosParser::CoroutineContext::CoroutineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::CoroutineContext::GO() {
  return getToken(LogosParser::GO, 0);
}

LogosParser::FuncCallContext* LogosParser::CoroutineContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::SelectionContext* LogosParser::CoroutineContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}

LogosParser::StatementsBlockContext* LogosParser::CoroutineContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
}


size_t LogosParser::CoroutineContext::getRuleIndex() const {
  return LogosParser::RuleCoroutine;
}


LogosParser::CoroutineContext* LogosParser::coroutine() {
  CoroutineContext *_localctx = _tracker.createInstance<CoroutineContext>(_ctx, getState());
  enterRule(_localctx, 82, LogosParser::RuleCoroutine);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(551);
    match(LogosParser::GO);
    setState(555);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
    case 1: {
      setState(552);
      funcCall();
      break;
    }

    case 2: {
      setState(553);
      selection();
      break;
    }

    case 3: {
      setState(554);
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
    setState(570);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
    case 1: {
      setState(558);
      match(LogosParser::LPAREN);
      setState(559);
      antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
      setState(560);
      match(LogosParser::RPAREN);
      setState(563);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
      case 1: {
        setState(561);
        match(LogosParser::ARROW);
        setState(562);
        type(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      setState(565);
      unaryExpr();
      setState(568);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
      case 1: {
        setState(566);
        match(LogosParser::ARROW);
        setState(567);
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
    setState(595);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(593);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(572);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(573);
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
          setState(574);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(575);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(576);
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
          setState(577);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(578);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(579);
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
          setState(580);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(581);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(582);
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
          setState(583);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(584);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(585);
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
          setState(586);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(587);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(588);
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
          setState(589);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(590);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(591);
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
          setState(592);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(597);
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
    setState(613);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(598);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(599);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(600);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(601);
      match(LogosParser::NULL_);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(602);
      prefixExpr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(603);
      postfixExpr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(604);
      funcCall();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(605);
      anonnymosFunc();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(606);
      vector();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(607);
      constructor();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(608);
      constant();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(609);
      iterIndex();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(610);
      selection();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(611);
      arrayExpr();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(612);
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
    setState(615);
    _la = _input->LA(1);
    if (!(_la == LogosParser::MINUS

    || _la == LogosParser::NOT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(616);
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
    setState(623);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      setState(618);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(619);
      iterIndex();
      break;
    }

    case 3: {
      setState(620);
      selection();
      break;
    }

    case 4: {
      setState(621);
      funcCall();
      break;
    }

    case 5: {
      setState(622);
      constant();
      break;
    }

    default:
      break;
    }
    setState(625);
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
    setState(627);
    match(LogosParser::LBRACK);
    setState(639);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -2292332072892623616) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & 253) != 0)) {
      setState(628);
      expr(0);
      setState(633);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(629);
          match(LogosParser::COMMA);
          setState(630);
          expr(0); 
        }
        setState(635);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx);
      }
      setState(637);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(636);
        match(LogosParser::COMMA);
      }
    }
    setState(641);
    match(LogosParser::RBRACK);
    setState(643);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
    case 1: {
      setState(642);
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
    setState(645);
    match(LogosParser::LBRACE);
    setState(657);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -2292332072892623616) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & 253) != 0)) {
      setState(646);
      keyValue();
      setState(651);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(647);
          match(LogosParser::COMMA);
          setState(648);
          keyValue(); 
        }
        setState(653);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
      }
      setState(655);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(654);
        match(LogosParser::COMMA);
      }
    }
    setState(659);
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
    setState(661);
    antlrcpp::downCast<KeyValueContext *>(_localctx)->key = expr(0);
    setState(662);
    match(LogosParser::COLON);
    setState(663);
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
    setState(665);
    match(LogosParser::IDENTIFIER);
    setState(666);
    match(LogosParser::LPAREN);
    setState(668);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -2292332072892623616) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & 253) != 0)) {
      setState(667);
      funcArgList();
    }
    setState(671);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TRIPLE_DOT) {
      setState(670);
      match(LogosParser::TRIPLE_DOT);
    }
    setState(674);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(673);
      match(LogosParser::COMMA);
    }
    setState(676);
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
    setState(678);
    funcArg();
    setState(683);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(679);
        match(LogosParser::COMMA);
        setState(680);
        funcArg(); 
      }
      setState(685);
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
    setState(688);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx)) {
    case 1: {
      setState(686);
      match(LogosParser::IDENTIFIER);
      setState(687);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(690);
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
    setState(692);
    match(LogosParser::IDENTIFIER);
    setState(693);
    match(LogosParser::LBRACE);
    setState(695);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(694);
      constructorArgList();
    }
    setState(697);
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
    setState(699);
    constructorArg();
    setState(704);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(700);
        match(LogosParser::COMMA);
        setState(701);
        constructorArg(); 
      }
      setState(706);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx);
    }
    setState(708);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(707);
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
    setState(710);
    match(LogosParser::IDENTIFIER);
    setState(711);
    match(LogosParser::EQUAL);
    setState(712);
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
    setState(714);
    _la = _input->LA(1);
    if (!(((((_la - 74) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 74)) & 39) != 0))) {
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
    setState(718);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 90, _ctx)) {
    case 1: {
      setState(716);
      funcCall();
      break;
    }

    case 2: {
      setState(717);
      match(LogosParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    setState(721); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(720);
              index();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(723); 
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
    setState(743);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(725);
      match(LogosParser::LBRACK);
      setState(726);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(728);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COLON) {
        setState(727);
        match(LogosParser::COLON);
      }
      setState(730);
      match(LogosParser::RBRACK);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(732);
      match(LogosParser::LBRACK);
      setState(733);
      match(LogosParser::COLON);
      setState(734);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(735);
      match(LogosParser::RBRACK);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(737);
      match(LogosParser::LBRACK);
      setState(738);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(739);
      match(LogosParser::COLON);
      setState(740);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(741);
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
    setState(745);
    firstSelectionElement();
    setState(747);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(746);
      match(LogosParser::QUEST_MARK);
    }
    setState(754); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(749);
              match(LogosParser::DOT);
              setState(750);
              innerSelectionElement();
              setState(752);
              _errHandler->sync(this);

              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 95, _ctx)) {
              case 1: {
                setState(751);
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
      setState(756); 
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
    setState(765);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(758);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(759);
      match(LogosParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(760);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(761);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(762);
      funcCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(763);
      constructor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(764);
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
    setState(770);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(767);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(768);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
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
    setState(781);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 99, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(772);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(773);
      match(LogosParser::DOUBLE_DOT);
      setState(774);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(776);
      match(LogosParser::DOUBLE_DOT);
      setState(777);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(778);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(779);
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
    setState(791);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::IDENTIFIER: {
        setState(784);
        match(LogosParser::IDENTIFIER);
        setState(786);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx)) {
        case 1: {
          setState(785);
          match(LogosParser::QUEST_MARK);
          break;
        }

        default:
          break;
        }
        break;
      }

      case LogosParser::SELF_CLASS: {
        setState(788);
        match(LogosParser::SELF_CLASS);
        break;
      }

      case LogosParser::LBRACE: {
        setState(789);
        mapType();
        break;
      }

      case LogosParser::LPAREN: {
        setState(790);
        funcType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(804);
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
        setState(793);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(795); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(794);
                  arraySize();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(797); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        setState(800);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 103, _ctx)) {
        case 1: {
          setState(799);
          match(LogosParser::EXCLA_MARK);
          break;
        }

        default:
          break;
        } 
      }
      setState(806);
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
    setState(807);
    match(LogosParser::LBRACE);
    setState(808);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->key = type(0);
    setState(809);
    match(LogosParser::COLON);
    setState(810);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->value = type(0);
    setState(811);
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
    setState(813);
    match(LogosParser::LBRACK);
    setState(815);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -2292332072892623616) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & 253) != 0)) {
      setState(814);
      expr(0);
    }
    setState(817);
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
    setState(819);
    match(LogosParser::LPAREN);
    setState(831);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 9007199254742272) != 0) || _la == LogosParser::IDENTIFIER) {
      setState(820);
      type(0);
      setState(825);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 106, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(821);
          match(LogosParser::COMMA);
          setState(822);
          type(0); 
        }
        setState(827);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 106, _ctx);
      }
      setState(829);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(828);
        match(LogosParser::COMMA);
      }
    }
    setState(833);
    match(LogosParser::RPAREN);
    setState(834);
    match(LogosParser::COLON);
    setState(835);
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
    setState(837);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -2305843009213693952) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(838);
    match(LogosParser::LPAREN);
    setState(850);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & -2292332072892623616) != 0) || ((((_la - 72) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 72)) & 253) != 0)) {
      setState(839);
      expr(0);
      setState(844);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 109, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(840);
          match(LogosParser::COMMA);
          setState(841);
          expr(0); 
        }
        setState(846);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 109, _ctx);
      }
      setState(848);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(847);
        match(LogosParser::COMMA);
      }
    }
    setState(852);
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
    setState(854);
    match(LogosParser::T__1);
    setState(855);
    match(LogosParser::T__2);
    setState(856);
    match(LogosParser::LBRACE);
    setState(862);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(857);
      match(LogosParser::IDENTIFIER);
      setState(858);
      match(LogosParser::COLON);
      setState(859);
      type(0);
      setState(864);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(865);
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
    setState(867);
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
