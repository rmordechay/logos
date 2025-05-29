
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
      "logosFile", "logosEnvFile", "logosAppFile", "mainFile", "objectFile", 
      "interfaceFile", "interface", "interfaceBody", "object", "objectBody", 
      "field", "objectDeclaration", "interfaceDeclaration", "objectImplements", 
      "funcSignature", "funcImpl", "anonnymosfuncSignature", "anonnymosFunc", 
      "methodImplementation", "funcBody", "param", "statement", "statementsBlock", 
      "assignment", "explicitVarDec", "implicitVarDec", "ifStatement", "elseIfStatement", 
      "elseStatement", "patternMatching", "pattern", "loopStatement", "breakStmt", 
      "returnStatement", "enumDeclaration", "enumField", "expr", "unaryExpr", 
      "array", "hashMap", "keyValue", "funcCall", "funcArgList", "funcArg", 
      "constructor", "constructorArgList", "constructorArg", "constant", 
      "iterIndex", "index", "selection", "firstSelectionElement", "innerSelectionElement", 
      "range", "type", "mapType", "arrayIndexType", "funcType", "vector", 
      "requireEnvVars"
    },
    std::vector<std::string>{
      "", "'require'", "'envs'", "'=='", "'!='", "'>='", "'<='", "'('", 
      "')'", "'{'", "'}'", "'['", "']'", "'->'", "'<'", "'>'", "','", "'...'", 
      "'..'", "'.'", "':'", "'='", "'-'", "'+'", "'*'", "'/'", "'#'", "'\\u003F'", 
      "'!'", "'%'", "'$'", "'&'", "'|'", "'^'", "'<<'", "'>>'", "'object'", 
      "'singleton'", "'self'", "'Self'", "'interface'", "'enum'", "'vec2'", 
      "'vec3'", "'vec4'", "'implements'", "'import'", "'if'", "'else'", 
      "'for'", "'break'", "'continue'", "'return'", "'pub'", "'const'", 
      "'and'", "'or'", "'not'", "'in'", "", "", "", "'null'"
    },
    std::vector<std::string>{
      "", "", "", "DOUBLE_EQUAL", "NOT_EQUAL", "GE", "LE", "LPAREN", "RPAREN", 
      "LBRACE", "RBRACE", "LBRACK", "RBRACK", "CAST", "LANGLE", "RANGLE", 
      "COMMA", "TRIPLE_DOT", "DOUBLE_DOT", "DOT", "COLON", "EQUAL", "MINUS", 
      "PLUS", "STAR", "SLASH", "HASH", "QUEST_MARK", "EXCLA_MARK", "PERCENT", 
      "DOLLAR", "AMPERSAND", "PIPE", "CARET", "DOUBLE_RANGLE", "DOUBLE_LANGLE", 
      "OBJECT", "SINGLETON", "SELF_INSTANCE", "SELF_CLASS", "INTERFACE", 
      "ENUM", "VEC2", "VEC3", "VEC4", "IMPLEMENTS", "IMPORT", "IF", "ELSE", 
      "FOR", "BREAK", "CONTINUE", "RETURN", "VISIBILITY", "CONST", "AND", 
      "OR", "NOT", "IN", "INTEGER", "FLOAT", "BOOL", "NULL", "CONST_NAME", 
      "TYPE", "VARIABLE", "STRING", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,69,742,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,1,0,1,0,1,0,3,0,124,8,0,1,1,1,1,5,1,
  	128,8,1,10,1,12,1,131,9,1,1,1,1,1,1,2,1,2,5,2,137,8,2,10,2,12,2,140,9,
  	2,1,2,3,2,143,8,2,1,2,1,2,1,3,1,3,1,3,5,3,150,8,3,10,3,12,3,153,9,3,1,
  	3,4,3,156,8,3,11,3,12,3,157,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,
  	6,1,6,1,6,1,6,1,6,1,6,1,7,5,7,177,8,7,10,7,12,7,180,9,7,1,7,4,7,183,8,
  	7,11,7,12,7,184,1,7,5,7,188,8,7,10,7,12,7,191,9,7,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,9,3,9,200,8,9,1,9,5,9,203,8,9,10,9,12,9,206,9,9,1,9,5,9,209,8,9,
  	10,9,12,9,212,9,9,1,10,3,10,215,8,10,1,10,3,10,218,8,10,1,10,1,10,1,10,
  	1,10,1,10,3,10,225,8,10,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,13,
  	1,13,1,13,1,13,1,13,3,13,240,8,13,1,13,3,13,243,8,13,1,14,1,14,1,14,1,
  	14,1,14,5,14,250,8,14,10,14,12,14,253,9,14,1,14,3,14,256,8,14,3,14,258,
  	8,14,1,14,1,14,1,14,3,14,263,8,14,1,15,1,15,1,15,1,16,1,16,1,16,1,16,
  	5,16,272,8,16,10,16,12,16,275,9,16,1,16,3,16,278,8,16,3,16,280,8,16,1,
  	16,1,16,1,16,3,16,285,8,16,1,17,1,17,1,17,1,18,3,18,291,8,18,1,18,1,18,
  	1,18,1,19,1,19,1,20,1,20,1,20,1,20,3,20,302,8,20,1,20,1,20,3,20,306,8,
  	20,1,20,1,20,3,20,310,8,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,
  	21,1,21,1,21,3,21,323,8,21,1,22,1,22,5,22,327,8,22,10,22,12,22,330,9,
  	22,1,22,1,22,1,23,1,23,1,23,3,23,337,8,23,1,23,1,23,1,23,1,23,1,24,1,
  	24,1,24,1,24,1,24,3,24,348,8,24,1,25,1,25,3,25,352,8,25,1,25,1,25,1,25,
  	1,26,1,26,1,26,1,26,5,26,361,8,26,10,26,12,26,364,9,26,1,26,3,26,367,
  	8,26,1,27,1,27,1,27,1,27,1,28,1,28,1,28,1,29,1,29,3,29,378,8,29,1,29,
  	1,29,5,29,382,8,29,10,29,12,29,385,9,29,1,29,1,29,1,29,3,29,390,8,29,
  	1,29,1,29,1,30,1,30,1,30,1,30,1,31,1,31,1,31,1,31,5,31,402,8,31,10,31,
  	12,31,405,9,31,1,31,3,31,408,8,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,
  	1,31,5,31,418,8,31,10,31,12,31,421,9,31,1,31,3,31,424,8,31,1,31,1,31,
  	1,31,1,31,1,31,1,31,3,31,432,8,31,1,31,3,31,435,8,31,1,32,1,32,1,33,1,
  	33,1,33,1,34,1,34,1,34,1,34,5,34,446,8,34,10,34,12,34,449,9,34,1,34,1,
  	34,1,35,1,35,1,35,3,35,456,8,35,1,36,1,36,1,36,1,36,1,36,1,36,3,36,464,
  	8,36,1,36,1,36,1,36,3,36,469,8,36,3,36,471,8,36,1,36,1,36,1,36,1,36,1,
  	36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,
  	36,1,36,1,36,5,36,494,8,36,10,36,12,36,497,9,36,1,37,1,37,1,37,1,37,1,
  	37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,1,37,3,37,513,8,37,1,38,1,
  	38,1,38,1,38,5,38,519,8,38,10,38,12,38,522,9,38,1,38,3,38,525,8,38,3,
  	38,527,8,38,1,38,1,38,1,39,1,39,1,39,1,39,5,39,535,8,39,10,39,12,39,538,
  	9,39,1,39,3,39,541,8,39,3,39,543,8,39,1,39,1,39,1,40,1,40,1,40,1,40,1,
  	41,1,41,1,41,3,41,554,8,41,1,41,1,41,1,42,1,42,1,42,5,42,561,8,42,10,
  	42,12,42,564,9,42,1,42,3,42,567,8,42,1,43,1,43,3,43,571,8,43,1,43,1,43,
  	1,44,1,44,1,44,3,44,578,8,44,1,44,1,44,1,45,1,45,1,45,5,45,585,8,45,10,
  	45,12,45,588,9,45,1,45,3,45,591,8,45,1,46,1,46,1,46,1,46,1,47,1,47,1,
  	48,1,48,3,48,601,8,48,1,48,4,48,604,8,48,11,48,12,48,605,1,49,1,49,1,
  	49,3,49,611,8,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,49,1,
  	49,1,49,1,49,3,49,626,8,49,1,50,1,50,1,50,4,50,631,8,50,11,50,12,50,632,
  	1,51,1,51,1,51,1,51,1,51,1,51,1,51,1,51,3,51,643,8,51,1,52,1,52,1,52,
  	3,52,648,8,52,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,1,53,3,53,659,8,
  	53,1,54,1,54,1,54,3,54,664,8,54,1,54,1,54,1,54,3,54,669,8,54,1,54,1,54,
  	4,54,673,8,54,11,54,12,54,674,5,54,677,8,54,10,54,12,54,680,9,54,1,55,
  	1,55,1,55,1,55,1,55,1,55,1,56,1,56,3,56,690,8,56,1,56,1,56,1,57,1,57,
  	1,57,1,57,5,57,698,8,57,10,57,12,57,701,9,57,1,57,3,57,704,8,57,3,57,
  	706,8,57,1,57,1,57,1,57,1,57,1,58,1,58,1,58,1,58,1,58,5,58,717,8,58,10,
  	58,12,58,720,9,58,1,58,3,58,723,8,58,3,58,725,8,58,1,58,1,58,1,59,1,59,
  	1,59,1,59,1,59,1,59,5,59,735,8,59,10,59,12,59,738,9,59,1,59,1,59,1,59,
  	0,2,72,108,60,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,
  	40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,
  	86,88,90,92,94,96,98,100,102,104,106,108,110,112,114,116,118,0,10,1,0,
  	36,37,1,0,24,25,1,0,22,23,2,0,5,6,14,15,1,0,3,4,1,0,55,56,1,0,31,33,1,
  	0,34,35,2,0,59,61,66,66,1,0,42,44,811,0,123,1,0,0,0,2,129,1,0,0,0,4,138,
  	1,0,0,0,6,151,1,0,0,0,8,161,1,0,0,0,10,165,1,0,0,0,12,169,1,0,0,0,14,
  	178,1,0,0,0,16,192,1,0,0,0,18,199,1,0,0,0,20,214,1,0,0,0,22,226,1,0,0,
  	0,24,230,1,0,0,0,26,234,1,0,0,0,28,244,1,0,0,0,30,264,1,0,0,0,32,267,
  	1,0,0,0,34,286,1,0,0,0,36,290,1,0,0,0,38,295,1,0,0,0,40,309,1,0,0,0,42,
  	322,1,0,0,0,44,324,1,0,0,0,46,336,1,0,0,0,48,342,1,0,0,0,50,349,1,0,0,
  	0,52,356,1,0,0,0,54,368,1,0,0,0,56,372,1,0,0,0,58,375,1,0,0,0,60,393,
  	1,0,0,0,62,434,1,0,0,0,64,436,1,0,0,0,66,438,1,0,0,0,68,441,1,0,0,0,70,
  	452,1,0,0,0,72,470,1,0,0,0,74,512,1,0,0,0,76,514,1,0,0,0,78,530,1,0,0,
  	0,80,546,1,0,0,0,82,550,1,0,0,0,84,557,1,0,0,0,86,570,1,0,0,0,88,574,
  	1,0,0,0,90,581,1,0,0,0,92,592,1,0,0,0,94,596,1,0,0,0,96,600,1,0,0,0,98,
  	625,1,0,0,0,100,627,1,0,0,0,102,642,1,0,0,0,104,647,1,0,0,0,106,658,1,
  	0,0,0,108,668,1,0,0,0,110,681,1,0,0,0,112,687,1,0,0,0,114,693,1,0,0,0,
  	116,711,1,0,0,0,118,728,1,0,0,0,120,124,3,6,3,0,121,124,3,8,4,0,122,124,
  	3,10,5,0,123,120,1,0,0,0,123,121,1,0,0,0,123,122,1,0,0,0,124,1,1,0,0,
  	0,125,128,3,50,25,0,126,128,3,48,24,0,127,125,1,0,0,0,127,126,1,0,0,0,
  	128,131,1,0,0,0,129,127,1,0,0,0,129,130,1,0,0,0,130,132,1,0,0,0,131,129,
  	1,0,0,0,132,133,5,0,0,1,133,3,1,0,0,0,134,137,3,50,25,0,135,137,3,48,
  	24,0,136,134,1,0,0,0,136,135,1,0,0,0,137,140,1,0,0,0,138,136,1,0,0,0,
  	138,139,1,0,0,0,139,142,1,0,0,0,140,138,1,0,0,0,141,143,3,118,59,0,142,
  	141,1,0,0,0,142,143,1,0,0,0,143,144,1,0,0,0,144,145,5,0,0,1,145,5,1,0,
  	0,0,146,150,3,16,8,0,147,150,3,68,34,0,148,150,3,12,6,0,149,146,1,0,0,
  	0,149,147,1,0,0,0,149,148,1,0,0,0,150,153,1,0,0,0,151,149,1,0,0,0,151,
  	152,1,0,0,0,152,155,1,0,0,0,153,151,1,0,0,0,154,156,3,30,15,0,155,154,
  	1,0,0,0,156,157,1,0,0,0,157,155,1,0,0,0,157,158,1,0,0,0,158,159,1,0,0,
  	0,159,160,5,0,0,1,160,7,1,0,0,0,161,162,3,22,11,0,162,163,3,18,9,0,163,
  	164,5,0,0,1,164,9,1,0,0,0,165,166,3,24,12,0,166,167,3,14,7,0,167,168,
  	5,0,0,1,168,11,1,0,0,0,169,170,5,40,0,0,170,171,5,64,0,0,171,172,5,9,
  	0,0,172,173,3,14,7,0,173,174,5,10,0,0,174,13,1,0,0,0,175,177,3,48,24,
  	0,176,175,1,0,0,0,177,180,1,0,0,0,178,176,1,0,0,0,178,179,1,0,0,0,179,
  	182,1,0,0,0,180,178,1,0,0,0,181,183,3,28,14,0,182,181,1,0,0,0,183,184,
  	1,0,0,0,184,182,1,0,0,0,184,185,1,0,0,0,185,189,1,0,0,0,186,188,3,30,
  	15,0,187,186,1,0,0,0,188,191,1,0,0,0,189,187,1,0,0,0,189,190,1,0,0,0,
  	190,15,1,0,0,0,191,189,1,0,0,0,192,193,7,0,0,0,193,194,5,64,0,0,194,195,
  	5,9,0,0,195,196,3,18,9,0,196,197,5,10,0,0,197,17,1,0,0,0,198,200,3,26,
  	13,0,199,198,1,0,0,0,199,200,1,0,0,0,200,204,1,0,0,0,201,203,3,20,10,
  	0,202,201,1,0,0,0,203,206,1,0,0,0,204,202,1,0,0,0,204,205,1,0,0,0,205,
  	210,1,0,0,0,206,204,1,0,0,0,207,209,3,36,18,0,208,207,1,0,0,0,209,212,
  	1,0,0,0,210,208,1,0,0,0,210,211,1,0,0,0,211,19,1,0,0,0,212,210,1,0,0,
  	0,213,215,5,53,0,0,214,213,1,0,0,0,214,215,1,0,0,0,215,217,1,0,0,0,216,
  	218,5,54,0,0,217,216,1,0,0,0,217,218,1,0,0,0,218,219,1,0,0,0,219,220,
  	5,65,0,0,220,221,5,20,0,0,221,224,3,108,54,0,222,223,5,21,0,0,223,225,
  	3,72,36,0,224,222,1,0,0,0,224,225,1,0,0,0,225,21,1,0,0,0,226,227,7,0,
  	0,0,227,228,5,20,0,0,228,229,5,64,0,0,229,23,1,0,0,0,230,231,5,40,0,0,
  	231,232,5,20,0,0,232,233,5,64,0,0,233,25,1,0,0,0,234,235,5,45,0,0,235,
  	236,5,20,0,0,236,239,5,64,0,0,237,238,5,16,0,0,238,240,5,64,0,0,239,237,
  	1,0,0,0,239,240,1,0,0,0,240,242,1,0,0,0,241,243,5,16,0,0,242,241,1,0,
  	0,0,242,243,1,0,0,0,243,27,1,0,0,0,244,245,5,65,0,0,245,257,5,7,0,0,246,
  	251,3,40,20,0,247,248,5,16,0,0,248,250,3,40,20,0,249,247,1,0,0,0,250,
  	253,1,0,0,0,251,249,1,0,0,0,251,252,1,0,0,0,252,255,1,0,0,0,253,251,1,
  	0,0,0,254,256,5,16,0,0,255,254,1,0,0,0,255,256,1,0,0,0,256,258,1,0,0,
  	0,257,246,1,0,0,0,257,258,1,0,0,0,258,259,1,0,0,0,259,262,5,8,0,0,260,
  	261,5,20,0,0,261,263,3,108,54,0,262,260,1,0,0,0,262,263,1,0,0,0,263,29,
  	1,0,0,0,264,265,3,28,14,0,265,266,3,38,19,0,266,31,1,0,0,0,267,279,5,
  	7,0,0,268,273,3,40,20,0,269,270,5,16,0,0,270,272,3,40,20,0,271,269,1,
  	0,0,0,272,275,1,0,0,0,273,271,1,0,0,0,273,274,1,0,0,0,274,277,1,0,0,0,
  	275,273,1,0,0,0,276,278,5,16,0,0,277,276,1,0,0,0,277,278,1,0,0,0,278,
  	280,1,0,0,0,279,268,1,0,0,0,279,280,1,0,0,0,280,281,1,0,0,0,281,284,5,
  	8,0,0,282,283,5,20,0,0,283,285,3,108,54,0,284,282,1,0,0,0,284,285,1,0,
  	0,0,285,33,1,0,0,0,286,287,3,32,16,0,287,288,3,38,19,0,288,35,1,0,0,0,
  	289,291,5,53,0,0,290,289,1,0,0,0,290,291,1,0,0,0,291,292,1,0,0,0,292,
  	293,3,28,14,0,293,294,3,38,19,0,294,37,1,0,0,0,295,296,3,44,22,0,296,
  	39,1,0,0,0,297,298,5,65,0,0,298,299,5,20,0,0,299,301,3,108,54,0,300,302,
  	5,17,0,0,301,300,1,0,0,0,301,302,1,0,0,0,302,305,1,0,0,0,303,304,5,21,
  	0,0,304,306,3,72,36,0,305,303,1,0,0,0,305,306,1,0,0,0,306,310,1,0,0,0,
  	307,308,5,65,0,0,308,310,3,114,57,0,309,297,1,0,0,0,309,307,1,0,0,0,310,
  	41,1,0,0,0,311,323,3,46,23,0,312,323,3,48,24,0,313,323,3,50,25,0,314,
  	323,3,52,26,0,315,323,3,58,29,0,316,323,3,62,31,0,317,323,5,51,0,0,318,
  	323,3,64,32,0,319,323,3,66,33,0,320,323,3,82,41,0,321,323,3,100,50,0,
  	322,311,1,0,0,0,322,312,1,0,0,0,322,313,1,0,0,0,322,314,1,0,0,0,322,315,
  	1,0,0,0,322,316,1,0,0,0,322,317,1,0,0,0,322,318,1,0,0,0,322,319,1,0,0,
  	0,322,320,1,0,0,0,322,321,1,0,0,0,323,43,1,0,0,0,324,328,5,9,0,0,325,
  	327,3,42,21,0,326,325,1,0,0,0,327,330,1,0,0,0,328,326,1,0,0,0,328,329,
  	1,0,0,0,329,331,1,0,0,0,330,328,1,0,0,0,331,332,5,10,0,0,332,45,1,0,0,
  	0,333,337,5,65,0,0,334,337,3,96,48,0,335,337,3,100,50,0,336,333,1,0,0,
  	0,336,334,1,0,0,0,336,335,1,0,0,0,337,338,1,0,0,0,338,339,5,20,0,0,339,
  	340,5,21,0,0,340,341,3,72,36,0,341,47,1,0,0,0,342,343,5,65,0,0,343,344,
  	5,20,0,0,344,347,3,108,54,0,345,346,5,21,0,0,346,348,3,72,36,0,347,345,
  	1,0,0,0,347,348,1,0,0,0,348,49,1,0,0,0,349,351,5,65,0,0,350,352,5,27,
  	0,0,351,350,1,0,0,0,351,352,1,0,0,0,352,353,1,0,0,0,353,354,5,21,0,0,
  	354,355,3,72,36,0,355,51,1,0,0,0,356,357,5,47,0,0,357,358,3,72,36,0,358,
  	362,3,44,22,0,359,361,3,54,27,0,360,359,1,0,0,0,361,364,1,0,0,0,362,360,
  	1,0,0,0,362,363,1,0,0,0,363,366,1,0,0,0,364,362,1,0,0,0,365,367,3,56,
  	28,0,366,365,1,0,0,0,366,367,1,0,0,0,367,53,1,0,0,0,368,369,5,48,0,0,
  	369,370,3,72,36,0,370,371,3,44,22,0,371,55,1,0,0,0,372,373,5,48,0,0,373,
  	374,3,44,22,0,374,57,1,0,0,0,375,377,5,47,0,0,376,378,3,72,36,0,377,376,
  	1,0,0,0,377,378,1,0,0,0,378,379,1,0,0,0,379,383,5,9,0,0,380,382,3,60,
  	30,0,381,380,1,0,0,0,382,385,1,0,0,0,383,381,1,0,0,0,383,384,1,0,0,0,
  	384,389,1,0,0,0,385,383,1,0,0,0,386,387,5,48,0,0,387,388,5,20,0,0,388,
  	390,3,44,22,0,389,386,1,0,0,0,389,390,1,0,0,0,390,391,1,0,0,0,391,392,
  	5,10,0,0,392,59,1,0,0,0,393,394,3,72,36,0,394,395,5,20,0,0,395,396,3,
  	44,22,0,396,61,1,0,0,0,397,398,5,49,0,0,398,403,5,65,0,0,399,400,5,16,
  	0,0,400,402,5,65,0,0,401,399,1,0,0,0,402,405,1,0,0,0,403,401,1,0,0,0,
  	403,404,1,0,0,0,404,407,1,0,0,0,405,403,1,0,0,0,406,408,5,16,0,0,407,
  	406,1,0,0,0,407,408,1,0,0,0,408,409,1,0,0,0,409,410,5,58,0,0,410,411,
  	3,106,53,0,411,412,3,44,22,0,412,435,1,0,0,0,413,414,5,49,0,0,414,419,
  	5,65,0,0,415,416,5,16,0,0,416,418,5,65,0,0,417,415,1,0,0,0,418,421,1,
  	0,0,0,419,417,1,0,0,0,419,420,1,0,0,0,420,423,1,0,0,0,421,419,1,0,0,0,
  	422,424,5,16,0,0,423,422,1,0,0,0,423,424,1,0,0,0,424,425,1,0,0,0,425,
  	426,5,58,0,0,426,427,3,74,37,0,427,428,3,44,22,0,428,435,1,0,0,0,429,
  	431,5,49,0,0,430,432,5,65,0,0,431,430,1,0,0,0,431,432,1,0,0,0,432,433,
  	1,0,0,0,433,435,3,44,22,0,434,397,1,0,0,0,434,413,1,0,0,0,434,429,1,0,
  	0,0,435,63,1,0,0,0,436,437,5,50,0,0,437,65,1,0,0,0,438,439,5,52,0,0,439,
  	440,3,72,36,0,440,67,1,0,0,0,441,442,5,41,0,0,442,443,5,64,0,0,443,447,
  	5,9,0,0,444,446,3,70,35,0,445,444,1,0,0,0,446,449,1,0,0,0,447,445,1,0,
  	0,0,447,448,1,0,0,0,448,450,1,0,0,0,449,447,1,0,0,0,450,451,5,10,0,0,
  	451,69,1,0,0,0,452,455,5,63,0,0,453,454,5,21,0,0,454,456,5,66,0,0,455,
  	453,1,0,0,0,455,456,1,0,0,0,456,71,1,0,0,0,457,458,6,36,-1,0,458,459,
  	5,7,0,0,459,460,3,72,36,0,460,463,5,8,0,0,461,462,5,13,0,0,462,464,3,
  	108,54,0,463,461,1,0,0,0,463,464,1,0,0,0,464,471,1,0,0,0,465,468,3,74,
  	37,0,466,467,5,13,0,0,467,469,3,108,54,0,468,466,1,0,0,0,468,469,1,0,
  	0,0,469,471,1,0,0,0,470,457,1,0,0,0,470,465,1,0,0,0,471,495,1,0,0,0,472,
  	473,10,7,0,0,473,474,7,1,0,0,474,494,3,72,36,8,475,476,10,6,0,0,476,477,
  	7,2,0,0,477,494,3,72,36,7,478,479,10,5,0,0,479,480,7,3,0,0,480,494,3,
  	72,36,6,481,482,10,4,0,0,482,483,7,4,0,0,483,494,3,72,36,5,484,485,10,
  	3,0,0,485,486,7,5,0,0,486,494,3,72,36,4,487,488,10,2,0,0,488,489,7,6,
  	0,0,489,494,3,72,36,3,490,491,10,1,0,0,491,492,7,7,0,0,492,494,3,72,36,
  	2,493,472,1,0,0,0,493,475,1,0,0,0,493,478,1,0,0,0,493,481,1,0,0,0,493,
  	484,1,0,0,0,493,487,1,0,0,0,493,490,1,0,0,0,494,497,1,0,0,0,495,493,1,
  	0,0,0,495,496,1,0,0,0,496,73,1,0,0,0,497,495,1,0,0,0,498,513,5,65,0,0,
  	499,513,5,63,0,0,500,513,5,38,0,0,501,513,5,39,0,0,502,513,5,62,0,0,503,
  	513,3,82,41,0,504,513,3,34,17,0,505,513,3,116,58,0,506,513,3,88,44,0,
  	507,513,3,94,47,0,508,513,3,76,38,0,509,513,3,78,39,0,510,513,3,96,48,
  	0,511,513,3,100,50,0,512,498,1,0,0,0,512,499,1,0,0,0,512,500,1,0,0,0,
  	512,501,1,0,0,0,512,502,1,0,0,0,512,503,1,0,0,0,512,504,1,0,0,0,512,505,
  	1,0,0,0,512,506,1,0,0,0,512,507,1,0,0,0,512,508,1,0,0,0,512,509,1,0,0,
  	0,512,510,1,0,0,0,512,511,1,0,0,0,513,75,1,0,0,0,514,526,5,11,0,0,515,
  	520,3,72,36,0,516,517,5,16,0,0,517,519,3,72,36,0,518,516,1,0,0,0,519,
  	522,1,0,0,0,520,518,1,0,0,0,520,521,1,0,0,0,521,524,1,0,0,0,522,520,1,
  	0,0,0,523,525,5,16,0,0,524,523,1,0,0,0,524,525,1,0,0,0,525,527,1,0,0,
  	0,526,515,1,0,0,0,526,527,1,0,0,0,527,528,1,0,0,0,528,529,5,12,0,0,529,
  	77,1,0,0,0,530,542,5,9,0,0,531,536,3,80,40,0,532,533,5,16,0,0,533,535,
  	3,80,40,0,534,532,1,0,0,0,535,538,1,0,0,0,536,534,1,0,0,0,536,537,1,0,
  	0,0,537,540,1,0,0,0,538,536,1,0,0,0,539,541,5,16,0,0,540,539,1,0,0,0,
  	540,541,1,0,0,0,541,543,1,0,0,0,542,531,1,0,0,0,542,543,1,0,0,0,543,544,
  	1,0,0,0,544,545,5,10,0,0,545,79,1,0,0,0,546,547,3,72,36,0,547,548,5,20,
  	0,0,548,549,3,72,36,0,549,81,1,0,0,0,550,551,5,65,0,0,551,553,5,7,0,0,
  	552,554,3,84,42,0,553,552,1,0,0,0,553,554,1,0,0,0,554,555,1,0,0,0,555,
  	556,5,8,0,0,556,83,1,0,0,0,557,562,3,86,43,0,558,559,5,16,0,0,559,561,
  	3,86,43,0,560,558,1,0,0,0,561,564,1,0,0,0,562,560,1,0,0,0,562,563,1,0,
  	0,0,563,566,1,0,0,0,564,562,1,0,0,0,565,567,5,16,0,0,566,565,1,0,0,0,
  	566,567,1,0,0,0,567,85,1,0,0,0,568,569,5,65,0,0,569,571,5,21,0,0,570,
  	568,1,0,0,0,570,571,1,0,0,0,571,572,1,0,0,0,572,573,3,72,36,0,573,87,
  	1,0,0,0,574,575,5,64,0,0,575,577,5,7,0,0,576,578,3,90,45,0,577,576,1,
  	0,0,0,577,578,1,0,0,0,578,579,1,0,0,0,579,580,5,8,0,0,580,89,1,0,0,0,
  	581,586,3,92,46,0,582,583,5,16,0,0,583,585,3,92,46,0,584,582,1,0,0,0,
  	585,588,1,0,0,0,586,584,1,0,0,0,586,587,1,0,0,0,587,590,1,0,0,0,588,586,
  	1,0,0,0,589,591,5,16,0,0,590,589,1,0,0,0,590,591,1,0,0,0,591,91,1,0,0,
  	0,592,593,5,65,0,0,593,594,5,21,0,0,594,595,3,72,36,0,595,93,1,0,0,0,
  	596,597,7,8,0,0,597,95,1,0,0,0,598,601,3,82,41,0,599,601,5,65,0,0,600,
  	598,1,0,0,0,600,599,1,0,0,0,601,603,1,0,0,0,602,604,3,98,49,0,603,602,
  	1,0,0,0,604,605,1,0,0,0,605,603,1,0,0,0,605,606,1,0,0,0,606,97,1,0,0,
  	0,607,608,5,11,0,0,608,610,3,72,36,0,609,611,5,20,0,0,610,609,1,0,0,0,
  	610,611,1,0,0,0,611,612,1,0,0,0,612,613,5,12,0,0,613,626,1,0,0,0,614,
  	615,5,11,0,0,615,616,5,20,0,0,616,617,3,72,36,0,617,618,5,12,0,0,618,
  	626,1,0,0,0,619,620,5,11,0,0,620,621,3,72,36,0,621,622,5,20,0,0,622,623,
  	3,72,36,0,623,624,5,12,0,0,624,626,1,0,0,0,625,607,1,0,0,0,625,614,1,
  	0,0,0,625,619,1,0,0,0,626,99,1,0,0,0,627,630,3,102,51,0,628,629,5,19,
  	0,0,629,631,3,104,52,0,630,628,1,0,0,0,631,632,1,0,0,0,632,630,1,0,0,
  	0,632,633,1,0,0,0,633,101,1,0,0,0,634,643,5,65,0,0,635,643,5,64,0,0,636,
  	643,5,66,0,0,637,643,5,39,0,0,638,643,5,38,0,0,639,643,3,82,41,0,640,
  	643,3,88,44,0,641,643,3,96,48,0,642,634,1,0,0,0,642,635,1,0,0,0,642,636,
  	1,0,0,0,642,637,1,0,0,0,642,638,1,0,0,0,642,639,1,0,0,0,642,640,1,0,0,
  	0,642,641,1,0,0,0,643,103,1,0,0,0,644,648,5,65,0,0,645,648,3,82,41,0,
  	646,648,3,96,48,0,647,644,1,0,0,0,647,645,1,0,0,0,647,646,1,0,0,0,648,
  	105,1,0,0,0,649,650,3,72,36,0,650,651,5,18,0,0,651,652,3,72,36,0,652,
  	659,1,0,0,0,653,654,5,18,0,0,654,659,3,72,36,0,655,656,3,72,36,0,656,
  	657,5,18,0,0,657,659,1,0,0,0,658,649,1,0,0,0,658,653,1,0,0,0,658,655,
  	1,0,0,0,659,107,1,0,0,0,660,661,6,54,-1,0,661,663,5,64,0,0,662,664,5,
  	27,0,0,663,662,1,0,0,0,663,664,1,0,0,0,664,669,1,0,0,0,665,669,5,39,0,
  	0,666,669,3,110,55,0,667,669,3,114,57,0,668,660,1,0,0,0,668,665,1,0,0,
  	0,668,666,1,0,0,0,668,667,1,0,0,0,669,678,1,0,0,0,670,672,10,3,0,0,671,
  	673,3,112,56,0,672,671,1,0,0,0,673,674,1,0,0,0,674,672,1,0,0,0,674,675,
  	1,0,0,0,675,677,1,0,0,0,676,670,1,0,0,0,677,680,1,0,0,0,678,676,1,0,0,
  	0,678,679,1,0,0,0,679,109,1,0,0,0,680,678,1,0,0,0,681,682,5,9,0,0,682,
  	683,3,108,54,0,683,684,5,20,0,0,684,685,3,108,54,0,685,686,5,10,0,0,686,
  	111,1,0,0,0,687,689,5,11,0,0,688,690,3,72,36,0,689,688,1,0,0,0,689,690,
  	1,0,0,0,690,691,1,0,0,0,691,692,5,12,0,0,692,113,1,0,0,0,693,705,5,7,
  	0,0,694,699,3,108,54,0,695,696,5,16,0,0,696,698,3,108,54,0,697,695,1,
  	0,0,0,698,701,1,0,0,0,699,697,1,0,0,0,699,700,1,0,0,0,700,703,1,0,0,0,
  	701,699,1,0,0,0,702,704,5,16,0,0,703,702,1,0,0,0,703,704,1,0,0,0,704,
  	706,1,0,0,0,705,694,1,0,0,0,705,706,1,0,0,0,706,707,1,0,0,0,707,708,5,
  	8,0,0,708,709,5,20,0,0,709,710,3,108,54,0,710,115,1,0,0,0,711,712,7,9,
  	0,0,712,724,5,7,0,0,713,718,3,72,36,0,714,715,5,16,0,0,715,717,3,72,36,
  	0,716,714,1,0,0,0,717,720,1,0,0,0,718,716,1,0,0,0,718,719,1,0,0,0,719,
  	722,1,0,0,0,720,718,1,0,0,0,721,723,5,16,0,0,722,721,1,0,0,0,722,723,
  	1,0,0,0,723,725,1,0,0,0,724,713,1,0,0,0,724,725,1,0,0,0,725,726,1,0,0,
  	0,726,727,5,8,0,0,727,117,1,0,0,0,728,729,5,1,0,0,729,730,5,2,0,0,730,
  	736,5,9,0,0,731,732,5,65,0,0,732,733,5,20,0,0,733,735,3,108,54,0,734,
  	731,1,0,0,0,735,738,1,0,0,0,736,734,1,0,0,0,736,737,1,0,0,0,737,739,1,
  	0,0,0,738,736,1,0,0,0,739,740,5,10,0,0,740,119,1,0,0,0,89,123,127,129,
  	136,138,142,149,151,157,178,184,189,199,204,210,214,217,224,239,242,251,
  	255,257,262,273,277,279,284,290,301,305,309,322,328,336,347,351,362,366,
  	377,383,389,403,407,419,423,431,434,447,455,463,468,470,493,495,512,520,
  	524,526,536,540,542,553,562,566,570,577,586,590,600,605,610,625,632,642,
  	647,658,663,668,674,678,689,699,703,705,718,722,724,736
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
    setState(123);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(120);
      mainFile();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(121);
      objectFile();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(122);
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
  enterRule(_localctx, 2, LogosParser::RuleLogosEnvFile);
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
    setState(129);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(127);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
      case 1: {
        setState(125);
        implicitVarDec();
        break;
      }

      case 2: {
        setState(126);
        explicitVarDec();
        break;
      }

      default:
        break;
      }
      setState(131);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(132);
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
  enterRule(_localctx, 4, LogosParser::RuleLogosAppFile);
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
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(136);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(134);
        implicitVarDec();
        break;
      }

      case 2: {
        setState(135);
        explicitVarDec();
        break;
      }

      default:
        break;
      }
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(142);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::T__0) {
      setState(141);
      requireEnvVars();
    }
    setState(144);
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
  enterRule(_localctx, 6, LogosParser::RuleMainFile);
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
    setState(151);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3504693313536) != 0)) {
      setState(149);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case LogosParser::OBJECT:
        case LogosParser::SINGLETON: {
          setState(146);
          object();
          break;
        }

        case LogosParser::ENUM: {
          setState(147);
          enumDeclaration();
          break;
        }

        case LogosParser::INTERFACE: {
          setState(148);
          interface();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(153);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(155); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(154);
      funcImpl();
      setState(157); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(159);
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
  enterRule(_localctx, 8, LogosParser::RuleObjectFile);

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
    objectDeclaration();
    setState(162);
    objectBody();
    setState(163);
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
  enterRule(_localctx, 10, LogosParser::RuleInterfaceFile);

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
    interfaceDeclaration();
    setState(166);
    interfaceBody();
    setState(167);
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

tree::TerminalNode* LogosParser::InterfaceContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
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
  enterRule(_localctx, 12, LogosParser::RuleInterface);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(169);
    match(LogosParser::INTERFACE);
    setState(170);
    match(LogosParser::TYPE);
    setState(171);
    match(LogosParser::LBRACE);
    setState(172);
    interfaceBody();
    setState(173);
    match(LogosParser::RBRACE);
   
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

std::vector<LogosParser::ExplicitVarDecContext *> LogosParser::InterfaceBodyContext::explicitVarDec() {
  return getRuleContexts<LogosParser::ExplicitVarDecContext>();
}

LogosParser::ExplicitVarDecContext* LogosParser::InterfaceBodyContext::explicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(i);
}

std::vector<LogosParser::FuncSignatureContext *> LogosParser::InterfaceBodyContext::funcSignature() {
  return getRuleContexts<LogosParser::FuncSignatureContext>();
}

LogosParser::FuncSignatureContext* LogosParser::InterfaceBodyContext::funcSignature(size_t i) {
  return getRuleContext<LogosParser::FuncSignatureContext>(i);
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
  enterRule(_localctx, 14, LogosParser::RuleInterfaceBody);
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
    setState(178);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(175);
        explicitVarDec(); 
      }
      setState(180);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
    setState(182); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(181);
              funcSignature();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(184); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(189);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(186);
      funcImpl();
      setState(191);
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

tree::TerminalNode* LogosParser::ObjectContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
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
  enterRule(_localctx, 16, LogosParser::RuleObject);
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
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(193);
    match(LogosParser::TYPE);
    setState(194);
    match(LogosParser::LBRACE);
    setState(195);
    objectBody();
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
  enterRule(_localctx, 18, LogosParser::RuleObjectBody);
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
    setState(199);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(198);
      objectImplements();
    }
    setState(204);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(201);
        field(); 
      }
      setState(206);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VISIBILITY

    || _la == LogosParser::VARIABLE) {
      setState(207);
      methodImplementation();
      setState(212);
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

tree::TerminalNode* LogosParser::FieldContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
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
  enterRule(_localctx, 20, LogosParser::RuleField);
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
    setState(214);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(213);
      match(LogosParser::VISIBILITY);
    }
    setState(217);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(216);
      match(LogosParser::CONST);
    }
    setState(219);
    match(LogosParser::VARIABLE);
    setState(220);
    match(LogosParser::COLON);
    setState(221);
    type(0);
    setState(224);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(222);
      match(LogosParser::EQUAL);
      setState(223);
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

