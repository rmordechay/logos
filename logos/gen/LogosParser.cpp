
// Generated from Logos.g4 by ANTLR 4.13.2


#include "LogosListener.h"

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
      "logosFile", "interfaceFile", "objectFile", "objectDeclaration", "interfaceDeclaration", 
      "objectImplements", "explicitVarDecList", "explicitVarDec", "implicitVarDec", 
      "funcDec", "funcCall", "funcImplementation", "funcBody", "statement", 
      "expr_list", "expr", "binary_expr", "unary_expr"
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
  	4,1,46,183,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,1,0,1,0,3,0,39,8,0,1,1,1,1,3,1,43,8,
  	1,1,1,5,1,46,8,1,10,1,12,1,49,9,1,1,1,4,1,52,8,1,11,1,12,1,53,1,1,5,1,
  	57,8,1,10,1,12,1,60,9,1,1,2,1,2,3,2,64,8,2,1,2,5,2,67,8,2,10,2,12,2,70,
  	9,2,1,2,5,2,73,8,2,10,2,12,2,76,9,2,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,
  	5,1,5,1,5,1,5,1,6,1,6,1,6,5,6,93,8,6,10,6,12,6,96,9,6,1,7,1,7,1,7,1,7,
  	1,7,3,7,103,8,7,1,8,1,8,1,8,3,8,108,8,8,1,9,1,9,1,9,3,9,113,8,9,1,9,1,
  	9,1,9,1,9,1,10,1,10,1,10,4,10,122,8,10,11,10,12,10,123,1,10,1,10,1,11,
  	1,11,1,11,1,12,1,12,5,12,133,8,12,10,12,12,12,136,9,12,1,12,1,12,1,13,
  	1,13,1,13,3,13,143,8,13,1,14,1,14,1,14,5,14,148,8,14,10,14,12,14,151,
  	9,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,163,8,15,
  	1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,173,8,16,1,17,1,17,1,17,
  	1,17,1,17,1,17,3,17,181,8,17,1,17,0,0,18,0,2,4,6,8,10,12,14,16,18,20,
  	22,24,26,28,30,32,34,0,2,1,0,15,16,1,0,13,14,190,0,38,1,0,0,0,2,40,1,
  	0,0,0,4,61,1,0,0,0,6,77,1,0,0,0,8,81,1,0,0,0,10,85,1,0,0,0,12,89,1,0,
  	0,0,14,97,1,0,0,0,16,104,1,0,0,0,18,109,1,0,0,0,20,118,1,0,0,0,22,127,
  	1,0,0,0,24,130,1,0,0,0,26,142,1,0,0,0,28,144,1,0,0,0,30,162,1,0,0,0,32,
  	172,1,0,0,0,34,180,1,0,0,0,36,39,3,4,2,0,37,39,3,2,1,0,38,36,1,0,0,0,
  	38,37,1,0,0,0,39,1,1,0,0,0,40,42,3,8,4,0,41,43,3,10,5,0,42,41,1,0,0,0,
  	42,43,1,0,0,0,43,47,1,0,0,0,44,46,3,14,7,0,45,44,1,0,0,0,46,49,1,0,0,
  	0,47,45,1,0,0,0,47,48,1,0,0,0,48,51,1,0,0,0,49,47,1,0,0,0,50,52,3,18,
  	9,0,51,50,1,0,0,0,52,53,1,0,0,0,53,51,1,0,0,0,53,54,1,0,0,0,54,58,1,0,
  	0,0,55,57,3,22,11,0,56,55,1,0,0,0,57,60,1,0,0,0,58,56,1,0,0,0,58,59,1,
  	0,0,0,59,3,1,0,0,0,60,58,1,0,0,0,61,63,3,6,3,0,62,64,3,10,5,0,63,62,1,
  	0,0,0,63,64,1,0,0,0,64,68,1,0,0,0,65,67,3,14,7,0,66,65,1,0,0,0,67,70,
  	1,0,0,0,68,66,1,0,0,0,68,69,1,0,0,0,69,74,1,0,0,0,70,68,1,0,0,0,71,73,
  	3,22,11,0,72,71,1,0,0,0,73,76,1,0,0,0,74,72,1,0,0,0,74,75,1,0,0,0,75,
  	5,1,0,0,0,76,74,1,0,0,0,77,78,5,23,0,0,78,79,5,11,0,0,79,80,5,41,0,0,
  	80,7,1,0,0,0,81,82,5,24,0,0,82,83,5,11,0,0,83,84,5,41,0,0,84,9,1,0,0,
  	0,85,86,5,26,0,0,86,87,5,11,0,0,87,88,5,41,0,0,88,11,1,0,0,0,89,94,3,
  	14,7,0,90,91,5,9,0,0,91,93,3,14,7,0,92,90,1,0,0,0,93,96,1,0,0,0,94,92,
  	1,0,0,0,94,95,1,0,0,0,95,13,1,0,0,0,96,94,1,0,0,0,97,98,5,40,0,0,98,99,
  	5,11,0,0,99,102,5,41,0,0,100,101,5,12,0,0,101,103,3,30,15,0,102,100,1,
  	0,0,0,102,103,1,0,0,0,103,15,1,0,0,0,104,107,5,40,0,0,105,106,5,12,0,
  	0,106,108,3,30,15,0,107,105,1,0,0,0,107,108,1,0,0,0,108,17,1,0,0,0,109,
  	110,5,40,0,0,110,112,5,1,0,0,111,113,3,12,6,0,112,111,1,0,0,0,112,113,
  	1,0,0,0,113,114,1,0,0,0,114,115,5,2,0,0,115,116,5,11,0,0,116,117,5,41,
  	0,0,117,19,1,0,0,0,118,119,5,40,0,0,119,121,5,1,0,0,120,122,3,28,14,0,
  	121,120,1,0,0,0,122,123,1,0,0,0,123,121,1,0,0,0,123,124,1,0,0,0,124,125,
  	1,0,0,0,125,126,5,2,0,0,126,21,1,0,0,0,127,128,3,18,9,0,128,129,3,24,
  	12,0,129,23,1,0,0,0,130,134,5,3,0,0,131,133,3,26,13,0,132,131,1,0,0,0,
  	133,136,1,0,0,0,134,132,1,0,0,0,134,135,1,0,0,0,135,137,1,0,0,0,136,134,
  	1,0,0,0,137,138,5,4,0,0,138,25,1,0,0,0,139,143,3,14,7,0,140,143,3,16,
  	8,0,141,143,3,30,15,0,142,139,1,0,0,0,142,140,1,0,0,0,142,141,1,0,0,0,
  	143,27,1,0,0,0,144,149,3,30,15,0,145,146,5,9,0,0,146,148,3,30,15,0,147,
  	145,1,0,0,0,148,151,1,0,0,0,149,147,1,0,0,0,149,150,1,0,0,0,150,29,1,
  	0,0,0,151,149,1,0,0,0,152,163,3,32,16,0,153,163,3,34,17,0,154,155,5,1,
  	0,0,155,156,3,32,16,0,156,157,5,2,0,0,157,163,1,0,0,0,158,159,5,1,0,0,
  	159,160,3,34,17,0,160,161,5,2,0,0,161,163,1,0,0,0,162,152,1,0,0,0,162,
  	153,1,0,0,0,162,154,1,0,0,0,162,158,1,0,0,0,163,31,1,0,0,0,164,165,3,
  	34,17,0,165,166,7,0,0,0,166,167,3,30,15,0,167,173,1,0,0,0,168,169,3,34,
  	17,0,169,170,7,1,0,0,170,171,3,30,15,0,171,173,1,0,0,0,172,164,1,0,0,
  	0,172,168,1,0,0,0,173,33,1,0,0,0,174,181,5,40,0,0,175,181,5,37,0,0,176,
  	181,5,38,0,0,177,181,5,39,0,0,178,181,5,43,0,0,179,181,3,20,10,0,180,
  	174,1,0,0,0,180,175,1,0,0,0,180,176,1,0,0,0,180,177,1,0,0,0,180,178,1,
  	0,0,0,180,179,1,0,0,0,181,35,1,0,0,0,19,38,42,47,53,58,63,68,74,94,102,
  	107,112,123,134,142,149,162,172,180
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

