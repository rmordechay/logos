
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
      "returnStatement", "enumDeclaration", "enumField", "expr", "unaryExpr", 
      "array", "map", "funcCall", "constructor", "funcArgList", "funcArg", 
      "constant", "arrayIndex", "selection", "firstSelectionElement", "innerSelectionElement", 
      "range", "type", "vector"
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
  	4,1,59,481,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,1,0,1,
  	0,1,0,3,0,88,8,0,1,1,5,1,91,8,1,10,1,12,1,94,9,1,1,1,4,1,97,8,1,11,1,
  	12,1,98,1,1,1,1,1,2,1,2,3,2,105,8,2,1,2,5,2,108,8,2,10,2,12,2,111,9,2,
  	1,2,5,2,114,8,2,10,2,12,2,117,9,2,1,2,1,2,1,3,1,3,5,3,123,8,3,10,3,12,
  	3,126,9,3,1,3,4,3,129,8,3,11,3,12,3,130,1,3,5,3,134,8,3,10,3,12,3,137,
  	9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,
  	7,3,7,156,8,7,1,7,1,7,1,7,3,7,161,8,7,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,
  	10,5,10,171,8,10,10,10,12,10,174,9,10,1,10,3,10,177,8,10,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,190,8,11,1,12,1,12,5,
  	12,194,8,12,10,12,12,12,197,9,12,1,12,1,12,1,13,1,13,1,13,3,13,204,8,
  	13,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,3,14,215,8,14,1,15,1,
  	15,1,15,1,15,1,16,1,16,1,16,1,16,5,16,225,8,16,10,16,12,16,228,9,16,1,
  	16,3,16,231,8,16,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,19,1,19,3,19,242,
  	8,19,1,19,1,19,5,19,246,8,19,10,19,12,19,249,9,19,1,19,1,19,1,19,3,19,
  	254,8,19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,5,21,266,8,
  	21,10,21,12,21,269,9,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,1,21,5,21,
  	279,8,21,10,21,12,21,282,9,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,290,
  	8,21,1,21,3,21,293,8,21,1,22,1,22,1,22,1,22,1,22,3,22,300,8,22,1,23,1,
  	23,1,23,1,24,1,24,1,24,1,24,5,24,309,8,24,10,24,12,24,312,9,24,1,24,1,
  	24,1,25,1,25,1,25,3,25,319,8,25,1,26,1,26,1,26,1,26,1,26,1,26,3,26,327,
  	8,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,26,5,26,338,8,26,10,26,
  	12,26,341,9,26,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,
  	1,27,3,27,355,8,27,1,28,1,28,1,28,1,28,5,28,361,8,28,10,28,12,28,364,
  	9,28,1,28,3,28,367,8,28,1,28,1,28,1,29,1,29,1,29,1,29,1,29,3,29,376,8,
  	29,5,29,378,8,29,10,29,12,29,381,9,29,1,29,1,29,1,30,1,30,1,30,3,30,388,
  	8,30,1,30,1,30,1,31,1,31,1,31,3,31,395,8,31,1,31,1,31,1,32,1,32,1,32,
  	5,32,402,8,32,10,32,12,32,405,9,32,1,32,3,32,408,8,32,1,33,1,33,3,33,
  	412,8,33,1,33,1,33,1,34,1,34,1,35,1,35,3,35,420,8,35,1,35,1,35,1,35,1,
  	35,4,35,426,8,35,11,35,12,35,427,1,36,1,36,1,36,4,36,433,8,36,11,36,12,
  	36,434,1,37,1,37,1,37,1,37,1,37,1,37,1,37,3,37,444,8,37,1,38,1,38,1,38,
  	3,38,449,8,38,1,39,3,39,452,8,39,1,39,1,39,1,39,1,40,1,40,3,40,459,8,
  	40,1,40,1,40,1,40,3,40,464,8,40,1,40,4,40,467,8,40,11,40,12,40,468,1,
  	40,1,40,1,40,1,40,1,40,1,40,3,40,477,8,40,1,41,1,41,1,41,0,1,52,42,0,
  	2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,
  	52,54,56,58,60,62,64,66,68,70,72,74,76,78,80,82,0,5,1,0,20,21,1,0,18,
  	19,2,0,1,4,11,12,2,0,49,51,56,56,1,0,33,36,521,0,87,1,0,0,0,2,92,1,0,
  	0,0,4,102,1,0,0,0,6,120,1,0,0,0,8,140,1,0,0,0,10,144,1,0,0,0,12,148,1,
  	0,0,0,14,152,1,0,0,0,16,162,1,0,0,0,18,165,1,0,0,0,20,167,1,0,0,0,22,
  	189,1,0,0,0,24,191,1,0,0,0,26,203,1,0,0,0,28,209,1,0,0,0,30,216,1,0,0,
  	0,32,220,1,0,0,0,34,232,1,0,0,0,36,236,1,0,0,0,38,239,1,0,0,0,40,257,
  	1,0,0,0,42,292,1,0,0,0,44,299,1,0,0,0,46,301,1,0,0,0,48,304,1,0,0,0,50,
  	315,1,0,0,0,52,326,1,0,0,0,54,354,1,0,0,0,56,356,1,0,0,0,58,370,1,0,0,
  	0,60,384,1,0,0,0,62,391,1,0,0,0,64,398,1,0,0,0,66,411,1,0,0,0,68,415,
  	1,0,0,0,70,419,1,0,0,0,72,429,1,0,0,0,74,443,1,0,0,0,76,448,1,0,0,0,78,
  	451,1,0,0,0,80,476,1,0,0,0,82,478,1,0,0,0,84,88,3,2,1,0,85,88,3,4,2,0,
  	86,88,3,6,3,0,87,84,1,0,0,0,87,85,1,0,0,0,87,86,1,0,0,0,88,1,1,0,0,0,
  	89,91,3,48,24,0,90,89,1,0,0,0,91,94,1,0,0,0,92,90,1,0,0,0,92,93,1,0,0,
  	0,93,96,1,0,0,0,94,92,1,0,0,0,95,97,3,16,8,0,96,95,1,0,0,0,97,98,1,0,
  	0,0,98,96,1,0,0,0,98,99,1,0,0,0,99,100,1,0,0,0,100,101,5,0,0,1,101,3,
  	1,0,0,0,102,104,3,8,4,0,103,105,3,12,6,0,104,103,1,0,0,0,104,105,1,0,
  	0,0,105,109,1,0,0,0,106,108,3,28,14,0,107,106,1,0,0,0,108,111,1,0,0,0,
  	109,107,1,0,0,0,109,110,1,0,0,0,110,115,1,0,0,0,111,109,1,0,0,0,112,114,
  	3,16,8,0,113,112,1,0,0,0,114,117,1,0,0,0,115,113,1,0,0,0,115,116,1,0,
  	0,0,116,118,1,0,0,0,117,115,1,0,0,0,118,119,5,0,0,1,119,5,1,0,0,0,120,
  	124,3,10,5,0,121,123,3,28,14,0,122,121,1,0,0,0,123,126,1,0,0,0,124,122,
  	1,0,0,0,124,125,1,0,0,0,125,128,1,0,0,0,126,124,1,0,0,0,127,129,3,14,
  	7,0,128,127,1,0,0,0,129,130,1,0,0,0,130,128,1,0,0,0,130,131,1,0,0,0,131,
  	135,1,0,0,0,132,134,3,16,8,0,133,132,1,0,0,0,134,137,1,0,0,0,135,133,
  	1,0,0,0,135,136,1,0,0,0,136,138,1,0,0,0,137,135,1,0,0,0,138,139,5,0,0,
  	1,139,7,1,0,0,0,140,141,5,28,0,0,141,142,5,16,0,0,142,143,5,54,0,0,143,
  	9,1,0,0,0,144,145,5,31,0,0,145,146,5,16,0,0,146,147,5,54,0,0,147,11,1,
  	0,0,0,148,149,5,37,0,0,149,150,5,16,0,0,150,151,5,54,0,0,151,13,1,0,0,
  	0,152,153,5,55,0,0,153,155,5,5,0,0,154,156,3,20,10,0,155,154,1,0,0,0,
  	155,156,1,0,0,0,156,157,1,0,0,0,157,160,5,6,0,0,158,159,5,16,0,0,159,
  	161,3,80,40,0,160,158,1,0,0,0,160,161,1,0,0,0,161,15,1,0,0,0,162,163,
  	3,14,7,0,163,164,3,18,9,0,164,17,1,0,0,0,165,166,3,24,12,0,166,19,1,0,
  	0,0,167,172,3,28,14,0,168,169,5,13,0,0,169,171,3,28,14,0,170,168,1,0,
  	0,0,171,174,1,0,0,0,172,170,1,0,0,0,172,173,1,0,0,0,173,176,1,0,0,0,174,
  	172,1,0,0,0,175,177,5,13,0,0,176,175,1,0,0,0,176,177,1,0,0,0,177,21,1,
  	0,0,0,178,190,3,26,13,0,179,190,3,28,14,0,180,190,3,30,15,0,181,190,3,
  	32,16,0,182,190,3,38,19,0,183,190,3,42,21,0,184,190,3,44,22,0,185,190,
  	3,46,23,0,186,190,3,48,24,0,187,190,3,60,30,0,188,190,3,72,36,0,189,178,
  	1,0,0,0,189,179,1,0,0,0,189,180,1,0,0,0,189,181,1,0,0,0,189,182,1,0,0,
  	0,189,183,1,0,0,0,189,184,1,0,0,0,189,185,1,0,0,0,189,186,1,0,0,0,189,
  	187,1,0,0,0,189,188,1,0,0,0,190,23,1,0,0,0,191,195,5,7,0,0,192,194,3,
  	22,11,0,193,192,1,0,0,0,194,197,1,0,0,0,195,193,1,0,0,0,195,196,1,0,0,
  	0,196,198,1,0,0,0,197,195,1,0,0,0,198,199,5,8,0,0,199,25,1,0,0,0,200,
  	204,5,55,0,0,201,204,3,70,35,0,202,204,3,72,36,0,203,200,1,0,0,0,203,
  	201,1,0,0,0,203,202,1,0,0,0,204,205,1,0,0,0,205,206,5,16,0,0,206,207,
  	5,17,0,0,207,208,3,52,26,0,208,27,1,0,0,0,209,210,5,55,0,0,210,211,5,
  	16,0,0,211,214,3,80,40,0,212,213,5,17,0,0,213,215,3,52,26,0,214,212,1,
  	0,0,0,214,215,1,0,0,0,215,29,1,0,0,0,216,217,5,55,0,0,217,218,5,17,0,
  	0,218,219,3,52,26,0,219,31,1,0,0,0,220,221,5,39,0,0,221,222,3,52,26,0,
  	222,226,3,24,12,0,223,225,3,34,17,0,224,223,1,0,0,0,225,228,1,0,0,0,226,
  	224,1,0,0,0,226,227,1,0,0,0,227,230,1,0,0,0,228,226,1,0,0,0,229,231,3,
  	36,18,0,230,229,1,0,0,0,230,231,1,0,0,0,231,33,1,0,0,0,232,233,5,40,0,
  	0,233,234,3,52,26,0,234,235,3,24,12,0,235,35,1,0,0,0,236,237,5,40,0,0,
  	237,238,3,24,12,0,238,37,1,0,0,0,239,241,5,39,0,0,240,242,3,52,26,0,241,
  	240,1,0,0,0,241,242,1,0,0,0,242,243,1,0,0,0,243,247,5,7,0,0,244,246,3,
  	40,20,0,245,244,1,0,0,0,246,249,1,0,0,0,247,245,1,0,0,0,247,248,1,0,0,
  	0,248,253,1,0,0,0,249,247,1,0,0,0,250,251,5,40,0,0,251,252,5,16,0,0,252,
  	254,3,24,12,0,253,250,1,0,0,0,253,254,1,0,0,0,254,255,1,0,0,0,255,256,
  	5,8,0,0,256,39,1,0,0,0,257,258,3,52,26,0,258,259,5,16,0,0,259,260,3,24,
  	12,0,260,41,1,0,0,0,261,262,5,41,0,0,262,267,5,55,0,0,263,264,5,13,0,
  	0,264,266,5,55,0,0,265,263,1,0,0,0,266,269,1,0,0,0,267,265,1,0,0,0,267,
  	268,1,0,0,0,268,270,1,0,0,0,269,267,1,0,0,0,270,271,5,48,0,0,271,272,
  	3,78,39,0,272,273,3,24,12,0,273,293,1,0,0,0,274,275,5,41,0,0,275,280,
  	5,55,0,0,276,277,5,13,0,0,277,279,5,55,0,0,278,276,1,0,0,0,279,282,1,
  	0,0,0,280,278,1,0,0,0,280,281,1,0,0,0,281,283,1,0,0,0,282,280,1,0,0,0,
  	283,284,5,48,0,0,284,285,3,54,27,0,285,286,3,24,12,0,286,293,1,0,0,0,
  	287,289,5,41,0,0,288,290,5,55,0,0,289,288,1,0,0,0,289,290,1,0,0,0,290,
  	291,1,0,0,0,291,293,3,24,12,0,292,261,1,0,0,0,292,274,1,0,0,0,292,287,
  	1,0,0,0,293,43,1,0,0,0,294,295,5,42,0,0,295,300,3,52,26,0,296,297,5,42,
  	0,0,297,300,5,39,0,0,298,300,5,43,0,0,299,294,1,0,0,0,299,296,1,0,0,0,
  	299,298,1,0,0,0,300,45,1,0,0,0,301,302,5,44,0,0,302,303,3,52,26,0,303,
  	47,1,0,0,0,304,305,5,32,0,0,305,306,5,54,0,0,306,310,5,7,0,0,307,309,
  	3,50,25,0,308,307,1,0,0,0,309,312,1,0,0,0,310,308,1,0,0,0,310,311,1,0,
  	0,0,311,313,1,0,0,0,312,310,1,0,0,0,313,314,5,8,0,0,314,49,1,0,0,0,315,
  	318,5,53,0,0,316,317,5,17,0,0,317,319,5,56,0,0,318,316,1,0,0,0,318,319,
  	1,0,0,0,319,51,1,0,0,0,320,321,6,26,-1,0,321,327,3,54,27,0,322,323,5,
  	5,0,0,323,324,3,52,26,0,324,325,5,6,0,0,325,327,1,0,0,0,326,320,1,0,0,
  	0,326,322,1,0,0,0,327,339,1,0,0,0,328,329,10,5,0,0,329,330,7,0,0,0,330,
  	338,3,52,26,6,331,332,10,4,0,0,332,333,7,1,0,0,333,338,3,52,26,5,334,
  	335,10,3,0,0,335,336,7,2,0,0,336,338,3,52,26,4,337,328,1,0,0,0,337,331,
  	1,0,0,0,337,334,1,0,0,0,338,341,1,0,0,0,339,337,1,0,0,0,339,340,1,0,0,
  	0,340,53,1,0,0,0,341,339,1,0,0,0,342,355,5,55,0,0,343,355,5,53,0,0,344,
  	355,5,29,0,0,345,355,5,30,0,0,346,355,5,52,0,0,347,355,3,60,30,0,348,
  	355,3,62,31,0,349,355,3,68,34,0,350,355,3,56,28,0,351,355,3,58,29,0,352,
  	355,3,70,35,0,353,355,3,72,36,0,354,342,1,0,0,0,354,343,1,0,0,0,354,344,
  	1,0,0,0,354,345,1,0,0,0,354,346,1,0,0,0,354,347,1,0,0,0,354,348,1,0,0,
  	0,354,349,1,0,0,0,354,350,1,0,0,0,354,351,1,0,0,0,354,352,1,0,0,0,354,
  	353,1,0,0,0,355,55,1,0,0,0,356,357,5,9,0,0,357,362,3,52,26,0,358,359,
  	5,13,0,0,359,361,3,52,26,0,360,358,1,0,0,0,361,364,1,0,0,0,362,360,1,
  	0,0,0,362,363,1,0,0,0,363,366,1,0,0,0,364,362,1,0,0,0,365,367,5,13,0,
  	0,366,365,1,0,0,0,366,367,1,0,0,0,367,368,1,0,0,0,368,369,5,10,0,0,369,
  	57,1,0,0,0,370,379,5,7,0,0,371,372,3,52,26,0,372,373,5,16,0,0,373,375,
  	3,52,26,0,374,376,5,13,0,0,375,374,1,0,0,0,375,376,1,0,0,0,376,378,1,
  	0,0,0,377,371,1,0,0,0,378,381,1,0,0,0,379,377,1,0,0,0,379,380,1,0,0,0,
  	380,382,1,0,0,0,381,379,1,0,0,0,382,383,5,8,0,0,383,59,1,0,0,0,384,385,
  	5,55,0,0,385,387,5,5,0,0,386,388,3,64,32,0,387,386,1,0,0,0,387,388,1,
  	0,0,0,388,389,1,0,0,0,389,390,5,6,0,0,390,61,1,0,0,0,391,392,5,54,0,0,
  	392,394,5,5,0,0,393,395,3,64,32,0,394,393,1,0,0,0,394,395,1,0,0,0,395,
  	396,1,0,0,0,396,397,5,6,0,0,397,63,1,0,0,0,398,403,3,66,33,0,399,400,
  	5,13,0,0,400,402,3,66,33,0,401,399,1,0,0,0,402,405,1,0,0,0,403,401,1,
  	0,0,0,403,404,1,0,0,0,404,407,1,0,0,0,405,403,1,0,0,0,406,408,5,13,0,
  	0,407,406,1,0,0,0,407,408,1,0,0,0,408,65,1,0,0,0,409,410,5,55,0,0,410,
  	412,5,17,0,0,411,409,1,0,0,0,411,412,1,0,0,0,412,413,1,0,0,0,413,414,
  	3,52,26,0,414,67,1,0,0,0,415,416,7,3,0,0,416,69,1,0,0,0,417,420,3,60,
  	30,0,418,420,5,55,0,0,419,417,1,0,0,0,419,418,1,0,0,0,420,425,1,0,0,0,
  	421,422,5,9,0,0,422,423,3,52,26,0,423,424,5,10,0,0,424,426,1,0,0,0,425,
  	421,1,0,0,0,426,427,1,0,0,0,427,425,1,0,0,0,427,428,1,0,0,0,428,71,1,
  	0,0,0,429,432,3,74,37,0,430,431,5,15,0,0,431,433,3,76,38,0,432,430,1,
  	0,0,0,433,434,1,0,0,0,434,432,1,0,0,0,434,435,1,0,0,0,435,73,1,0,0,0,
  	436,444,5,55,0,0,437,444,5,54,0,0,438,444,5,30,0,0,439,444,5,29,0,0,440,
  	444,3,60,30,0,441,444,3,62,31,0,442,444,3,70,35,0,443,436,1,0,0,0,443,
  	437,1,0,0,0,443,438,1,0,0,0,443,439,1,0,0,0,443,440,1,0,0,0,443,441,1,
  	0,0,0,443,442,1,0,0,0,444,75,1,0,0,0,445,449,5,55,0,0,446,449,3,60,30,
  	0,447,449,3,70,35,0,448,445,1,0,0,0,448,446,1,0,0,0,448,447,1,0,0,0,449,
  	77,1,0,0,0,450,452,3,52,26,0,451,450,1,0,0,0,451,452,1,0,0,0,452,453,
  	1,0,0,0,453,454,5,14,0,0,454,455,3,52,26,0,455,79,1,0,0,0,456,458,5,54,
  	0,0,457,459,5,23,0,0,458,457,1,0,0,0,458,459,1,0,0,0,459,477,1,0,0,0,
  	460,466,5,54,0,0,461,463,5,9,0,0,462,464,5,49,0,0,463,462,1,0,0,0,463,
  	464,1,0,0,0,464,465,1,0,0,0,465,467,5,10,0,0,466,461,1,0,0,0,467,468,
  	1,0,0,0,468,466,1,0,0,0,468,469,1,0,0,0,469,477,1,0,0,0,470,471,5,7,0,
  	0,471,472,3,80,40,0,472,473,5,16,0,0,473,474,3,80,40,0,474,475,5,8,0,
  	0,475,477,1,0,0,0,476,456,1,0,0,0,476,460,1,0,0,0,476,470,1,0,0,0,477,
  	81,1,0,0,0,478,479,7,4,0,0,479,83,1,0,0,0,52,87,92,98,104,109,115,124,
  	130,135,155,160,172,176,189,195,203,214,226,230,241,247,253,267,280,289,
  	292,299,310,318,326,337,339,354,362,366,375,379,387,394,403,407,411,419,
  	427,434,443,448,451,458,463,468,476
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
      case LogosParser::ENUM:
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