tree::TerminalNode* LogosParser::ObjectDeclarationContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::ObjectDeclarationContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
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
  enterRule(_localctx, 22, LogosParser::RuleObjectDeclaration);
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
    setState(226);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(227);
    match(LogosParser::COLON);
    setState(228);
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
  enterRule(_localctx, 24, LogosParser::RuleInterfaceDeclaration);

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
    match(LogosParser::INTERFACE);
    setState(231);
    match(LogosParser::COLON);
    setState(232);
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

std::vector<tree::TerminalNode *> LogosParser::ObjectImplementsContext::TYPE() {
  return getTokens(LogosParser::TYPE);
}

tree::TerminalNode* LogosParser::ObjectImplementsContext::TYPE(size_t i) {
  return getToken(LogosParser::TYPE, i);
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
  enterRule(_localctx, 26, LogosParser::RuleObjectImplements);
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
    setState(234);
    match(LogosParser::IMPLEMENTS);
    setState(235);
    match(LogosParser::COLON);
    setState(236);
    match(LogosParser::TYPE);
    setState(239);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(237);
      match(LogosParser::COMMA);
      setState(238);
      match(LogosParser::TYPE);
      break;
    }

    default:
      break;
    }
    setState(242);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(241);
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

tree::TerminalNode* LogosParser::FuncSignatureContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
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
  enterRule(_localctx, 28, LogosParser::RuleFuncSignature);
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
    setState(244);
    match(LogosParser::VARIABLE);
    setState(245);
    match(LogosParser::LPAREN);
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(246);
      param();
      setState(251);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(247);
          match(LogosParser::COMMA);
          setState(248);
          param(); 
        }
        setState(253);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
      }
      setState(255);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(254);
        match(LogosParser::COMMA);
      }
    }
    setState(259);
    match(LogosParser::RPAREN);
    setState(262);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(260);
      match(LogosParser::COLON);
      setState(261);
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
  enterRule(_localctx, 30, LogosParser::RuleFuncImpl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(264);
    funcSignature();
    setState(265);
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
  enterRule(_localctx, 32, LogosParser::RuleAnonnymosfuncSignature);
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
    match(LogosParser::LPAREN);
    setState(279);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(268);
      param();
      setState(273);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(269);
          match(LogosParser::COMMA);
          setState(270);
          param(); 
        }
        setState(275);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
      }
      setState(277);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(276);
        match(LogosParser::COMMA);
      }
    }
    setState(281);
    match(LogosParser::RPAREN);
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(282);
      match(LogosParser::COLON);
      setState(283);
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
  enterRule(_localctx, 34, LogosParser::RuleAnonnymosFunc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(286);
    anonnymosfuncSignature();
    setState(287);
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
  enterRule(_localctx, 36, LogosParser::RuleMethodImplementation);
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
    setState(290);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(289);
      match(LogosParser::VISIBILITY);
    }
    setState(292);
    funcSignature();
    setState(293);
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
  enterRule(_localctx, 38, LogosParser::RuleFuncBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
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

tree::TerminalNode* LogosParser::ParamContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
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
  enterRule(_localctx, 40, LogosParser::RuleParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(309);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(297);
      match(LogosParser::VARIABLE);
      setState(298);
      match(LogosParser::COLON);
      setState(299);
      type(0);
      setState(301);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::TRIPLE_DOT) {
        setState(300);
        match(LogosParser::TRIPLE_DOT);
      }
      setState(305);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::EQUAL) {
        setState(303);
        match(LogosParser::EQUAL);
        setState(304);
        expr(0);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(307);
      match(LogosParser::VARIABLE);
      setState(308);
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


size_t LogosParser::StatementContext::getRuleIndex() const {
  return LogosParser::RuleStatement;
}


LogosParser::StatementContext* LogosParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 42, LogosParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(322);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(311);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(312);
      explicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(313);
      implicitVarDec();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(314);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(315);
      patternMatching();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(316);
      loopStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(317);
      match(LogosParser::CONTINUE);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(318);
      breakStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(319);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(320);
      funcCall();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(321);
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
    setState(324);
    match(LogosParser::LBRACE);
    setState(328);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 38) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 38)) & 469793283) != 0)) {
      setState(325);
      statement();
      setState(330);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(331);
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
  enterRule(_localctx, 46, LogosParser::RuleAssignment);

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
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(333);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      setState(334);
      iterIndex();
      break;
    }

    case 3: {
      setState(335);
      selection();
      break;
    }

    default:
      break;
    }
    setState(338);
    match(LogosParser::COLON);
    setState(339);
    match(LogosParser::EQUAL);
    setState(340);
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
  enterRule(_localctx, 48, LogosParser::RuleExplicitVarDec);
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
    match(LogosParser::VARIABLE);
    setState(343);
    match(LogosParser::COLON);
    setState(344);
    type(0);
    setState(347);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(345);
      match(LogosParser::EQUAL);
      setState(346);
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

