
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
      "funcSignature", "funcImplementation", "methodImplementation", "funcBody", 
      "paramList", "param", "statement", "statementsBlock", "assignment", 
      "explicitVarDec", "implicitVarDec", "ifStatement", "elseIfStatement", 
      "elseStatement", "patternMatching", "pattern", "loopStatement", "breakStmt", 
      "returnStatement", "enumDeclaration", "enumField", "expr", "unaryExpr", 
      "array", "hashMap", "keyValue", "funcCall", "funcArgList", "funcArg", 
      "constructor", "constructorArgList", "constructorArg", "constant", 
      "arrayIndex", "index", "selection", "firstSelectionElement", "innerSelectionElement", 
      "range", "type", "vector", "requireEnvVars"
    },
    std::vector<std::string>{
      "", "'require'", "'envs'", "'=='", "'!='", "'>='", "'<='", "'('", 
      "')'", "'{'", "'}'", "'['", "']'", "'->'", "'<'", "'>'", "','", "'..'", 
      "'.'", "':'", "'='", "'-'", "'+'", "'*'", "'/'", "'#'", "'\\u003F'", 
      "'!'", "'%'", "'$'", "'&'", "'|'", "'^'", "'<<'", "'>>'", "'object'", 
      "'singleton'", "'self'", "'Self'", "'interface'", "'enum'", "'vec2'", 
      "'vec3'", "'vec4'", "'implements'", "'import'", "'if'", "'else'", 
      "'for'", "'break'", "'continue'", "'return'", "'pub'", "'const'", 
      "'and'", "'or'", "'not'", "'in'", "", "", "", "'null'"
    },
    std::vector<std::string>{
      "", "", "", "DOUBLE_EQUAL", "NOT_EQUAL", "GE", "LE", "LPAREN", "RPAREN", 
      "LBRACE", "RBRACE", "LBRACK", "RBRACK", "CAST", "LANGLE", "RANGLE", 
      "COMMA", "DOUBLE_DOT", "DOT", "COLON", "EQUAL", "MINUS", "PLUS", "STAR", 
      "SLASH", "HASH", "QUEST_MARK", "EXCLA_MARK", "PERCENT", "DOLLAR", 
      "AMPERSAND", "PIPE", "CARET", "DOUBLE_RANGLE", "DOUBLE_LANGLE", "OBJECT", 
      "SINGLETON", "SELF_INSTANCE", "SELF_CLASS", "INTERFACE", "ENUM", "VEC2", 
      "VEC3", "VEC4", "IMPLEMENTS", "IMPORT", "IF", "ELSE", "FOR", "BREAK", 
      "CONTINUE", "RETURN", "VISIBILITY", "CONST", "AND", "OR", "NOT", "IN", 
      "INTEGER", "FLOAT", "BOOL", "NULL", "CONST_NAME", "TYPE", "VARIABLE", 
      "STRING", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,68,662,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,1,0,1,
  	0,1,0,3,0,116,8,0,1,1,1,1,5,1,120,8,1,10,1,12,1,123,9,1,1,1,1,1,1,2,1,
  	2,5,2,129,8,2,10,2,12,2,132,9,2,1,2,3,2,135,8,2,1,2,1,2,1,3,1,3,1,3,5,
  	3,142,8,3,10,3,12,3,145,9,3,1,3,4,3,148,8,3,11,3,12,3,149,1,3,1,3,1,4,
  	1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,7,5,7,169,8,7,10,
  	7,12,7,172,9,7,1,7,4,7,175,8,7,11,7,12,7,176,1,7,5,7,180,8,7,10,7,12,
  	7,183,9,7,1,8,1,8,1,8,1,8,1,8,1,8,1,9,3,9,192,8,9,1,9,5,9,195,8,9,10,
  	9,12,9,198,9,9,1,9,5,9,201,8,9,10,9,12,9,204,9,9,1,10,3,10,207,8,10,1,
  	10,3,10,210,8,10,1,10,1,10,1,10,1,10,1,10,3,10,217,8,10,1,11,1,11,1,11,
  	1,11,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,3,13,232,8,13,1,13,
  	3,13,235,8,13,1,14,1,14,1,14,3,14,240,8,14,1,14,1,14,1,14,3,14,245,8,
  	14,1,15,1,15,1,15,1,16,3,16,251,8,16,1,16,1,16,1,16,1,17,1,17,1,18,1,
  	18,1,18,5,18,261,8,18,10,18,12,18,264,9,18,1,18,3,18,267,8,18,1,19,1,
  	19,3,19,271,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,
  	20,3,20,284,8,20,1,21,1,21,5,21,288,8,21,10,21,12,21,291,9,21,1,21,1,
  	21,1,22,1,22,1,22,3,22,298,8,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,
  	23,1,23,3,23,309,8,23,1,24,1,24,3,24,313,8,24,1,24,1,24,1,24,1,25,1,25,
  	1,25,1,25,5,25,322,8,25,10,25,12,25,325,9,25,1,25,3,25,328,8,25,1,26,
  	1,26,1,26,1,26,1,27,1,27,1,27,1,28,1,28,3,28,339,8,28,1,28,1,28,5,28,
  	343,8,28,10,28,12,28,346,9,28,1,28,1,28,1,28,3,28,351,8,28,1,28,1,28,
  	1,29,1,29,1,29,1,29,1,30,1,30,1,30,1,30,5,30,363,8,30,10,30,12,30,366,
  	9,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,5,30,376,8,30,10,30,12,30,
  	379,9,30,1,30,1,30,1,30,1,30,1,30,1,30,3,30,387,8,30,1,30,3,30,390,8,
  	30,1,31,1,31,1,32,1,32,1,32,1,33,1,33,1,33,1,33,5,33,401,8,33,10,33,12,
  	33,404,9,33,1,33,1,33,1,34,1,34,1,34,3,34,411,8,34,1,35,1,35,1,35,1,35,
  	1,35,1,35,3,35,419,8,35,1,35,1,35,1,35,3,35,424,8,35,3,35,426,8,35,1,
  	35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,
  	35,1,35,1,35,1,35,1,35,1,35,1,35,5,35,449,8,35,10,35,12,35,452,9,35,1,
  	36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,467,
  	8,36,1,37,1,37,1,37,1,37,5,37,473,8,37,10,37,12,37,476,9,37,1,37,3,37,
  	479,8,37,3,37,481,8,37,1,37,1,37,1,38,1,38,1,38,1,38,5,38,489,8,38,10,
  	38,12,38,492,9,38,1,38,3,38,495,8,38,3,38,497,8,38,1,38,1,38,1,39,1,39,
  	1,39,1,39,1,40,1,40,1,40,3,40,508,8,40,1,40,1,40,1,41,1,41,1,41,5,41,
  	515,8,41,10,41,12,41,518,9,41,1,41,3,41,521,8,41,1,42,1,42,3,42,525,8,
  	42,1,42,1,42,1,43,1,43,1,43,3,43,532,8,43,1,43,1,43,1,44,1,44,1,44,5,
  	44,539,8,44,10,44,12,44,542,9,44,1,44,3,44,545,8,44,1,45,1,45,1,45,1,
  	45,1,46,1,46,1,47,1,47,3,47,555,8,47,1,47,4,47,558,8,47,11,47,12,47,559,
  	1,48,1,48,1,48,3,48,565,8,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,1,48,
  	1,48,1,48,1,48,1,48,1,48,3,48,580,8,48,1,49,1,49,1,49,4,49,585,8,49,11,
  	49,12,49,586,1,50,1,50,1,50,1,50,1,50,1,50,1,50,3,50,596,8,50,1,51,1,
  	51,1,51,3,51,601,8,51,1,52,3,52,604,8,52,1,52,1,52,1,52,1,53,1,53,1,53,
  	3,53,612,8,53,1,53,1,53,1,53,3,53,617,8,53,1,53,4,53,620,8,53,11,53,12,
  	53,621,1,53,1,53,1,53,1,53,1,53,1,53,3,53,630,8,53,1,54,1,54,1,54,1,54,
  	1,54,5,54,637,8,54,10,54,12,54,640,9,54,1,54,3,54,643,8,54,3,54,645,8,
  	54,1,54,1,54,1,55,1,55,1,55,1,55,1,55,1,55,5,55,655,8,55,10,55,12,55,
  	658,9,55,1,55,1,55,1,55,0,1,70,56,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,
  	74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,0,10,1,
  	0,35,36,1,0,23,24,1,0,21,22,2,0,5,6,14,15,1,0,3,4,1,0,54,55,1,0,30,32,
  	1,0,33,34,2,0,58,60,65,65,1,0,41,43,720,0,115,1,0,0,0,2,121,1,0,0,0,4,
  	130,1,0,0,0,6,143,1,0,0,0,8,153,1,0,0,0,10,157,1,0,0,0,12,161,1,0,0,0,
  	14,170,1,0,0,0,16,184,1,0,0,0,18,191,1,0,0,0,20,206,1,0,0,0,22,218,1,
  	0,0,0,24,222,1,0,0,0,26,226,1,0,0,0,28,236,1,0,0,0,30,246,1,0,0,0,32,
  	250,1,0,0,0,34,255,1,0,0,0,36,257,1,0,0,0,38,270,1,0,0,0,40,283,1,0,0,
  	0,42,285,1,0,0,0,44,297,1,0,0,0,46,303,1,0,0,0,48,310,1,0,0,0,50,317,
  	1,0,0,0,52,329,1,0,0,0,54,333,1,0,0,0,56,336,1,0,0,0,58,354,1,0,0,0,60,
  	389,1,0,0,0,62,391,1,0,0,0,64,393,1,0,0,0,66,396,1,0,0,0,68,407,1,0,0,
  	0,70,425,1,0,0,0,72,466,1,0,0,0,74,468,1,0,0,0,76,484,1,0,0,0,78,500,
  	1,0,0,0,80,504,1,0,0,0,82,511,1,0,0,0,84,524,1,0,0,0,86,528,1,0,0,0,88,
  	535,1,0,0,0,90,546,1,0,0,0,92,550,1,0,0,0,94,554,1,0,0,0,96,579,1,0,0,
  	0,98,581,1,0,0,0,100,595,1,0,0,0,102,600,1,0,0,0,104,603,1,0,0,0,106,
  	629,1,0,0,0,108,631,1,0,0,0,110,648,1,0,0,0,112,116,3,6,3,0,113,116,3,
  	8,4,0,114,116,3,10,5,0,115,112,1,0,0,0,115,113,1,0,0,0,115,114,1,0,0,
  	0,116,1,1,0,0,0,117,120,3,48,24,0,118,120,3,46,23,0,119,117,1,0,0,0,119,
  	118,1,0,0,0,120,123,1,0,0,0,121,119,1,0,0,0,121,122,1,0,0,0,122,124,1,
  	0,0,0,123,121,1,0,0,0,124,125,5,0,0,1,125,3,1,0,0,0,126,129,3,48,24,0,
  	127,129,3,46,23,0,128,126,1,0,0,0,128,127,1,0,0,0,129,132,1,0,0,0,130,
  	128,1,0,0,0,130,131,1,0,0,0,131,134,1,0,0,0,132,130,1,0,0,0,133,135,3,
  	110,55,0,134,133,1,0,0,0,134,135,1,0,0,0,135,136,1,0,0,0,136,137,5,0,
  	0,1,137,5,1,0,0,0,138,142,3,16,8,0,139,142,3,66,33,0,140,142,3,12,6,0,
  	141,138,1,0,0,0,141,139,1,0,0,0,141,140,1,0,0,0,142,145,1,0,0,0,143,141,
  	1,0,0,0,143,144,1,0,0,0,144,147,1,0,0,0,145,143,1,0,0,0,146,148,3,30,
  	15,0,147,146,1,0,0,0,148,149,1,0,0,0,149,147,1,0,0,0,149,150,1,0,0,0,
  	150,151,1,0,0,0,151,152,5,0,0,1,152,7,1,0,0,0,153,154,3,22,11,0,154,155,
  	3,18,9,0,155,156,5,0,0,1,156,9,1,0,0,0,157,158,3,24,12,0,158,159,3,14,
  	7,0,159,160,5,0,0,1,160,11,1,0,0,0,161,162,5,39,0,0,162,163,5,63,0,0,
  	163,164,5,9,0,0,164,165,3,14,7,0,165,166,5,10,0,0,166,13,1,0,0,0,167,
  	169,3,46,23,0,168,167,1,0,0,0,169,172,1,0,0,0,170,168,1,0,0,0,170,171,
  	1,0,0,0,171,174,1,0,0,0,172,170,1,0,0,0,173,175,3,28,14,0,174,173,1,0,
  	0,0,175,176,1,0,0,0,176,174,1,0,0,0,176,177,1,0,0,0,177,181,1,0,0,0,178,
  	180,3,30,15,0,179,178,1,0,0,0,180,183,1,0,0,0,181,179,1,0,0,0,181,182,
  	1,0,0,0,182,15,1,0,0,0,183,181,1,0,0,0,184,185,7,0,0,0,185,186,5,63,0,
  	0,186,187,5,9,0,0,187,188,3,18,9,0,188,189,5,10,0,0,189,17,1,0,0,0,190,
  	192,3,26,13,0,191,190,1,0,0,0,191,192,1,0,0,0,192,196,1,0,0,0,193,195,
  	3,20,10,0,194,193,1,0,0,0,195,198,1,0,0,0,196,194,1,0,0,0,196,197,1,0,
  	0,0,197,202,1,0,0,0,198,196,1,0,0,0,199,201,3,32,16,0,200,199,1,0,0,0,
  	201,204,1,0,0,0,202,200,1,0,0,0,202,203,1,0,0,0,203,19,1,0,0,0,204,202,
  	1,0,0,0,205,207,5,52,0,0,206,205,1,0,0,0,206,207,1,0,0,0,207,209,1,0,
  	0,0,208,210,5,53,0,0,209,208,1,0,0,0,209,210,1,0,0,0,210,211,1,0,0,0,
  	211,212,5,64,0,0,212,213,5,19,0,0,213,216,3,106,53,0,214,215,5,20,0,0,
  	215,217,3,70,35,0,216,214,1,0,0,0,216,217,1,0,0,0,217,21,1,0,0,0,218,
  	219,7,0,0,0,219,220,5,19,0,0,220,221,5,63,0,0,221,23,1,0,0,0,222,223,
  	5,39,0,0,223,224,5,19,0,0,224,225,5,63,0,0,225,25,1,0,0,0,226,227,5,44,
  	0,0,227,228,5,19,0,0,228,231,5,63,0,0,229,230,5,16,0,0,230,232,5,63,0,
  	0,231,229,1,0,0,0,231,232,1,0,0,0,232,234,1,0,0,0,233,235,5,16,0,0,234,
  	233,1,0,0,0,234,235,1,0,0,0,235,27,1,0,0,0,236,237,5,64,0,0,237,239,5,
  	7,0,0,238,240,3,36,18,0,239,238,1,0,0,0,239,240,1,0,0,0,240,241,1,0,0,
  	0,241,244,5,8,0,0,242,243,5,19,0,0,243,245,3,106,53,0,244,242,1,0,0,0,
  	244,245,1,0,0,0,245,29,1,0,0,0,246,247,3,28,14,0,247,248,3,34,17,0,248,
  	31,1,0,0,0,249,251,5,52,0,0,250,249,1,0,0,0,250,251,1,0,0,0,251,252,1,
  	0,0,0,252,253,3,28,14,0,253,254,3,34,17,0,254,33,1,0,0,0,255,256,3,42,
  	21,0,256,35,1,0,0,0,257,262,3,38,19,0,258,259,5,16,0,0,259,261,3,38,19,
  	0,260,258,1,0,0,0,261,264,1,0,0,0,262,260,1,0,0,0,262,263,1,0,0,0,263,
  	266,1,0,0,0,264,262,1,0,0,0,265,267,5,16,0,0,266,265,1,0,0,0,266,267,
  	1,0,0,0,267,37,1,0,0,0,268,271,3,46,23,0,269,271,3,28,14,0,270,268,1,
  	0,0,0,270,269,1,0,0,0,271,39,1,0,0,0,272,284,3,44,22,0,273,284,3,46,23,
  	0,274,284,3,48,24,0,275,284,3,50,25,0,276,284,3,56,28,0,277,284,3,60,
  	30,0,278,284,5,50,0,0,279,284,3,62,31,0,280,284,3,64,32,0,281,284,3,80,
  	40,0,282,284,3,98,49,0,283,272,1,0,0,0,283,273,1,0,0,0,283,274,1,0,0,
  	0,283,275,1,0,0,0,283,276,1,0,0,0,283,277,1,0,0,0,283,278,1,0,0,0,283,
  	279,1,0,0,0,283,280,1,0,0,0,283,281,1,0,0,0,283,282,1,0,0,0,284,41,1,
  	0,0,0,285,289,5,9,0,0,286,288,3,40,20,0,287,286,1,0,0,0,288,291,1,0,0,
  	0,289,287,1,0,0,0,289,290,1,0,0,0,290,292,1,0,0,0,291,289,1,0,0,0,292,
  	293,5,10,0,0,293,43,1,0,0,0,294,298,5,64,0,0,295,298,3,94,47,0,296,298,
  	3,98,49,0,297,294,1,0,0,0,297,295,1,0,0,0,297,296,1,0,0,0,298,299,1,0,
  	0,0,299,300,5,19,0,0,300,301,5,20,0,0,301,302,3,70,35,0,302,45,1,0,0,
  	0,303,304,5,64,0,0,304,305,5,19,0,0,305,308,3,106,53,0,306,307,5,20,0,
  	0,307,309,3,70,35,0,308,306,1,0,0,0,308,309,1,0,0,0,309,47,1,0,0,0,310,
  	312,5,64,0,0,311,313,5,26,0,0,312,311,1,0,0,0,312,313,1,0,0,0,313,314,
  	1,0,0,0,314,315,5,20,0,0,315,316,3,70,35,0,316,49,1,0,0,0,317,318,5,46,
  	0,0,318,319,3,70,35,0,319,323,3,42,21,0,320,322,3,52,26,0,321,320,1,0,
  	0,0,322,325,1,0,0,0,323,321,1,0,0,0,323,324,1,0,0,0,324,327,1,0,0,0,325,
  	323,1,0,0,0,326,328,3,54,27,0,327,326,1,0,0,0,327,328,1,0,0,0,328,51,
  	1,0,0,0,329,330,5,47,0,0,330,331,3,70,35,0,331,332,3,42,21,0,332,53,1,
  	0,0,0,333,334,5,47,0,0,334,335,3,42,21,0,335,55,1,0,0,0,336,338,5,46,
  	0,0,337,339,3,70,35,0,338,337,1,0,0,0,338,339,1,0,0,0,339,340,1,0,0,0,
  	340,344,5,9,0,0,341,343,3,58,29,0,342,341,1,0,0,0,343,346,1,0,0,0,344,
  	342,1,0,0,0,344,345,1,0,0,0,345,350,1,0,0,0,346,344,1,0,0,0,347,348,5,
  	47,0,0,348,349,5,19,0,0,349,351,3,42,21,0,350,347,1,0,0,0,350,351,1,0,
  	0,0,351,352,1,0,0,0,352,353,5,10,0,0,353,57,1,0,0,0,354,355,3,70,35,0,
  	355,356,5,19,0,0,356,357,3,42,21,0,357,59,1,0,0,0,358,359,5,48,0,0,359,
  	364,5,64,0,0,360,361,5,16,0,0,361,363,5,64,0,0,362,360,1,0,0,0,363,366,
  	1,0,0,0,364,362,1,0,0,0,364,365,1,0,0,0,365,367,1,0,0,0,366,364,1,0,0,
  	0,367,368,5,57,0,0,368,369,3,104,52,0,369,370,3,42,21,0,370,390,1,0,0,
  	0,371,372,5,48,0,0,372,377,5,64,0,0,373,374,5,16,0,0,374,376,5,64,0,0,
  	375,373,1,0,0,0,376,379,1,0,0,0,377,375,1,0,0,0,377,378,1,0,0,0,378,380,
  	1,0,0,0,379,377,1,0,0,0,380,381,5,57,0,0,381,382,3,72,36,0,382,383,3,
  	42,21,0,383,390,1,0,0,0,384,386,5,48,0,0,385,387,5,64,0,0,386,385,1,0,
  	0,0,386,387,1,0,0,0,387,388,1,0,0,0,388,390,3,42,21,0,389,358,1,0,0,0,
  	389,371,1,0,0,0,389,384,1,0,0,0,390,61,1,0,0,0,391,392,5,49,0,0,392,63,
  	1,0,0,0,393,394,5,51,0,0,394,395,3,70,35,0,395,65,1,0,0,0,396,397,5,40,
  	0,0,397,398,5,63,0,0,398,402,5,9,0,0,399,401,3,68,34,0,400,399,1,0,0,
  	0,401,404,1,0,0,0,402,400,1,0,0,0,402,403,1,0,0,0,403,405,1,0,0,0,404,
  	402,1,0,0,0,405,406,5,10,0,0,406,67,1,0,0,0,407,410,5,62,0,0,408,409,
  	5,20,0,0,409,411,5,65,0,0,410,408,1,0,0,0,410,411,1,0,0,0,411,69,1,0,
  	0,0,412,413,6,35,-1,0,413,414,5,7,0,0,414,415,3,70,35,0,415,418,5,8,0,
  	0,416,417,5,13,0,0,417,419,3,106,53,0,418,416,1,0,0,0,418,419,1,0,0,0,
  	419,426,1,0,0,0,420,423,3,72,36,0,421,422,5,13,0,0,422,424,3,106,53,0,
  	423,421,1,0,0,0,423,424,1,0,0,0,424,426,1,0,0,0,425,412,1,0,0,0,425,420,
  	1,0,0,0,426,450,1,0,0,0,427,428,10,7,0,0,428,429,7,1,0,0,429,449,3,70,
  	35,8,430,431,10,6,0,0,431,432,7,2,0,0,432,449,3,70,35,7,433,434,10,5,
  	0,0,434,435,7,3,0,0,435,449,3,70,35,6,436,437,10,4,0,0,437,438,7,4,0,
  	0,438,449,3,70,35,5,439,440,10,3,0,0,440,441,7,5,0,0,441,449,3,70,35,
  	4,442,443,10,2,0,0,443,444,7,6,0,0,444,449,3,70,35,3,445,446,10,1,0,0,
  	446,447,7,7,0,0,447,449,3,70,35,2,448,427,1,0,0,0,448,430,1,0,0,0,448,
  	433,1,0,0,0,448,436,1,0,0,0,448,439,1,0,0,0,448,442,1,0,0,0,448,445,1,
  	0,0,0,449,452,1,0,0,0,450,448,1,0,0,0,450,451,1,0,0,0,451,71,1,0,0,0,
  	452,450,1,0,0,0,453,467,5,64,0,0,454,467,5,62,0,0,455,467,5,37,0,0,456,
  	467,5,38,0,0,457,467,5,61,0,0,458,467,3,80,40,0,459,467,3,108,54,0,460,
  	467,3,86,43,0,461,467,3,92,46,0,462,467,3,74,37,0,463,467,3,76,38,0,464,
  	467,3,94,47,0,465,467,3,98,49,0,466,453,1,0,0,0,466,454,1,0,0,0,466,455,
  	1,0,0,0,466,456,1,0,0,0,466,457,1,0,0,0,466,458,1,0,0,0,466,459,1,0,0,
  	0,466,460,1,0,0,0,466,461,1,0,0,0,466,462,1,0,0,0,466,463,1,0,0,0,466,
  	464,1,0,0,0,466,465,1,0,0,0,467,73,1,0,0,0,468,480,5,11,0,0,469,474,3,
  	70,35,0,470,471,5,16,0,0,471,473,3,70,35,0,472,470,1,0,0,0,473,476,1,
  	0,0,0,474,472,1,0,0,0,474,475,1,0,0,0,475,478,1,0,0,0,476,474,1,0,0,0,
  	477,479,5,16,0,0,478,477,1,0,0,0,478,479,1,0,0,0,479,481,1,0,0,0,480,
  	469,1,0,0,0,480,481,1,0,0,0,481,482,1,0,0,0,482,483,5,12,0,0,483,75,1,
  	0,0,0,484,496,5,9,0,0,485,490,3,78,39,0,486,487,5,16,0,0,487,489,3,78,
  	39,0,488,486,1,0,0,0,489,492,1,0,0,0,490,488,1,0,0,0,490,491,1,0,0,0,
  	491,494,1,0,0,0,492,490,1,0,0,0,493,495,5,16,0,0,494,493,1,0,0,0,494,
  	495,1,0,0,0,495,497,1,0,0,0,496,485,1,0,0,0,496,497,1,0,0,0,497,498,1,
  	0,0,0,498,499,5,10,0,0,499,77,1,0,0,0,500,501,3,70,35,0,501,502,5,19,
  	0,0,502,503,3,70,35,0,503,79,1,0,0,0,504,505,5,64,0,0,505,507,5,7,0,0,
  	506,508,3,82,41,0,507,506,1,0,0,0,507,508,1,0,0,0,508,509,1,0,0,0,509,
  	510,5,8,0,0,510,81,1,0,0,0,511,516,3,84,42,0,512,513,5,16,0,0,513,515,
  	3,84,42,0,514,512,1,0,0,0,515,518,1,0,0,0,516,514,1,0,0,0,516,517,1,0,
  	0,0,517,520,1,0,0,0,518,516,1,0,0,0,519,521,5,16,0,0,520,519,1,0,0,0,
  	520,521,1,0,0,0,521,83,1,0,0,0,522,523,5,64,0,0,523,525,5,20,0,0,524,
  	522,1,0,0,0,524,525,1,0,0,0,525,526,1,0,0,0,526,527,3,70,35,0,527,85,
  	1,0,0,0,528,529,5,63,0,0,529,531,5,7,0,0,530,532,3,88,44,0,531,530,1,
  	0,0,0,531,532,1,0,0,0,532,533,1,0,0,0,533,534,5,8,0,0,534,87,1,0,0,0,
  	535,540,3,90,45,0,536,537,5,16,0,0,537,539,3,90,45,0,538,536,1,0,0,0,
  	539,542,1,0,0,0,540,538,1,0,0,0,540,541,1,0,0,0,541,544,1,0,0,0,542,540,
  	1,0,0,0,543,545,5,16,0,0,544,543,1,0,0,0,544,545,1,0,0,0,545,89,1,0,0,
  	0,546,547,5,64,0,0,547,548,5,20,0,0,548,549,3,70,35,0,549,91,1,0,0,0,
  	550,551,7,8,0,0,551,93,1,0,0,0,552,555,3,80,40,0,553,555,5,64,0,0,554,
  	552,1,0,0,0,554,553,1,0,0,0,555,557,1,0,0,0,556,558,3,96,48,0,557,556,
  	1,0,0,0,558,559,1,0,0,0,559,557,1,0,0,0,559,560,1,0,0,0,560,95,1,0,0,
  	0,561,562,5,11,0,0,562,564,3,70,35,0,563,565,5,19,0,0,564,563,1,0,0,0,
  	564,565,1,0,0,0,565,566,1,0,0,0,566,567,5,12,0,0,567,580,1,0,0,0,568,
  	569,5,11,0,0,569,570,5,19,0,0,570,571,3,70,35,0,571,572,5,12,0,0,572,
  	580,1,0,0,0,573,574,5,11,0,0,574,575,3,70,35,0,575,576,5,19,0,0,576,577,
  	3,70,35,0,577,578,5,12,0,0,578,580,1,0,0,0,579,561,1,0,0,0,579,568,1,
  	0,0,0,579,573,1,0,0,0,580,97,1,0,0,0,581,584,3,100,50,0,582,583,5,18,
  	0,0,583,585,3,102,51,0,584,582,1,0,0,0,585,586,1,0,0,0,586,584,1,0,0,
  	0,586,587,1,0,0,0,587,99,1,0,0,0,588,596,5,64,0,0,589,596,5,63,0,0,590,
  	596,5,38,0,0,591,596,5,37,0,0,592,596,3,80,40,0,593,596,3,86,43,0,594,
  	596,3,94,47,0,595,588,1,0,0,0,595,589,1,0,0,0,595,590,1,0,0,0,595,591,
  	1,0,0,0,595,592,1,0,0,0,595,593,1,0,0,0,595,594,1,0,0,0,596,101,1,0,0,
  	0,597,601,5,64,0,0,598,601,3,80,40,0,599,601,3,94,47,0,600,597,1,0,0,
  	0,600,598,1,0,0,0,600,599,1,0,0,0,601,103,1,0,0,0,602,604,3,70,35,0,603,
  	602,1,0,0,0,603,604,1,0,0,0,604,605,1,0,0,0,605,606,5,17,0,0,606,607,
  	3,70,35,0,607,105,1,0,0,0,608,630,5,38,0,0,609,611,5,63,0,0,610,612,5,
  	26,0,0,611,610,1,0,0,0,611,612,1,0,0,0,612,630,1,0,0,0,613,619,5,63,0,
  	0,614,616,5,11,0,0,615,617,5,58,0,0,616,615,1,0,0,0,616,617,1,0,0,0,617,
  	618,1,0,0,0,618,620,5,12,0,0,619,614,1,0,0,0,620,621,1,0,0,0,621,619,
  	1,0,0,0,621,622,1,0,0,0,622,630,1,0,0,0,623,624,5,9,0,0,624,625,3,106,
  	53,0,625,626,5,19,0,0,626,627,3,106,53,0,627,628,5,10,0,0,628,630,1,0,
  	0,0,629,608,1,0,0,0,629,609,1,0,0,0,629,613,1,0,0,0,629,623,1,0,0,0,630,
  	107,1,0,0,0,631,632,7,9,0,0,632,644,5,7,0,0,633,638,3,70,35,0,634,635,
  	5,16,0,0,635,637,3,70,35,0,636,634,1,0,0,0,637,640,1,0,0,0,638,636,1,
  	0,0,0,638,639,1,0,0,0,639,642,1,0,0,0,640,638,1,0,0,0,641,643,5,16,0,
  	0,642,641,1,0,0,0,642,643,1,0,0,0,643,645,1,0,0,0,644,633,1,0,0,0,644,
  	645,1,0,0,0,645,646,1,0,0,0,646,647,5,8,0,0,647,109,1,0,0,0,648,649,5,
  	1,0,0,649,650,5,2,0,0,650,656,5,9,0,0,651,652,5,64,0,0,652,653,5,19,0,
  	0,653,655,3,106,53,0,654,651,1,0,0,0,655,658,1,0,0,0,656,654,1,0,0,0,
  	656,657,1,0,0,0,657,659,1,0,0,0,658,656,1,0,0,0,659,660,5,10,0,0,660,
  	111,1,0,0,0,77,115,119,121,128,130,134,141,143,149,170,176,181,191,196,
  	202,206,209,216,231,234,239,244,250,262,266,270,283,289,297,308,312,323,
  	327,338,344,350,364,377,386,389,402,410,418,423,425,448,450,466,474,478,
  	480,490,494,496,507,516,520,524,531,540,544,554,559,564,579,586,595,600,
  	603,611,616,621,629,638,642,644,656
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
    setState(115);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(112);
      mainFile();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(113);
      objectFile();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(114);
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
    setState(121);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(119);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
      case 1: {
        setState(117);
        implicitVarDec();
        break;
      }

      case 2: {
        setState(118);
        explicitVarDec();
        break;
      }

      default:
        break;
      }
      setState(123);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(124);
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
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(128);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(126);
        implicitVarDec();
        break;
      }

      case 2: {
        setState(127);
        explicitVarDec();
        break;
      }

      default:
        break;
      }
      setState(132);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(134);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::T__0) {
      setState(133);
      requireEnvVars();
    }
    setState(136);
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
    setState(143);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1752346656768) != 0)) {
      setState(141);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case LogosParser::OBJECT:
        case LogosParser::SINGLETON: {
          setState(138);
          object();
          break;
        }

        case LogosParser::ENUM: {
          setState(139);
          enumDeclaration();
          break;
        }

        case LogosParser::INTERFACE: {
          setState(140);
          interface();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(145);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(147); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(146);
      funcImplementation();
      setState(149); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(151);
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
    setState(153);
    objectDeclaration();
    setState(154);
    objectBody();
    setState(155);
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
    setState(157);
    interfaceDeclaration();
    setState(158);
    interfaceBody();
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
    setState(161);
    match(LogosParser::INTERFACE);
    setState(162);
    match(LogosParser::TYPE);
    setState(163);
    match(LogosParser::LBRACE);
    setState(164);
    interfaceBody();
    setState(165);
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

std::vector<LogosParser::FuncImplementationContext *> LogosParser::InterfaceBodyContext::funcImplementation() {
  return getRuleContexts<LogosParser::FuncImplementationContext>();
}

LogosParser::FuncImplementationContext* LogosParser::InterfaceBodyContext::funcImplementation(size_t i) {
  return getRuleContext<LogosParser::FuncImplementationContext>(i);
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
    setState(170);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(167);
        explicitVarDec(); 
      }
      setState(172);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
    setState(174); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(173);
              funcSignature();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(176); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(181);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(178);
      funcImplementation();
      setState(183);
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
    setState(184);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(185);
    match(LogosParser::TYPE);
    setState(186);
    match(LogosParser::LBRACE);
    setState(187);
    objectBody();
    setState(188);
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
    setState(191);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(190);
      objectImplements();
    }
    setState(196);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(193);
        field(); 
      }
      setState(198);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
    setState(202);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VISIBILITY

    || _la == LogosParser::VARIABLE) {
      setState(199);
      methodImplementation();
      setState(204);
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
    setState(206);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(205);
      match(LogosParser::VISIBILITY);
    }
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(208);
      match(LogosParser::CONST);
    }
    setState(211);
    match(LogosParser::VARIABLE);
    setState(212);
    match(LogosParser::COLON);
    setState(213);
    type();
    setState(216);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(214);
      match(LogosParser::EQUAL);
      setState(215);
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
    setState(218);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(219);
    match(LogosParser::COLON);
    setState(220);
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
    setState(222);
    match(LogosParser::INTERFACE);
    setState(223);
    match(LogosParser::COLON);
    setState(224);
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
    setState(226);
    match(LogosParser::IMPLEMENTS);
    setState(227);
    match(LogosParser::COLON);
    setState(228);
    match(LogosParser::TYPE);
    setState(231);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(229);
      match(LogosParser::COMMA);
      setState(230);
      match(LogosParser::TYPE);
      break;
    }

    default:
      break;
    }
    setState(234);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(233);
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
    enterOuterAlt(_localctx, 1);
    setState(236);
    match(LogosParser::VARIABLE);
    setState(237);
    match(LogosParser::LPAREN);
    setState(239);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(238);
      paramList();
    }
    setState(241);
    match(LogosParser::RPAREN);
    setState(244);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(242);
      match(LogosParser::COLON);
      setState(243);
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
  enterRule(_localctx, 30, LogosParser::RuleFuncImplementation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    funcSignature();
    setState(247);
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
  enterRule(_localctx, 32, LogosParser::RuleMethodImplementation);
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
    setState(250);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(249);
      match(LogosParser::VISIBILITY);
    }
    setState(252);
    funcSignature();
    setState(253);
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
  enterRule(_localctx, 34, LogosParser::RuleFuncBody);

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