std::vector<LogosParser::EnumDeclarationContext *> LogosParser::MainFileContext::enumDeclaration() {
  return getRuleContexts<LogosParser::EnumDeclarationContext>();
}

LogosParser::EnumDeclarationContext* LogosParser::MainFileContext::enumDeclaration(size_t i) {
  return getRuleContext<LogosParser::EnumDeclarationContext>(i);
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
    setState(92);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::ENUM) {
      setState(89);
      enumDeclaration();
      setState(94);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(96); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(95);
      funcImplementation();
      setState(98); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(100);
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
    setState(102);
    objectDeclaration();
    setState(104);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(103);
      objectImplements();
    }
    setState(109);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(106);
        explicitVarDec(); 
      }
      setState(111);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
    setState(115);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(112);
      funcImplementation();
      setState(117);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(118);
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
    setState(120);
    interfaceDeclaration();
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

LogosParser::PatternMatchingContext* LogosParser::StatementContext::patternMatching() {
  return getRuleContext<LogosParser::PatternMatchingContext>(0);
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

LogosParser::SelectionContext* LogosParser::StatementContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
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
    setState(189);
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
      patternMatching();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(183);
      loopStatement();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(184);
      controlFlow();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(185);
      returnStatement();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(186);
      enumDeclaration();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(187);
      funcCall();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(188);
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
    setState(191);
    match(LogosParser::LBRACE);
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 54076736538673152) != 0)) {
      setState(192);
      statement();
      setState(197);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(198);
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
    setState(203);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(200);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      setState(201);
      arrayIndex();
      break;
    }

    case 3: {
      setState(202);
      selection();
      break;
    }

    default:
      break;
    }
    setState(205);
    match(LogosParser::COLON);
    setState(206);
    match(LogosParser::EQUAL);
    setState(207);
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
    setState(209);
    match(LogosParser::VARIABLE);
    setState(210);
    match(LogosParser::COLON);
    setState(211);
    type();
    setState(214);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(212);
      match(LogosParser::EQUAL);
      setState(213);
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
    setState(216);
    match(LogosParser::VARIABLE);
    setState(217);
    match(LogosParser::EQUAL);
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
    enterOuterAlt(_localctx, 1);
    setState(220);
    match(LogosParser::IF);
    setState(221);
    expr(0);
    setState(222);
    statementsBlock();
    setState(226);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(223);
        elseIfStatement(); 
      }
      setState(228);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx);
    }
    setState(230);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(229);
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
    setState(232);
    match(LogosParser::ELSE);
    setState(233);
    expr(0);
    setState(234);
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
    setState(236);
    match(LogosParser::ELSE);
    setState(237);
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
    setState(239);
    match(LogosParser::IF);
    setState(241);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(240);
      expr(0);
      break;
    }

    default:
      break;
    }
    setState(243);
    match(LogosParser::LBRACE);
    setState(247);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 143552239733047968) != 0)) {
      setState(244);
      pattern();
      setState(249);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(253);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(250);
      match(LogosParser::ELSE);
      setState(251);
      match(LogosParser::COLON);
      setState(252);
      statementsBlock();
    }
    setState(255);
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
    setState(257);
    expr(0);
    setState(258);
    match(LogosParser::COLON);
    setState(259);
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
    setState(292);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(261);
      match(LogosParser::FOR);
      setState(262);
      match(LogosParser::VARIABLE);
      setState(267);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LogosParser::COMMA) {
        setState(263);
        match(LogosParser::COMMA);
        setState(264);
        match(LogosParser::VARIABLE);
        setState(269);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(270);
      match(LogosParser::IN);
      setState(271);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableRange = range();
      setState(272);
      statementsBlock();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(274);
      match(LogosParser::FOR);
      setState(275);
      match(LogosParser::VARIABLE);
      setState(280);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == LogosParser::COMMA) {
        setState(276);
        match(LogosParser::COMMA);
        setState(277);
        match(LogosParser::VARIABLE);
        setState(282);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(283);
      match(LogosParser::IN);
      setState(284);
      antlrcpp::downCast<LoopStatementContext *>(_localctx)->iterableExpr = unaryExpr();
      setState(285);
      statementsBlock();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(287);
      match(LogosParser::FOR);
      setState(289);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::VARIABLE) {
        setState(288);
        match(LogosParser::VARIABLE);
      }
      setState(291);
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
    setState(299);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(294);
      match(LogosParser::BREAK);
      setState(295);
      expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(296);
      match(LogosParser::BREAK);
      setState(297);
      match(LogosParser::IF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(298);
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
    setState(301);
    match(LogosParser::RETURN);
    setState(302);
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
    setState(304);
    match(LogosParser::ENUM);
    setState(305);
    match(LogosParser::TYPE);
    setState(306);
    match(LogosParser::LBRACE);
    setState(310);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST) {
      setState(307);
      enumField();
      setState(312);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(313);
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
    setState(315);
    match(LogosParser::CONST);
    setState(318);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(316);
      match(LogosParser::EQUAL);
      setState(317);
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
    setState(326);
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
      case LogosParser::CONST:
      case LogosParser::TYPE:
      case LogosParser::VARIABLE:
      case LogosParser::STRING: {
        setState(321);
        unaryExpr();
        break;
      }

      case LogosParser::LPAREN: {
        setState(322);
        match(LogosParser::LPAREN);
        setState(323);
        antlrcpp::downCast<ExprContext *>(_localctx)->left = expr(0);
        setState(324);
        match(LogosParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(339);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(337);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(328);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(329);
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
          setState(330);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(331);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(332);
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
          setState(333);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          _localctx->left = previousContext;
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(334);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(335);
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
          setState(336);
          antlrcpp::downCast<ExprContext *>(_localctx)->right = expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(341);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
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

tree::TerminalNode* LogosParser::UnaryExprContext::CONST() {
  return getToken(LogosParser::CONST, 0);
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
  enterRule(_localctx, 54, LogosParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(354);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(342);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(343);
      match(LogosParser::CONST);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(344);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(345);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(346);
      match(LogosParser::NULL_);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(347);
      funcCall();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(348);
      constructor();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(349);
      constant();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(350);
      array();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(351);
      map();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(352);
      arrayIndex();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(353);
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
  enterRule(_localctx, 56, LogosParser::RuleArray);
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
    match(LogosParser::LBRACK);
    setState(357);
    expr(0);
    setState(362);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(358);
        match(LogosParser::COMMA);
        setState(359);
        expr(0); 
      }
      setState(364);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
    setState(366);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(365);
      match(LogosParser::COMMA);
    }
    setState(368);
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
  enterRule(_localctx, 58, LogosParser::RuleMap);
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
    setState(370);
    match(LogosParser::LBRACE);
    setState(379);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 143552239733047968) != 0)) {
      setState(371);
      expr(0);
      setState(372);
      match(LogosParser::COLON);
      setState(373);
      expr(0);
      setState(375);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::COMMA) {
        setState(374);
        match(LogosParser::COMMA);
      }
      setState(381);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(382);
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
  enterRule(_localctx, 60, LogosParser::RuleFuncCall);
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
    setState(384);
    match(LogosParser::VARIABLE);
    setState(385);
    match(LogosParser::LPAREN);
    setState(387);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 143552239733047968) != 0)) {
      setState(386);
      funcArgList();
    }
    setState(389);
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
  enterRule(_localctx, 62, LogosParser::RuleConstructor);
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
    setState(391);
    match(LogosParser::TYPE);
    setState(392);
    match(LogosParser::LPAREN);
    setState(394);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 143552239733047968) != 0)) {
      setState(393);
      funcArgList();
    }
    setState(396);
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
  enterRule(_localctx, 64, LogosParser::RuleFuncArgList);
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
    setState(398);
    funcArg();
    setState(403);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(399);
        match(LogosParser::COMMA);
        setState(400);
        funcArg(); 
      }
      setState(405);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    }
    setState(407);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::COMMA) {
      setState(406);
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
  enterRule(_localctx, 66, LogosParser::RuleFuncArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(411);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      setState(409);
      match(LogosParser::VARIABLE);
      setState(410);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(413);
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
  enterRule(_localctx, 68, LogosParser::RuleConstant);
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
  enterRule(_localctx, 70, LogosParser::RuleArrayIndex);

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
    setState(419);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(417);
      funcCall();
      break;
    }

    case 2: {
      setState(418);
      match(LogosParser::VARIABLE);
      break;
    }

    default:
      break;
    }
    setState(425); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(421);
              match(LogosParser::LBRACK);
              setState(422);
              expr(0);
              setState(423);
              match(LogosParser::RBRACK);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(427); 
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
  enterRule(_localctx, 72, LogosParser::RuleSelection);

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
    setState(429);
    firstSelectionElement();
    setState(432); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(430);
              match(LogosParser::DOT);
              setState(431);
              innerSelectionElement();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(434); 
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
  enterRule(_localctx, 74, LogosParser::RuleFirstSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(443);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(436);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(437);
      match(LogosParser::TYPE);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(438);
      match(LogosParser::SELF_CLASS);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(439);
      match(LogosParser::SELF_INSTANCE);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(440);
      funcCall();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(441);
      constructor();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(442);
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
  enterRule(_localctx, 76, LogosParser::RuleInnerSelectionElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(448);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(445);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(446);
      funcCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(447);
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
    setState(451);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 143552239733047968) != 0)) {
      setState(450);
      antlrcpp::downCast<RangeContext *>(_localctx)->start = expr(0);
    }
    setState(453);
    match(LogosParser::DOUBLE_DOT);
    setState(454);
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
  enterRule(_localctx, 80, LogosParser::RuleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(476);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(456);
      match(LogosParser::TYPE);
      setState(458);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == LogosParser::QUEST_MARK) {
        setState(457);
        match(LogosParser::QUEST_MARK);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(460);
      match(LogosParser::TYPE);
      setState(466); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(461);
        match(LogosParser::LBRACK);
        setState(463);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LogosParser::INTEGER) {
          setState(462);
          match(LogosParser::INTEGER);
        }
        setState(465);
        match(LogosParser::RBRACK);
        setState(468); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == LogosParser::LBRACK);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(470);
      match(LogosParser::LBRACE);
      setState(471);
      type();
      setState(472);
      match(LogosParser::COLON);
      setState(473);
      type();
      setState(474);
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
  enterRule(_localctx, 82, LogosParser::RuleVector);
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
    setState(478);
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
