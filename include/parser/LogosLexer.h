
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    DOUBLE_EQUAL = 1, NOT_EQUAL = 2, GE = 3, LE = 4, LPAREN = 5, RPAREN = 6, 
    LBRACE = 7, RBRACE = 8, LBRACK = 9, RBRACK = 10, LANGLE = 11, RANGLE = 12, 
    COMMA = 13, DOUBLE_DOT = 14, DOT = 15, COLON = 16, EQUAL = 17, MINUS = 18, 
    PLUS = 19, STAR = 20, SLASH = 21, HASH = 22, QUEST_MARK = 23, EXCLA_MARK = 24, 
    PERCENT = 25, DOLLAR = 26, AMPERSAND = 27, OBJECT = 28, SELF = 29, INTERFACE = 30, 
    ENUM = 31, VEC = 32, VEC2 = 33, VEC3 = 34, VEC4 = 35, IMPLEMENTS = 36, 
    IMPORT = 37, IF = 38, ELSE = 39, FOR = 40, BREAK = 41, CONTINUE = 42, 
    RETURN = 43, AND = 44, OR = 45, NOT = 46, IN = 47, INTEGER = 48, FLOAT = 49, 
    BOOL = 50, CONST = 51, TYPE = 52, VARIABLE = 53, STRING = 54, LINE_COMMENT = 55, 
    BLOCK_COMMENT = 56, WS = 57
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

