
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    DOUBLE_EQUAL = 1, GE = 2, LE = 3, LPAREN = 4, RPAREN = 5, LBRACE = 6, 
    RBRACE = 7, LBRACK = 8, RBRACK = 9, LANGLE = 10, RANGLE = 11, COMMA = 12, 
    DOUBLE_DOT = 13, DOT = 14, COLON = 15, EQUAL = 16, MINUS = 17, PLUS = 18, 
    STAR = 19, SLASH = 20, HASH = 21, QUEST_MARK = 22, EXCLA_MARK = 23, 
    PERCENT = 24, DOLLAR = 25, AMPERSAND = 26, OBJECT = 27, INTERFACE = 28, 
    ENUM = 29, IMPLEMENTS = 30, IMPORT = 31, IF = 32, ELSE = 33, FOR = 34, 
    BREAK = 35, CONTINUE = 36, RETURN = 37, AND = 38, OR = 39, NOT = 40, 
    IN = 41, INTEGER = 42, FLOAT = 43, BOOL = 44, CONST = 45, TYPE = 46, 
    VARIABLE = 47, STRING = 48, LINE_COMMENT = 49, BLOCK_COMMENT = 50, WS = 51
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