tree::TerminalNode* LogosParser::ImplicitVarDecContext::QUEST_MARK() {
  return getToken(LogosParser::QUEST_MARK, 0);
}


size_t LogosParser::ImplicitVarDecContext::getRuleIndex() const {
  return LogosParser::RuleImplicitVarDec;
}


LogosParser::ImplicitVarDecContext* LogosParser::implicitVarDec() {
  ImplicitVarDecContext *_localctx = _tracker.createInstance<ImplicitVarDecContext>(_ctx, getState());
  enterRule(_localctx, 50, LogosParser::RuleImplicitVarDec);
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
    setState(349);
    match(LogosParser::VARIABLE);
    setState(351);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(350);
      match(LogosParser::QUEST_MARK);
    }
    setState(353);
    match(LogosParser::EQUAL);
    setState(354);
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


size_t LogosParser::IfStatementContext::getRuleIndex() const {
  return LogosParser::RuleIfStatement;
}


LogosParser::IfStatementContext* LogosParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 52, LogosParser::RuleIfStatement);
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
    setState(356);
    match(LogosParser::IF);
    setState(357);
    expr(0);
    setState(358);
    statementsBlock();
    setState(362);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(359);
        elseIfStatement(); 
      }
      setState(364);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    }
    setState(366);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(365);
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
  enterRule(_localctx, 54, LogosParser::RuleElseIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(368);
    match(LogosParser::ELSE);
    setState(369);
    expr(0);
    setState(370);
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
  enterRule(_localctx, 56, LogosParser::RuleElseStatement);

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
    match(LogosParser::ELSE);
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
  enterRule(_localctx, 58, LogosParser::RulePatternMatching);
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
    setState(375);
    match(LogosParser::IF);
    setState(377);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      setState(376);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(379);
    match(LogosParser::LBRACE);
    setState(383);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 1148418151940096021) != 0)) {
      setState(380);
      pattern();
      setState(385);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(389);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(386);
      match(LogosParser::ELSE);
      setState(387);
      match(LogosParser::COLON);
      setState(388);
      statementsBlock();
    }
    setState(391);
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
  enterRule(_localctx, 60, LogosParser::RulePattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(393);
    expr(0);
    setState(394);
    match(LogosParser::COLON);
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
  enterRule(_localctx, 62, LogosParser::RuleLoopStatement);
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
    setState(434);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(397);
      match(LogosParser::FOR);
      setState(398);
      match(LogosParser::VARIABLE);
      setState(403);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(399);
          match(LogosParser::COMMA);
          setState(400);
          match(LogosParser::VARIABLE); 
        }
        setState(405);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx);
      }
      setState(407);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(406);
        match(LogosParser::COMMA);
      }
      setState(409);
      match(LogosParser::IN);
      setState(410);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(411);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(413);
      match(LogosParser::FOR);
      setState(414);
      match(LogosParser::VARIABLE);
      setState(419);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(415);
          match(LogosParser::COMMA);
          setState(416);
          match(LogosParser::VARIABLE); 
        }
        setState(421);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
      }
      setState(423);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(422);
        match(LogosParser::COMMA);
      }
      setState(425);
      match(LogosParser::IN);
      setState(426);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = unaryExpr();
      setState(427);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(429);
      match(LogosParser::FOR);
      setState(431);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::VARIABLE) {
        setState(430);
        match(LogosParser::VARIABLE);
      }
      setState(433);
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


