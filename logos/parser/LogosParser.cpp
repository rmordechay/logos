
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
      "logosFile", "mainFile", "interfaceFile", "objectFile", "objectDeclaration", 
      "interfaceDeclaration", "objectImplements", "funcDec", "funcImplementation", 
      "funcBody", "funcCall", "constructorCall", "explicitVarDecList", "explicitVarDec", 
      "implicitVarDec", "paramCall", "paramCallList", "statement", "statemets_block", 
      "expr", "binaryExpr", "unaryExpr", "selection", "ifStatement", "elseStatement", 
      "patterMatching", "pattern"
    },
    std::vector<std::string>{
      "", "'('", "')'", "'{'", "'}'", "'['", "']'", "'<'", "'>'", "','", 
      "'.'", "':'", "'='", "'-'", "'+'", "'*'", "'/'", "'#'", "'\\u003F'", 
      "'!'", "'%'", "'$'", "'&'", "'object'", "'interface'", "'enum'", "'implements'", 
      "'import'", "'if'", "'else'", "'for'", "'break'", "'continue'", "'return'", 
      "'and'", "'or'", "'not'", "'in'"
    },
    std::vector<std::string>{
      "", "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", 
      "RIGHT_BRACKET", "LEFT_ANGLE", "RIGHT_ANGLE", "COMMA", "DOT", "COLON", 
      "EQUAL", "MINUS", "PLUS", "STAR", "SLASH", "HASH", "QUEST_MARK", "EXCLA_MARK", 
      "PERCENT", "DOLLAR", "AMPERSAND", "OBJECT", "INTERFACE", "ENUM", "IMPLEMENTS", 
      "IMPORT", "IF", "ELSE", "FOR", "BREAK", "CONTINUE", "RETURN", "AND", 
      "OR", "NOT", "IN", "INTEGER", "FLOAT", "BOOL", "VARIABLE", "TYPE", 
      "CONST", "STRING", "LINE_COMMENT", "BLOCK_COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,47,278,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,1,0,1,0,1,0,3,0,
  	58,8,0,1,1,4,1,61,8,1,11,1,12,1,62,1,1,1,1,1,2,1,2,3,2,69,8,2,1,2,5,2,
  	72,8,2,10,2,12,2,75,9,2,1,2,4,2,78,8,2,11,2,12,2,79,1,2,5,2,83,8,2,10,
  	2,12,2,86,9,2,1,2,1,2,1,3,1,3,3,3,92,8,3,1,3,5,3,95,8,3,10,3,12,3,98,
  	9,3,1,3,5,3,101,8,3,10,3,12,3,104,9,3,1,3,1,3,1,4,1,4,1,4,1,4,1,5,1,5,
  	1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,7,3,7,123,8,7,1,7,1,7,1,7,1,7,1,8,1,
  	8,1,8,1,9,1,9,1,10,1,10,1,10,5,10,137,8,10,10,10,12,10,140,9,10,1,10,
  	1,10,1,11,1,11,1,11,5,11,147,8,11,10,11,12,11,150,9,11,1,11,1,11,1,12,
  	1,12,1,12,5,12,157,8,12,10,12,12,12,160,9,12,1,13,1,13,1,13,1,13,1,13,
  	3,13,167,8,13,1,14,1,14,1,14,3,14,172,8,14,1,15,1,15,3,15,176,8,15,1,
  	15,1,15,1,16,1,16,1,16,5,16,183,8,16,10,16,12,16,186,9,16,1,17,1,17,1,
  	17,1,17,3,17,192,8,17,1,18,1,18,5,18,196,8,18,10,18,12,18,199,9,18,1,
  	18,1,18,1,19,1,19,1,19,3,19,206,8,19,1,20,1,20,1,20,1,20,1,20,1,20,1,
  	20,1,20,3,20,216,8,20,1,21,1,21,1,21,1,21,1,21,1,21,1,21,3,21,225,8,21,
  	1,22,1,22,1,22,5,22,230,8,22,10,22,12,22,233,9,22,1,23,1,23,1,23,1,23,
  	1,23,1,23,3,23,241,8,23,1,24,1,24,1,24,1,24,5,24,247,8,24,10,24,12,24,
  	250,9,24,1,24,1,24,3,24,254,8,24,1,25,1,25,3,25,258,8,25,1,25,1,25,5,
  	25,262,8,25,10,25,12,25,265,9,25,1,25,1,25,1,25,3,25,270,8,25,1,25,1,
  	25,1,26,1,26,1,26,1,26,1,26,0,0,27,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,52,0,2,1,0,15,16,1,0,13,14,288,
  	0,57,1,0,0,0,2,60,1,0,0,0,4,66,1,0,0,0,6,89,1,0,0,0,8,107,1,0,0,0,10,
  	111,1,0,0,0,12,115,1,0,0,0,14,119,1,0,0,0,16,128,1,0,0,0,18,131,1,0,0,
  	0,20,133,1,0,0,0,22,143,1,0,0,0,24,153,1,0,0,0,26,161,1,0,0,0,28,168,
  	1,0,0,0,30,175,1,0,0,0,32,179,1,0,0,0,34,191,1,0,0,0,36,193,1,0,0,0,38,
  	205,1,0,0,0,40,215,1,0,0,0,42,224,1,0,0,0,44,226,1,0,0,0,46,240,1,0,0,
  	0,48,248,1,0,0,0,50,255,1,0,0,0,52,273,1,0,0,0,54,58,3,2,1,0,55,58,3,
  	6,3,0,56,58,3,4,2,0,57,54,1,0,0,0,57,55,1,0,0,0,57,56,1,0,0,0,58,1,1,
  	0,0,0,59,61,3,16,8,0,60,59,1,0,0,0,61,62,1,0,0,0,62,60,1,0,0,0,62,63,
  	1,0,0,0,63,64,1,0,0,0,64,65,5,0,0,1,65,3,1,0,0,0,66,68,3,10,5,0,67,69,
  	3,12,6,0,68,67,1,0,0,0,68,69,1,0,0,0,69,73,1,0,0,0,70,72,3,26,13,0,71,
  	70,1,0,0,0,72,75,1,0,0,0,73,71,1,0,0,0,73,74,1,0,0,0,74,77,1,0,0,0,75,
  	73,1,0,0,0,76,78,3,14,7,0,77,76,1,0,0,0,78,79,1,0,0,0,79,77,1,0,0,0,79,
  	80,1,0,0,0,80,84,1,0,0,0,81,83,3,16,8,0,82,81,1,0,0,0,83,86,1,0,0,0,84,
  	82,1,0,0,0,84,85,1,0,0,0,85,87,1,0,0,0,86,84,1,0,0,0,87,88,5,0,0,1,88,
  	5,1,0,0,0,89,91,3,8,4,0,90,92,3,12,6,0,91,90,1,0,0,0,91,92,1,0,0,0,92,
  	96,1,0,0,0,93,95,3,26,13,0,94,93,1,0,0,0,95,98,1,0,0,0,96,94,1,0,0,0,
  	96,97,1,0,0,0,97,102,1,0,0,0,98,96,1,0,0,0,99,101,3,16,8,0,100,99,1,0,
  	0,0,101,104,1,0,0,0,102,100,1,0,0,0,102,103,1,0,0,0,103,105,1,0,0,0,104,
  	102,1,0,0,0,105,106,5,0,0,1,106,7,1,0,0,0,107,108,5,23,0,0,108,109,5,
  	11,0,0,109,110,5,42,0,0,110,9,1,0,0,0,111,112,5,24,0,0,112,113,5,11,0,
  	0,113,114,5,42,0,0,114,11,1,0,0,0,115,116,5,26,0,0,116,117,5,11,0,0,117,
  	118,5,42,0,0,118,13,1,0,0,0,119,120,5,41,0,0,120,122,5,1,0,0,121,123,
  	3,24,12,0,122,121,1,0,0,0,122,123,1,0,0,0,123,124,1,0,0,0,124,125,5,2,
  	0,0,125,126,5,11,0,0,126,127,5,42,0,0,127,15,1,0,0,0,128,129,3,14,7,0,
  	129,130,3,18,9,0,130,17,1,0,0,0,131,132,3,36,18,0,132,19,1,0,0,0,133,
  	134,5,41,0,0,134,138,5,1,0,0,135,137,3,32,16,0,136,135,1,0,0,0,137,140,
  	1,0,0,0,138,136,1,0,0,0,138,139,1,0,0,0,139,141,1,0,0,0,140,138,1,0,0,
  	0,141,142,5,2,0,0,142,21,1,0,0,0,143,144,5,42,0,0,144,148,5,1,0,0,145,
  	147,3,32,16,0,146,145,1,0,0,0,147,150,1,0,0,0,148,146,1,0,0,0,148,149,
  	1,0,0,0,149,151,1,0,0,0,150,148,1,0,0,0,151,152,5,2,0,0,152,23,1,0,0,
  	0,153,158,3,26,13,0,154,155,5,9,0,0,155,157,3,26,13,0,156,154,1,0,0,0,
  	157,160,1,0,0,0,158,156,1,0,0,0,158,159,1,0,0,0,159,25,1,0,0,0,160,158,
  	1,0,0,0,161,162,5,41,0,0,162,163,5,11,0,0,163,166,5,42,0,0,164,165,5,
  	12,0,0,165,167,3,38,19,0,166,164,1,0,0,0,166,167,1,0,0,0,167,27,1,0,0,
  	0,168,171,5,41,0,0,169,170,5,12,0,0,170,172,3,38,19,0,171,169,1,0,0,0,
  	171,172,1,0,0,0,172,29,1,0,0,0,173,174,5,41,0,0,174,176,5,12,0,0,175,
  	173,1,0,0,0,175,176,1,0,0,0,176,177,1,0,0,0,177,178,3,38,19,0,178,31,
  	1,0,0,0,179,184,3,30,15,0,180,181,5,9,0,0,181,183,3,30,15,0,182,180,1,
  	0,0,0,183,186,1,0,0,0,184,182,1,0,0,0,184,185,1,0,0,0,185,33,1,0,0,0,
  	186,184,1,0,0,0,187,192,3,26,13,0,188,192,3,28,14,0,189,192,3,46,23,0,
  	190,192,3,38,19,0,191,187,1,0,0,0,191,188,1,0,0,0,191,189,1,0,0,0,191,
  	190,1,0,0,0,192,35,1,0,0,0,193,197,5,3,0,0,194,196,3,34,17,0,195,194,
  	1,0,0,0,196,199,1,0,0,0,197,195,1,0,0,0,197,198,1,0,0,0,198,200,1,0,0,
  	0,199,197,1,0,0,0,200,201,5,4,0,0,201,37,1,0,0,0,202,206,3,40,20,0,203,
  	206,3,42,21,0,204,206,3,44,22,0,205,202,1,0,0,0,205,203,1,0,0,0,205,204,
  	1,0,0,0,206,39,1,0,0,0,207,208,3,42,21,0,208,209,7,0,0,0,209,210,3,38,
  	19,0,210,216,1,0,0,0,211,212,3,42,21,0,212,213,7,1,0,0,213,214,3,38,19,
  	0,214,216,1,0,0,0,215,207,1,0,0,0,215,211,1,0,0,0,216,41,1,0,0,0,217,
  	225,3,20,10,0,218,225,3,22,11,0,219,225,5,38,0,0,220,225,5,39,0,0,221,
  	225,5,40,0,0,222,225,5,44,0,0,223,225,5,41,0,0,224,217,1,0,0,0,224,218,
  	1,0,0,0,224,219,1,0,0,0,224,220,1,0,0,0,224,221,1,0,0,0,224,222,1,0,0,
  	0,224,223,1,0,0,0,225,43,1,0,0,0,226,231,3,42,21,0,227,228,5,10,0,0,228,
  	230,3,42,21,0,229,227,1,0,0,0,230,233,1,0,0,0,231,229,1,0,0,0,231,232,
  	1,0,0,0,232,45,1,0,0,0,233,231,1,0,0,0,234,235,5,28,0,0,235,236,3,38,
  	19,0,236,237,3,36,18,0,237,238,3,48,24,0,238,241,1,0,0,0,239,241,3,50,
  	25,0,240,234,1,0,0,0,240,239,1,0,0,0,241,47,1,0,0,0,242,243,5,29,0,0,
  	243,244,3,38,19,0,244,245,3,36,18,0,245,247,1,0,0,0,246,242,1,0,0,0,247,
  	250,1,0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,253,1,0,0,0,250,248,1,
  	0,0,0,251,252,5,29,0,0,252,254,3,36,18,0,253,251,1,0,0,0,253,254,1,0,
  	0,0,254,49,1,0,0,0,255,257,5,28,0,0,256,258,3,38,19,0,257,256,1,0,0,0,
  	257,258,1,0,0,0,258,259,1,0,0,0,259,263,5,3,0,0,260,262,3,52,26,0,261,
  	260,1,0,0,0,262,265,1,0,0,0,263,261,1,0,0,0,263,264,1,0,0,0,264,269,1,
  	0,0,0,265,263,1,0,0,0,266,267,5,29,0,0,267,268,5,11,0,0,268,270,3,36,
  	18,0,269,266,1,0,0,0,269,270,1,0,0,0,270,271,1,0,0,0,271,272,5,4,0,0,
  	272,51,1,0,0,0,273,274,3,38,19,0,274,275,5,11,0,0,275,276,3,36,18,0,276,
  	53,1,0,0,0,29,57,62,68,73,79,84,91,96,102,122,138,148,158,166,171,175,
  	184,191,197,205,215,224,231,240,248,253,257,263,269
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
    setState(57);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::VARIABLE: {
        enterOuterAlt(_localctx, 1);
        setState(54);
        mainFile();
        break;
      }

      case LogosParser::OBJECT: {
        enterOuterAlt(_localctx, 2);
        setState(55);
        objectFile();
        break;
      }

      case LogosParser::INTERFACE: {
        enterOuterAlt(_localctx, 3);
        setState(56);
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
    setState(60); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(59);
      funcImplementation();
      setState(62); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == LogosParser::VARIABLE);
    setState(64);
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
    setState(66);
    interfaceDeclaration();
    setState(68);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(67);
      objectImplements();
    }
    setState(73);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(70);
        explicitVarDec(); 
      }
      setState(75);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
    setState(77); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(76);
              funcDec();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(79); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(84);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(81);
      funcImplementation();
      setState(86);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
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
    setState(89);
    objectDeclaration();
    setState(91);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(90);
      objectImplements();
    }
    setState(96);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(93);
        explicitVarDec(); 
      }
      setState(98);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
    setState(102);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(99);
      funcImplementation();
      setState(104);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(105);
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
    setState(107);
    match(LogosParser::OBJECT);
    setState(108);
    match(LogosParser::COLON);
    setState(109);
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
    setState(111);
    match(LogosParser::INTERFACE);
    setState(112);
    match(LogosParser::COLON);
    setState(113);
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
    setState(115);
    match(LogosParser::IMPLEMENTS);
    setState(116);
    match(LogosParser::COLON);
    setState(117);
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
  enterRule(_localctx, 14, LogosParser::RuleFuncDec);
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
    setState(119);
    match(LogosParser::VARIABLE);
    setState(120);
    match(LogosParser::LEFT_PAREN);
    setState(122);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(121);
      explicitVarDecList();
    }
    setState(124);
    match(LogosParser::RIGHT_PAREN);
    setState(125);
    match(LogosParser::COLON);
    setState(126);
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
    setState(128);
    funcDec();
    setState(129);
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
    setState(131);
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
  enterRule(_localctx, 20, LogosParser::RuleFuncCall);
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
    setState(133);
    match(LogosParser::VARIABLE);
    setState(134);
    match(LogosParser::LEFT_PAREN);
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26113401159680) != 0)) {
      setState(135);
      paramCallList();
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(141);
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
  enterRule(_localctx, 22, LogosParser::RuleConstructorCall);
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
    match(LogosParser::TYPE);
    setState(144);
    match(LogosParser::LEFT_PAREN);
    setState(148);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26113401159680) != 0)) {
      setState(145);
      paramCallList();
      setState(150);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(151);
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
  enterRule(_localctx, 24, LogosParser::RuleExplicitVarDecList);
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
    setState(153);
    explicitVarDec();
    setState(158);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::COMMA) {
      setState(154);
      match(LogosParser::COMMA);
      setState(155);
      explicitVarDec();
      setState(160);
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


size_t LogosParser::ExplicitVarDecContext::getRuleIndex() const {
  return LogosParser::RuleExplicitVarDec;
}


LogosParser::ExplicitVarDecContext* LogosParser::explicitVarDec() {
  ExplicitVarDecContext *_localctx = _tracker.createInstance<ExplicitVarDecContext>(_ctx, getState());
  enterRule(_localctx, 26, LogosParser::RuleExplicitVarDec);
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
    match(LogosParser::VARIABLE);
    setState(162);
    match(LogosParser::COLON);
    setState(163);
    match(LogosParser::TYPE);
    setState(166);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(164);
      match(LogosParser::EQUAL);
      setState(165);
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
  enterRule(_localctx, 28, LogosParser::RuleImplicitVarDec);
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
    setState(168);
    match(LogosParser::VARIABLE);
    setState(171);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(169);
      match(LogosParser::EQUAL);
      setState(170);
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
  enterRule(_localctx, 30, LogosParser::RuleParamCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      setState(173);
      match(LogosParser::VARIABLE);
      setState(174);
      match(LogosParser::EQUAL);
      break;
    }

    default:
      break;
    }
    setState(177);
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
  enterRule(_localctx, 32, LogosParser::RuleParamCallList);
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
    setState(179);
    paramCall();
    setState(184);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::COMMA) {
      setState(180);
      match(LogosParser::COMMA);
      setState(181);
      paramCall();
      setState(186);
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

LogosParser::ExprContext* LogosParser::StatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::StatementContext::getRuleIndex() const {
  return LogosParser::RuleStatement;
}


LogosParser::StatementContext* LogosParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 34, LogosParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(191);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(187);
      explicitVarDec();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(188);
      implicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(189);
      ifStatement();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(190);
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
  enterRule(_localctx, 36, LogosParser::RuleStatemets_block);
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
    setState(193);
    match(LogosParser::LEFT_BRACE);
    setState(197);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26113669595136) != 0)) {
      setState(194);
      statement();
      setState(199);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(200);
    match(LogosParser::RIGHT_BRACE);
   
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

LogosParser::SelectionContext* LogosParser::ExprContext::selection() {
  return getRuleContext<LogosParser::SelectionContext>(0);
}


size_t LogosParser::ExprContext::getRuleIndex() const {
  return LogosParser::RuleExpr;
}


LogosParser::ExprContext* LogosParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 38, LogosParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(205);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(202);
      binaryExpr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(203);
      unaryExpr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(204);
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
  enterRule(_localctx, 40, LogosParser::RuleBinaryExpr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(215);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(207);
      unaryExpr();
      setState(208);
      _la = _input->LA(1);
      if (!(_la == LogosParser::STAR

      || _la == LogosParser::SLASH)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(209);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(211);
      unaryExpr();
      setState(212);
      _la = _input->LA(1);
      if (!(_la == LogosParser::MINUS

      || _la == LogosParser::PLUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(213);
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
  enterRule(_localctx, 42, LogosParser::RuleUnaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(224);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(217);
      funcCall();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(218);
      constructorCall();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(219);
      match(LogosParser::INTEGER);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(220);
      match(LogosParser::FLOAT);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(221);
      match(LogosParser::BOOL);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(222);
      match(LogosParser::STRING);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(223);
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
  enterRule(_localctx, 44, LogosParser::RuleSelection);
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
    unaryExpr();
    setState(231);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::DOT) {
      setState(227);
      match(LogosParser::DOT);
      setState(228);
      unaryExpr();
      setState(233);
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
  enterRule(_localctx, 46, LogosParser::RuleIfStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(240);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(234);
      match(LogosParser::IF);
      setState(235);
      expr();
      setState(236);
      statemets_block();
      setState(237);
      elseStatement();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(239);
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
  enterRule(_localctx, 48, LogosParser::RuleElseStatement);
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
    setState(248);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(242);
        match(LogosParser::ELSE);
        setState(243);
        expr();
        setState(244);
        statemets_block(); 
      }
      setState(250);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    }
    setState(253);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(251);
      match(LogosParser::ELSE);
      setState(252);
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
  enterRule(_localctx, 50, LogosParser::RulePatterMatching);
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
    setState(255);
    match(LogosParser::IF);
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26113401159680) != 0)) {
      setState(256);
      expr();
    }
    setState(259);
    match(LogosParser::LEFT_BRACE);
    setState(263);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 26113401159680) != 0)) {
      setState(260);
      pattern();
      setState(265);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(269);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::ELSE) {
      setState(266);
      match(LogosParser::ELSE);
      setState(267);
      match(LogosParser::COLON);
      setState(268);
      statemets_block();
    }
    setState(271);
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
  enterRule(_localctx, 52, LogosParser::RulePattern);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(273);
    expr();
    setState(274);
    match(LogosParser::COLON);
    setState(275);
    statemets_block();
   
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