LogosParser::ObjectFileContext* LogosParser::LogosFileContext::objectFile() {
  return getRuleContext<LogosParser::ObjectFileContext>(0);
}

LogosParser::InterfaceFileContext* LogosParser::LogosFileContext::interfaceFile() {
  return getRuleContext<LogosParser::InterfaceFileContext>(0);
}


size_t LogosParser::LogosFileContext::getRuleIndex() const {
  return LogosParser::RuleLogosFile;
}

void LogosParser::LogosFileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogosFile(this);
}

void LogosParser::LogosFileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogosFile(this);
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
    setState(38);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case LogosParser::OBJECT: {
        enterOuterAlt(_localctx, 1);
        setState(36);
        objectFile();
        break;
      }

      case LogosParser::INTERFACE: {
        enterOuterAlt(_localctx, 2);
        setState(37);
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

//----------------- InterfaceFileContext ------------------------------------------------------------------

LogosParser::InterfaceFileContext::InterfaceFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::InterfaceDeclarationContext* LogosParser::InterfaceFileContext::interfaceDeclaration() {
  return getRuleContext<LogosParser::InterfaceDeclarationContext>(0);
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

void LogosParser::InterfaceFileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceFile(this);
}

void LogosParser::InterfaceFileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceFile(this);
}