size_t LogosParser::BreakStmtContext::getRuleIndex() const {
  return LogosParser::RuleBreakStmt;
}


LogosParser::BreakStmtContext* LogosParser::breakStmt() {
  BreakStmtContext *_localctx = _tracker.createInstance<BreakStmtContext>(_ctx, getState());
  enterRule(_localctx, 64, LogosParser::RuleBreakStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(436);
    match(LogosParser::BREAK);
   
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
  enterRule(_localctx, 66, LogosParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(438);
    match(LogosParser::RETURN);
    setState(439);
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
  enterRule(_localctx, 68, LogosParser::RuleEnumDeclaration);
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
    match(LogosParser::ENUM);
    setState(442);
    match(LogosParser::TYPE);
    setState(443);
    match(LogosParser::LBRACE);
    setState(447);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST_NAME) {
      setState(444);
      enumField();
      setState(449);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(450);
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

tree::TerminalNode* LogosParser::EnumFieldContext::CONST_NAME() {
  return getToken(LogosParser::CONST_NAME, 0);
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
  enterRule(_localctx, 70, LogosParser::RuleEnumField);
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
    setState(452);
    match(LogosParser::CONST_NAME);
    setState(455);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(453);
      match(LogosParser::EQUAL);
      setState(454);
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

tree::TerminalNode* LogosParser::ExprContext::CAST() {
  return getToken(LogosParser::CAST, 0);
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
  size_t startState = 72;
  enterRecursionRule(_localctx, 72, LogosParser::RuleExpr, precedence);

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
    setState(470);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx)) {
    case 1: {
      setState(458);
      match(LogosParser::LPAREN);
      setState(459);
      antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
      setState(460);
      match(LogosParser::RPAREN);
      setState(463);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
      case 1: {
        setState(461);
        match(LogosParser::CAST);
        setState(462);
        type(0);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      setState(465);
      unaryExpr();
      setState(468);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
      case 1: {
        setState(466);
        match(LogosParser::CAST);
        setState(467);
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
    setState(495);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(493);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(472);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(473);
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
          setState(474);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(475);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(476);
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
          setState(477);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(478);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(479);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 49248) != 0))) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(480);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(481);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(482);
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
          setState(483);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(484);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(485);
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
          setState(486);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(487);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(488);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 15032385536) != 0))) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(489);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(490);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(491);
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
          setState(492);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(497);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
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

