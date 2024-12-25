
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    LEFT_PAREN = 1, RIGHT_PAREN = 2, LEFT_BRACE = 3, RIGHT_BRACE = 4, LEFT_BRACKET = 5, 
    RIGHT_BRACKET = 6, LEFT_ANGLE = 7, RIGHT_ANGLE = 8, COMMA = 9, DOT = 10, 
    COLON = 11, EQUAL = 12, MINUS = 13, PLUS = 14, STAR = 15, SLASH = 16, 
    HASH = 17, QUEST_MARK = 18, EXCLA_MARK = 19, PERCENT = 20, DOLLAR = 21, 
    AMPERSAND = 22, OBJECT = 23, INTERFACE = 24, ENUM = 25, IMPLEMENTS = 26, 
    IMPORT = 27, IF = 28, FOR = 29, BREAK = 30, CONTINUE = 31, RETURN = 32, 
    AND = 33, OR = 34, NOT = 35, IN = 36, INTEGER = 37, FLOAT = 38, BOOL = 39, 
    VARIABLE = 40, TYPE = 41, CONST = 42, STRING = 43, LINE_COMMENT = 44, 
    BLOCK_COMMENT = 45, WS = 46
  };

  explicit LogosLexer(antlr4::CharStream *input);

  ~LogosLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