LogosParser::InterfaceFileContext* LogosParser::interfaceFile() {
  InterfaceFileContext *_localctx = _tracker.createInstance<InterfaceFileContext>(_ctx, getState());
  enterRule(_localctx, 2, LogosParser::RuleInterfaceFile);
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
    setState(40);
    interfaceDeclaration();
    setState(42);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(41);
      objectImplements();
    }
    setState(47);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(44);
        explicitVarDec(); 
      }
      setState(49);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
    setState(51); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(50);
              funcDec();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(53); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(58);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(55);
      funcImplementation();
      setState(60);
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

//----------------- ObjectFileContext ------------------------------------------------------------------

LogosParser::ObjectFileContext::ObjectFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::ObjectDeclarationContext* LogosParser::ObjectFileContext::objectDeclaration() {
  return getRuleContext<LogosParser::ObjectDeclarationContext>(0);
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

void LogosParser::ObjectFileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjectFile(this);
}

void LogosParser::ObjectFileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjectFile(this);
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
    setState(61);
    objectDeclaration();
    setState(63);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::IMPLEMENTS) {
      setState(62);
      objectImplements();
    }
    setState(68);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(65);
        explicitVarDec(); 
      }
      setState(70);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
    setState(74);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::VARIABLE) {
      setState(71);
      funcImplementation();
      setState(76);
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

void LogosParser::ObjectDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjectDeclaration(this);
}

void LogosParser::ObjectDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjectDeclaration(this);
}

LogosParser::ObjectDeclarationContext* LogosParser::objectDeclaration() {
  ObjectDeclarationContext *_localctx = _tracker.createInstance<ObjectDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 6, LogosParser::RuleObjectDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(77);
    match(LogosParser::OBJECT);
    setState(78);
    match(LogosParser::COLON);
    setState(79);
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

void LogosParser::InterfaceDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterfaceDeclaration(this);
}

void LogosParser::InterfaceDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterfaceDeclaration(this);
}

LogosParser::InterfaceDeclarationContext* LogosParser::interfaceDeclaration() {
  InterfaceDeclarationContext *_localctx = _tracker.createInstance<InterfaceDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 8, LogosParser::RuleInterfaceDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(81);
    match(LogosParser::INTERFACE);
    setState(82);
    match(LogosParser::COLON);
    setState(83);
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

void LogosParser::ObjectImplementsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjectImplements(this);
}

void LogosParser::ObjectImplementsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjectImplements(this);
}

