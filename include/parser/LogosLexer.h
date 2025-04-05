
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, DOUBLE_EQUAL = 2, NOT_EQUAL = 3, GE = 4, LE = 5, LPAREN = 6, 
    RPAREN = 7, LBRACE = 8, RBRACE = 9, LBRACK = 10, RBRACK = 11, CAST = 12, 
    LANGLE = 13, RANGLE = 14, COMMA = 15, DOUBLE_DOT = 16, DOT = 17, COLON = 18, 
    EQUAL = 19, MINUS = 20, PLUS = 21, STAR = 22, SLASH = 23, HASH = 24, 
    QUEST_MARK = 25, EXCLA_MARK = 26, PERCENT = 27, DOLLAR = 28, AMPERSAND = 29, 
    OBJECT = 30, SELF_INSTANCE = 31, SELF_CLASS = 32, INTERFACE = 33, ENUM = 34, 
    VEC = 35, VEC2 = 36, VEC3 = 37, VEC4 = 38, IMPLEMENTS = 39, IMPORT = 40, 
    IF = 41, ELSE = 42, FOR = 43, BREAK = 44, CONTINUE = 45, RETURN = 46, 
    AND = 47, OR = 48, NOT = 49, IN = 50, INTEGER = 51, FLOAT = 52, BOOL = 53, 
    NULL_ = 54, CONST = 55, TYPE = 56, VARIABLE = 57, STRING = 58, LINE_COMMENT = 59, 
    BLOCK_COMMENT = 60, WS = 61
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