std::vector<LogosParser::ParamContext *> LogosParser::ParamListContext::param() {
  return getRuleContexts<LogosParser::ParamContext>();
}

LogosParser::ParamContext* LogosParser::ParamListContext::param(size_t i) {
  return getRuleContext<LogosParser::ParamContext>(i);
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
  enterRule(_localctx, 36, LogosParser::RuleParamList);
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
    setState(257);
    param();
    setState(262);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(258);
        match(LogosParser::COMMA);
        setState(259);
        param(); 
      }
      setState(264);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
    setState(266);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(265);
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

//----------------- ParamContext ------------------------------------------------------------------

LogosParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ExplicitVarDecContext* LogosParser::ParamContext::explicitVarDec() {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(0);
}

LogosParser::FuncSignatureContext* LogosParser::ParamContext::funcSignature() {
  return getRuleContext<LogosParser::FuncSignatureContext>(0);
}


size_t LogosParser::ParamContext::getRuleIndex() const {
  return LogosParser::RuleParam;
}


LogosParser::ParamContext* LogosParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 38, LogosParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(270);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(268);
      explicitVarDec();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(269);
      funcSignature();
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
  enterRule(_localctx, 40, LogosParser::RuleStatement);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(272);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(273);
      explicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(274);
      implicitVarDec();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(275);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(276);
      patternMatching();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(277);
      loopStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(278);
      match(LogosParser::CONTINUE);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(279);
      breakStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(280);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(281);
      funcCall();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(282);
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
    setState(285);
    match(LogosParser::LBRACE);
    setState(289);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 37) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 37)) & 201357827) != 0)) {
      setState(286);
      statement();
      setState(291);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(292);
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
  enterRule(_localctx, 44, LogosParser::RuleAssignment);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      setState(294);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      setState(295);
      arrayIndex();
      break;
    }

    case 3: {
      setState(296);
      selection();
      break;
    }

    default:
      break;
    }
    setState(299);
    match(LogosParser::COLON);
    setState(300);
    match(LogosParser::EQUAL);
    setState(301);
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
  enterRule(_localctx, 46, LogosParser::RuleExplicitVarDec);
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
    setState(303);
    match(LogosParser::VARIABLE);
    setState(304);
    match(LogosParser::COLON);
    setState(305);
    type();
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
  enterRule(_localctx, 48, LogosParser::RuleImplicitVarDec);
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
    match(LogosParser::VARIABLE);
    setState(312);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(311);
      match(LogosParser::QUEST_MARK);
    }
    setState(314);
    match(LogosParser::EQUAL);
    setState(315);
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
  enterRule(_localctx, 50, LogosParser::RuleIfStatement);
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
    setState(317);
    match(LogosParser::IF);
    setState(318);
    expr(0);
    setState(319);
    statementsBlock();
    setState(323);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(320);
        elseIfStatement(); 
      }
      setState(325);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
    setState(327);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(326);
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
  enterRule(_localctx, 52, LogosParser::RuleElseIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    match(LogosParser::ELSE);
    setState(330);
    expr(0);
    setState(331);
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
  enterRule(_localctx, 54, LogosParser::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(333);
    match(LogosParser::ELSE);
    setState(334);
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
  enterRule(_localctx, 56, LogosParser::RulePatternMatching);
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

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      setState(337);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(340);
    match(LogosParser::LBRACE);
    setState(344);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
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
  enterRule(_localctx, 58, LogosParser::RulePattern);

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
  enterRule(_localctx, 60, LogosParser::RuleLoopStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(389);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(358);
      match(LogosParser::FOR);
      setState(359);
      match(LogosParser::VARIABLE);
      setState(364);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LogosParser::COMMA) {
        setState(360);
        match(LogosParser::COMMA);
        setState(361);
        match(LogosParser::VARIABLE);
        setState(366);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(367);
      match(LogosParser::IN);
      setState(368);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(369);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(371);
      match(LogosParser::FOR);
      setState(372);
      match(LogosParser::VARIABLE);
      setState(377);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LogosParser::COMMA) {
        setState(373);
        match(LogosParser::COMMA);
        setState(374);
        match(LogosParser::VARIABLE);
        setState(379);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(380);
      match(LogosParser::IN);
      setState(381);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = unaryExpr();
      setState(382);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(384);
      match(LogosParser::FOR);
      setState(386);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::VARIABLE) {
        setState(385);
        match(LogosParser::VARIABLE);
      }
      setState(388);
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
  enterRule(_localctx, 62, LogosParser::RuleBreakStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(391);
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
  enterRule(_localctx, 64, LogosParser::RuleReturnStatement);

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
    match(LogosParser::RETURN);
    setState(394);
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
  enterRule(_localctx, 66, LogosParser::RuleEnumDeclaration);
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
    match(LogosParser::ENUM);
    setState(397);
    match(LogosParser::TYPE);
    setState(398);
    match(LogosParser::LBRACE);
    setState(402);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST_NAME) {
      setState(399);
      enumField();
      setState(404);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(405);
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
  enterRule(_localctx, 68, LogosParser::RuleEnumField);
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
    setState(407);
    match(LogosParser::CONST_NAME);
    setState(410);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(408);
      match(LogosParser::EQUAL);
      setState(409);
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
  size_t startState = 70;
  enterRecursionRule(_localctx, 70, LogosParser::RuleExpr, precedence);

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
    setState(425);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::LPAREN: {
        setState(413);
        match(LogosParser::LPAREN);
        setState(414);
        antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
        setState(415);
        match(LogosParser::RPAREN);
        setState(418);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
        case 1: {
          setState(416);
          match(LogosParser::CAST);
          setState(417);
          type();
          break;
        }

        default:
          break;
        }
        break;
      }

      case LogosParser::LBRACE:
      case LogosParser::LBRACK:
      case LogosParser::SELF_INSTANCE:
      case LogosParser::SELF_CLASS:
      case LogosParser::VEC2:
      case LogosParser::VEC3:
      case LogosParser::VEC4:
      case LogosParser::INTEGER:
      case LogosParser::FLOAT:
      case LogosParser::BOOL:
      case LogosParser::NULL_:
      case LogosParser::CONST_NAME:
      case LogosParser::TYPE:
      case LogosParser::VARIABLE:
      case LogosParser::STRING: {
        setState(420);
        unaryExpr();
        setState(423);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          setState(421);
          match(LogosParser::CAST);
          setState(422);
          antlrcpp::downCast<ExprContext *>(_localctx)->cast = type();
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
    _ctx->stop = _input->LT(-1);
    setState(450);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(448);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(427);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(428);
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
          setState(429);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(430);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(431);
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
          setState(432);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(433);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(434);
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
          setState(435);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(436);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(437);
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
          setState(438);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(439);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(440);
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
          setState(441);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(442);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(443);
          antlrcpp::downCast<ExprContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 7516192768) != 0))) {
            antlrcpp::downCast<ExprContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(444);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(445);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(446);
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
          setState(447);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(452);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
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
  enterRule(_localctx, 72, LogosParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(466);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(453);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(454);
      match(LogosParser::CONST_NAME);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(455);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(456);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(457);
      match(LogosParser::NULL_);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(458);
      funcCall();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(459);
      vector();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(460);
      constructor();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(461);
      constant();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(462);
      array();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(463);
      hashMap();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(464);
      arrayIndex();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(465);
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
  enterRule(_localctx, 74, LogosParser::RuleArray);
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
    setState(468);
    match(LogosParser::LBRACK);
    setState(480);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(469);
      expr(0);
      setState(474);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(470);
          match(LogosParser::COMMA);
          setState(471);
          expr(0); 
        }
        setState(476);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
      }
      setState(478);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(477);
        match(LogosParser::COMMA);
      }
    }
    setState(482);
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
  enterRule(_localctx, 76, LogosParser::RuleHashMap);
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
    setState(484);
    match(LogosParser::LBRACE);
    setState(496);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(485);
      keyValue();
      setState(490);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(486);
          match(LogosParser::COMMA);
          setState(487);
          keyValue(); 
        }
        setState(492);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
      }
      setState(494);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(493);
        match(LogosParser::COMMA);
      }
    }
    setState(498);
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
  enterRule(_localctx, 78, LogosParser::RuleKeyValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(500);
    antlrcpp::downCast<KeyValueContext *>(_localctx)->key = expr(0);
    setState(501);
    match(LogosParser::COLON);
    setState(502);
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
  enterRule(_localctx, 80, LogosParser::RuleFuncCall);
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
    setState(504);
    match(LogosParser::VARIABLE);
    setState(505);
    match(LogosParser::LPAREN);
    setState(507);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(506);
      funcArgList();
    }
    setState(509);
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
  enterRule(_localctx, 82, LogosParser::RuleFuncArgList);
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
    setState(511);
    funcArg();
    setState(516);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(512);
        match(LogosParser::COMMA);
        setState(513);
        funcArg(); 
      }
      setState(518);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    }
    setState(520);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(519);
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
  enterRule(_localctx, 84, LogosParser::RuleFuncArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(524);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      setState(522);
      match(LogosParser::VARIABLE);
      setState(523);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(526);
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
  enterRule(_localctx, 86, LogosParser::RuleConstructor);
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
    match(LogosParser::TYPE);
    setState(529);
    match(LogosParser::LPAREN);
    setState(531);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(530);
      constructorArgList();
    }
    setState(533);
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
  enterRule(_localctx, 88, LogosParser::RuleConstructorArgList);
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
    setState(535);
    constructorArg();
    setState(540);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(536);
        match(LogosParser::COMMA);
        setState(537);
        constructorArg(); 
      }
      setState(542);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
    }
    setState(544);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(543);
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
  enterRule(_localctx, 90, LogosParser::RuleConstructorArg);

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
    match(LogosParser::VARIABLE);
    setState(547);
    match(LogosParser::EQUAL);
    setState(548);
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
  enterRule(_localctx, 92, LogosParser::RuleConstant);
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
    _la = _input->LA(1);
    if (!(((((_la - 58) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 58)) & 135) != 0))) {
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

std::vector<LogosParser::IndexContext *> LogosParser::ArrayIndexContext::index() {
  return getRuleContexts<LogosParser::IndexContext>();
}

LogosParser::IndexContext* LogosParser::ArrayIndexContext::index(size_t i) {
  return getRuleContext<LogosParser::IndexContext>(i);
}


size_t LogosParser::ArrayIndexContext::getRuleIndex() const {
  return LogosParser::RuleArrayIndex;
}


LogosParser::ArrayIndexContext* LogosParser::arrayIndex() {
  ArrayIndexContext *_localctx = _tracker.createInstance<ArrayIndexContext>(_ctx, getState());
  enterRule(_localctx, 94, LogosParser::RuleArrayIndex);

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
    setState(554);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
    case 1: {
      setState(552);
      funcCall();
      break;
    }

    case 2: {
      setState(553);
      match(LogosParser::VARIABLE);
      break;
    }

    default:
      break;
    }
    setState(557); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(556);
              index();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(559); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx);
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
  enterRule(_localctx, 96, LogosParser::RuleIndex);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(579);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(561);
      match(LogosParser::LBRACK);
      setState(562);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(564);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COLON) {
        setState(563);
        match(LogosParser::COLON);
      }
      setState(566);
      match(LogosParser::RBRACK);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(568);
      match(LogosParser::LBRACK);
      setState(569);
      match(LogosParser::COLON);
      setState(570);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(571);
      match(LogosParser::RBRACK);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(573);
      match(LogosParser::LBRACK);
      setState(574);
      antlrcpp::downCast<IndexContext *>(_localctx)->from = expr(0);
      setState(575);
      match(LogosParser::COLON);
      setState(576);
      antlrcpp::downCast<IndexContext *>(_localctx)->to = expr(0);
      setState(577);
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
  enterRule(_localctx, 98, LogosParser::RuleSelection);

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
    firstSelectionElement();
    setState(584); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(582);
              match(LogosParser::DOT);
              setState(583);
              innerSelectionElement();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(586); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
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
  enterRule(_localctx, 100, LogosParser::RuleFirstSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(595);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(588);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(589);
      match(LogosParser::TYPE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(590);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(591);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(592);
      funcCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(593);
      constructor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(594);
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
  enterRule(_localctx, 102, LogosParser::RuleInnerSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(600);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(597);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(598);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(599);
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
  enterRule(_localctx, 104, LogosParser::RuleRange);
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
    setState(603);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(602);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
    }
    setState(605);
    match(LogosParser::DOUBLE_DOT);
    setState(606);
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

tree::TerminalNode* LogosParser::TypeContext::SELF_CLASS() {
  return getToken(LogosParser::SELF_CLASS, 0);
}

tree::TerminalNode* LogosParser::TypeContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::TypeContext::QUEST_MARK() {
  return getToken(LogosParser::QUEST_MARK, 0);
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

tree::TerminalNode* LogosParser::TypeContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::TypeContext::RBRACE() {
  return getToken(LogosParser::RBRACE, 0);
}

std::vector<LogosParser::TypeContext *> LogosParser::TypeContext::type() {
  return getRuleContexts<LogosParser::TypeContext>();
}

LogosParser::TypeContext* LogosParser::TypeContext::type(size_t i) {
  return getRuleContext<LogosParser::TypeContext>(i);
}


size_t LogosParser::TypeContext::getRuleIndex() const {
  return LogosParser::RuleType;
}


LogosParser::TypeContext* LogosParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 106, LogosParser::RuleType);
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
    setState(629);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(608);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(609);
      match(LogosParser::TYPE);
      setState(611);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
      case 1: {
        setState(610);
        match(LogosParser::QUEST_MARK);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(613);
      match(LogosParser::TYPE);
      setState(619); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(614);
                match(LogosParser::LBRACK);
                setState(616);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == LogosParser::INTEGER) {
                  setState(615);
                  match(LogosParser::INTEGER);
                }
                setState(618);
                match(LogosParser::RBRACK);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(621); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(623);
      match(LogosParser::LBRACE);
      setState(624);
      antlrcpp::downCast<TypeContext *>(_localctx)->key = type();
      setState(625);
      match(LogosParser::COLON);
      setState(626);
      antlrcpp::downCast<TypeContext *>(_localctx)->value = type();
      setState(627);
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
  enterRule(_localctx, 108, LogosParser::RuleVector);
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
    setState(631);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 15393162788864) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(632);
    match(LogosParser::LPAREN);
    setState(644);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(633);
      expr(0);
      setState(638);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(634);
          match(LogosParser::COMMA);
          setState(635);
          expr(0); 
        }
        setState(640);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx);
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
  enterRule(_localctx, 110, LogosParser::RuleRequireEnvVars);
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
    setState(648);
    match(LogosParser::T__0);
    setState(649);
    match(LogosParser::T__1);
    setState(650);
    match(LogosParser::LBRACE);
    setState(656);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(651);
      match(LogosParser::VARIABLE);
      setState(652);
      match(LogosParser::COLON);
      setState(653);
      type();
      setState(658);
      _errHandler->sync(this);
      _la = _input->LA(1);
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

bool LogosParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 35: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

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

void LogosParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  logosParserInitialize();
#else
  ::antlr4::internal::call_once(logosParserOnceFlag, logosParserInitialize);
#endif
}
