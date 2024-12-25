
// Generated from Logos.g4 by ANTLR 4.13.2


#include "LogosLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct LogosLexerStaticData final {
  LogosLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LogosLexerStaticData(const LogosLexerStaticData&) = delete;
  LogosLexerStaticData(LogosLexerStaticData&&) = delete;
  LogosLexerStaticData& operator=(const LogosLexerStaticData&) = delete;
  LogosLexerStaticData& operator=(LogosLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag logoslexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<LogosLexerStaticData> logoslexerLexerStaticData = nullptr;

void logoslexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (logoslexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(logoslexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<LogosLexerStaticData>(
    std::vector<std::string>{
      "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", 
      "RIGHT_BRACKET", "LEFT_ANGLE", "RIGHT_ANGLE", "COMMA", "DOT", "COLON", 
      "EQUAL", "MINUS", "PLUS", "STAR", "SLASH", "HASH", "QUEST_MARK", "EXCLA_MARK", 
      "PERCENT", "DOLLAR", "AMPERSAND", "OBJECT", "INTERFACE", "ENUM", "IMPLEMENTS", 
      "IMPORT", "IF", "FOR", "BREAK", "CONTINUE", "RETURN", "AND", "OR", 
      "NOT", "IN", "INTEGER", "FLOAT", "BOOL", "VARIABLE", "TYPE", "CONST", 
      "STRING", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'{'", "'}'", "'['", "']'", "'<'", "'>'", "','", 
      "'.'", "':'", "'='", "'-'", "'+'", "'*'", "'/'", "'#'", "'\\u003F'", 
      "'!'", "'%'", "'$'", "'&'", "'object'", "'interface'", "'enum'", "'implements'", 
      "'import'", "'if'", "'for'", "'break'", "'continue'", "'return'", 
      "'and'", "'or'", "'not'", "'in'"
    },
    std::vector<std::string>{
      "", "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", 
      "RIGHT_BRACKET", "LEFT_ANGLE", "RIGHT_ANGLE", "COMMA", "DOT", "COLON", 
      "EQUAL", "MINUS", "PLUS", "STAR", "SLASH", "HASH", "QUEST_MARK", "EXCLA_MARK", 
      "PERCENT", "DOLLAR", "AMPERSAND", "OBJECT", "INTERFACE", "ENUM", "IMPLEMENTS", 
      "IMPORT", "IF", "FOR", "BREAK", "CONTINUE", "RETURN", "AND", "OR", 
      "NOT", "IN", "INTEGER", "FLOAT", "BOOL", "VARIABLE", "TYPE", "CONST", 
      "STRING", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,46,311,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,
  	7,42,2,43,7,43,2,44,7,44,2,45,7,45,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,
  	4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,
  	1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,19,
  	1,19,1,20,1,20,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,23,1,23,
  	1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,24,1,25,
  	1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,1,26,1,26,1,26,1,26,
  	1,26,1,26,1,26,1,27,1,27,1,27,1,28,1,28,1,28,1,28,1,29,1,29,1,29,1,29,
  	1,29,1,29,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,31,1,31,1,31,
  	1,31,1,31,1,31,1,31,1,32,1,32,1,32,1,32,1,33,1,33,1,33,1,34,1,34,1,34,
  	1,34,1,35,1,35,1,35,1,36,4,36,222,8,36,11,36,12,36,223,1,37,4,37,227,
  	8,37,11,37,12,37,228,1,37,1,37,4,37,233,8,37,11,37,12,37,234,1,38,1,38,
  	1,38,1,38,1,38,1,38,1,38,1,38,1,38,3,38,246,8,38,1,39,1,39,5,39,250,8,
  	39,10,39,12,39,253,9,39,1,40,1,40,5,40,257,8,40,10,40,12,40,260,9,40,
  	1,41,4,41,263,8,41,11,41,12,41,264,1,42,1,42,1,42,1,42,5,42,271,8,42,
  	10,42,12,42,274,9,42,1,42,1,42,1,43,1,43,1,43,1,43,5,43,282,8,43,10,43,
  	12,43,285,9,43,1,43,1,43,1,44,1,44,1,44,1,44,1,44,5,44,294,8,44,10,44,
  	12,44,297,9,44,1,44,1,44,1,44,1,44,1,44,1,44,1,45,4,45,306,8,45,11,45,
  	12,45,307,1,45,1,45,1,295,0,46,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,
  	9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,
  	21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,
  	65,33,67,34,69,35,71,36,73,37,75,38,77,39,79,40,81,41,83,42,85,43,87,
  	44,89,45,91,46,1,0,8,1,0,48,57,2,0,95,95,97,122,4,0,48,57,65,90,95,95,
  	97,122,1,0,65,90,3,0,48,57,65,90,95,95,2,0,34,34,92,92,2,0,10,10,13,13,
  	3,0,9,10,13,13,32,32,322,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,
  	0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,
  	19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,0,29,1,
  	0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,1,0,0,
  	0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,0,0,0,
  	51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,0,61,1,
  	0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,1,0,0,
  	0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,0,79,1,0,0,0,0,81,1,0,0,0,0,
  	83,1,0,0,0,0,85,1,0,0,0,0,87,1,0,0,0,0,89,1,0,0,0,0,91,1,0,0,0,1,93,1,
  	0,0,0,3,95,1,0,0,0,5,97,1,0,0,0,7,99,1,0,0,0,9,101,1,0,0,0,11,103,1,0,
  	0,0,13,105,1,0,0,0,15,107,1,0,0,0,17,109,1,0,0,0,19,111,1,0,0,0,21,113,
  	1,0,0,0,23,115,1,0,0,0,25,117,1,0,0,0,27,119,1,0,0,0,29,121,1,0,0,0,31,
  	123,1,0,0,0,33,125,1,0,0,0,35,127,1,0,0,0,37,129,1,0,0,0,39,131,1,0,0,
  	0,41,133,1,0,0,0,43,135,1,0,0,0,45,137,1,0,0,0,47,144,1,0,0,0,49,154,
  	1,0,0,0,51,159,1,0,0,0,53,170,1,0,0,0,55,177,1,0,0,0,57,180,1,0,0,0,59,
  	184,1,0,0,0,61,190,1,0,0,0,63,199,1,0,0,0,65,206,1,0,0,0,67,210,1,0,0,
  	0,69,213,1,0,0,0,71,217,1,0,0,0,73,221,1,0,0,0,75,226,1,0,0,0,77,245,
  	1,0,0,0,79,247,1,0,0,0,81,254,1,0,0,0,83,262,1,0,0,0,85,266,1,0,0,0,87,
  	277,1,0,0,0,89,288,1,0,0,0,91,305,1,0,0,0,93,94,5,40,0,0,94,2,1,0,0,0,
  	95,96,5,41,0,0,96,4,1,0,0,0,97,98,5,123,0,0,98,6,1,0,0,0,99,100,5,125,
  	0,0,100,8,1,0,0,0,101,102,5,91,0,0,102,10,1,0,0,0,103,104,5,93,0,0,104,
  	12,1,0,0,0,105,106,5,60,0,0,106,14,1,0,0,0,107,108,5,62,0,0,108,16,1,
  	0,0,0,109,110,5,44,0,0,110,18,1,0,0,0,111,112,5,46,0,0,112,20,1,0,0,0,
  	113,114,5,58,0,0,114,22,1,0,0,0,115,116,5,61,0,0,116,24,1,0,0,0,117,118,
  	5,45,0,0,118,26,1,0,0,0,119,120,5,43,0,0,120,28,1,0,0,0,121,122,5,42,
  	0,0,122,30,1,0,0,0,123,124,5,47,0,0,124,32,1,0,0,0,125,126,5,35,0,0,126,
  	34,1,0,0,0,127,128,5,63,0,0,128,36,1,0,0,0,129,130,5,33,0,0,130,38,1,
  	0,0,0,131,132,5,37,0,0,132,40,1,0,0,0,133,134,5,36,0,0,134,42,1,0,0,0,
  	135,136,5,38,0,0,136,44,1,0,0,0,137,138,5,111,0,0,138,139,5,98,0,0,139,
  	140,5,106,0,0,140,141,5,101,0,0,141,142,5,99,0,0,142,143,5,116,0,0,143,
  	46,1,0,0,0,144,145,5,105,0,0,145,146,5,110,0,0,146,147,5,116,0,0,147,
  	148,5,101,0,0,148,149,5,114,0,0,149,150,5,102,0,0,150,151,5,97,0,0,151,
  	152,5,99,0,0,152,153,5,101,0,0,153,48,1,0,0,0,154,155,5,101,0,0,155,156,
  	5,110,0,0,156,157,5,117,0,0,157,158,5,109,0,0,158,50,1,0,0,0,159,160,
  	5,105,0,0,160,161,5,109,0,0,161,162,5,112,0,0,162,163,5,108,0,0,163,164,
  	5,101,0,0,164,165,5,109,0,0,165,166,5,101,0,0,166,167,5,110,0,0,167,168,
  	5,116,0,0,168,169,5,115,0,0,169,52,1,0,0,0,170,171,5,105,0,0,171,172,
  	5,109,0,0,172,173,5,112,0,0,173,174,5,111,0,0,174,175,5,114,0,0,175,176,
  	5,116,0,0,176,54,1,0,0,0,177,178,5,105,0,0,178,179,5,102,0,0,179,56,1,
  	0,0,0,180,181,5,102,0,0,181,182,5,111,0,0,182,183,5,114,0,0,183,58,1,
  	0,0,0,184,185,5,98,0,0,185,186,5,114,0,0,186,187,5,101,0,0,187,188,5,
  	97,0,0,188,189,5,107,0,0,189,60,1,0,0,0,190,191,5,99,0,0,191,192,5,111,
  	0,0,192,193,5,110,0,0,193,194,5,116,0,0,194,195,5,105,0,0,195,196,5,110,
  	0,0,196,197,5,117,0,0,197,198,5,101,0,0,198,62,1,0,0,0,199,200,5,114,
  	0,0,200,201,5,101,0,0,201,202,5,116,0,0,202,203,5,117,0,0,203,204,5,114,
  	0,0,204,205,5,110,0,0,205,64,1,0,0,0,206,207,5,97,0,0,207,208,5,110,0,
  	0,208,209,5,100,0,0,209,66,1,0,0,0,210,211,5,111,0,0,211,212,5,114,0,
  	0,212,68,1,0,0,0,213,214,5,110,0,0,214,215,5,111,0,0,215,216,5,116,0,
  	0,216,70,1,0,0,0,217,218,5,105,0,0,218,219,5,110,0,0,219,72,1,0,0,0,220,
  	222,7,0,0,0,221,220,1,0,0,0,222,223,1,0,0,0,223,221,1,0,0,0,223,224,1,
  	0,0,0,224,74,1,0,0,0,225,227,7,0,0,0,226,225,1,0,0,0,227,228,1,0,0,0,
  	228,226,1,0,0,0,228,229,1,0,0,0,229,230,1,0,0,0,230,232,5,46,0,0,231,
  	233,7,0,0,0,232,231,1,0,0,0,233,234,1,0,0,0,234,232,1,0,0,0,234,235,1,
  	0,0,0,235,76,1,0,0,0,236,237,5,116,0,0,237,238,5,114,0,0,238,239,5,117,
  	0,0,239,246,5,101,0,0,240,241,5,102,0,0,241,242,5,97,0,0,242,243,5,108,
  	0,0,243,244,5,115,0,0,244,246,5,101,0,0,245,236,1,0,0,0,245,240,1,0,0,
  	0,246,78,1,0,0,0,247,251,7,1,0,0,248,250,7,2,0,0,249,248,1,0,0,0,250,
  	253,1,0,0,0,251,249,1,0,0,0,251,252,1,0,0,0,252,80,1,0,0,0,253,251,1,
  	0,0,0,254,258,7,3,0,0,255,257,7,2,0,0,256,255,1,0,0,0,257,260,1,0,0,0,
  	258,256,1,0,0,0,258,259,1,0,0,0,259,82,1,0,0,0,260,258,1,0,0,0,261,263,
  	7,4,0,0,262,261,1,0,0,0,263,264,1,0,0,0,264,262,1,0,0,0,264,265,1,0,0,
  	0,265,84,1,0,0,0,266,272,5,34,0,0,267,271,8,5,0,0,268,269,5,92,0,0,269,
  	271,9,0,0,0,270,267,1,0,0,0,270,268,1,0,0,0,271,274,1,0,0,0,272,270,1,
  	0,0,0,272,273,1,0,0,0,273,275,1,0,0,0,274,272,1,0,0,0,275,276,5,34,0,
  	0,276,86,1,0,0,0,277,278,5,47,0,0,278,279,5,47,0,0,279,283,1,0,0,0,280,
  	282,8,6,0,0,281,280,1,0,0,0,282,285,1,0,0,0,283,281,1,0,0,0,283,284,1,
  	0,0,0,284,286,1,0,0,0,285,283,1,0,0,0,286,287,6,43,0,0,287,88,1,0,0,0,
  	288,289,5,47,0,0,289,290,5,47,0,0,290,291,5,47,0,0,291,295,1,0,0,0,292,
  	294,9,0,0,0,293,292,1,0,0,0,294,297,1,0,0,0,295,296,1,0,0,0,295,293,1,
  	0,0,0,296,298,1,0,0,0,297,295,1,0,0,0,298,299,5,47,0,0,299,300,5,47,0,
  	0,300,301,5,47,0,0,301,302,1,0,0,0,302,303,6,44,0,0,303,90,1,0,0,0,304,
  	306,7,7,0,0,305,304,1,0,0,0,306,307,1,0,0,0,307,305,1,0,0,0,307,308,1,
  	0,0,0,308,309,1,0,0,0,309,310,6,45,0,0,310,92,1,0,0,0,13,0,223,228,234,
  	245,251,258,264,270,272,283,295,307,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  logoslexerLexerStaticData = std::move(staticData);
}

}

LogosLexer::LogosLexer(CharStream *input) : Lexer(input) {
  LogosLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *logoslexerLexerStaticData->atn, logoslexerLexerStaticData->decisionToDFA, logoslexerLexerStaticData->sharedContextCache);
}

LogosLexer::~LogosLexer() {
  delete _interpreter;
}

std::string LogosLexer::getGrammarFileName() const {
  return "Logos.g4";
}

const std::vector<std::string>& LogosLexer::getRuleNames() const {
  return logoslexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& LogosLexer::getChannelNames() const {
  return logoslexerLexerStaticData->channelNames;
}

const std::vector<std::string>& LogosLexer::getModeNames() const {
  return logoslexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& LogosLexer::getVocabulary() const {
  return logoslexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView LogosLexer::getSerializedATN() const {
  return logoslexerLexerStaticData->serializedATN;
}

const atn::ATN& LogosLexer::getATN() const {
  return *logoslexerLexerStaticData->atn;
}




void LogosLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  logoslexerLexerInitialize();
#else
  ::antlr4::internal::call_once(logoslexerLexerOnceFlag, logoslexerLexerInitialize);
#endif
}