LogosParser::ObjectImplementsContext* LogosParser::objectImplements() {
  ObjectImplementsContext *_localctx = _tracker.createInstance<ObjectImplementsContext>(_ctx, getState());
  enterRule(_localctx, 10, LogosParser::RuleObjectImplements);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(LogosParser::IMPLEMENTS);
    setState(86);
    match(LogosParser::COLON);
    setState(87);
    match(LogosParser::TYPE);
   
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

void LogosParser::ExplicitVarDecListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExplicitVarDecList(this);
}

void LogosParser::ExplicitVarDecListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExplicitVarDecList(this);
}

LogosParser::ExplicitVarDecListContext* LogosParser::explicitVarDecList() {
  ExplicitVarDecListContext *_localctx = _tracker.createInstance<ExplicitVarDecListContext>(_ctx, getState());
  enterRule(_localctx, 12, LogosParser::RuleExplicitVarDecList);
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
    setState(89);
    explicitVarDec();
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::COMMA) {
      setState(90);
      match(LogosParser::COMMA);
      setState(91);
      explicitVarDec();
      setState(96);
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

void LogosParser::ExplicitVarDecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExplicitVarDec(this);
}

void LogosParser::ExplicitVarDecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExplicitVarDec(this);
}

LogosParser::ExplicitVarDecContext* LogosParser::explicitVarDec() {
  ExplicitVarDecContext *_localctx = _tracker.createInstance<ExplicitVarDecContext>(_ctx, getState());
  enterRule(_localctx, 14, LogosParser::RuleExplicitVarDec);
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
    setState(97);
    match(LogosParser::VARIABLE);
    setState(98);
    match(LogosParser::COLON);
    setState(99);
    match(LogosParser::TYPE);
    setState(102);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(100);
      match(LogosParser::EQUAL);
      setState(101);
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

void LogosParser::ImplicitVarDecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImplicitVarDec(this);
}

void LogosParser::ImplicitVarDecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImplicitVarDec(this);
}

LogosParser::ImplicitVarDecContext* LogosParser::implicitVarDec() {
  ImplicitVarDecContext *_localctx = _tracker.createInstance<ImplicitVarDecContext>(_ctx, getState());
  enterRule(_localctx, 16, LogosParser::RuleImplicitVarDec);
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
    setState(104);
    match(LogosParser::VARIABLE);
    setState(107);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::EQUAL) {
      setState(105);
      match(LogosParser::EQUAL);
      setState(106);
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

void LogosParser::FuncDecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncDec(this);
}

void LogosParser::FuncDecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncDec(this);
}

LogosParser::FuncDecContext* LogosParser::funcDec() {
  FuncDecContext *_localctx = _tracker.createInstance<FuncDecContext>(_ctx, getState());
  enterRule(_localctx, 18, LogosParser::RuleFuncDec);
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
    setState(109);
    match(LogosParser::VARIABLE);
    setState(110);
    match(LogosParser::LEFT_PAREN);
    setState(112);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == LogosParser::VARIABLE) {
      setState(111);
      explicitVarDecList();
    }
    setState(114);
    match(LogosParser::RIGHT_PAREN);
    setState(115);
    match(LogosParser::COLON);
    setState(116);
    match(LogosParser::TYPE);
   
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

std::vector<LogosParser::Expr_listContext *> LogosParser::FuncCallContext::expr_list() {
  return getRuleContexts<LogosParser::Expr_listContext>();
}

LogosParser::Expr_listContext* LogosParser::FuncCallContext::expr_list(size_t i) {
  return getRuleContext<LogosParser::Expr_listContext>(i);
}


size_t LogosParser::FuncCallContext::getRuleIndex() const {
  return LogosParser::RuleFuncCall;
}

void LogosParser::FuncCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCall(this);
}

void LogosParser::FuncCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCall(this);
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
    setState(118);
    match(LogosParser::VARIABLE);
    setState(119);
    match(LogosParser::LEFT_PAREN);
    setState(121); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(120);
      expr_list();
      setState(123); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 10857677324290) != 0));
    setState(125);
    match(LogosParser::RIGHT_PAREN);
   
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

void LogosParser::FuncImplementationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncImplementation(this);
}

void LogosParser::FuncImplementationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncImplementation(this);
}

