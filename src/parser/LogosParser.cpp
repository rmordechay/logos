
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
      "funcSignature", "interfaceFuncSignature", "funcImpl", "anonymosFuncSignature", 
      "anonnymosFunc", "methodImplementation", "param", "anonymousParam", 
      "statement", "statementsBlock", "assignment", "explicitVarDec", "implicitVarDec", 
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
  	4,1,82,865,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
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
  	379,8,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,3,25,389,8,25,1,25,1,
  	25,3,25,393,8,25,3,25,395,8,25,1,26,1,26,1,26,3,26,400,8,26,1,27,1,27,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,414,8,27,1,28,
  	1,28,5,28,418,8,28,10,28,12,28,421,9,28,1,28,1,28,1,29,1,29,1,29,3,29,
  	428,8,29,1,29,1,29,1,29,1,30,3,30,434,8,30,1,30,1,30,1,30,1,30,1,30,3,
  	30,441,8,30,1,31,3,31,444,8,31,1,31,1,31,3,31,448,8,31,1,31,1,31,1,31,
  	1,32,1,32,1,32,3,32,456,8,32,1,32,1,32,5,32,460,8,32,10,32,12,32,463,
  	9,32,1,32,3,32,466,8,32,1,33,1,33,1,33,1,33,1,34,1,34,1,34,1,35,1,35,
  	3,35,477,8,35,1,35,1,35,5,35,481,8,35,10,35,12,35,484,9,35,1,35,1,35,
  	1,35,3,35,489,8,35,1,35,1,35,1,36,1,36,1,36,1,36,1,37,1,37,1,37,3,37,
  	500,8,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,5,37,510,8,37,10,37,
  	12,37,513,9,37,1,37,3,37,516,8,37,1,37,1,37,1,37,1,37,1,37,1,37,3,37,
  	524,8,37,1,37,3,37,527,8,37,1,38,1,38,3,38,531,8,38,1,39,1,39,3,39,535,
  	8,39,1,40,1,40,1,40,1,40,5,40,541,8,40,10,40,12,40,544,9,40,1,40,1,40,
  	1,41,1,41,1,41,3,41,551,8,41,1,42,1,42,1,42,1,42,1,42,1,42,3,42,559,8,
  	42,1,42,1,42,1,42,3,42,564,8,42,3,42,566,8,42,1,42,1,42,1,42,1,42,1,42,
  	1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,1,42,
  	1,42,1,42,5,42,589,8,42,10,42,12,42,592,9,42,1,43,1,43,1,43,1,43,1,43,
  	1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,1,43,3,43,609,8,43,1,44,
  	1,44,1,44,1,45,1,45,1,45,1,45,1,45,3,45,619,8,45,1,45,1,45,1,46,1,46,
  	1,46,1,46,5,46,627,8,46,10,46,12,46,630,9,46,1,46,3,46,633,8,46,3,46,
  	635,8,46,1,46,1,46,3,46,639,8,46,1,47,1,47,1,47,1,47,5,47,645,8,47,10,
  	47,12,47,648,9,47,1,47,3,47,651,8,47,3,47,653,8,47,1,47,1,47,1,48,1,48,
  	1,48,1,48,1,49,1,49,1,49,3,49,664,8,49,1,49,3,49,667,8,49,1,49,3,49,670,
  	8,49,1,49,1,49,1,50,1,50,1,50,5,50,677,8,50,10,50,12,50,680,9,50,1,51,
  	1,51,3,51,684,8,51,1,51,1,51,1,52,1,52,1,52,3,52,691,8,52,1,52,1,52,1,
  	53,1,53,1,53,5,53,698,8,53,10,53,12,53,701,9,53,1,53,3,53,704,8,53,1,
  	54,1,54,1,54,1,54,1,55,1,55,1,56,1,56,3,56,714,8,56,1,56,4,56,717,8,56,
  	11,56,12,56,718,1,57,1,57,1,57,3,57,724,8,57,1,57,1,57,1,57,1,57,1,57,
  	1,57,1,57,1,57,1,57,1,57,1,57,1,57,1,57,3,57,739,8,57,1,58,1,58,3,58,
  	743,8,58,1,58,1,58,1,58,3,58,748,8,58,4,58,750,8,58,11,58,12,58,751,1,
  	59,1,59,1,59,1,59,1,59,1,59,1,59,3,59,761,8,59,1,60,1,60,1,60,3,60,766,
  	8,60,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,1,61,3,61,777,8,61,1,62,
  	1,62,1,62,3,62,782,8,62,1,62,1,62,1,62,3,62,787,8,62,1,62,1,62,4,62,791,
  	8,62,11,62,12,62,792,1,62,3,62,796,8,62,5,62,798,8,62,10,62,12,62,801,
  	9,62,1,63,1,63,1,63,1,63,1,63,1,63,1,64,1,64,3,64,811,8,64,1,64,1,64,
  	1,65,1,65,1,65,1,65,5,65,819,8,65,10,65,12,65,822,9,65,1,65,3,65,825,
  	8,65,3,65,827,8,65,1,65,1,65,1,65,1,65,1,66,1,66,1,66,1,66,1,66,5,66,
  	838,8,66,10,66,12,66,841,9,66,1,66,3,66,844,8,66,3,66,846,8,66,1,66,1,
  	66,1,67,1,67,1,67,1,67,1,67,1,67,5,67,856,8,67,10,67,12,67,859,9,67,1,
  	67,1,67,1,68,1,68,1,68,0,2,84,124,69,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,
  	72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,
  	114,116,118,120,122,124,126,128,130,132,134,136,0,13,1,0,50,51,2,0,38,
  	39,43,43,1,0,36,37,2,0,6,7,15,16,1,0,4,5,1,0,69,70,1,0,45,47,1,0,48,49,
  	2,0,37,37,71,71,1,0,31,32,2,0,73,75,78,78,1,0,60,62,1,0,20,30,953,0,139,
  	1,0,0,0,2,146,1,0,0,0,4,161,1,0,0,0,6,170,1,0,0,0,8,184,1,0,0,0,10,194,
  	1,0,0,0,12,198,1,0,0,0,14,203,1,0,0,0,16,209,1,0,0,0,18,219,1,0,0,0,20,
  	230,1,0,0,0,22,242,1,0,0,0,24,262,1,0,0,0,26,269,1,0,0,0,28,284,1,0,0,
  	0,30,297,1,0,0,0,32,309,1,0,0,0,34,312,1,0,0,0,36,322,1,0,0,0,38,339,
  	1,0,0,0,40,344,1,0,0,0,42,352,1,0,0,0,44,355,1,0,0,0,46,374,1,0,0,0,48,
  	378,1,0,0,0,50,383,1,0,0,0,52,396,1,0,0,0,54,413,1,0,0,0,56,415,1,0,0,
  	0,58,427,1,0,0,0,60,433,1,0,0,0,62,443,1,0,0,0,64,452,1,0,0,0,66,467,
  	1,0,0,0,68,471,1,0,0,0,70,474,1,0,0,0,72,492,1,0,0,0,74,526,1,0,0,0,76,
  	528,1,0,0,0,78,532,1,0,0,0,80,536,1,0,0,0,82,547,1,0,0,0,84,565,1,0,0,
  	0,86,608,1,0,0,0,88,610,1,0,0,0,90,618,1,0,0,0,92,622,1,0,0,0,94,640,
  	1,0,0,0,96,656,1,0,0,0,98,660,1,0,0,0,100,673,1,0,0,0,102,683,1,0,0,0,
  	104,687,1,0,0,0,106,694,1,0,0,0,108,705,1,0,0,0,110,709,1,0,0,0,112,713,
  	1,0,0,0,114,738,1,0,0,0,116,740,1,0,0,0,118,760,1,0,0,0,120,765,1,0,0,
  	0,122,776,1,0,0,0,124,786,1,0,0,0,126,802,1,0,0,0,128,808,1,0,0,0,130,
  	814,1,0,0,0,132,832,1,0,0,0,134,849,1,0,0,0,136,862,1,0,0,0,138,140,3,
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
  	0,198,199,5,54,0,0,199,200,5,77,0,0,200,201,3,22,11,0,201,202,5,0,0,1,
  	202,13,1,0,0,0,203,204,5,54,0,0,204,205,5,77,0,0,205,206,5,10,0,0,206,
  	207,3,22,11,0,207,208,5,11,0,0,208,15,1,0,0,0,209,210,5,77,0,0,210,211,
  	5,35,0,0,211,212,5,10,0,0,212,213,3,18,9,0,213,214,5,11,0,0,214,215,5,
  	14,0,0,215,216,5,10,0,0,216,217,3,20,10,0,217,218,5,11,0,0,218,17,1,0,
  	0,0,219,224,3,124,62,0,220,221,5,17,0,0,221,223,3,124,62,0,222,220,1,
  	0,0,0,223,226,1,0,0,0,224,222,1,0,0,0,224,225,1,0,0,0,225,228,1,0,0,0,
  	226,224,1,0,0,0,227,229,5,17,0,0,228,227,1,0,0,0,228,229,1,0,0,0,229,
  	19,1,0,0,0,230,235,5,77,0,0,231,232,5,17,0,0,232,234,5,77,0,0,233,231,
  	1,0,0,0,234,237,1,0,0,0,235,233,1,0,0,0,235,236,1,0,0,0,236,239,1,0,0,
  	0,237,235,1,0,0,0,238,240,5,17,0,0,239,238,1,0,0,0,239,240,1,0,0,0,240,
  	21,1,0,0,0,241,243,3,34,17,0,242,241,1,0,0,0,242,243,1,0,0,0,243,247,
  	1,0,0,0,244,246,3,30,15,0,245,244,1,0,0,0,246,249,1,0,0,0,247,245,1,0,
  	0,0,247,248,1,0,0,0,248,253,1,0,0,0,249,247,1,0,0,0,250,252,3,40,20,0,
  	251,250,1,0,0,0,252,255,1,0,0,0,253,251,1,0,0,0,253,254,1,0,0,0,254,259,
  	1,0,0,0,255,253,1,0,0,0,256,258,3,42,21,0,257,256,1,0,0,0,258,261,1,0,
  	0,0,259,257,1,0,0,0,259,260,1,0,0,0,260,23,1,0,0,0,261,259,1,0,0,0,262,
  	263,7,0,0,0,263,264,5,77,0,0,264,265,5,10,0,0,265,266,3,26,13,0,266,267,
  	5,11,0,0,267,25,1,0,0,0,268,270,3,34,17,0,269,268,1,0,0,0,269,270,1,0,
  	0,0,270,274,1,0,0,0,271,273,3,28,14,0,272,271,1,0,0,0,273,276,1,0,0,0,
  	274,272,1,0,0,0,274,275,1,0,0,0,275,280,1,0,0,0,276,274,1,0,0,0,277,279,
  	3,48,24,0,278,277,1,0,0,0,279,282,1,0,0,0,280,278,1,0,0,0,280,281,1,0,
  	0,0,281,27,1,0,0,0,282,280,1,0,0,0,283,285,5,56,0,0,284,283,1,0,0,0,284,
  	285,1,0,0,0,285,287,1,0,0,0,286,288,5,58,0,0,287,286,1,0,0,0,287,288,
  	1,0,0,0,288,289,1,0,0,0,289,290,5,77,0,0,290,291,5,34,0,0,291,294,3,124,
  	62,0,292,293,5,35,0,0,293,295,3,84,42,0,294,292,1,0,0,0,294,295,1,0,0,
  	0,295,29,1,0,0,0,296,298,5,58,0,0,297,296,1,0,0,0,297,298,1,0,0,0,298,
  	299,1,0,0,0,299,301,5,77,0,0,300,302,5,41,0,0,301,300,1,0,0,0,301,302,
  	1,0,0,0,302,303,1,0,0,0,303,304,5,34,0,0,304,307,3,124,62,0,305,306,5,
  	35,0,0,306,308,3,84,42,0,307,305,1,0,0,0,307,308,1,0,0,0,308,31,1,0,0,
  	0,309,310,7,0,0,0,310,311,5,77,0,0,311,33,1,0,0,0,312,313,5,57,0,0,313,
  	314,5,34,0,0,314,317,5,77,0,0,315,316,5,17,0,0,316,318,5,77,0,0,317,315,
  	1,0,0,0,317,318,1,0,0,0,318,320,1,0,0,0,319,321,5,17,0,0,320,319,1,0,
  	0,0,320,321,1,0,0,0,321,35,1,0,0,0,322,323,5,77,0,0,323,335,5,8,0,0,324,
  	329,3,50,25,0,325,326,5,17,0,0,326,328,3,50,25,0,327,325,1,0,0,0,328,
  	331,1,0,0,0,329,327,1,0,0,0,329,330,1,0,0,0,330,333,1,0,0,0,331,329,1,
  	0,0,0,332,334,5,17,0,0,333,332,1,0,0,0,333,334,1,0,0,0,334,336,1,0,0,
  	0,335,324,1,0,0,0,335,336,1,0,0,0,336,337,1,0,0,0,337,338,5,9,0,0,338,
  	37,1,0,0,0,339,342,3,36,18,0,340,341,5,34,0,0,341,343,3,124,62,0,342,
  	340,1,0,0,0,342,343,1,0,0,0,343,39,1,0,0,0,344,346,3,36,18,0,345,347,
  	5,41,0,0,346,345,1,0,0,0,346,347,1,0,0,0,347,350,1,0,0,0,348,349,5,34,
  	0,0,349,351,3,124,62,0,350,348,1,0,0,0,350,351,1,0,0,0,351,41,1,0,0,0,
  	352,353,3,38,19,0,353,354,3,56,28,0,354,43,1,0,0,0,355,367,5,8,0,0,356,
  	361,3,52,26,0,357,358,5,17,0,0,358,360,3,52,26,0,359,357,1,0,0,0,360,
  	363,1,0,0,0,361,359,1,0,0,0,361,362,1,0,0,0,362,365,1,0,0,0,363,361,1,
  	0,0,0,364,366,5,17,0,0,365,364,1,0,0,0,365,366,1,0,0,0,366,368,1,0,0,
  	0,367,356,1,0,0,0,367,368,1,0,0,0,368,369,1,0,0,0,369,372,5,9,0,0,370,
  	371,5,34,0,0,371,373,3,124,62,0,372,370,1,0,0,0,372,373,1,0,0,0,373,45,
  	1,0,0,0,374,375,3,44,22,0,375,376,3,56,28,0,376,47,1,0,0,0,377,379,5,
  	56,0,0,378,377,1,0,0,0,378,379,1,0,0,0,379,380,1,0,0,0,380,381,3,38,19,
  	0,381,382,3,56,28,0,382,49,1,0,0,0,383,384,5,77,0,0,384,394,5,34,0,0,
  	385,395,3,130,65,0,386,388,3,124,62,0,387,389,5,18,0,0,388,387,1,0,0,
  	0,388,389,1,0,0,0,389,392,1,0,0,0,390,391,5,35,0,0,391,393,3,84,42,0,
  	392,390,1,0,0,0,392,393,1,0,0,0,393,395,1,0,0,0,394,385,1,0,0,0,394,386,
  	1,0,0,0,395,51,1,0,0,0,396,399,5,77,0,0,397,398,5,34,0,0,398,400,3,124,
  	62,0,399,397,1,0,0,0,399,400,1,0,0,0,400,53,1,0,0,0,401,414,3,58,29,0,
  	402,414,3,60,30,0,403,414,3,62,31,0,404,414,3,64,32,0,405,414,3,70,35,
  	0,406,414,3,74,37,0,407,414,5,67,0,0,408,414,3,76,38,0,409,414,3,78,39,
  	0,410,414,3,98,49,0,411,414,3,116,58,0,412,414,3,90,45,0,413,401,1,0,
  	0,0,413,402,1,0,0,0,413,403,1,0,0,0,413,404,1,0,0,0,413,405,1,0,0,0,413,
  	406,1,0,0,0,413,407,1,0,0,0,413,408,1,0,0,0,413,409,1,0,0,0,413,410,1,
  	0,0,0,413,411,1,0,0,0,413,412,1,0,0,0,414,55,1,0,0,0,415,419,5,10,0,0,
  	416,418,3,54,27,0,417,416,1,0,0,0,418,421,1,0,0,0,419,417,1,0,0,0,419,
  	420,1,0,0,0,420,422,1,0,0,0,421,419,1,0,0,0,422,423,5,11,0,0,423,57,1,
  	0,0,0,424,428,5,77,0,0,425,428,3,112,56,0,426,428,3,116,58,0,427,424,
  	1,0,0,0,427,425,1,0,0,0,427,426,1,0,0,0,428,429,1,0,0,0,429,430,3,136,
  	68,0,430,431,3,84,42,0,431,59,1,0,0,0,432,434,5,58,0,0,433,432,1,0,0,
  	0,433,434,1,0,0,0,434,435,1,0,0,0,435,436,5,77,0,0,436,437,5,34,0,0,437,
  	440,3,124,62,0,438,439,5,35,0,0,439,441,3,84,42,0,440,438,1,0,0,0,440,
  	441,1,0,0,0,441,61,1,0,0,0,442,444,5,58,0,0,443,442,1,0,0,0,443,444,1,
  	0,0,0,444,445,1,0,0,0,445,447,5,77,0,0,446,448,5,41,0,0,447,446,1,0,0,
  	0,447,448,1,0,0,0,448,449,1,0,0,0,449,450,5,35,0,0,450,451,3,84,42,0,
  	451,63,1,0,0,0,452,453,5,63,0,0,453,455,3,84,42,0,454,456,5,79,0,0,455,
  	454,1,0,0,0,455,456,1,0,0,0,456,457,1,0,0,0,457,461,3,56,28,0,458,460,
  	3,66,33,0,459,458,1,0,0,0,460,463,1,0,0,0,461,459,1,0,0,0,461,462,1,0,
  	0,0,462,465,1,0,0,0,463,461,1,0,0,0,464,466,3,68,34,0,465,464,1,0,0,0,
  	465,466,1,0,0,0,466,65,1,0,0,0,467,468,5,64,0,0,468,469,3,84,42,0,469,
  	470,3,56,28,0,470,67,1,0,0,0,471,472,5,64,0,0,472,473,3,56,28,0,473,69,
  	1,0,0,0,474,476,5,63,0,0,475,477,3,84,42,0,476,475,1,0,0,0,476,477,1,
  	0,0,0,477,478,1,0,0,0,478,482,5,10,0,0,479,481,3,72,36,0,480,479,1,0,
  	0,0,481,484,1,0,0,0,482,480,1,0,0,0,482,483,1,0,0,0,483,488,1,0,0,0,484,
  	482,1,0,0,0,485,486,5,64,0,0,486,487,5,34,0,0,487,489,3,56,28,0,488,485,
  	1,0,0,0,488,489,1,0,0,0,489,490,1,0,0,0,490,491,5,11,0,0,491,71,1,0,0,
  	0,492,493,3,84,42,0,493,494,5,34,0,0,494,495,3,56,28,0,495,73,1,0,0,0,
  	496,497,5,65,0,0,497,499,5,77,0,0,498,500,5,17,0,0,499,498,1,0,0,0,499,
  	500,1,0,0,0,500,501,1,0,0,0,501,502,5,72,0,0,502,503,3,122,61,0,503,504,
  	3,56,28,0,504,527,1,0,0,0,505,506,5,65,0,0,506,511,5,77,0,0,507,508,5,
  	17,0,0,508,510,5,77,0,0,509,507,1,0,0,0,510,513,1,0,0,0,511,509,1,0,0,
  	0,511,512,1,0,0,0,512,515,1,0,0,0,513,511,1,0,0,0,514,516,5,17,0,0,515,
  	514,1,0,0,0,515,516,1,0,0,0,516,517,1,0,0,0,517,518,5,72,0,0,518,519,
  	3,86,43,0,519,520,3,56,28,0,520,527,1,0,0,0,521,523,5,65,0,0,522,524,
  	5,77,0,0,523,522,1,0,0,0,523,524,1,0,0,0,524,525,1,0,0,0,525,527,3,56,
  	28,0,526,496,1,0,0,0,526,505,1,0,0,0,526,521,1,0,0,0,527,75,1,0,0,0,528,
  	530,5,66,0,0,529,531,5,79,0,0,530,529,1,0,0,0,530,531,1,0,0,0,531,77,
  	1,0,0,0,532,534,5,68,0,0,533,535,3,84,42,0,534,533,1,0,0,0,534,535,1,
  	0,0,0,535,79,1,0,0,0,536,537,5,59,0,0,537,538,5,77,0,0,538,542,5,10,0,
  	0,539,541,3,82,41,0,540,539,1,0,0,0,541,544,1,0,0,0,542,540,1,0,0,0,542,
  	543,1,0,0,0,543,545,1,0,0,0,544,542,1,0,0,0,545,546,5,11,0,0,546,81,1,
  	0,0,0,547,550,5,77,0,0,548,549,5,35,0,0,549,551,5,78,0,0,550,548,1,0,
  	0,0,550,551,1,0,0,0,551,83,1,0,0,0,552,553,6,42,-1,0,553,554,5,8,0,0,
  	554,555,3,84,42,0,555,558,5,9,0,0,556,557,5,14,0,0,557,559,3,124,62,0,
  	558,556,1,0,0,0,558,559,1,0,0,0,559,566,1,0,0,0,560,563,3,86,43,0,561,
  	562,5,14,0,0,562,564,3,124,62,0,563,561,1,0,0,0,563,564,1,0,0,0,564,566,
  	1,0,0,0,565,552,1,0,0,0,565,560,1,0,0,0,566,590,1,0,0,0,567,568,10,7,
  	0,0,568,569,7,1,0,0,569,589,3,84,42,8,570,571,10,6,0,0,571,572,7,2,0,
  	0,572,589,3,84,42,7,573,574,10,5,0,0,574,575,7,3,0,0,575,589,3,84,42,
  	6,576,577,10,4,0,0,577,578,7,4,0,0,578,589,3,84,42,5,579,580,10,3,0,0,
  	580,581,7,5,0,0,581,589,3,84,42,4,582,583,10,2,0,0,583,584,7,6,0,0,584,
  	589,3,84,42,3,585,586,10,1,0,0,586,587,7,7,0,0,587,589,3,84,42,2,588,
  	567,1,0,0,0,588,570,1,0,0,0,588,573,1,0,0,0,588,576,1,0,0,0,588,579,1,
  	0,0,0,588,582,1,0,0,0,588,585,1,0,0,0,589,592,1,0,0,0,590,588,1,0,0,0,
  	590,591,1,0,0,0,591,85,1,0,0,0,592,590,1,0,0,0,593,609,5,77,0,0,594,609,
  	5,52,0,0,595,609,5,53,0,0,596,609,5,76,0,0,597,609,3,88,44,0,598,609,
  	3,90,45,0,599,609,3,98,49,0,600,609,3,46,23,0,601,609,3,132,66,0,602,
  	609,3,104,52,0,603,609,3,110,55,0,604,609,3,112,56,0,605,609,3,116,58,
  	0,606,609,3,92,46,0,607,609,3,94,47,0,608,593,1,0,0,0,608,594,1,0,0,0,
  	608,595,1,0,0,0,608,596,1,0,0,0,608,597,1,0,0,0,608,598,1,0,0,0,608,599,
  	1,0,0,0,608,600,1,0,0,0,608,601,1,0,0,0,608,602,1,0,0,0,608,603,1,0,0,
  	0,608,604,1,0,0,0,608,605,1,0,0,0,608,606,1,0,0,0,608,607,1,0,0,0,609,
  	87,1,0,0,0,610,611,7,8,0,0,611,612,3,84,42,0,612,89,1,0,0,0,613,619,5,
  	77,0,0,614,619,3,112,56,0,615,619,3,116,58,0,616,619,3,98,49,0,617,619,
  	3,110,55,0,618,613,1,0,0,0,618,614,1,0,0,0,618,615,1,0,0,0,618,616,1,
  	0,0,0,618,617,1,0,0,0,619,620,1,0,0,0,620,621,7,9,0,0,621,91,1,0,0,0,
  	622,634,5,12,0,0,623,628,3,84,42,0,624,625,5,17,0,0,625,627,3,84,42,0,
  	626,624,1,0,0,0,627,630,1,0,0,0,628,626,1,0,0,0,628,629,1,0,0,0,629,632,
  	1,0,0,0,630,628,1,0,0,0,631,633,5,17,0,0,632,631,1,0,0,0,632,633,1,0,
  	0,0,633,635,1,0,0,0,634,623,1,0,0,0,634,635,1,0,0,0,635,636,1,0,0,0,636,
  	638,5,13,0,0,637,639,5,42,0,0,638,637,1,0,0,0,638,639,1,0,0,0,639,93,
  	1,0,0,0,640,652,5,10,0,0,641,646,3,96,48,0,642,643,5,17,0,0,643,645,3,
  	96,48,0,644,642,1,0,0,0,645,648,1,0,0,0,646,644,1,0,0,0,646,647,1,0,0,
  	0,647,650,1,0,0,0,648,646,1,0,0,0,649,651,5,17,0,0,650,649,1,0,0,0,650,
  	651,1,0,0,0,651,653,1,0,0,0,652,641,1,0,0,0,652,653,1,0,0,0,653,654,1,
  	0,0,0,654,655,5,11,0,0,655,95,1,0,0,0,656,657,3,84,42,0,657,658,5,34,
  	0,0,658,659,3,84,42,0,659,97,1,0,0,0,660,661,5,77,0,0,661,663,5,8,0,0,
  	662,664,3,100,50,0,663,662,1,0,0,0,663,664,1,0,0,0,664,666,1,0,0,0,665,
  	667,5,18,0,0,666,665,1,0,0,0,666,667,1,0,0,0,667,669,1,0,0,0,668,670,
  	5,17,0,0,669,668,1,0,0,0,669,670,1,0,0,0,670,671,1,0,0,0,671,672,5,9,
  	0,0,672,99,1,0,0,0,673,678,3,102,51,0,674,675,5,17,0,0,675,677,3,102,
  	51,0,676,674,1,0,0,0,677,680,1,0,0,0,678,676,1,0,0,0,678,679,1,0,0,0,
  	679,101,1,0,0,0,680,678,1,0,0,0,681,682,5,77,0,0,682,684,5,35,0,0,683,
  	681,1,0,0,0,683,684,1,0,0,0,684,685,1,0,0,0,685,686,3,84,42,0,686,103,
  	1,0,0,0,687,688,5,77,0,0,688,690,5,10,0,0,689,691,3,106,53,0,690,689,
  	1,0,0,0,690,691,1,0,0,0,691,692,1,0,0,0,692,693,5,11,0,0,693,105,1,0,
  	0,0,694,699,3,108,54,0,695,696,5,17,0,0,696,698,3,108,54,0,697,695,1,
  	0,0,0,698,701,1,0,0,0,699,697,1,0,0,0,699,700,1,0,0,0,700,703,1,0,0,0,
  	701,699,1,0,0,0,702,704,5,17,0,0,703,702,1,0,0,0,703,704,1,0,0,0,704,
  	107,1,0,0,0,705,706,5,77,0,0,706,707,5,35,0,0,707,708,3,84,42,0,708,109,
  	1,0,0,0,709,710,7,10,0,0,710,111,1,0,0,0,711,714,3,98,49,0,712,714,5,
  	77,0,0,713,711,1,0,0,0,713,712,1,0,0,0,714,716,1,0,0,0,715,717,3,114,
  	57,0,716,715,1,0,0,0,717,718,1,0,0,0,718,716,1,0,0,0,718,719,1,0,0,0,
  	719,113,1,0,0,0,720,721,5,12,0,0,721,723,3,84,42,0,722,724,5,34,0,0,723,
  	722,1,0,0,0,723,724,1,0,0,0,724,725,1,0,0,0,725,726,5,13,0,0,726,739,
  	1,0,0,0,727,728,5,12,0,0,728,729,5,34,0,0,729,730,3,84,42,0,730,731,5,
  	13,0,0,731,739,1,0,0,0,732,733,5,12,0,0,733,734,3,84,42,0,734,735,5,34,
  	0,0,735,736,3,84,42,0,736,737,5,13,0,0,737,739,1,0,0,0,738,720,1,0,0,
  	0,738,727,1,0,0,0,738,732,1,0,0,0,739,115,1,0,0,0,740,742,3,118,59,0,
  	741,743,5,41,0,0,742,741,1,0,0,0,742,743,1,0,0,0,743,749,1,0,0,0,744,
  	745,5,33,0,0,745,747,3,120,60,0,746,748,5,41,0,0,747,746,1,0,0,0,747,
  	748,1,0,0,0,748,750,1,0,0,0,749,744,1,0,0,0,750,751,1,0,0,0,751,749,1,
  	0,0,0,751,752,1,0,0,0,752,117,1,0,0,0,753,761,5,77,0,0,754,761,5,78,0,
  	0,755,761,5,53,0,0,756,761,5,52,0,0,757,761,3,98,49,0,758,761,3,104,52,
  	0,759,761,3,112,56,0,760,753,1,0,0,0,760,754,1,0,0,0,760,755,1,0,0,0,
  	760,756,1,0,0,0,760,757,1,0,0,0,760,758,1,0,0,0,760,759,1,0,0,0,761,119,
  	1,0,0,0,762,766,5,77,0,0,763,766,3,98,49,0,764,766,3,112,56,0,765,762,
  	1,0,0,0,765,763,1,0,0,0,765,764,1,0,0,0,766,121,1,0,0,0,767,768,3,84,
  	42,0,768,769,5,19,0,0,769,770,3,84,42,0,770,777,1,0,0,0,771,772,5,19,
  	0,0,772,777,3,84,42,0,773,774,3,84,42,0,774,775,5,19,0,0,775,777,1,0,
  	0,0,776,767,1,0,0,0,776,771,1,0,0,0,776,773,1,0,0,0,777,123,1,0,0,0,778,
  	779,6,62,-1,0,779,781,5,77,0,0,780,782,5,41,0,0,781,780,1,0,0,0,781,782,
  	1,0,0,0,782,787,1,0,0,0,783,787,5,53,0,0,784,787,3,126,63,0,785,787,3,
  	130,65,0,786,778,1,0,0,0,786,783,1,0,0,0,786,784,1,0,0,0,786,785,1,0,
  	0,0,787,799,1,0,0,0,788,790,10,3,0,0,789,791,3,128,64,0,790,789,1,0,0,
  	0,791,792,1,0,0,0,792,790,1,0,0,0,792,793,1,0,0,0,793,795,1,0,0,0,794,
  	796,5,42,0,0,795,794,1,0,0,0,795,796,1,0,0,0,796,798,1,0,0,0,797,788,
  	1,0,0,0,798,801,1,0,0,0,799,797,1,0,0,0,799,800,1,0,0,0,800,125,1,0,0,
  	0,801,799,1,0,0,0,802,803,5,10,0,0,803,804,3,124,62,0,804,805,5,34,0,
  	0,805,806,3,124,62,0,806,807,5,11,0,0,807,127,1,0,0,0,808,810,5,12,0,
  	0,809,811,3,84,42,0,810,809,1,0,0,0,810,811,1,0,0,0,811,812,1,0,0,0,812,
  	813,5,13,0,0,813,129,1,0,0,0,814,826,5,8,0,0,815,820,3,124,62,0,816,817,
  	5,17,0,0,817,819,3,124,62,0,818,816,1,0,0,0,819,822,1,0,0,0,820,818,1,
  	0,0,0,820,821,1,0,0,0,821,824,1,0,0,0,822,820,1,0,0,0,823,825,5,17,0,
  	0,824,823,1,0,0,0,824,825,1,0,0,0,825,827,1,0,0,0,826,815,1,0,0,0,826,
  	827,1,0,0,0,827,828,1,0,0,0,828,829,5,9,0,0,829,830,5,34,0,0,830,831,
  	3,124,62,0,831,131,1,0,0,0,832,833,7,11,0,0,833,845,5,8,0,0,834,839,3,
  	84,42,0,835,836,5,17,0,0,836,838,3,84,42,0,837,835,1,0,0,0,838,841,1,
  	0,0,0,839,837,1,0,0,0,839,840,1,0,0,0,840,843,1,0,0,0,841,839,1,0,0,0,
  	842,844,5,17,0,0,843,842,1,0,0,0,843,844,1,0,0,0,844,846,1,0,0,0,845,
  	834,1,0,0,0,845,846,1,0,0,0,846,847,1,0,0,0,847,848,5,9,0,0,848,133,1,
  	0,0,0,849,850,5,2,0,0,850,851,5,3,0,0,851,857,5,10,0,0,852,853,5,77,0,
  	0,853,854,5,34,0,0,854,856,3,124,62,0,855,852,1,0,0,0,856,859,1,0,0,0,
  	857,855,1,0,0,0,857,858,1,0,0,0,858,860,1,0,0,0,859,857,1,0,0,0,860,861,
  	5,11,0,0,861,135,1,0,0,0,862,863,7,12,0,0,863,137,1,0,0,0,112,139,144,
  	152,159,161,168,170,174,182,184,190,224,228,235,239,242,247,253,259,269,
  	274,280,284,287,294,297,301,307,317,320,329,333,335,342,346,350,361,365,
  	367,372,378,388,392,394,399,413,419,427,433,440,443,447,455,461,465,476,
  	482,488,499,511,515,523,526,530,534,542,550,558,563,565,588,590,608,618,
  	628,632,634,638,646,650,652,663,666,669,678,683,690,699,703,713,718,723,
  	738,742,747,751,760,765,776,781,786,792,795,799,810,820,824,826,839,843,
  	845,857
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