tree::TerminalNode* LogosParser::UnaryExprContext::CONST_NAME() {
  return getToken(LogosParser::CONST_NAME, 0);
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

LogosParser::ArrayContext* LogosParser::UnaryExprContext::array() {
  return getRuleContext<LogosParser::ArrayContext>(0);
}

LogosParser::HashMapContext* LogosParser::UnaryExprContext::hashMap() {
  return getRuleContext<LogosParser::HashMapContext>(0);
}

LogosParser::IterIndexContext* LogosParser::UnaryExprContext::iterIndex() {
  return getRuleContext<LogosParser::IterIndexContext>(0);
}

LogosParser::SelectionContext* LogosParser::UnaryExprContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}


size_t LogosParser::UnaryExprContext::getRuleIndex() const {
  return LogosParser::RuleUnaryExpr;
}


LogosParser::UnaryExprContext* LogosParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 74, LogosParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(512);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(498);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(499);
      match(LogosParser::CONST_NAME);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(500);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(501);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(502);
      match(LogosParser::NULL_);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(503);
      funcCall();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(504);
      anonnymosFunc();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(505);
      vector();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(506);
      constructor();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(507);
      constant();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(508);
      array();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(509);
      hashMap();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(510);
      iterIndex();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(511);
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

tree::TerminalNode* LogosParser::ArrayContext::RBRACK() {
  return getToken(LogosParser::RBRACK, 0);
}

