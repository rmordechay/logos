
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
      "array", "map", "funcCall", "funcArgList", "funcArg", "constructor", 
      "constructorArgList", "constructorArg", "constant", "arrayIndex", 
      "selection", "firstSelectionElement", "innerSelectionElement", "range", 
      "type", "vector", "requireEnvVars"
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
  	4,1,68,635,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,1,0,1,0,1,0,3,0,112,8,0,1,
  	1,1,1,5,1,116,8,1,10,1,12,1,119,9,1,1,1,1,1,1,2,1,2,5,2,125,8,2,10,2,
  	12,2,128,9,2,1,2,3,2,131,8,2,1,2,1,2,1,3,1,3,1,3,5,3,138,8,3,10,3,12,
  	3,141,9,3,1,3,4,3,144,8,3,11,3,12,3,145,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,
  	5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,7,5,7,165,8,7,10,7,12,7,168,9,7,1,
  	7,4,7,171,8,7,11,7,12,7,172,1,7,5,7,176,8,7,10,7,12,7,179,9,7,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,9,3,9,188,8,9,1,9,5,9,191,8,9,10,9,12,9,194,9,9,1,9,
  	5,9,197,8,9,10,9,12,9,200,9,9,1,10,3,10,203,8,10,1,10,3,10,206,8,10,1,
  	10,1,10,1,10,1,10,1,10,3,10,213,8,10,1,11,1,11,1,11,1,11,1,12,1,12,1,
  	12,1,12,1,13,1,13,1,13,1,13,1,13,3,13,228,8,13,1,13,3,13,231,8,13,1,14,
  	1,14,1,14,3,14,236,8,14,1,14,1,14,1,14,3,14,241,8,14,1,15,1,15,1,15,1,
  	16,3,16,247,8,16,1,16,1,16,1,16,1,17,1,17,1,18,1,18,1,18,5,18,257,8,18,
  	10,18,12,18,260,9,18,1,18,3,18,263,8,18,1,19,1,19,3,19,267,8,19,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,3,20,280,8,20,1,21,
  	1,21,5,21,284,8,21,10,21,12,21,287,9,21,1,21,1,21,1,22,1,22,1,22,3,22,
  	294,8,22,1,22,1,22,1,22,1,22,1,23,1,23,1,23,1,23,1,23,3,23,305,8,23,1,
  	24,1,24,3,24,309,8,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,5,25,318,8,25,
  	10,25,12,25,321,9,25,1,25,3,25,324,8,25,1,26,1,26,1,26,1,26,1,27,1,27,
  	1,27,1,28,1,28,3,28,335,8,28,1,28,1,28,5,28,339,8,28,10,28,12,28,342,
  	9,28,1,28,1,28,1,28,3,28,347,8,28,1,28,1,28,1,29,1,29,1,29,1,29,1,30,
  	1,30,1,30,1,30,5,30,359,8,30,10,30,12,30,362,9,30,1,30,1,30,1,30,1,30,
  	1,30,1,30,1,30,1,30,5,30,372,8,30,10,30,12,30,375,9,30,1,30,1,30,1,30,
  	1,30,1,30,1,30,3,30,383,8,30,1,30,3,30,386,8,30,1,31,1,31,1,32,1,32,1,
  	32,1,33,1,33,1,33,1,33,5,33,397,8,33,10,33,12,33,400,9,33,1,33,1,33,1,
  	34,1,34,1,34,3,34,407,8,34,1,35,1,35,1,35,1,35,1,35,1,35,3,35,415,8,35,
  	1,35,1,35,1,35,3,35,420,8,35,3,35,422,8,35,1,35,1,35,1,35,1,35,1,35,1,
  	35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,35,1,
  	35,1,35,5,35,445,8,35,10,35,12,35,448,9,35,1,36,1,36,1,36,1,36,1,36,1,
  	36,1,36,1,36,1,36,1,36,1,36,1,36,1,36,3,36,463,8,36,1,37,1,37,1,37,1,
  	37,5,37,469,8,37,10,37,12,37,472,9,37,1,37,3,37,475,8,37,3,37,477,8,37,
  	1,37,1,37,1,38,1,38,1,38,1,38,1,38,3,38,486,8,38,5,38,488,8,38,10,38,
  	12,38,491,9,38,1,38,1,38,1,39,1,39,1,39,3,39,498,8,39,1,39,1,39,1,40,
  	1,40,1,40,5,40,505,8,40,10,40,12,40,508,9,40,1,40,3,40,511,8,40,1,41,
  	1,41,3,41,515,8,41,1,41,1,41,1,42,1,42,1,42,3,42,522,8,42,1,42,1,42,1,
  	43,1,43,1,43,5,43,529,8,43,10,43,12,43,532,9,43,1,43,3,43,535,8,43,1,
  	44,1,44,1,44,1,44,1,45,1,45,1,46,1,46,3,46,545,8,46,1,46,1,46,1,46,1,
  	46,4,46,551,8,46,11,46,12,46,552,1,47,1,47,1,47,4,47,558,8,47,11,47,12,
  	47,559,1,48,1,48,1,48,1,48,1,48,1,48,1,48,3,48,569,8,48,1,49,1,49,1,49,
  	3,49,574,8,49,1,50,3,50,577,8,50,1,50,1,50,1,50,1,51,1,51,1,51,3,51,585,
  	8,51,1,51,1,51,1,51,3,51,590,8,51,1,51,4,51,593,8,51,11,51,12,51,594,
  	1,51,1,51,1,51,1,51,1,51,1,51,3,51,603,8,51,1,52,1,52,1,52,1,52,1,52,
  	5,52,610,8,52,10,52,12,52,613,9,52,1,52,3,52,616,8,52,3,52,618,8,52,1,
  	52,1,52,1,53,1,53,1,53,1,53,1,53,1,53,5,53,628,8,53,10,53,12,53,631,9,
  	53,1,53,1,53,1,53,0,1,70,54,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,
  	32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,74,76,
  	78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,0,10,1,0,35,36,1,0,23,
  	24,1,0,21,22,2,0,5,6,14,15,1,0,3,4,1,0,54,55,1,0,30,32,1,0,33,34,2,0,
  	58,60,65,65,1,0,41,43,691,0,111,1,0,0,0,2,117,1,0,0,0,4,126,1,0,0,0,6,
  	139,1,0,0,0,8,149,1,0,0,0,10,153,1,0,0,0,12,157,1,0,0,0,14,166,1,0,0,
  	0,16,180,1,0,0,0,18,187,1,0,0,0,20,202,1,0,0,0,22,214,1,0,0,0,24,218,
  	1,0,0,0,26,222,1,0,0,0,28,232,1,0,0,0,30,242,1,0,0,0,32,246,1,0,0,0,34,
  	251,1,0,0,0,36,253,1,0,0,0,38,266,1,0,0,0,40,279,1,0,0,0,42,281,1,0,0,
  	0,44,293,1,0,0,0,46,299,1,0,0,0,48,306,1,0,0,0,50,313,1,0,0,0,52,325,
  	1,0,0,0,54,329,1,0,0,0,56,332,1,0,0,0,58,350,1,0,0,0,60,385,1,0,0,0,62,
  	387,1,0,0,0,64,389,1,0,0,0,66,392,1,0,0,0,68,403,1,0,0,0,70,421,1,0,0,
  	0,72,462,1,0,0,0,74,464,1,0,0,0,76,480,1,0,0,0,78,494,1,0,0,0,80,501,
  	1,0,0,0,82,514,1,0,0,0,84,518,1,0,0,0,86,525,1,0,0,0,88,536,1,0,0,0,90,
  	540,1,0,0,0,92,544,1,0,0,0,94,554,1,0,0,0,96,568,1,0,0,0,98,573,1,0,0,
  	0,100,576,1,0,0,0,102,602,1,0,0,0,104,604,1,0,0,0,106,621,1,0,0,0,108,
  	112,3,6,3,0,109,112,3,8,4,0,110,112,3,10,5,0,111,108,1,0,0,0,111,109,
  	1,0,0,0,111,110,1,0,0,0,112,1,1,0,0,0,113,116,3,48,24,0,114,116,3,46,
  	23,0,115,113,1,0,0,0,115,114,1,0,0,0,116,119,1,0,0,0,117,115,1,0,0,0,
  	117,118,1,0,0,0,118,120,1,0,0,0,119,117,1,0,0,0,120,121,5,0,0,1,121,3,
  	1,0,0,0,122,125,3,48,24,0,123,125,3,46,23,0,124,122,1,0,0,0,124,123,1,
  	0,0,0,125,128,1,0,0,0,126,124,1,0,0,0,126,127,1,0,0,0,127,130,1,0,0,0,
  	128,126,1,0,0,0,129,131,3,106,53,0,130,129,1,0,0,0,130,131,1,0,0,0,131,
  	132,1,0,0,0,132,133,5,0,0,1,133,5,1,0,0,0,134,138,3,16,8,0,135,138,3,
  	66,33,0,136,138,3,12,6,0,137,134,1,0,0,0,137,135,1,0,0,0,137,136,1,0,
  	0,0,138,141,1,0,0,0,139,137,1,0,0,0,139,140,1,0,0,0,140,143,1,0,0,0,141,
  	139,1,0,0,0,142,144,3,30,15,0,143,142,1,0,0,0,144,145,1,0,0,0,145,143,
  	1,0,0,0,145,146,1,0,0,0,146,147,1,0,0,0,147,148,5,0,0,1,148,7,1,0,0,0,
  	149,150,3,22,11,0,150,151,3,18,9,0,151,152,5,0,0,1,152,9,1,0,0,0,153,
  	154,3,24,12,0,154,155,3,14,7,0,155,156,5,0,0,1,156,11,1,0,0,0,157,158,
  	5,39,0,0,158,159,5,63,0,0,159,160,5,9,0,0,160,161,3,14,7,0,161,162,5,
  	10,0,0,162,13,1,0,0,0,163,165,3,46,23,0,164,163,1,0,0,0,165,168,1,0,0,
  	0,166,164,1,0,0,0,166,167,1,0,0,0,167,170,1,0,0,0,168,166,1,0,0,0,169,
  	171,3,28,14,0,170,169,1,0,0,0,171,172,1,0,0,0,172,170,1,0,0,0,172,173,
  	1,0,0,0,173,177,1,0,0,0,174,176,3,30,15,0,175,174,1,0,0,0,176,179,1,0,
  	0,0,177,175,1,0,0,0,177,178,1,0,0,0,178,15,1,0,0,0,179,177,1,0,0,0,180,
  	181,7,0,0,0,181,182,5,63,0,0,182,183,5,9,0,0,183,184,3,18,9,0,184,185,
  	5,10,0,0,185,17,1,0,0,0,186,188,3,26,13,0,187,186,1,0,0,0,187,188,1,0,
  	0,0,188,192,1,0,0,0,189,191,3,20,10,0,190,189,1,0,0,0,191,194,1,0,0,0,
  	192,190,1,0,0,0,192,193,1,0,0,0,193,198,1,0,0,0,194,192,1,0,0,0,195,197,
  	3,32,16,0,196,195,1,0,0,0,197,200,1,0,0,0,198,196,1,0,0,0,198,199,1,0,
  	0,0,199,19,1,0,0,0,200,198,1,0,0,0,201,203,5,52,0,0,202,201,1,0,0,0,202,
  	203,1,0,0,0,203,205,1,0,0,0,204,206,5,53,0,0,205,204,1,0,0,0,205,206,
  	1,0,0,0,206,207,1,0,0,0,207,208,5,64,0,0,208,209,5,19,0,0,209,212,3,102,
  	51,0,210,211,5,20,0,0,211,213,3,70,35,0,212,210,1,0,0,0,212,213,1,0,0,
  	0,213,21,1,0,0,0,214,215,7,0,0,0,215,216,5,19,0,0,216,217,5,63,0,0,217,
  	23,1,0,0,0,218,219,5,39,0,0,219,220,5,19,0,0,220,221,5,63,0,0,221,25,
  	1,0,0,0,222,223,5,44,0,0,223,224,5,19,0,0,224,227,5,63,0,0,225,226,5,
  	16,0,0,226,228,5,63,0,0,227,225,1,0,0,0,227,228,1,0,0,0,228,230,1,0,0,
  	0,229,231,5,16,0,0,230,229,1,0,0,0,230,231,1,0,0,0,231,27,1,0,0,0,232,
  	233,5,64,0,0,233,235,5,7,0,0,234,236,3,36,18,0,235,234,1,0,0,0,235,236,
  	1,0,0,0,236,237,1,0,0,0,237,240,5,8,0,0,238,239,5,19,0,0,239,241,3,102,
  	51,0,240,238,1,0,0,0,240,241,1,0,0,0,241,29,1,0,0,0,242,243,3,28,14,0,
  	243,244,3,34,17,0,244,31,1,0,0,0,245,247,5,52,0,0,246,245,1,0,0,0,246,
  	247,1,0,0,0,247,248,1,0,0,0,248,249,3,28,14,0,249,250,3,34,17,0,250,33,
  	1,0,0,0,251,252,3,42,21,0,252,35,1,0,0,0,253,258,3,38,19,0,254,255,5,
  	16,0,0,255,257,3,38,19,0,256,254,1,0,0,0,257,260,1,0,0,0,258,256,1,0,
  	0,0,258,259,1,0,0,0,259,262,1,0,0,0,260,258,1,0,0,0,261,263,5,16,0,0,
  	262,261,1,0,0,0,262,263,1,0,0,0,263,37,1,0,0,0,264,267,3,46,23,0,265,
  	267,3,28,14,0,266,264,1,0,0,0,266,265,1,0,0,0,267,39,1,0,0,0,268,280,
  	3,44,22,0,269,280,3,46,23,0,270,280,3,48,24,0,271,280,3,50,25,0,272,280,
  	3,56,28,0,273,280,3,60,30,0,274,280,5,50,0,0,275,280,3,62,31,0,276,280,
  	3,64,32,0,277,280,3,78,39,0,278,280,3,94,47,0,279,268,1,0,0,0,279,269,
  	1,0,0,0,279,270,1,0,0,0,279,271,1,0,0,0,279,272,1,0,0,0,279,273,1,0,0,
  	0,279,274,1,0,0,0,279,275,1,0,0,0,279,276,1,0,0,0,279,277,1,0,0,0,279,
  	278,1,0,0,0,280,41,1,0,0,0,281,285,5,9,0,0,282,284,3,40,20,0,283,282,
  	1,0,0,0,284,287,1,0,0,0,285,283,1,0,0,0,285,286,1,0,0,0,286,288,1,0,0,
  	0,287,285,1,0,0,0,288,289,5,10,0,0,289,43,1,0,0,0,290,294,5,64,0,0,291,
  	294,3,92,46,0,292,294,3,94,47,0,293,290,1,0,0,0,293,291,1,0,0,0,293,292,
  	1,0,0,0,294,295,1,0,0,0,295,296,5,19,0,0,296,297,5,20,0,0,297,298,3,70,
  	35,0,298,45,1,0,0,0,299,300,5,64,0,0,300,301,5,19,0,0,301,304,3,102,51,
  	0,302,303,5,20,0,0,303,305,3,70,35,0,304,302,1,0,0,0,304,305,1,0,0,0,
  	305,47,1,0,0,0,306,308,5,64,0,0,307,309,5,26,0,0,308,307,1,0,0,0,308,
  	309,1,0,0,0,309,310,1,0,0,0,310,311,5,20,0,0,311,312,3,70,35,0,312,49,
  	1,0,0,0,313,314,5,46,0,0,314,315,3,70,35,0,315,319,3,42,21,0,316,318,
  	3,52,26,0,317,316,1,0,0,0,318,321,1,0,0,0,319,317,1,0,0,0,319,320,1,0,
  	0,0,320,323,1,0,0,0,321,319,1,0,0,0,322,324,3,54,27,0,323,322,1,0,0,0,
  	323,324,1,0,0,0,324,51,1,0,0,0,325,326,5,47,0,0,326,327,3,70,35,0,327,
  	328,3,42,21,0,328,53,1,0,0,0,329,330,5,47,0,0,330,331,3,42,21,0,331,55,
  	1,0,0,0,332,334,5,46,0,0,333,335,3,70,35,0,334,333,1,0,0,0,334,335,1,
  	0,0,0,335,336,1,0,0,0,336,340,5,9,0,0,337,339,3,58,29,0,338,337,1,0,0,
  	0,339,342,1,0,0,0,340,338,1,0,0,0,340,341,1,0,0,0,341,346,1,0,0,0,342,
  	340,1,0,0,0,343,344,5,47,0,0,344,345,5,19,0,0,345,347,3,42,21,0,346,343,
  	1,0,0,0,346,347,1,0,0,0,347,348,1,0,0,0,348,349,5,10,0,0,349,57,1,0,0,
  	0,350,351,3,70,35,0,351,352,5,19,0,0,352,353,3,42,21,0,353,59,1,0,0,0,
  	354,355,5,48,0,0,355,360,5,64,0,0,356,357,5,16,0,0,357,359,5,64,0,0,358,
  	356,1,0,0,0,359,362,1,0,0,0,360,358,1,0,0,0,360,361,1,0,0,0,361,363,1,
  	0,0,0,362,360,1,0,0,0,363,364,5,57,0,0,364,365,3,100,50,0,365,366,3,42,
  	21,0,366,386,1,0,0,0,367,368,5,48,0,0,368,373,5,64,0,0,369,370,5,16,0,
  	0,370,372,5,64,0,0,371,369,1,0,0,0,372,375,1,0,0,0,373,371,1,0,0,0,373,
  	374,1,0,0,0,374,376,1,0,0,0,375,373,1,0,0,0,376,377,5,57,0,0,377,378,
  	3,72,36,0,378,379,3,42,21,0,379,386,1,0,0,0,380,382,5,48,0,0,381,383,
  	5,64,0,0,382,381,1,0,0,0,382,383,1,0,0,0,383,384,1,0,0,0,384,386,3,42,
  	21,0,385,354,1,0,0,0,385,367,1,0,0,0,385,380,1,0,0,0,386,61,1,0,0,0,387,
  	388,5,49,0,0,388,63,1,0,0,0,389,390,5,51,0,0,390,391,3,70,35,0,391,65,
  	1,0,0,0,392,393,5,40,0,0,393,394,5,63,0,0,394,398,5,9,0,0,395,397,3,68,
  	34,0,396,395,1,0,0,0,397,400,1,0,0,0,398,396,1,0,0,0,398,399,1,0,0,0,
  	399,401,1,0,0,0,400,398,1,0,0,0,401,402,5,10,0,0,402,67,1,0,0,0,403,406,
  	5,62,0,0,404,405,5,20,0,0,405,407,5,65,0,0,406,404,1,0,0,0,406,407,1,
  	0,0,0,407,69,1,0,0,0,408,409,6,35,-1,0,409,410,5,7,0,0,410,411,3,70,35,
  	0,411,414,5,8,0,0,412,413,5,13,0,0,413,415,3,102,51,0,414,412,1,0,0,0,
  	414,415,1,0,0,0,415,422,1,0,0,0,416,419,3,72,36,0,417,418,5,13,0,0,418,
  	420,3,102,51,0,419,417,1,0,0,0,419,420,1,0,0,0,420,422,1,0,0,0,421,408,
  	1,0,0,0,421,416,1,0,0,0,422,446,1,0,0,0,423,424,10,7,0,0,424,425,7,1,
  	0,0,425,445,3,70,35,8,426,427,10,6,0,0,427,428,7,2,0,0,428,445,3,70,35,
  	7,429,430,10,5,0,0,430,431,7,3,0,0,431,445,3,70,35,6,432,433,10,4,0,0,
  	433,434,7,4,0,0,434,445,3,70,35,5,435,436,10,3,0,0,436,437,7,5,0,0,437,
  	445,3,70,35,4,438,439,10,2,0,0,439,440,7,6,0,0,440,445,3,70,35,3,441,
  	442,10,1,0,0,442,443,7,7,0,0,443,445,3,70,35,2,444,423,1,0,0,0,444,426,
  	1,0,0,0,444,429,1,0,0,0,444,432,1,0,0,0,444,435,1,0,0,0,444,438,1,0,0,
  	0,444,441,1,0,0,0,445,448,1,0,0,0,446,444,1,0,0,0,446,447,1,0,0,0,447,
  	71,1,0,0,0,448,446,1,0,0,0,449,463,5,64,0,0,450,463,5,62,0,0,451,463,
  	5,37,0,0,452,463,5,38,0,0,453,463,5,61,0,0,454,463,3,78,39,0,455,463,
  	3,104,52,0,456,463,3,84,42,0,457,463,3,90,45,0,458,463,3,74,37,0,459,
  	463,3,76,38,0,460,463,3,92,46,0,461,463,3,94,47,0,462,449,1,0,0,0,462,
  	450,1,0,0,0,462,451,1,0,0,0,462,452,1,0,0,0,462,453,1,0,0,0,462,454,1,
  	0,0,0,462,455,1,0,0,0,462,456,1,0,0,0,462,457,1,0,0,0,462,458,1,0,0,0,
  	462,459,1,0,0,0,462,460,1,0,0,0,462,461,1,0,0,0,463,73,1,0,0,0,464,476,
  	5,11,0,0,465,470,3,70,35,0,466,467,5,16,0,0,467,469,3,70,35,0,468,466,
  	1,0,0,0,469,472,1,0,0,0,470,468,1,0,0,0,470,471,1,0,0,0,471,474,1,0,0,
  	0,472,470,1,0,0,0,473,475,5,16,0,0,474,473,1,0,0,0,474,475,1,0,0,0,475,
  	477,1,0,0,0,476,465,1,0,0,0,476,477,1,0,0,0,477,478,1,0,0,0,478,479,5,
  	12,0,0,479,75,1,0,0,0,480,489,5,9,0,0,481,482,3,70,35,0,482,483,5,19,
  	0,0,483,485,3,70,35,0,484,486,5,16,0,0,485,484,1,0,0,0,485,486,1,0,0,
  	0,486,488,1,0,0,0,487,481,1,0,0,0,488,491,1,0,0,0,489,487,1,0,0,0,489,
  	490,1,0,0,0,490,492,1,0,0,0,491,489,1,0,0,0,492,493,5,10,0,0,493,77,1,
  	0,0,0,494,495,5,64,0,0,495,497,5,7,0,0,496,498,3,80,40,0,497,496,1,0,
  	0,0,497,498,1,0,0,0,498,499,1,0,0,0,499,500,5,8,0,0,500,79,1,0,0,0,501,
  	506,3,82,41,0,502,503,5,16,0,0,503,505,3,82,41,0,504,502,1,0,0,0,505,
  	508,1,0,0,0,506,504,1,0,0,0,506,507,1,0,0,0,507,510,1,0,0,0,508,506,1,
  	0,0,0,509,511,5,16,0,0,510,509,1,0,0,0,510,511,1,0,0,0,511,81,1,0,0,0,
  	512,513,5,64,0,0,513,515,5,20,0,0,514,512,1,0,0,0,514,515,1,0,0,0,515,
  	516,1,0,0,0,516,517,3,70,35,0,517,83,1,0,0,0,518,519,5,63,0,0,519,521,
  	5,7,0,0,520,522,3,86,43,0,521,520,1,0,0,0,521,522,1,0,0,0,522,523,1,0,
  	0,0,523,524,5,8,0,0,524,85,1,0,0,0,525,530,3,88,44,0,526,527,5,16,0,0,
  	527,529,3,88,44,0,528,526,1,0,0,0,529,532,1,0,0,0,530,528,1,0,0,0,530,
  	531,1,0,0,0,531,534,1,0,0,0,532,530,1,0,0,0,533,535,5,16,0,0,534,533,
  	1,0,0,0,534,535,1,0,0,0,535,87,1,0,0,0,536,537,5,64,0,0,537,538,5,20,
  	0,0,538,539,3,70,35,0,539,89,1,0,0,0,540,541,7,8,0,0,541,91,1,0,0,0,542,
  	545,3,78,39,0,543,545,5,64,0,0,544,542,1,0,0,0,544,543,1,0,0,0,545,550,
  	1,0,0,0,546,547,5,11,0,0,547,548,3,70,35,0,548,549,5,12,0,0,549,551,1,
  	0,0,0,550,546,1,0,0,0,551,552,1,0,0,0,552,550,1,0,0,0,552,553,1,0,0,0,
  	553,93,1,0,0,0,554,557,3,96,48,0,555,556,5,18,0,0,556,558,3,98,49,0,557,
  	555,1,0,0,0,558,559,1,0,0,0,559,557,1,0,0,0,559,560,1,0,0,0,560,95,1,
  	0,0,0,561,569,5,64,0,0,562,569,5,63,0,0,563,569,5,38,0,0,564,569,5,37,
  	0,0,565,569,3,78,39,0,566,569,3,84,42,0,567,569,3,92,46,0,568,561,1,0,
  	0,0,568,562,1,0,0,0,568,563,1,0,0,0,568,564,1,0,0,0,568,565,1,0,0,0,568,
  	566,1,0,0,0,568,567,1,0,0,0,569,97,1,0,0,0,570,574,5,64,0,0,571,574,3,
  	78,39,0,572,574,3,92,46,0,573,570,1,0,0,0,573,571,1,0,0,0,573,572,1,0,
  	0,0,574,99,1,0,0,0,575,577,3,70,35,0,576,575,1,0,0,0,576,577,1,0,0,0,
  	577,578,1,0,0,0,578,579,5,17,0,0,579,580,3,70,35,0,580,101,1,0,0,0,581,
  	603,5,38,0,0,582,584,5,63,0,0,583,585,5,26,0,0,584,583,1,0,0,0,584,585,
  	1,0,0,0,585,603,1,0,0,0,586,592,5,63,0,0,587,589,5,11,0,0,588,590,5,58,
  	0,0,589,588,1,0,0,0,589,590,1,0,0,0,590,591,1,0,0,0,591,593,5,12,0,0,
  	592,587,1,0,0,0,593,594,1,0,0,0,594,592,1,0,0,0,594,595,1,0,0,0,595,603,
  	1,0,0,0,596,597,5,9,0,0,597,598,3,102,51,0,598,599,5,19,0,0,599,600,3,
  	102,51,0,600,601,5,10,0,0,601,603,1,0,0,0,602,581,1,0,0,0,602,582,1,0,
  	0,0,602,586,1,0,0,0,602,596,1,0,0,0,603,103,1,0,0,0,604,605,7,9,0,0,605,
  	617,5,7,0,0,606,611,3,70,35,0,607,608,5,16,0,0,608,610,3,70,35,0,609,
  	607,1,0,0,0,610,613,1,0,0,0,611,609,1,0,0,0,611,612,1,0,0,0,612,615,1,
  	0,0,0,613,611,1,0,0,0,614,616,5,16,0,0,615,614,1,0,0,0,615,616,1,0,0,
  	0,616,618,1,0,0,0,617,606,1,0,0,0,617,618,1,0,0,0,618,619,1,0,0,0,619,
  	620,5,8,0,0,620,105,1,0,0,0,621,622,5,1,0,0,622,623,5,2,0,0,623,629,5,
  	9,0,0,624,625,5,64,0,0,625,626,5,19,0,0,626,628,3,102,51,0,627,624,1,
  	0,0,0,628,631,1,0,0,0,629,627,1,0,0,0,629,630,1,0,0,0,630,632,1,0,0,0,
  	631,629,1,0,0,0,632,633,5,10,0,0,633,107,1,0,0,0,74,111,115,117,124,126,
  	130,137,139,145,166,172,177,187,192,198,202,205,212,227,230,235,240,246,
  	258,262,266,279,285,293,304,308,319,323,334,340,346,360,373,382,385,398,
  	406,414,419,421,444,446,462,470,474,476,485,489,497,506,510,514,521,530,
  	534,544,552,559,568,573,576,584,589,594,602,611,615,617,629
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
    setState(111);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(108);
      mainFile();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(109);
      objectFile();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(110);
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
    setState(117);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(115);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
      case 1: {
        setState(113);
        implicitVarDec();
        break;
      }

      case 2: {
        setState(114);
        explicitVarDec();
        break;
      }

      default:
        break;
      }
      setState(119);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(120);
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
    setState(126);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(124);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
      case 1: {
        setState(122);
        implicitVarDec();
        break;
      }

      case 2: {
        setState(123);
        explicitVarDec();
        break;
      }

      default:
        break;
      }
      setState(128);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(130);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::T__0) {
      setState(129);
      requireEnvVars();
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
    setState(139);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1752346656768) != 0)) {
      setState(137);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case LogosParser::OBJECT:
        case LogosParser::SINGLETON: {
          setState(134);
          object();
          break;
        }

        case LogosParser::ENUM: {
          setState(135);
          enumDeclaration();
          break;
        }

        case LogosParser::INTERFACE: {
          setState(136);
          interface();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(141);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(143); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(142);
      funcImplementation();
      setState(145); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(147);
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
    setState(149);
    objectDeclaration();
    setState(150);
    objectBody();
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
    setState(153);
    interfaceDeclaration();
    setState(154);
    interfaceBody();
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
    setState(157);
    match(LogosParser::INTERFACE);
    setState(158);
    match(LogosParser::TYPE);
    setState(159);
    match(LogosParser::LBRACE);
    setState(160);
    interfaceBody();
    setState(161);
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
    setState(166);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(163);
        explicitVarDec(); 
      }
      setState(168);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
    setState(170); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(169);
              funcSignature();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(172); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(177);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(174);
      funcImplementation();
      setState(179);
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
    setState(180);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(181);
    match(LogosParser::TYPE);
    setState(182);
    match(LogosParser::LBRACE);
    setState(183);
    objectBody();
    setState(184);
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
    setState(187);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(186);
      objectImplements();
    }
    setState(192);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(189);
        field(); 
      }
      setState(194);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
    setState(198);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VISIBILITY

    || _la == LogosParser::VARIABLE) {
      setState(195);
      methodImplementation();
      setState(200);
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
    setState(202);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(201);
      match(LogosParser::VISIBILITY);
    }
    setState(205);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::CONST) {
      setState(204);
      match(LogosParser::CONST);
    }
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
    setState(214);
    _la = _input->LA(1);
    if (!(_la == LogosParser::OBJECT

    || _la == LogosParser::SINGLETON)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(215);
    match(LogosParser::COLON);
    setState(216);
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
    setState(218);
    match(LogosParser::INTERFACE);
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
    setState(222);
    match(LogosParser::IMPLEMENTS);
    setState(223);
    match(LogosParser::COLON);
    setState(224);
    match(LogosParser::TYPE);
    setState(227);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      setState(225);
      match(LogosParser::COMMA);
      setState(226);
      match(LogosParser::TYPE);
      break;
    }

    default:
      break;
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
    setState(232);
    match(LogosParser::VARIABLE);
    setState(233);
    match(LogosParser::LPAREN);
    setState(235);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(234);
      paramList();
    }
    setState(237);
    match(LogosParser::RPAREN);
    setState(240);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COLON) {
      setState(238);
      match(LogosParser::COLON);
      setState(239);
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
    setState(242);
    funcSignature();
    setState(243);
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
    setState(246);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VISIBILITY) {
      setState(245);
      match(LogosParser::VISIBILITY);
    }
    setState(248);
    funcSignature();
    setState(249);
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
    setState(251);
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
    setState(253);
    param();
    setState(258);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(254);
        match(LogosParser::COMMA);
        setState(255);
        param(); 
      }
      setState(260);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
    setState(262);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(261);
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
    setState(266);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(264);
      explicitVarDec();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(265);
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
    setState(279);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(268);
      assignment();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(269);
      explicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(270);
      implicitVarDec();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(271);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(272);
      patternMatching();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(273);
      loopStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(274);
      match(LogosParser::CONTINUE);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(275);
      breakStmt();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(276);
      returnStatement();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(277);
      funcCall();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(278);
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
    setState(281);
    match(LogosParser::LBRACE);
    setState(285);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 37) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 37)) & 201357827) != 0)) {
      setState(282);
      statement();
      setState(287);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(288);
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
    setState(293);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      setState(290);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      setState(291);
      arrayIndex();
      break;
    }

    case 3: {
      setState(292);
      selection();
      break;
    }

    default:
      break;
    }
    setState(295);
    match(LogosParser::COLON);
    setState(296);
    match(LogosParser::EQUAL);
    setState(297);
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
    setState(299);
    match(LogosParser::VARIABLE);
    setState(300);
    match(LogosParser::COLON);
    setState(301);
    type();
    setState(304);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(302);
      match(LogosParser::EQUAL);
      setState(303);
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
    setState(306);
    match(LogosParser::VARIABLE);
    setState(308);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::QUEST_MARK) {
      setState(307);
      match(LogosParser::QUEST_MARK);
    }
    setState(310);
    match(LogosParser::EQUAL);
    setState(311);
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
    setState(313);
    match(LogosParser::IF);
    setState(314);
    expr(0);
    setState(315);
    statementsBlock();
    setState(319);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(316);
        elseIfStatement(); 
      }
      setState(321);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
    setState(323);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(322);
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
    setState(325);
    match(LogosParser::ELSE);
    setState(326);
    expr(0);
    setState(327);
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
    setState(329);
    match(LogosParser::ELSE);
    setState(330);
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
    setState(332);
    match(LogosParser::IF);
    setState(334);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      setState(333);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(336);
    match(LogosParser::LBRACE);
    setState(340);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(337);
      pattern();
      setState(342);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(346);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(343);
      match(LogosParser::ELSE);
      setState(344);
      match(LogosParser::COLON);
      setState(345);
      statementsBlock();
    }
    setState(348);
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
    setState(350);
    expr(0);
    setState(351);
    match(LogosParser::COLON);
    setState(352);
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
    setState(385);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(354);
      match(LogosParser::FOR);
      setState(355);
      match(LogosParser::VARIABLE);
      setState(360);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LogosParser::COMMA) {
        setState(356);
        match(LogosParser::COMMA);
        setState(357);
        match(LogosParser::VARIABLE);
        setState(362);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(363);
      match(LogosParser::IN);
      setState(364);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(365);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(367);
      match(LogosParser::FOR);
      setState(368);
      match(LogosParser::VARIABLE);
      setState(373);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LogosParser::COMMA) {
        setState(369);
        match(LogosParser::COMMA);
        setState(370);
        match(LogosParser::VARIABLE);
        setState(375);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(376);
      match(LogosParser::IN);
      setState(377);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = unaryExpr();
      setState(378);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(380);
      match(LogosParser::FOR);
      setState(382);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::VARIABLE) {
        setState(381);
        match(LogosParser::VARIABLE);
      }
      setState(384);
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
    setState(387);
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
    setState(389);
    match(LogosParser::RETURN);
    setState(390);
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
    setState(392);
    match(LogosParser::ENUM);
    setState(393);
    match(LogosParser::TYPE);
    setState(394);
    match(LogosParser::LBRACE);
    setState(398);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST_NAME) {
      setState(395);
      enumField();
      setState(400);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(401);
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
    setState(403);
    match(LogosParser::CONST_NAME);
    setState(406);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(404);
      match(LogosParser::EQUAL);
      setState(405);
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
    setState(421);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::LPAREN: {
        setState(409);
        match(LogosParser::LPAREN);
        setState(410);
        antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
        setState(411);
        match(LogosParser::RPAREN);
        setState(414);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
        case 1: {
          setState(412);
          match(LogosParser::CAST);
          setState(413);
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
        setState(416);
        unaryExpr();
        setState(419);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          setState(417);
          match(LogosParser::CAST);
          setState(418);
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
    setState(446);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(444);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(423);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(424);
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
          setState(425);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(8);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(426);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(427);
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
          setState(428);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(7);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(429);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(430);
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
          setState(431);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(432);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(433);
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
          setState(434);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(435);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(436);
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
          setState(437);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(438);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(439);
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
          setState(440);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(3);
          break;
        }

        case 7: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(441);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(442);
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
          setState(443);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(448);
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
  enterRule(_localctx, 72, LogosParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(462);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(449);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(450);
      match(LogosParser::CONST_NAME);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(451);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(452);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(453);
      match(LogosParser::NULL_);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(454);
      funcCall();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(455);
      vector();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(456);
      constructor();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(457);
      constant();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(458);
      array();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(459);
      map();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(460);
      arrayIndex();
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(461);
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
    setState(464);
    match(LogosParser::LBRACK);
    setState(476);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(465);
      expr(0);
      setState(470);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(466);
          match(LogosParser::COMMA);
          setState(467);
          expr(0); 
        }
        setState(472);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
      }
      setState(474);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(473);
        match(LogosParser::COMMA);
      }
    }
    setState(478);
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
  enterRule(_localctx, 76, LogosParser::RuleMap);
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
    setState(480);
    match(LogosParser::LBRACE);
    setState(489);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(481);
      expr(0);
      setState(482);
      match(LogosParser::COLON);
      setState(483);
      expr(0);
      setState(485);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(484);
        match(LogosParser::COMMA);
      }
      setState(491);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(492);
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
  enterRule(_localctx, 78, LogosParser::RuleFuncCall);
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
    setState(494);
    match(LogosParser::VARIABLE);
    setState(495);
    match(LogosParser::LPAREN);
    setState(497);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(496);
      funcArgList();
    }
    setState(499);
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
  enterRule(_localctx, 80, LogosParser::RuleFuncArgList);
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
    setState(501);
    funcArg();
    setState(506);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(502);
        match(LogosParser::COMMA);
        setState(503);
        funcArg(); 
      }
      setState(508);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    }
    setState(510);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(509);
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
  enterRule(_localctx, 82, LogosParser::RuleFuncArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(514);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
    case 1: {
      setState(512);
      match(LogosParser::VARIABLE);
      setState(513);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(516);
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
  enterRule(_localctx, 84, LogosParser::RuleConstructor);
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
    setState(518);
    match(LogosParser::TYPE);
    setState(519);
    match(LogosParser::LPAREN);
    setState(521);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(520);
      constructorArgList();
    }
    setState(523);
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
  enterRule(_localctx, 86, LogosParser::RuleConstructorArgList);
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
    setState(525);
    constructorArg();
    setState(530);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(526);
        match(LogosParser::COMMA);
        setState(527);
        constructorArg(); 
      }
      setState(532);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    }
    setState(534);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(533);
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
  enterRule(_localctx, 88, LogosParser::RuleConstructorArg);

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
    match(LogosParser::VARIABLE);
    setState(537);
    match(LogosParser::EQUAL);
    setState(538);
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
  enterRule(_localctx, 90, LogosParser::RuleConstant);
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
    setState(540);
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
  enterRule(_localctx, 92, LogosParser::RuleArrayIndex);

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
    setState(544);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
    case 1: {
      setState(542);
      funcCall();
      break;
    }

    case 2: {
      setState(543);
      match(LogosParser::VARIABLE);
      break;
    }

    default:
      break;
    }
    setState(550); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(546);
              match(LogosParser::LBRACK);
              setState(547);
              expr(0);
              setState(548);
              match(LogosParser::RBRACK);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(552); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx);
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
  enterRule(_localctx, 94, LogosParser::RuleSelection);

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
    firstSelectionElement();
    setState(557); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(555);
              match(LogosParser::DOT);
              setState(556);
              innerSelectionElement();
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
  enterRule(_localctx, 96, LogosParser::RuleFirstSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(568);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(561);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(562);
      match(LogosParser::TYPE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(563);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(564);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(565);
      funcCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(566);
      constructor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(567);
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
  enterRule(_localctx, 98, LogosParser::RuleInnerSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(573);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(570);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(571);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(572);
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
  enterRule(_localctx, 100, LogosParser::RuleRange);
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
    setState(576);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(575);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
    }
    setState(578);
    match(LogosParser::DOUBLE_DOT);
    setState(579);
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
  enterRule(_localctx, 102, LogosParser::RuleType);
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
    setState(602);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(581);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(582);
      match(LogosParser::TYPE);
      setState(584);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
      case 1: {
        setState(583);
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
      setState(586);
      match(LogosParser::TYPE);
      setState(592); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(587);
                match(LogosParser::LBRACK);
                setState(589);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == LogosParser::INTEGER) {
                  setState(588);
                  match(LogosParser::INTEGER);
                }
                setState(591);
                match(LogosParser::RBRACK);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(594); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(596);
      match(LogosParser::LBRACE);
      setState(597);
      type();
      setState(598);
      match(LogosParser::COLON);
      setState(599);
      type();
      setState(600);
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
  enterRule(_localctx, 104, LogosParser::RuleVector);
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
    setState(604);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 15393162788864) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(605);
    match(LogosParser::LPAREN);
    setState(617);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 7) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 7)) & 574209075970048021) != 0)) {
      setState(606);
      expr(0);
      setState(611);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(607);
          match(LogosParser::COMMA);
          setState(608);
          expr(0); 
        }
        setState(613);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx);
      }
      setState(615);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(614);
        match(LogosParser::COMMA);
      }
    }
    setState(619);
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
  enterRule(_localctx, 106, LogosParser::RuleRequireEnvVars);
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
    setState(621);
    match(LogosParser::T__0);
    setState(622);
    match(LogosParser::T__1);
    setState(623);
    match(LogosParser::LBRACE);
    setState(629);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(624);
      match(LogosParser::VARIABLE);
      setState(625);
      match(LogosParser::COLON);
      setState(626);
      type();
      setState(631);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(632);
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