LogosParser::FuncImplementationContext* LogosParser::funcImplementation() {
  FuncImplementationContext *_localctx = _tracker.createInstance<FuncImplementationContext>(_ctx, getState());
  enterRule(_localctx, 22, LogosParser::RuleFuncImplementation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    funcDec();
    setState(128);
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

tree::TerminalNode* LogosParser::FuncBodyContext::LEFT_BRACE() {
  return getToken(LogosParser::LEFT_BRACE, 0);
}

tree::TerminalNode* LogosParser::FuncBodyContext::RIGHT_BRACE() {
  return getToken(LogosParser::RIGHT_BRACE, 0);
}

std::vector<LogosParser::StatementContext *> LogosParser::FuncBodyContext::statement() {
  return getRuleContexts<LogosParser::StatementContext>();
}

LogosParser::StatementContext* LogosParser::FuncBodyContext::statement(size_t i) {
  return getRuleContext<LogosParser::StatementContext>(i);
}


size_t LogosParser::FuncBodyContext::getRuleIndex() const {
  return LogosParser::RuleFuncBody;
}

void LogosParser::FuncBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncBody(this);
}

void LogosParser::FuncBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncBody(this);
}

LogosParser::FuncBodyContext* LogosParser::funcBody() {
  FuncBodyContext *_localctx = _tracker.createInstance<FuncBodyContext>(_ctx, getState());
  enterRule(_localctx, 24, LogosParser::RuleFuncBody);
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
    match(LogosParser::LEFT_BRACE);
    setState(134);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 10857677324290) != 0)) {
      setState(131);
      statement();
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(137);
    match(LogosParser::RIGHT_BRACE);
   
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

LogosParser::ExprContext* LogosParser::StatementContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}


size_t LogosParser::StatementContext::getRuleIndex() const {
  return LogosParser::RuleStatement;
}

void LogosParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void LogosParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

LogosParser::StatementContext* LogosParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 26, LogosParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(142);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(139);
      explicitVarDec();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(140);
      implicitVarDec();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(141);
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

//----------------- Expr_listContext ------------------------------------------------------------------

LogosParser::Expr_listContext::Expr_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<LogosParser::ExprContext *> LogosParser::Expr_listContext::expr() {
  return getRuleContexts<LogosParser::ExprContext>();
}

LogosParser::ExprContext* LogosParser::Expr_listContext::expr(size_t i) {
  return getRuleContext<LogosParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> LogosParser::Expr_listContext::COMMA() {
  return getTokens(LogosParser::COMMA);
}

tree::TerminalNode* LogosParser::Expr_listContext::COMMA(size_t i) {
  return getToken(LogosParser::COMMA, i);
}


size_t LogosParser::Expr_listContext::getRuleIndex() const {
  return LogosParser::RuleExpr_list;
}

void LogosParser::Expr_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr_list(this);
}

void LogosParser::Expr_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr_list(this);
}

LogosParser::Expr_listContext* LogosParser::expr_list() {
  Expr_listContext *_localctx = _tracker.createInstance<Expr_listContext>(_ctx, getState());
  enterRule(_localctx, 28, LogosParser::RuleExpr_list);
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
    setState(144);
    expr();
    setState(149);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == LogosParser::COMMA) {
      setState(145);
      match(LogosParser::COMMA);
      setState(146);
      expr();
      setState(151);
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

LogosParser::Binary_exprContext* LogosParser::ExprContext::binary_expr() {
  return getRuleContext<LogosParser::Binary_exprContext>(0);
}

LogosParser::Unary_exprContext* LogosParser::ExprContext::unary_expr() {
  return getRuleContext<LogosParser::Unary_exprContext>(0);
}

tree::TerminalNode* LogosParser::ExprContext::LEFT_PAREN() {
  return getToken(LogosParser::LEFT_PAREN, 0);
}

tree::TerminalNode* LogosParser::ExprContext::RIGHT_PAREN() {
  return getToken(LogosParser::RIGHT_PAREN, 0);
}


size_t LogosParser::ExprContext::getRuleIndex() const {
  return LogosParser::RuleExpr;
}

void LogosParser::ExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpr(this);
}

void LogosParser::ExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpr(this);
}