std::vector<LogosParser::ExprContext *> LogosParser::ArrayContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::ArrayContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
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
  enterRule(_localctx, 76, LogosParser::RuleArray);
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
    setState(514);
    match(LogosParser::LBRACK);
    setState(526);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 1148418151940096021) != 0)) {
      setState(515);
      expr(0);
      setState(520);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(516);
          match(LogosParser::COMMA);
          setState(517);
          expr(0); 
        }
        setState(522);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
      }
      setState(524);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(523);
        match(LogosParser::COMMA);
      }
    }
    setState(528);
    match(LogosParser::RBRACK);
   
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
  enterRule(_localctx, 78, LogosParser::RuleHashMap);
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
    setState(530);
    match(LogosParser::LBRACE);
    setState(542);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 1148418151940096021) != 0)) {
      setState(531);
      keyValue();
      setState(536);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(532);
          match(LogosParser::COMMA);
          setState(533);
          keyValue(); 
        }
        setState(538);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
      }
      setState(540);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(539);
        match(LogosParser::COMMA);
      }
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
  enterRule(_localctx, 80, LogosParser::RuleKeyValue);

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
    antlrcpp::downCast<KeyValueContext *>(_localctx)->key = expr(0);
    setState(547);
    match(LogosParser::COLON);
    setState(548);
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
  enterRule(_localctx, 82, LogosParser::RuleFuncCall);
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
    setState(550);
    match(LogosParser::VARIABLE);
    setState(551);
    match(LogosParser::LPAREN);
    setState(553);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 1148418151940096021) != 0)) {
      setState(552);
      funcArgList();
    }
    setState(555);
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
  enterRule(_localctx, 84, LogosParser::RuleFuncArgList);
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
    setState(557);
    funcArg();
    setState(562);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(558);
        match(LogosParser::COMMA);
        setState(559);
        funcArg(); 
      }
      setState(564);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx);
    }
    setState(566);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(565);
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
  enterRule(_localctx, 86, LogosParser::RuleFuncArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(570);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx)) {
    case 1: {
      setState(568);
      match(LogosParser::VARIABLE);
      setState(569);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(572);
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

tree::TerminalNode* LogosParser::ConstructorContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::ConstructorContext::LPAREN() {
  return getToken(LogosParser::LPAREN, 0);
}

tree::TerminalNode* LogosParser::ConstructorContext::RPAREN() {
  return getToken(LogosParser::RPAREN, 0);
}

LogosParser::ConstructorArgListContext* LogosParser::ConstructorContext::constructorArgList() {
  return getRuleContext<LogosParser::ConstructorArgListContext>(0);
}


size_t LogosParser::ConstructorContext::getRuleIndex() const {
  return LogosParser::RuleConstructor;
}


LogosParser::ConstructorContext* LogosParser::constructor() {
  ConstructorContext *_localctx = _tracker.createInstance<ConstructorContext>(_ctx, getState());
  enterRule(_localctx, 88, LogosParser::RuleConstructor);
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
    setState(574);
    match(LogosParser::TYPE);
    setState(575);
    match(LogosParser::LPAREN);
    setState(577);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(576);
      constructorArgList();
    }
    setState(579);
    match(LogosParser::RPAREN);
   
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
  enterRule(_localctx, 90, LogosParser::RuleConstructorArgList);
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
    setState(581);
    constructorArg();
    setState(586);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(582);
        match(LogosParser::COMMA);
        setState(583);
        constructorArg(); 
      }
      setState(588);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx);
    }
    setState(590);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(589);
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