LogosParser::StatementsBlockContext* LogosParser::FuncImplContext::statementsBlock() {
  return getRuleContext<LogosParser::StatementsBlockContext>(0);
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
  enterRule(_localctx, 44, LogosParser::RuleAnonymosFuncSignature);
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
      anonymousParam();
      setState(361);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(357);
          match(LogosParser::COMMA);
          setState(358);
          anonymousParam(); 
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
    anonymosFuncSignature();
    setState(375);
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
  enterRule(_localctx, 50, LogosParser::RuleParam);
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
    match(LogosParser::IDENTIFIER);
    setState(384);
    match(LogosParser::COLON);
    setState(394);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      setState(385);
      funcType();
      break;
    }

    case 2: {
      setState(386);
      type(0);
      setState(388);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::TRIPLE_DOT) {
        setState(387);
        match(LogosParser::TRIPLE_DOT);
      }
      setState(392);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::EQUAL) {
        setState(390);
        match(LogosParser::EQUAL);
        setState(391);
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
  enterRule(_localctx, 52, LogosParser::RuleAnonymousParam);
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
    setState(396);
    match(LogosParser::IDENTIFIER);
    setState(399);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(397);
      match(LogosParser::COLON);
      setState(398);
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
    setState(413);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(401);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(402);
      explicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(403);
      implicitVarDec();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(404);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(405);
      patternMatching();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(406);
      loopStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(407);
      match(LogosParser::CONTINUE);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(408);
      breakStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(409);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(410);
      funcCall();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(411);
      selection();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(412);
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
    setState(415);
    match(LogosParser::LBRACE);
    setState(419);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 52) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 52)) & 115468355) != 0)) {
      setState(416);
      statement();
      setState(421);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(422);
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
    setState(427);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      setState(424);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(425);
      iterIndex();
      break;
    }

    case 3: {
      setState(426);
      selection();
      break;
    }

    default:
      break;
    }
    setState(429);
    assignemntOp();
    setState(430);
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
    setState(433);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(432);
      match(LogosParser::CONST);
    }
    setState(435);
    match(LogosParser::IDENTIFIER);
    setState(436);
    match(LogosParser::COLON);
    setState(437);
    type(0);
    setState(440);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(438);
      match(LogosParser::EQUAL);
      setState(439);
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
    setState(443);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(442);
      match(LogosParser::CONST);
    }
    setState(445);
    match(LogosParser::IDENTIFIER);
    setState(447);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(446);
      match(LogosParser::QUEST_MARK);
    }
    setState(449);
    match(LogosParser::EQUAL);
    setState(450);
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
    setState(452);
    match(LogosParser::IF);
    setState(453);
    expr(0);
    setState(455);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TAG) {
      setState(454);
      match(LogosParser::TAG);
    }
    setState(457);
    statementsBlock();
    setState(461);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(458);
        elseIfStatement(); 
      }
      setState(463);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
    }
    setState(465);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(464);
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
    setState(467);
    match(LogosParser::ELSE);
    setState(468);
    expr(0);
    setState(469);
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
    setState(471);
    match(LogosParser::ELSE);
    setState(472);
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
    setState(474);
    match(LogosParser::IF);
    setState(476);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      setState(475);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(478);
    match(LogosParser::LBRACE);
    setState(482);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(479);
      pattern();
      setState(484);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(488);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(485);
      match(LogosParser::ELSE);
      setState(486);
      match(LogosParser::COLON);
      setState(487);
      statementsBlock();
    }
    setState(490);
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
    setState(492);
    expr(0);
    setState(493);
    match(LogosParser::COLON);
    setState(494);
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
    setState(526);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(496);
      match(LogosParser::FOR);
      setState(497);
      match(LogosParser::IDENTIFIER);
      setState(499);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(498);
        match(LogosParser::COMMA);
      }
      setState(501);
      match(LogosParser::IN);
      setState(502);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(503);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(505);
      match(LogosParser::FOR);
      setState(506);
      match(LogosParser::IDENTIFIER);
      setState(511);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(507);
          match(LogosParser::COMMA);
          setState(508);
          match(LogosParser::IDENTIFIER); 
        }
        setState(513);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
      }
      setState(515);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(514);
        match(LogosParser::COMMA);
      }
      setState(517);
      match(LogosParser::IN);
      setState(518);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = unaryExpr();
      setState(519);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(521);
      match(LogosParser::FOR);
      setState(523);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::IDENTIFIER) {
        setState(522);
        match(LogosParser::IDENTIFIER);
      }
      setState(525);
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
    setState(528);
    match(LogosParser::BREAK);
    setState(530);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TAG) {
      setState(529);
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
    setState(532);
    match(LogosParser::RETURN);
    setState(534);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      setState(533);
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
    setState(536);
    match(LogosParser::ENUM);
    setState(537);
    match(LogosParser::IDENTIFIER);
    setState(538);
    match(LogosParser::LBRACE);
    setState(542);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(539);
      enumField();
      setState(544);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(545);
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
    setState(547);
    match(LogosParser::IDENTIFIER);
    setState(550);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(548);
      match(LogosParser::EQUAL);
      setState(549);
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
    setState(565);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      setState(553);
      match(LogosParser::LPAREN);
      setState(554);
      antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
      setState(555);
      match(LogosParser::RPAREN);
      setState(558);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
      case 1: {
        setState(556);
        match(LogosParser::ARROW);
        setState(557);
        type(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      setState(560);
      unaryExpr();
      setState(563);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
      case 1: {
        setState(561);
        match(LogosParser::ARROW);
        setState(562);
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
    setState(590);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(588);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(567);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(568);
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
          setState(569);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(570);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(571);
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
          setState(572);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(573);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(574);
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
          setState(575);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(576);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(577);
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
          setState(578);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(579);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(580);
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
          setState(581);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(582);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(583);
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
          setState(584);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(585);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(586);
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
          setState(587);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(592);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
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
    setState(608);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(593);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(594);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(595);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(596);
      match(LogosParser::NULL_);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(597);
      prefixExpr();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(598);
      postfixExpr();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(599);
      funcCall();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(600);
      anonnymosFunc();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(601);
      vector();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(602);
      constructor();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(603);
      constant();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(604);
      iterIndex();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(605);
      selection();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(606);
      arrayExpr();
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(607);
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
    setState(610);
    _la = _input->LA(1);
    if (!(_la == LogosParser::MINUS

    || _la == LogosParser::NOT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(611);
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
    setState(618);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      setState(613);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      setState(614);
      iterIndex();
      break;
    }

    case 3: {
      setState(615);
      selection();
      break;
    }

    case 4: {
      setState(616);
      funcCall();
      break;
    }

    case 5: {
      setState(617);
      constant();
      break;
    }

    default:
      break;
    }
    setState(620);
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
    setState(622);
    match(LogosParser::LBRACK);
    setState(634);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(623);
      expr(0);
      setState(628);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(624);
          match(LogosParser::COMMA);
          setState(625);
          expr(0); 
        }
        setState(630);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx);
      }
      setState(632);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(631);
        match(LogosParser::COMMA);
      }
    }
    setState(636);
    match(LogosParser::RBRACK);
    setState(638);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx)) {
    case 1: {
      setState(637);
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
    setState(640);
    match(LogosParser::LBRACE);
    setState(652);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(641);
      keyValue();
      setState(646);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(642);
          match(LogosParser::COMMA);
          setState(643);
          keyValue(); 
        }
        setState(648);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx);
      }
      setState(650);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(649);
        match(LogosParser::COMMA);
      }
    }
    setState(654);
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
    setState(656);
    antlrcpp::downCast<KeyValueContext *>(_localctx)->key = expr(0);
    setState(657);
    match(LogosParser::COLON);
    setState(658);
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
    setState(660);
    match(LogosParser::IDENTIFIER);
    setState(661);
    match(LogosParser::LPAREN);
    setState(663);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(662);
      funcArgList();
    }
    setState(666);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::TRIPLE_DOT) {
      setState(665);
      match(LogosParser::TRIPLE_DOT);
    }
    setState(669);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(668);
      match(LogosParser::COMMA);
    }
    setState(671);
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
    setState(673);
    funcArg();
    setState(678);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(674);
        match(LogosParser::COMMA);
        setState(675);
        funcArg(); 
      }
      setState(680);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx);
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
    setState(683);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
    case 1: {
      setState(681);
      match(LogosParser::IDENTIFIER);
      setState(682);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(685);
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
    setState(687);
    match(LogosParser::IDENTIFIER);
    setState(688);
    match(LogosParser::LBRACE);
    setState(690);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IDENTIFIER) {
      setState(689);
      constructorArgList();
    }
    setState(692);
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
    setState(694);
    constructorArg();
    setState(699);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(695);
        match(LogosParser::COMMA);
        setState(696);
        constructorArg(); 
      }
      setState(701);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx);
    }
    setState(703);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(702);
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
    setState(705);
    match(LogosParser::IDENTIFIER);
    setState(706);
    match(LogosParser::EQUAL);
    setState(707);
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
    setState(709);
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
    setState(713);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 89, _ctx)) {
    case 1: {
      setState(711);
      funcCall();
      break;
    }

    case 2: {
      setState(712);
      match(LogosParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    setState(716); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(715);
              index();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(718); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 90, _ctx);
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
    setState(738);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(720);
      match(LogosParser::LBRACK);
      setState(721);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(723);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COLON) {
        setState(722);
        match(LogosParser::COLON);
      }
      setState(725);
      match(LogosParser::RBRACK);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(727);
      match(LogosParser::LBRACK);
      setState(728);
      match(LogosParser::COLON);
      setState(729);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(730);
      match(LogosParser::RBRACK);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(732);
      match(LogosParser::LBRACK);
      setState(733);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(734);
      match(LogosParser::COLON);
      setState(735);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(736);
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
    setState(740);
    firstSelectionElement();
    setState(742);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(741);
      match(LogosParser::QUEST_MARK);
    }
    setState(749); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(744);
              match(LogosParser::DOT);
              setState(745);
              innerSelectionElement();
              setState(747);
              _errHandler->sync(this);

              switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 94, _ctx)) {
              case 1: {
                setState(746);
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
      setState(751); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 95, _ctx);
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
    setState(760);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(753);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(754);
      match(LogosParser::STRING);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(755);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(756);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(757);
      funcCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(758);
      constructor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(759);
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
    setState(765);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(762);
      match(LogosParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(763);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
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
    setState(776);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(767);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(768);
      match(LogosParser::DOUBLE_DOT);
      setState(769);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(771);
      match(LogosParser::DOUBLE_DOT);
      setState(772);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(773);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(774);
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
    setState(786);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::IDENTIFIER: {
        setState(779);
        match(LogosParser::IDENTIFIER);
        setState(781);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 99, _ctx)) {
        case 1: {
          setState(780);
          match(LogosParser::QUEST_MARK);
          break;
        }

        default:
          break;
        }
        break;
      }

      case LogosParser::SELF_CLASS: {
        setState(783);
        match(LogosParser::SELF_CLASS);
        break;
      }

      case LogosParser::LBRACE: {
        setState(784);
        mapType();
        break;
      }

      case LogosParser::LPAREN: {
        setState(785);
        funcType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(799);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 103, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        _localctx->baseType = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(788);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(790); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(789);
                  arraySize();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(792); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 101, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        setState(795);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx)) {
        case 1: {
          setState(794);
          match(LogosParser::EXCLA_MARK);
          break;
        }

        default:
          break;
        } 
      }
      setState(801);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 103, _ctx);
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
    setState(802);
    match(LogosParser::LBRACE);
    setState(803);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->key = type(0);
    setState(804);
    match(LogosParser::COLON);
    setState(805);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->value = type(0);
    setState(806);
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
    setState(808);
    match(LogosParser::LBRACK);
    setState(810);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(809);
      expr(0);
    }
    setState(812);
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
    setState(814);
    match(LogosParser::LPAREN);
    setState(826);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 9007199254742272) != 0) || _la == LogosParser::IDENTIFIER) {
      setState(815);
      type(0);
      setState(820);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(816);
          match(LogosParser::COMMA);
          setState(817);
          type(0); 
        }
        setState(822);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx);
      }
      setState(824);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(823);
        match(LogosParser::COMMA);
      }
    }
    setState(828);
    match(LogosParser::RPAREN);
    setState(829);
    match(LogosParser::COLON);
    setState(830);
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
    setState(832);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8070450532247928832) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(833);
    match(LogosParser::LPAREN);
    setState(845);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 8083961468568999168) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & 253) != 0)) {
      setState(834);
      expr(0);
      setState(839);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 108, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(835);
          match(LogosParser::COMMA);
          setState(836);
          expr(0); 
        }
        setState(841);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 108, _ctx);
      }
      setState(843);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(842);
        match(LogosParser::COMMA);
      }
    }
    setState(847);
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
    setState(849);
    match(LogosParser::T__1);
    setState(850);
    match(LogosParser::T__2);
    setState(851);
    match(LogosParser::LBRACE);
    setState(857);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::IDENTIFIER) {
      setState(852);
      match(LogosParser::IDENTIFIER);
      setState(853);
      match(LogosParser::COLON);
      setState(854);
      type(0);
      setState(859);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(860);
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
    setState(862);
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
