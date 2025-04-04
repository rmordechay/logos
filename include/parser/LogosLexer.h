
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    DOUBLE_EQUAL = 1, NOT_EQUAL = 2, GE = 3, LE = 4, LPAREN = 5, RPAREN = 6, 
    LBRACE = 7, RBRACE = 8, LBRACK = 9, RBRACK = 10, CAST = 11, LANGLE = 12, 
    RANGLE = 13, COMMA = 14, DOUBLE_DOT = 15, DOT = 16, COLON = 17, EQUAL = 18, 
    MINUS = 19, PLUS = 20, STAR = 21, SLASH = 22, HASH = 23, QUEST_MARK = 24, 
    EXCLA_MARK = 25, PERCENT = 26, DOLLAR = 27, AMPERSAND = 28, OBJECT = 29, 
    SELF_INSTANCE = 30, SELF_CLASS = 31, INTERFACE = 32, ENUM = 33, VEC = 34, 
    VEC2 = 35, VEC3 = 36, VEC4 = 37, IMPLEMENTS = 38, IMPORT = 39, IF = 40, 
    ELSE = 41, FOR = 42, BREAK = 43, CONTINUE = 44, RETURN = 45, AND = 46, 
    OR = 47, NOT = 48, IN = 49, INTEGER = 50, FLOAT = 51, BOOL = 52, NULL_ = 53, 
    CONST = 54, TYPE = 55, VARIABLE = 56, STRING = 57, LINE_COMMENT = 58, 
    BLOCK_COMMENT = 59, WS = 60
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