LogosParser::ExprContext* LogosParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 30, LogosParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(162);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(152);
      binary_expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(153);
      unary_expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(154);
      match(LogosParser::LEFT_PAREN);
      setState(155);
      binary_expr();
      setState(156);
      match(LogosParser::RIGHT_PAREN);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(158);
      match(LogosParser::LEFT_PAREN);
      setState(159);
      unary_expr();
      setState(160);
      match(LogosParser::RIGHT_PAREN);
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

//----------------- Binary_exprContext ------------------------------------------------------------------

LogosParser::Binary_exprContext::Binary_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

LogosParser::Unary_exprContext* LogosParser::Binary_exprContext::unary_expr() {
  return getRuleContext<LogosParser::Unary_exprContext>(0);
}

LogosParser::ExprContext* LogosParser::Binary_exprContext::expr() {
  return getRuleContext<LogosParser::ExprContext>(0);
}

tree::TerminalNode* LogosParser::Binary_exprContext::STAR() {
  return getToken(LogosParser::STAR, 0);
}

tree::TerminalNode* LogosParser::Binary_exprContext::SLASH() {
  return getToken(LogosParser::SLASH, 0);
}

tree::TerminalNode* LogosParser::Binary_exprContext::PLUS() {
  return getToken(LogosParser::PLUS, 0);
}

tree::TerminalNode* LogosParser::Binary_exprContext::MINUS() {
  return getToken(LogosParser::MINUS, 0);
}


size_t LogosParser::Binary_exprContext::getRuleIndex() const {
  return LogosParser::RuleBinary_expr;
}

void LogosParser::Binary_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBinary_expr(this);
}

void LogosParser::Binary_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBinary_expr(this);
}

LogosParser::Binary_exprContext* LogosParser::binary_expr() {
  Binary_exprContext *_localctx = _tracker.createInstance<Binary_exprContext>(_ctx, getState());
  enterRule(_localctx, 32, LogosParser::RuleBinary_expr);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(172);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(164);
      unary_expr();
      setState(165);
      _la = _input->LA(1);
      if (!(_la == LogosParser::STAR

      || _la == LogosParser::SLASH)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(166);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(168);
      unary_expr();
      setState(169);
      _la = _input->LA(1);
      if (!(_la == LogosParser::MINUS

      || _la == LogosParser::PLUS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(170);
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

//----------------- Unary_exprContext ------------------------------------------------------------------

LogosParser::Unary_exprContext::Unary_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LogosParser::Unary_exprContext::VARIABLE() {
  return getToken(LogosParser::VARIABLE, 0);
}

tree::TerminalNode* LogosParser::Unary_exprContext::INTEGER() {
  return getToken(LogosParser::INTEGER, 0);
}

tree::TerminalNode* LogosParser::Unary_exprContext::FLOAT() {
  return getToken(LogosParser::FLOAT, 0);
}

tree::TerminalNode* LogosParser::Unary_exprContext::BOOL() {
  return getToken(LogosParser::BOOL, 0);
}

tree::TerminalNode* LogosParser::Unary_exprContext::STRING() {
  return getToken(LogosParser::STRING, 0);
}

LogosParser::FuncCallContext* LogosParser::Unary_exprContext::funcCall() {
  return getRuleContext<LogosParser::FuncCallContext>(0);
}


size_t LogosParser::Unary_exprContext::getRuleIndex() const {
  return LogosParser::RuleUnary_expr;
}

void LogosParser::Unary_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnary_expr(this);
}

void LogosParser::Unary_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LogosListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnary_expr(this);
}

LogosParser::Unary_exprContext* LogosParser::unary_expr() {
  Unary_exprContext *_localctx = _tracker.createInstance<Unary_exprContext>(_ctx, getState());
  enterRule(_localctx, 34, LogosParser::RuleUnary_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(180);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(174);
      match(LogosParser::VARIABLE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(175);
      match(LogosParser::INTEGER);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(176);
      match(LogosParser::FLOAT);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(177);
      match(LogosParser::BOOL);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(178);
      match(LogosParser::STRING);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(179);
      funcCall();
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
