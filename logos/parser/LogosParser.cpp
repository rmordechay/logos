
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
      "logosFile", "mainFile", "interfaceFile", "objectFile", "importStatement", 
      "objectDeclaration", "interfaceDeclaration", "objectImplements", "funcDec", 
      "funcImplementation", "funcBody", "funcCall", "constructorCall", "explicitVarDecList", 
      "explicitVarDec", "implicitVarDec", "paramCall", "paramCallList", 
      "statement", "enumDeclaration", "enumField", "statemets_block", "exprList", 
      "expr", "binaryExpr", "boolExpr", "unaryExpr", "selection", "ifStatement", 
      "elseStatement", "patterMatching", "pattern", "loopStatemet", "range", 
      "controlFlowStatement"
    },
    std::vector<std::string>{
      "", "'=='", "'>='", "'<='", "'('", "')'", "'{'", "'}'", "'['", "']'", 
      "'<'", "'>'", "','", "'..'", "'.'", "':'", "'='", "'-'", "'+'", "'*'", 
      "'/'", "'#'", "'\\u003F'", "'!'", "'%'", "'$'", "'&'", "'object'", 
      "'interface'", "'enum'", "'implements'", "'import'", "'if'", "'else'", 
      "'for'", "'break'", "'continue'", "'return'", "'and'", "'or'", "'not'", 
      "'in'"
    },
    std::vector<std::string>{
      "", "DOUBLE_EQUAL", "GREATER_EQUAL_THAN", "LESS_EQUAL_THAN", "LEFT_PAREN", 
      "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", "RIGHT_BRACKET", 
      "LEFT_ANGLE", "RIGHT_ANGLE", "COMMA", "DOUBLE_DOT", "DOT", "COLON", 
      "EQUAL", "MINUS", "PLUS", "STAR", "SLASH", "HASH", "QUEST_MARK", "EXCLA_MARK", 
      "PERCENT", "DOLLAR", "AMPERSAND", "OBJECT", "INTERFACE", "ENUM", "IMPLEMENTS", 
      "IMPORT", "IF", "ELSE", "FOR", "BREAK", "CONTINUE", "RETURN", "AND", 
      "OR", "NOT", "IN", "INTEGER", "FLOAT", "BOOL", "CONST", "TYPE", "VARIABLE", 
      "STRING", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,380,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,1,0,3,
  	0,72,8,0,1,0,1,0,1,0,3,0,77,8,0,1,1,1,1,3,1,81,8,1,1,1,4,1,84,8,1,11,
  	1,12,1,85,1,1,1,1,1,2,1,2,3,2,92,8,2,1,2,5,2,95,8,2,10,2,12,2,98,9,2,
  	1,2,4,2,101,8,2,11,2,12,2,102,1,2,5,2,106,8,2,10,2,12,2,109,9,2,1,2,1,
  	2,1,3,1,3,3,3,115,8,3,1,3,5,3,118,8,3,10,3,12,3,121,9,3,1,3,5,3,124,8,
  	3,10,3,12,3,127,9,3,1,3,1,3,1,4,1,4,1,4,5,4,134,8,4,10,4,12,4,137,9,4,
  	1,4,1,4,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,3,
  	8,156,8,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,10,1,10,1,11,1,11,1,11,5,11,170,
  	8,11,10,11,12,11,173,9,11,1,11,1,11,1,12,1,12,1,12,5,12,180,8,12,10,12,
  	12,12,183,9,12,1,12,1,12,1,13,1,13,1,13,5,13,190,8,13,10,13,12,13,193,
  	9,13,1,14,1,14,1,14,1,14,1,14,3,14,200,8,14,1,14,3,14,203,8,14,1,15,1,
  	15,1,15,3,15,208,8,15,1,16,1,16,3,16,212,8,16,1,16,1,16,1,17,1,17,1,17,
  	5,17,219,8,17,10,17,12,17,222,9,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
  	3,18,231,8,18,1,19,1,19,1,19,1,19,5,19,237,8,19,10,19,12,19,240,9,19,
  	1,19,1,19,1,20,1,20,1,20,3,20,247,8,20,1,21,1,21,5,21,251,8,21,10,21,
  	12,21,254,9,21,1,21,1,21,1,22,1,22,1,22,5,22,261,8,22,10,22,12,22,264,
  	9,22,1,23,1,23,1,23,1,23,3,23,270,8,23,1,24,1,24,1,24,1,24,1,24,1,24,
  	1,24,1,24,3,24,280,8,24,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,
  	1,26,1,26,3,26,293,8,26,1,27,1,27,1,27,5,27,298,8,27,10,27,12,27,301,
  	9,27,1,28,1,28,1,28,1,28,1,28,1,28,3,28,309,8,28,1,29,1,29,1,29,1,29,
  	5,29,315,8,29,10,29,12,29,318,9,29,1,29,1,29,3,29,322,8,29,1,30,1,30,
  	3,30,326,8,30,1,30,1,30,5,30,330,8,30,10,30,12,30,333,9,30,1,30,1,30,
  	1,30,3,30,338,8,30,1,30,1,30,1,31,1,31,1,31,1,31,1,32,1,32,3,32,348,8,
  	32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,1,32,3,
  	32,363,8,32,1,33,3,33,366,8,33,1,33,1,33,1,33,1,34,1,34,1,34,1,34,1,34,
  	1,34,1,34,3,34,378,8,34,1,34,0,0,35,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,0,3,
  	1,0,19,20,1,0,17,18,2,0,1,3,8,9,400,0,71,1,0,0,0,2,80,1,0,0,0,4,89,1,
  	0,0,0,6,112,1,0,0,0,8,130,1,0,0,0,10,140,1,0,0,0,12,144,1,0,0,0,14,148,
  	1,0,0,0,16,152,1,0,0,0,18,161,1,0,0,0,20,164,1,0,0,0,22,166,1,0,0,0,24,
  	176,1,0,0,0,26,186,1,0,0,0,28,202,1,0,0,0,30,204,1,0,0,0,32,211,1,0,0,
  	0,34,215,1,0,0,0,36,230,1,0,0,0,38,232,1,0,0,0,40,243,1,0,0,0,42,248,
  	1,0,0,0,44,257,1,0,0,0,46,269,1,0,0,0,48,279,1,0,0,0,50,281,1,0,0,0,52,
  	292,1,0,0,0,54,294,1,0,0,0,56,308,1,0,0,0,58,316,1,0,0,0,60,323,1,0,0,
  	0,62,341,1,0,0,0,64,362,1,0,0,0,66,365,1,0,0,0,68,377,1,0,0,0,70,72,3,
  	8,4,0,71,70,1,0,0,0,71,72,1,0,0,0,72,76,1,0,0,0,73,77,3,2,1,0,74,77,3,
  	6,3,0,75,77,3,4,2,0,76,73,1,0,0,0,76,74,1,0,0,0,76,75,1,0,0,0,77,1,1,
  	0,0,0,78,81,3,28,14,0,79,81,3,30,15,0,80,78,1,0,0,0,80,79,1,0,0,0,81,
  	83,1,0,0,0,82,84,3,18,9,0,83,82,1,0,0,0,84,85,1,0,0,0,85,83,1,0,0,0,85,
  	86,1,0,0,0,86,87,1,0,0,0,87,88,5,0,0,1,88,3,1,0,0,0,89,91,3,12,6,0,90,
  	92,3,14,7,0,91,90,1,0,0,0,91,92,1,0,0,0,92,96,1,0,0,0,93,95,3,28,14,0,
  	94,93,1,0,0,0,95,98,1,0,0,0,96,94,1,0,0,0,96,97,1,0,0,0,97,100,1,0,0,
  	0,98,96,1,0,0,0,99,101,3,16,8,0,100,99,1,0,0,0,101,102,1,0,0,0,102,100,
  	1,0,0,0,102,103,1,0,0,0,103,107,1,0,0,0,104,106,3,18,9,0,105,104,1,0,
  	0,0,106,109,1,0,0,0,107,105,1,0,0,0,107,108,1,0,0,0,108,110,1,0,0,0,109,
  	107,1,0,0,0,110,111,5,0,0,1,111,5,1,0,0,0,112,114,3,10,5,0,113,115,3,
  	14,7,0,114,113,1,0,0,0,114,115,1,0,0,0,115,119,1,0,0,0,116,118,3,28,14,
  	0,117,116,1,0,0,0,118,121,1,0,0,0,119,117,1,0,0,0,119,120,1,0,0,0,120,
  	125,1,0,0,0,121,119,1,0,0,0,122,124,3,18,9,0,123,122,1,0,0,0,124,127,
  	1,0,0,0,125,123,1,0,0,0,125,126,1,0,0,0,126,128,1,0,0,0,127,125,1,0,0,
  	0,128,129,5,0,0,1,129,7,1,0,0,0,130,131,5,31,0,0,131,135,5,4,0,0,132,
  	134,3,46,23,0,133,132,1,0,0,0,134,137,1,0,0,0,135,133,1,0,0,0,135,136,
  	1,0,0,0,136,138,1,0,0,0,137,135,1,0,0,0,138,139,5,5,0,0,139,9,1,0,0,0,
  	140,141,5,27,0,0,141,142,5,15,0,0,142,143,5,46,0,0,143,11,1,0,0,0,144,
  	145,5,28,0,0,145,146,5,15,0,0,146,147,5,46,0,0,147,13,1,0,0,0,148,149,
  	5,30,0,0,149,150,5,15,0,0,150,151,5,46,0,0,151,15,1,0,0,0,152,153,5,47,
  	0,0,153,155,5,4,0,0,154,156,3,26,13,0,155,154,1,0,0,0,155,156,1,0,0,0,
  	156,157,1,0,0,0,157,158,5,5,0,0,158,159,5,15,0,0,159,160,5,46,0,0,160,
  	17,1,0,0,0,161,162,3,16,8,0,162,163,3,20,10,0,163,19,1,0,0,0,164,165,
  	3,42,21,0,165,21,1,0,0,0,166,167,5,47,0,0,167,171,5,4,0,0,168,170,3,34,
  	17,0,169,168,1,0,0,0,170,173,1,0,0,0,171,169,1,0,0,0,171,172,1,0,0,0,
  	172,174,1,0,0,0,173,171,1,0,0,0,174,175,5,5,0,0,175,23,1,0,0,0,176,177,
  	5,46,0,0,177,181,5,4,0,0,178,180,3,34,17,0,179,178,1,0,0,0,180,183,1,
  	0,0,0,181,179,1,0,0,0,181,182,1,0,0,0,182,184,1,0,0,0,183,181,1,0,0,0,
  	184,185,5,5,0,0,185,25,1,0,0,0,186,191,3,28,14,0,187,188,5,12,0,0,188,
  	190,3,28,14,0,189,187,1,0,0,0,190,193,1,0,0,0,191,189,1,0,0,0,191,192,
  	1,0,0,0,192,27,1,0,0,0,193,191,1,0,0,0,194,195,5,47,0,0,195,196,5,15,
  	0,0,196,199,5,46,0,0,197,198,5,16,0,0,198,200,3,46,23,0,199,197,1,0,0,
  	0,199,200,1,0,0,0,200,203,1,0,0,0,201,203,3,38,19,0,202,194,1,0,0,0,202,
  	201,1,0,0,0,203,29,1,0,0,0,204,207,5,47,0,0,205,206,5,16,0,0,206,208,
  	3,46,23,0,207,205,1,0,0,0,207,208,1,0,0,0,208,31,1,0,0,0,209,210,5,47,
  	0,0,210,212,5,16,0,0,211,209,1,0,0,0,211,212,1,0,0,0,212,213,1,0,0,0,
  	213,214,3,46,23,0,214,33,1,0,0,0,215,220,3,32,16,0,216,217,5,12,0,0,217,
  	219,3,32,16,0,218,216,1,0,0,0,219,222,1,0,0,0,220,218,1,0,0,0,220,221,
  	1,0,0,0,221,35,1,0,0,0,222,220,1,0,0,0,223,231,3,28,14,0,224,231,3,30,
  	15,0,225,231,3,56,28,0,226,231,3,64,32,0,227,231,3,68,34,0,228,231,3,
  	38,19,0,229,231,3,46,23,0,230,223,1,0,0,0,230,224,1,0,0,0,230,225,1,0,
  	0,0,230,226,1,0,0,0,230,227,1,0,0,0,230,228,1,0,0,0,230,229,1,0,0,0,231,
  	37,1,0,0,0,232,233,5,29,0,0,233,234,5,46,0,0,234,238,5,6,0,0,235,237,
  	3,40,20,0,236,235,1,0,0,0,237,240,1,0,0,0,238,236,1,0,0,0,238,239,1,0,
  	0,0,239,241,1,0,0,0,240,238,1,0,0,0,241,242,5,7,0,0,242,39,1,0,0,0,243,
  	246,5,45,0,0,244,245,5,16,0,0,245,247,5,48,0,0,246,244,1,0,0,0,246,247,
  	1,0,0,0,247,41,1,0,0,0,248,252,5,6,0,0,249,251,3,36,18,0,250,249,1,0,
  	0,0,251,254,1,0,0,0,252,250,1,0,0,0,252,253,1,0,0,0,253,255,1,0,0,0,254,
  	252,1,0,0,0,255,256,5,7,0,0,256,43,1,0,0,0,257,262,3,46,23,0,258,259,
  	5,12,0,0,259,261,3,46,23,0,260,258,1,0,0,0,261,264,1,0,0,0,262,260,1,
  	0,0,0,262,263,1,0,0,0,263,45,1,0,0,0,264,262,1,0,0,0,265,270,3,48,24,
  	0,266,270,3,52,26,0,267,270,3,50,25,0,268,270,3,54,27,0,269,265,1,0,0,
  	0,269,266,1,0,0,0,269,267,1,0,0,0,269,268,1,0,0,0,270,47,1,0,0,0,271,
  	272,3,52,26,0,272,273,7,0,0,0,273,274,3,46,23,0,274,280,1,0,0,0,275,276,
  	3,52,26,0,276,277,7,1,0,0,277,278,3,46,23,0,278,280,1,0,0,0,279,271,1,
  	0,0,0,279,275,1,0,0,0,280,49,1,0,0,0,281,282,3,52,26,0,282,283,7,2,0,
  	0,283,284,3,46,23,0,284,51,1,0,0,0,285,293,3,22,11,0,286,293,3,24,12,
  	0,287,293,5,42,0,0,288,293,5,43,0,0,289,293,5,44,0,0,290,293,5,48,0,0,
  	291,293,5,47,0,0,292,285,1,0,0,0,292,286,1,0,0,0,292,287,1,0,0,0,292,
  	288,1,0,0,0,292,289,1,0,0,0,292,290,1,0,0,0,292,291,1,0,0,0,293,53,1,
  	0,0,0,294,299,3,52,26,0,295,296,5,14,0,0,296,298,3,52,26,0,297,295,1,
  	0,0,0,298,301,1,0,0,0,299,297,1,0,0,0,299,300,1,0,0,0,300,55,1,0,0,0,
  	301,299,1,0,0,0,302,303,5,32,0,0,303,304,3,46,23,0,304,305,3,42,21,0,
  	305,306,3,58,29,0,306,309,1,0,0,0,307,309,3,60,30,0,308,302,1,0,0,0,308,
  	307,1,0,0,0,309,57,1,0,0,0,310,311,5,33,0,0,311,312,3,46,23,0,312,313,
  	3,42,21,0,313,315,1,0,0,0,314,310,1,0,0,0,315,318,1,0,0,0,316,314,1,0,
  	0,0,316,317,1,0,0,0,317,321,1,0,0,0,318,316,1,0,0,0,319,320,5,33,0,0,
  	320,322,3,42,21,0,321,319,1,0,0,0,321,322,1,0,0,0,322,59,1,0,0,0,323,
  	325,5,32,0,0,324,326,3,46,23,0,325,324,1,0,0,0,325,326,1,0,0,0,326,327,
  	1,0,0,0,327,331,5,6,0,0,328,330,3,62,31,0,329,328,1,0,0,0,330,333,1,0,
  	0,0,331,329,1,0,0,0,331,332,1,0,0,0,332,337,1,0,0,0,333,331,1,0,0,0,334,
  	335,5,33,0,0,335,336,5,15,0,0,336,338,3,42,21,0,337,334,1,0,0,0,337,338,
  	1,0,0,0,338,339,1,0,0,0,339,340,5,7,0,0,340,61,1,0,0,0,341,342,3,46,23,
  	0,342,343,5,15,0,0,343,344,3,42,21,0,344,63,1,0,0,0,345,347,5,34,0,0,
  	346,348,3,46,23,0,347,346,1,0,0,0,347,348,1,0,0,0,348,349,1,0,0,0,349,
  	363,3,42,21,0,350,351,5,34,0,0,351,352,3,44,22,0,352,353,5,41,0,0,353,
  	354,3,46,23,0,354,355,3,42,21,0,355,363,1,0,0,0,356,357,5,34,0,0,357,
  	358,3,44,22,0,358,359,5,41,0,0,359,360,3,66,33,0,360,361,3,42,21,0,361,
  	363,1,0,0,0,362,345,1,0,0,0,362,350,1,0,0,0,362,356,1,0,0,0,363,65,1,
  	0,0,0,364,366,3,46,23,0,365,364,1,0,0,0,365,366,1,0,0,0,366,367,1,0,0,
  	0,367,368,5,13,0,0,368,369,3,46,23,0,369,67,1,0,0,0,370,371,5,35,0,0,
  	371,378,3,46,23,0,372,373,5,35,0,0,373,378,5,32,0,0,374,378,5,36,0,0,
  	375,376,5,37,0,0,376,378,3,46,23,0,377,370,1,0,0,0,377,372,1,0,0,0,377,
  	374,1,0,0,0,377,375,1,0,0,0,378,69,1,0,0,0,40,71,76,80,85,91,96,102,107,
  	114,119,125,135,155,171,181,191,199,202,207,211,220,230,238,246,252,262,
  	269,279,292,299,308,316,321,325,331,337,347,362,365,377
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

LogosParser::ImportStatementContext* LogosParser::LogosFileContext::importStatement() {
  return getRuleContext<LogosParser::ImportStatementContext>(0);
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
    setState(71);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPORT) {
      setState(70);
      importStatement();
    }
    setState(76);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::ENUM:
      case LogosParser::VARIABLE: {
        setState(73);
        mainFile();
        break;
      }

      case LogosParser::OBJECT: {
        setState(74);
        objectFile();
        break;
      }

      case LogosParser::INTERFACE: {
        setState(75);
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

LogosParser::ExplicitVarDecContext* LogosParser::MainFileContext::explicitVarDec() {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(0);
}

LogosParser::ImplicitVarDecContext* LogosParser::MainFileContext::implicitVarDec() {
  return getRuleContext<LogosParser::ImplicitVarDecContext>(0);
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
    setState(80);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(78);
      explicitVarDec();
      break;
    }

    case 2: {
      setState(79);
      implicitVarDec();
      break;
    }

    default:
      break;
    }
    setState(83); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(82);
      funcImplementation();
      setState(85); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(87);
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

std::vector<LogosParser::FuncDecContext *> LogosParser::InterfaceFileContext::funcDec() {
  return getRuleContexts<LogosParser::FuncDecContext>();
}

LogosParser::FuncDecContext* LogosParser::InterfaceFileContext::funcDec(size_t i) {
  return getRuleContext<LogosParser::FuncDecContext>(i);
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
  enterRule(_localctx, 4, LogosParser::RuleInterfaceFile);
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
    setState(89);
    interfaceDeclaration();
    setState(91);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(90);
      objectImplements();
    }
    setState(96);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(93);
        explicitVarDec(); 
      }
      setState(98);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
    setState(100); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(99);
              funcDec();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(102); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(107);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(104);
      funcImplementation();
      setState(109);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(110);
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
  enterRule(_localctx, 6, LogosParser::RuleObjectFile);
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
    setState(112);
    objectDeclaration();
    setState(114);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(113);
      objectImplements();
    }
    setState(119);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(116);
        explicitVarDec(); 
      }
      setState(121);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
    setState(125);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(122);
      funcImplementation();
      setState(127);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(128);
    match(LogosParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

LogosParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ImportStatementContext::IMPORT() {
  return getToken(LogosParser::IMPORT, 0);
}

tree::TerminalNode* LogosParser::ImportStatementContext::LEFT_PAREN() {
  return getToken(LogosParser::LEFT_PAREN, 0);
}

tree::TerminalNode* LogosParser::ImportStatementContext::RIGHT_PAREN() {
  return getToken(LogosParser::RIGHT_PAREN, 0);
}

std::vector<LogosParser::ExprContext *> LogosParser::ImportStatementContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::ImportStatementContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}