tree::TerminalNode* LogosParser::ConstructorArgContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
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
  enterRule(_localctx, 92, LogosParser::RuleConstructorArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(592);
    match(LogosParser::VARIABLE);
    setState(593);
    match(LogosParser::EQUAL);
    setState(594);
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
  enterRule(_localctx, 94, LogosParser::RuleConstant);
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
    setState(596);
    _la = _input->LA(1);
    if (!(((((_la - 59) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 59)) & 135) != 0))) {
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

tree::TerminalNode* LogosParser::IterIndexContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
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
  enterRule(_localctx, 96, LogosParser::RuleIterIndex);

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
    setState(600);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      setState(598);
      funcCall();
      break;
    }

    case 2: {
      setState(599);
      match(LogosParser::VARIABLE);
      break;
    }

    default:
      break;
    }
    setState(603); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(602);
              index();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(605); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx);
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
  enterRule(_localctx, 98, LogosParser::RuleIndex);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(625);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(607);
      match(LogosParser::LBRACK);
      setState(608);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(610);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COLON) {
        setState(609);
        match(LogosParser::COLON);
      }
      setState(612);
      match(LogosParser::RBRACK);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(614);
      match(LogosParser::LBRACK);
      setState(615);
      match(LogosParser::COLON);
      setState(616);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(617);
      match(LogosParser::RBRACK);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(619);
      match(LogosParser::LBRACK);
      setState(620);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(621);
      match(LogosParser::COLON);
      setState(622);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(623);
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
  enterRule(_localctx, 100, LogosParser::RuleSelection);

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
    firstSelectionElement();
    setState(630); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(628);
              match(LogosParser::DOT);
              setState(629);
              innerSelectionElement();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(632); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
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
  enterRule(_localctx, 102, LogosParser::RuleFirstSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(642);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(634);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(635);
      match(LogosParser::TYPE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(636);
      match(LogosParser::STRING);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(637);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(638);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(639);
      funcCall();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(640);
      constructor();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(641);
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

tree::TerminalNode* LogosParser::InnerSelectionElementContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
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
  enterRule(_localctx, 104, LogosParser::RuleInnerSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(647);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(644);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(645);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(646);
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
  enterRule(_localctx, 106, LogosParser::RuleRange);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(658);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(649);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(650);
      match(LogosParser::DOUBLE_DOT);
      setState(651);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(653);
      match(LogosParser::DOUBLE_DOT);
      setState(654);
      antlrcpp::downCast<RangeContext *>(_localctx)->end = expr(0);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(655);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
      setState(656);
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

tree::TerminalNode* LogosParser::TypeContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
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

std::vector<LogosParser::ArrayIndexTypeContext *> LogosParser::TypeContext::arrayIndexType() {
  return getRuleContexts<LogosParser::ArrayIndexTypeContext>();
}

LogosParser::ArrayIndexTypeContext* LogosParser::TypeContext::arrayIndexType(size_t i) {
  return getRuleContext<LogosParser::ArrayIndexTypeContext>(i);
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
  size_t startState = 108;
  enterRecursionRule(_localctx, 108, LogosParser::RuleType, precedence);

    

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
    setState(668);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::TYPE: {
        setState(661);
        match(LogosParser::TYPE);
        setState(663);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx)) {
        case 1: {
          setState(662);
          match(LogosParser::QUEST_MARK);
          break;
        }

        default:
          break;
        }
        break;
      }

      case LogosParser::SELF_CLASS: {
        setState(665);
        match(LogosParser::SELF_CLASS);
        break;
      }

      case LogosParser::LBRACE: {
        setState(666);
        mapType();
        break;
      }

      case LogosParser::LPAREN: {
        setState(667);
        funcType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(678);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TypeContext>(parentContext, parentState);
        _localctx->baseType = previousContext;
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(670);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(672); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(671);
                  arrayIndexType();
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(674); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER); 
      }
      setState(680);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx);
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
  enterRule(_localctx, 110, LogosParser::RuleMapType);

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
    match(LogosParser::LBRACE);
    setState(682);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->key = type(0);
    setState(683);
    match(LogosParser::COLON);
    setState(684);
    antlrcpp::downCast<MapTypeContext *>(_localctx)->value = type(0);
    setState(685);
    match(LogosParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayIndexTypeContext ------------------------------------------------------------------

LogosParser::ArrayIndexTypeContext::ArrayIndexTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ArrayIndexTypeContext::LBRACK() {
  return getToken(LogosParser::LBRACK, 0);
}

tree::TerminalNode* LogosParser::ArrayIndexTypeContext::RBRACK() {
  return getToken(LogosParser::RBRACK, 0);
}

LogosParser::ExprContext* LogosParser::ArrayIndexTypeContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::ArrayIndexTypeContext::getRuleIndex() const {
  return LogosParser::RuleArrayIndexType;
}


LogosParser::ArrayIndexTypeContext* LogosParser::arrayIndexType() {
  ArrayIndexTypeContext *_localctx = _tracker.createInstance<ArrayIndexTypeContext>(_ctx, getState());
  enterRule(_localctx, 112, LogosParser::RuleArrayIndexType);
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
    match(LogosParser::LBRACK);
    setState(689);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 1148418151940096021) != 0)) {
      setState(688);
      expr(0);
    }
    setState(691);
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
  enterRule(_localctx, 114, LogosParser::RuleFuncType);
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
    setState(693);
    match(LogosParser::LPAREN);
    setState(705);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 144115192370823173) != 0)) {
      setState(694);
      type(0);
      setState(699);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(695);
          match(LogosParser::COMMA);
          setState(696);
          type(0); 
        }
        setState(701);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
      }
      setState(703);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(702);
        match(LogosParser::COMMA);
      }
    }
    setState(707);
    match(LogosParser::RPAREN);
    setState(708);
    match(LogosParser::COLON);
    setState(709);
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
  enterRule(_localctx, 116, LogosParser::RuleVector);
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
    setState(711);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30786325577728) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(712);
    match(LogosParser::LPAREN);
    setState(724);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 1148418151940096021) != 0)) {
      setState(713);
      expr(0);
      setState(718);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(714);
          match(LogosParser::COMMA);
          setState(715);
          expr(0); 
        }
        setState(720);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx);
      }
      setState(722);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(721);
        match(LogosParser::COMMA);
      }
    }
    setState(726);
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

std::vector<tree::TerminalNode *> LogosParser::RequireEnvVarsContext::VARIABLE() {
  return getTokens(LogosParser::VARIABLE);
}

tree::TerminalNode* LogosParser::RequireEnvVarsContext::VARIABLE(size_t i) {
  return getToken(LogosParser::VARIABLE, i);
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
  enterRule(_localctx, 118, LogosParser::RuleRequireEnvVars);
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
    setState(728);
    match(LogosParser::T__0);
    setState(729);
    match(LogosParser::T__1);
    setState(730);
    match(LogosParser::LBRACE);
    setState(736);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(731);
      match(LogosParser::VARIABLE);
      setState(732);
      match(LogosParser::COLON);
      setState(733);
      type(0);
      setState(738);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(739);
    match(LogosParser::RBRACE);
   
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
    case 36: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);
    case 54: return typeSempred(antlrcpp::downCast<TypeContext *>(context), predicateIndex);

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