size_t LogosParser::ImportStatementContext::getRuleIndex() const {
  return LogosParser::RuleImportStatement;
}


LogosParser::ImportStatementContext* LogosParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 8, LogosParser::RuleImportStatement);
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
    match(LogosParser::IMPORT);
    setState(131);
    match(LogosParser::LEFT_PAREN);
    setState(135);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821376) != 0)) {
      setState(132);
      expr();
      setState(137);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(138);
    match(LogosParser::RIGHT_PAREN);
   
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
  enterRule(_localctx, 10, LogosParser::RuleObjectDeclaration);

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
  enterRule(_localctx, 12, LogosParser::RuleInterfaceDeclaration);

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
  enterRule(_localctx, 14, LogosParser::RuleObjectImplements);

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

//----------------- FuncDecContext ------------------------------------------------------------------

LogosParser::FuncDecContext::FuncDecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::FuncDecContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::FuncDecContext::LEFT_PAREN() {
  return getToken(LogosParser::LEFT_PAREN, 0);
}

tree::TerminalNode* LogosParser::FuncDecContext::RIGHT_PAREN() {
  return getToken(LogosParser::RIGHT_PAREN, 0);
}

tree::TerminalNode* LogosParser::FuncDecContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

tree::TerminalNode* LogosParser::FuncDecContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

LogosParser::ExplicitVarDecListContext* LogosParser::FuncDecContext::explicitVarDecList() {
  return getRuleContext<LogosParser::ExplicitVarDecListContext>(0);
}


size_t LogosParser::FuncDecContext::getRuleIndex() const {
  return LogosParser::RuleFuncDec;
}


LogosParser::FuncDecContext* LogosParser::funcDec() {
  FuncDecContext *_localctx = _tracker.createInstance<FuncDecContext>(_ctx, getState());
  enterRule(_localctx, 16, LogosParser::RuleFuncDec);
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
    match(LogosParser::LEFT_PAREN);
    setState(155);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ENUM

    || _la == LogosParser::VARIABLE) {
      setState(154);
      explicitVarDecList();
    }
    setState(157);
    match(LogosParser::RIGHT_PAREN);
    setState(158);
    match(LogosParser::COLON);
    setState(159);
    match(LogosParser::TYPE);
   
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

LogosParser::FuncDecContext* LogosParser::FuncImplementationContext::funcDec() {
  return getRuleContext<LogosParser::FuncDecContext>(0);
}

LogosParser::FuncBodyContext* LogosParser::FuncImplementationContext::funcBody() {
  return getRuleContext<LogosParser::FuncBodyContext>(0);
}


size_t LogosParser::FuncImplementationContext::getRuleIndex() const {
  return LogosParser::RuleFuncImplementation;
}


LogosParser::FuncImplementationContext* LogosParser::funcImplementation() {
  FuncImplementationContext *_localctx = _tracker.createInstance<FuncImplementationContext>(_ctx, getState());
  enterRule(_localctx, 18, LogosParser::RuleFuncImplementation);

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
    funcDec();
    setState(162);
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

LogosParser::Statemets_blockContext* LogosParser::FuncBodyContext::statemets_block() {
  return getRuleContext<LogosParser::Statemets_blockContext>(0);
}


size_t LogosParser::FuncBodyContext::getRuleIndex() const {
  return LogosParser::RuleFuncBody;
}


LogosParser::FuncBodyContext* LogosParser::funcBody() {
  FuncBodyContext *_localctx = _tracker.createInstance<FuncBodyContext>(_ctx, getState());
  enterRule(_localctx, 20, LogosParser::RuleFuncBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    statemets_block();
   
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

tree::TerminalNode* LogosParser::FuncCallContext::LEFT_PAREN() {
  return getToken(LogosParser::LEFT_PAREN, 0);
}

tree::TerminalNode* LogosParser::FuncCallContext::RIGHT_PAREN() {
  return getToken(LogosParser::RIGHT_PAREN, 0);
}

std::vector<LogosParser::ParamCallListContext *> LogosParser::FuncCallContext::paramCallList() {
  return getRuleContexts<LogosParser::ParamCallListContext>();
}

LogosParser::ParamCallListContext* LogosParser::FuncCallContext::paramCallList(size_t i) {
  return getRuleContext<LogosParser::ParamCallListContext>(i);
}


size_t LogosParser::FuncCallContext::getRuleIndex() const {
  return LogosParser::RuleFuncCall;
}


LogosParser::FuncCallContext* LogosParser::funcCall() {
  FuncCallContext *_localctx = _tracker.createInstance<FuncCallContext>(_ctx, getState());
  enterRule(_localctx, 22, LogosParser::RuleFuncCall);
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
    setState(166);
    match(LogosParser::VARIABLE);
    setState(167);
    match(LogosParser::LEFT_PAREN);
    setState(171);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821376) != 0)) {
      setState(168);
      paramCallList();
      setState(173);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(174);
    match(LogosParser::RIGHT_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructorCallContext ------------------------------------------------------------------

LogosParser::ConstructorCallContext::ConstructorCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ConstructorCallContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::ConstructorCallContext::LEFT_PAREN() {
  return getToken(LogosParser::LEFT_PAREN, 0);
}

tree::TerminalNode* LogosParser::ConstructorCallContext::RIGHT_PAREN() {
  return getToken(LogosParser::RIGHT_PAREN, 0);
}

std::vector<LogosParser::ParamCallListContext *> LogosParser::ConstructorCallContext::paramCallList() {
  return getRuleContexts<LogosParser::ParamCallListContext>();
}

LogosParser::ParamCallListContext* LogosParser::ConstructorCallContext::paramCallList(size_t i) {
  return getRuleContext<LogosParser::ParamCallListContext>(i);
}


size_t LogosParser::ConstructorCallContext::getRuleIndex() const {
  return LogosParser::RuleConstructorCall;
}


LogosParser::ConstructorCallContext* LogosParser::constructorCall() {
  ConstructorCallContext *_localctx = _tracker.createInstance<ConstructorCallContext>(_ctx, getState());
  enterRule(_localctx, 24, LogosParser::RuleConstructorCall);
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
    setState(176);
    match(LogosParser::TYPE);
    setState(177);
    match(LogosParser::LEFT_PAREN);
    setState(181);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821376) != 0)) {
      setState(178);
      paramCallList();
      setState(183);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(184);
    match(LogosParser::RIGHT_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExplicitVarDecListContext ------------------------------------------------------------------

LogosParser::ExplicitVarDecListContext::ExplicitVarDecListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::ExplicitVarDecContext *> LogosParser::ExplicitVarDecListContext::explicitVarDec() {
  return getRuleContexts<LogosParser::ExplicitVarDecContext>();
}

LogosParser::ExplicitVarDecContext* LogosParser::ExplicitVarDecListContext::explicitVarDec(size_t i) {
  return getRuleContext<LogosParser::ExplicitVarDecContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::ExplicitVarDecListContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ExplicitVarDecListContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ExplicitVarDecListContext::getRuleIndex() const {
  return LogosParser::RuleExplicitVarDecList;
}


LogosParser::ExplicitVarDecListContext* LogosParser::explicitVarDecList() {
  ExplicitVarDecListContext *_localctx = _tracker.createInstance<ExplicitVarDecListContext>(_ctx, getState());
  enterRule(_localctx, 26, LogosParser::RuleExplicitVarDecList);
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
    explicitVarDec();
    setState(191);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::COMMA) {
      setState(187);
      match(LogosParser::COMMA);
      setState(188);
      explicitVarDec();
      setState(193);
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

tree::TerminalNode* LogosParser::ExplicitVarDecContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::ExplicitVarDecContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}

LogosParser::ExprContext* LogosParser::ExplicitVarDecContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

LogosParser::EnumDeclarationContext* LogosParser::ExplicitVarDecContext::enumDeclaration() {
  return getRuleContext<LogosParser::EnumDeclarationContext>(0);
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
    setState(202);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::VARIABLE: {
        enterOuterAlt(_localctx, 1);
        setState(194);
        match(LogosParser::VARIABLE);
        setState(195);
        match(LogosParser::COLON);
        setState(196);
        match(LogosParser::TYPE);
        setState(199);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == LogosParser::EQUAL) {
          setState(197);
          match(LogosParser::EQUAL);
          setState(198);
          expr();
        }
        break;
      }

      case LogosParser::ENUM: {
        enterOuterAlt(_localctx, 2);
        setState(201);
        enumDeclaration();
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
    setState(207);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(205);
      match(LogosParser::EQUAL);
      setState(206);
      expr();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamCallContext ------------------------------------------------------------------

LogosParser::ParamCallContext::ParamCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ExprContext* LogosParser::ParamCallContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::ParamCallContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::ParamCallContext::EQUAL() {
  return getToken(LogosParser::EQUAL, 0);
}


size_t LogosParser::ParamCallContext::getRuleIndex() const {
  return LogosParser::RuleParamCall;
}


LogosParser::ParamCallContext* LogosParser::paramCall() {
  ParamCallContext *_localctx = _tracker.createInstance<ParamCallContext>(_ctx, getState());
  enterRule(_localctx, 32, LogosParser::RuleParamCall);

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
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      setState(209);
      match(LogosParser::VARIABLE);
      setState(210);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(213);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamCallListContext ------------------------------------------------------------------

LogosParser::ParamCallListContext::ParamCallListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::ParamCallContext *> LogosParser::ParamCallListContext::paramCall() {
  return getRuleContexts<LogosParser::ParamCallContext>();
}

LogosParser::ParamCallContext* LogosParser::ParamCallListContext::paramCall(size_t i) {
  return getRuleContext<LogosParser::ParamCallContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::ParamCallListContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::ParamCallListContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::ParamCallListContext::getRuleIndex() const {
  return LogosParser::RuleParamCallList;
}


LogosParser::ParamCallListContext* LogosParser::paramCallList() {
  ParamCallListContext *_localctx = _tracker.createInstance<ParamCallListContext>(_ctx, getState());
  enterRule(_localctx, 34, LogosParser::RuleParamCallList);
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
    setState(215);
    paramCall();
    setState(220);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::COMMA) {
      setState(216);
      match(LogosParser::COMMA);
      setState(217);
      paramCall();
      setState(222);
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

//----------------- StatementContext ------------------------------------------------------------------

LogosParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
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

LogosParser::LoopStatemetContext* LogosParser::StatementContext::loopStatemet() {
  return getRuleContext<LogosParser::LoopStatemetContext>(0);
}

LogosParser::ControlFlowStatementContext* LogosParser::StatementContext::controlFlowStatement() {
  return getRuleContext<LogosParser::ControlFlowStatementContext>(0);
}

LogosParser::EnumDeclarationContext* LogosParser::StatementContext::enumDeclaration() {
  return getRuleContext<LogosParser::EnumDeclarationContext>(0);
}

LogosParser::ExprContext* LogosParser::StatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::StatementContext::getRuleIndex() const {
  return LogosParser::RuleStatement;
}


LogosParser::StatementContext* LogosParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 36, LogosParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(230);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(223);
      explicitVarDec();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(224);
      implicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(225);
      ifStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(226);
      loopStatemet();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(227);
      controlFlowStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(228);
      enumDeclaration();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(229);
      expr();
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

tree::TerminalNode* LogosParser::EnumDeclarationContext::TYPE() {
  return getToken(LogosParser::TYPE, 0);
}

tree::TerminalNode* LogosParser::EnumDeclarationContext::LEFT_BRACE() {
  return getToken(LogosParser::LEFT_BRACE, 0);
}

tree::TerminalNode* LogosParser::EnumDeclarationContext::RIGHT_BRACE() {
  return getToken(LogosParser::RIGHT_BRACE, 0);
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
  enterRule(_localctx, 38, LogosParser::RuleEnumDeclaration);
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
    match(LogosParser::ENUM);
    setState(233);
    match(LogosParser::TYPE);
    setState(234);
    match(LogosParser::LEFT_BRACE);
    setState(238);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::CONST) {
      setState(235);
      enumField();
      setState(240);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(241);
    match(LogosParser::RIGHT_BRACE);
   
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
  enterRule(_localctx, 40, LogosParser::RuleEnumField);
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
    setState(243);
    match(LogosParser::CONST);
    setState(246);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(244);
      match(LogosParser::EQUAL);
      setState(245);
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

//----------------- Statemets_blockContext ------------------------------------------------------------------

LogosParser::Statemets_blockContext::Statemets_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::Statemets_blockContext::LEFT_BRACE() {
  return getToken(LogosParser::LEFT_BRACE, 0);
}

tree::TerminalNode* LogosParser::Statemets_blockContext::RIGHT_BRACE() {
  return getToken(LogosParser::RIGHT_BRACE, 0);
}

std::vector<LogosParser::StatementContext *> LogosParser::Statemets_blockContext::statement() {
  return getRuleContexts<LogosParser::StatementContext>();
}

LogosParser::StatementContext* LogosParser::Statemets_blockContext::statement(size_t i) {
  return getRuleContext<LogosParser::StatementContext>(i);
}


size_t LogosParser::Statemets_blockContext::getRuleIndex() const {
  return LogosParser::RuleStatemets_block;
}


LogosParser::Statemets_blockContext* LogosParser::statemets_block() {
  Statemets_blockContext *_localctx = _tracker.createInstance<Statemets_blockContext>(_ctx, getState());
  enterRule(_localctx, 42, LogosParser::RuleStatemets_block);
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
    setState(248);
    match(LogosParser::LEFT_BRACE);
    setState(252);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523630064697344) != 0)) {
      setState(249);
      statement();
      setState(254);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(255);
    match(LogosParser::RIGHT_BRACE);
   
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
  enterRule(_localctx, 44, LogosParser::RuleExprList);
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
    setState(257);
    expr();
    setState(262);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::COMMA) {
      setState(258);
      match(LogosParser::COMMA);
      setState(259);
      expr();
      setState(264);
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

//----------------- ExprContext ------------------------------------------------------------------

LogosParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::BinaryExprContext* LogosParser::ExprContext::binaryExpr() {
  return getRuleContext<LogosParser::BinaryExprContext>(0);
}

LogosParser::UnaryExprContext* LogosParser::ExprContext::unaryExpr() {
  return getRuleContext<LogosParser::UnaryExprContext>(0);
}

LogosParser::BoolExprContext* LogosParser::ExprContext::boolExpr() {
  return getRuleContext<LogosParser::BoolExprContext>(0);
}

LogosParser::SelectionContext* LogosParser::ExprContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}


size_t LogosParser::ExprContext::getRuleIndex() const {
  return LogosParser::RuleExpr;
}


LogosParser::ExprContext* LogosParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 46, LogosParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(269);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(265);
      binaryExpr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(266);
      unaryExpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(267);
      boolExpr();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(268);
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

//----------------- BinaryExprContext ------------------------------------------------------------------

LogosParser::BinaryExprContext::BinaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::UnaryExprContext* LogosParser::BinaryExprContext::unaryExpr() {
  return getRuleContext<LogosParser::UnaryExprContext>(0);
}

LogosParser::ExprContext* LogosParser::BinaryExprContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::BinaryExprContext::STAR() {
  return getToken(LogosParser::STAR, 0);
}

tree::TerminalNode* LogosParser::BinaryExprContext::SLASH() {
  return getToken(LogosParser::SLASH, 0);
}

tree::TerminalNode* LogosParser::BinaryExprContext::PLUS() {
  return getToken(LogosParser::PLUS, 0);
}

tree::TerminalNode* LogosParser::BinaryExprContext::MINUS() {
  return getToken(LogosParser::MINUS, 0);
}


size_t LogosParser::BinaryExprContext::getRuleIndex() const {
  return LogosParser::RuleBinaryExpr;
}


LogosParser::BinaryExprContext* LogosParser::binaryExpr() {
  BinaryExprContext *_localctx = _tracker.createInstance<BinaryExprContext>(_ctx, getState());
  enterRule(_localctx, 48, LogosParser::RuleBinaryExpr);
  size_t _la = 0;

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(271);
      unaryExpr();
      setState(272);
      _la = _input->LA(1);
      if (!(_la == LogosParser::STAR

      || _la == LogosParser::SLASH)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(273);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(275);
      unaryExpr();
      setState(276);
      _la = _input->LA(1);
      if (!(_la == LogosParser::MINUS

      || _la == LogosParser::PLUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(277);
      expr();
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

//----------------- BoolExprContext ------------------------------------------------------------------

LogosParser::BoolExprContext::BoolExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::UnaryExprContext* LogosParser::BoolExprContext::unaryExpr() {
  return getRuleContext<LogosParser::UnaryExprContext>(0);
}

LogosParser::ExprContext* LogosParser::BoolExprContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::BoolExprContext::DOUBLE_EQUAL() {
  return getToken(LogosParser::DOUBLE_EQUAL, 0);
}

tree::TerminalNode* LogosParser::BoolExprContext::RIGHT_BRACKET() {
  return getToken(LogosParser::RIGHT_BRACKET, 0);
}

tree::TerminalNode* LogosParser::BoolExprContext::LEFT_BRACKET() {
  return getToken(LogosParser::LEFT_BRACKET, 0);
}

tree::TerminalNode* LogosParser::BoolExprContext::GREATER_EQUAL_THAN() {
  return getToken(LogosParser::GREATER_EQUAL_THAN, 0);
}

tree::TerminalNode* LogosParser::BoolExprContext::LESS_EQUAL_THAN() {
  return getToken(LogosParser::LESS_EQUAL_THAN, 0);
}


size_t LogosParser::BoolExprContext::getRuleIndex() const {
  return LogosParser::RuleBoolExpr;
}


LogosParser::BoolExprContext* LogosParser::boolExpr() {
  BoolExprContext *_localctx = _tracker.createInstance<BoolExprContext>(_ctx, getState());
  enterRule(_localctx, 50, LogosParser::RuleBoolExpr);
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
    unaryExpr();
    setState(282);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 782) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(283);
    expr();
   
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

LogosParser::FuncCallContext* LogosParser::UnaryExprContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}

LogosParser::ConstructorCallContext* LogosParser::UnaryExprContext::constructorCall() {
  return getRuleContext<LogosParser::ConstructorCallContext>(0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::INTEGER() {
  return getToken(LogosParser::INTEGER, 0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::FLOAT() {
  return getToken(LogosParser::FLOAT, 0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::BOOL() {
  return getToken(LogosParser::BOOL, 0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::STRING() {
  return getToken(LogosParser::STRING, 0);
}

tree::TerminalNode* LogosParser::UnaryExprContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}


size_t LogosParser::UnaryExprContext::getRuleIndex() const {
  return LogosParser::RuleUnaryExpr;
}


LogosParser::UnaryExprContext* LogosParser::unaryExpr() {
  UnaryExprContext *_localctx = _tracker.createInstance<UnaryExprContext>(_ctx, getState());
  enterRule(_localctx, 52, LogosParser::RuleUnaryExpr);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(285);
      funcCall();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(286);
      constructorCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(287);
      match(LogosParser::INTEGER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(288);
      match(LogosParser::FLOAT);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(289);
      match(LogosParser::BOOL);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(290);
      match(LogosParser::STRING);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(291);
      match(LogosParser::VARIABLE);
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

std::vector<LogosParser::UnaryExprContext *> LogosParser::SelectionContext::unaryExpr() {
  return getRuleContexts<LogosParser::UnaryExprContext>();
}

LogosParser::UnaryExprContext* LogosParser::SelectionContext::unaryExpr(size_t i) {
  return getRuleContext<LogosParser::UnaryExprContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::SelectionContext::DOT() {
  return getTokens(LogosParser::DOT);
}

tree::TerminalNode* LogosParser::SelectionContext::DOT(size_t i) {
  return getToken(LogosParser::DOT, i);
}


size_t LogosParser::SelectionContext::getRuleIndex() const {
  return LogosParser::RuleSelection;
}


LogosParser::SelectionContext* LogosParser::selection() {
  SelectionContext *_localctx = _tracker.createInstance<SelectionContext>(_ctx, getState());
  enterRule(_localctx, 54, LogosParser::RuleSelection);
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
    setState(294);
    unaryExpr();
    setState(299);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::DOT) {
      setState(295);
      match(LogosParser::DOT);
      setState(296);
      unaryExpr();
      setState(301);
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

LogosParser::Statemets_blockContext* LogosParser::IfStatementContext::statemets_block() {
  return getRuleContext<LogosParser::Statemets_blockContext>(0);
}

LogosParser::ElseStatementContext* LogosParser::IfStatementContext::elseStatement() {
  return getRuleContext<LogosParser::ElseStatementContext>(0);
}

LogosParser::PatterMatchingContext* LogosParser::IfStatementContext::patterMatching() {
  return getRuleContext<LogosParser::PatterMatchingContext>(0);
}


size_t LogosParser::IfStatementContext::getRuleIndex() const {
  return LogosParser::RuleIfStatement;
}


LogosParser::IfStatementContext* LogosParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 56, LogosParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(308);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(302);
      match(LogosParser::IF);
      setState(303);
      expr();
      setState(304);
      statemets_block();
      setState(305);
      elseStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(307);
      patterMatching();
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

//----------------- ElseStatementContext ------------------------------------------------------------------

LogosParser::ElseStatementContext::ElseStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LogosParser::ElseStatementContext::ELSE() {
  return getTokens(LogosParser::ELSE);
}

tree::TerminalNode* LogosParser::ElseStatementContext::ELSE(size_t i) {
  return getToken(LogosParser::ELSE, i);
}

std::vector<LogosParser::ExprContext *> LogosParser::ElseStatementContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::ElseStatementContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

std::vector<LogosParser::Statemets_blockContext *> LogosParser::ElseStatementContext::statemets_block() {
  return getRuleContexts<LogosParser::Statemets_blockContext>();
}

LogosParser::Statemets_blockContext* LogosParser::ElseStatementContext::statemets_block(size_t i) {
  return getRuleContext<LogosParser::Statemets_blockContext>(i);
}


size_t LogosParser::ElseStatementContext::getRuleIndex() const {
  return LogosParser::RuleElseStatement;
}


LogosParser::ElseStatementContext* LogosParser::elseStatement() {
  ElseStatementContext *_localctx = _tracker.createInstance<ElseStatementContext>(_ctx, getState());
  enterRule(_localctx, 58, LogosParser::RuleElseStatement);
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
    setState(316);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(310);
        match(LogosParser::ELSE);
        setState(311);
        expr();
        setState(312);
        statemets_block(); 
      }
      setState(318);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
    }
    setState(321);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(319);
      match(LogosParser::ELSE);
      setState(320);
      statemets_block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatterMatchingContext ------------------------------------------------------------------

LogosParser::PatterMatchingContext::PatterMatchingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::PatterMatchingContext::IF() {
  return getToken(LogosParser::IF, 0);
}

tree::TerminalNode* LogosParser::PatterMatchingContext::LEFT_BRACE() {
  return getToken(LogosParser::LEFT_BRACE, 0);
}

tree::TerminalNode* LogosParser::PatterMatchingContext::RIGHT_BRACE() {
  return getToken(LogosParser::RIGHT_BRACE, 0);
}

LogosParser::ExprContext* LogosParser::PatterMatchingContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

std::vector<LogosParser::PatternContext *> LogosParser::PatterMatchingContext::pattern() {
  return getRuleContexts<LogosParser::PatternContext>();
}

LogosParser::PatternContext* LogosParser::PatterMatchingContext::pattern(size_t i) {
  return getRuleContext<LogosParser::PatternContext>(i);
}

tree::TerminalNode* LogosParser::PatterMatchingContext::ELSE() {
  return getToken(LogosParser::ELSE, 0);
}

tree::TerminalNode* LogosParser::PatterMatchingContext::COLON() {
  return getToken(LogosParser::COLON, 0);
}

LogosParser::Statemets_blockContext* LogosParser::PatterMatchingContext::statemets_block() {
  return getRuleContext<LogosParser::Statemets_blockContext>(0);
}


size_t LogosParser::PatterMatchingContext::getRuleIndex() const {
  return LogosParser::RulePatterMatching;
}


LogosParser::PatterMatchingContext* LogosParser::patterMatching() {
  PatterMatchingContext *_localctx = _tracker.createInstance<PatterMatchingContext>(_ctx, getState());
  enterRule(_localctx, 60, LogosParser::RulePatterMatching);
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
    setState(323);
    match(LogosParser::IF);
    setState(325);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821376) != 0)) {
      setState(324);
      expr();
    }
    setState(327);
    match(LogosParser::LEFT_BRACE);
    setState(331);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821376) != 0)) {
      setState(328);
      pattern();
      setState(333);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(337);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(334);
      match(LogosParser::ELSE);
      setState(335);
      match(LogosParser::COLON);
      setState(336);
      statemets_block();
    }
    setState(339);
    match(LogosParser::RIGHT_BRACE);
   
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

LogosParser::Statemets_blockContext* LogosParser::PatternContext::statemets_block() {
  return getRuleContext<LogosParser::Statemets_blockContext>(0);
}


size_t LogosParser::PatternContext::getRuleIndex() const {
  return LogosParser::RulePattern;
}


LogosParser::PatternContext* LogosParser::pattern() {
  PatternContext *_localctx = _tracker.createInstance<PatternContext>(_ctx, getState());
  enterRule(_localctx, 62, LogosParser::RulePattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(341);
    expr();
    setState(342);
    match(LogosParser::COLON);
    setState(343);
    statemets_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoopStatemetContext ------------------------------------------------------------------

LogosParser::LoopStatemetContext::LoopStatemetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::LoopStatemetContext::FOR() {
  return getToken(LogosParser::FOR, 0);
}

LogosParser::Statemets_blockContext* LogosParser::LoopStatemetContext::statemets_block() {
  return getRuleContext<LogosParser::Statemets_blockContext>(0);
}

LogosParser::ExprContext* LogosParser::LoopStatemetContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

LogosParser::ExprListContext* LogosParser::LoopStatemetContext::exprList() {
  return getRuleContext<LogosParser::ExprListContext>(0);
}

tree::TerminalNode* LogosParser::LoopStatemetContext::IN() {
  return getToken(LogosParser::IN, 0);
}

LogosParser::RangeContext* LogosParser::LoopStatemetContext::range() {
  return getRuleContext<LogosParser::RangeContext>(0);
}


size_t LogosParser::LoopStatemetContext::getRuleIndex() const {
  return LogosParser::RuleLoopStatemet;
}


LogosParser::LoopStatemetContext* LogosParser::loopStatemet() {
  LoopStatemetContext *_localctx = _tracker.createInstance<LoopStatemetContext>(_ctx, getState());
  enterRule(_localctx, 64, LogosParser::RuleLoopStatemet);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(362);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(345);
      match(LogosParser::FOR);
      setState(347);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 523367534821376) != 0)) {
        setState(346);
        expr();
      }
      setState(349);
      statemets_block();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(350);
      match(LogosParser::FOR);
      setState(351);
      exprList();
      setState(352);
      match(LogosParser::IN);
      setState(353);
      expr();
      setState(354);
      statemets_block();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(356);
      match(LogosParser::FOR);
      setState(357);
      exprList();
      setState(358);
      match(LogosParser::IN);
      setState(359);
      range();
      setState(360);
      statemets_block();
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
  enterRule(_localctx, 66, LogosParser::RuleRange);
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
    setState(365);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 523367534821376) != 0)) {
      setState(364);
      expr();
    }
    setState(367);
    match(LogosParser::DOUBLE_DOT);
    setState(368);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ControlFlowStatementContext ------------------------------------------------------------------

LogosParser::ControlFlowStatementContext::ControlFlowStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::ControlFlowStatementContext::BREAK() {
  return getToken(LogosParser::BREAK, 0);
}

LogosParser::ExprContext* LogosParser::ControlFlowStatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::ControlFlowStatementContext::IF() {
  return getToken(LogosParser::IF, 0);
}

tree::TerminalNode* LogosParser::ControlFlowStatementContext::CONTINUE() {
  return getToken(LogosParser::CONTINUE, 0);
}

tree::TerminalNode* LogosParser::ControlFlowStatementContext::RETURN() {
  return getToken(LogosParser::RETURN, 0);
}


size_t LogosParser::ControlFlowStatementContext::getRuleIndex() const {
  return LogosParser::RuleControlFlowStatement;
}


LogosParser::ControlFlowStatementContext* LogosParser::controlFlowStatement() {
  ControlFlowStatementContext *_localctx = _tracker.createInstance<ControlFlowStatementContext>(_ctx, getState());
  enterRule(_localctx, 68, LogosParser::RuleControlFlowStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(377);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(370);
      match(LogosParser::BREAK);
      setState(371);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(372);
      match(LogosParser::BREAK);
      setState(373);
      match(LogosParser::IF);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(374);
      match(LogosParser::CONTINUE);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(375);
      match(LogosParser::RETURN);
      setState(376);
      expr();
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

void LogosParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  logosParserInitialize();
#else
  ::antlr4::internal::call_once(logosParserOnceFlag, logosParserInitialize);
#endif
}
