
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, DOUBLE_EQUAL = 3, NOT_EQUAL = 4, GE = 5, LE = 6, 
    LPAREN = 7, RPAREN = 8, LBRACE = 9, RBRACE = 10, LBRACK = 11, RBRACK = 12, 
    CAST = 13, LANGLE = 14, RANGLE = 15, COMMA = 16, DOUBLE_DOT = 17, DOT = 18, 
    COLON = 19, EQUAL = 20, MINUS = 21, PLUS = 22, STAR = 23, SLASH = 24, 
    HASH = 25, QUEST_MARK = 26, EXCLA_MARK = 27, PERCENT = 28, DOLLAR = 29, 
    AMPERSAND = 30, OBJECT = 31, SELF_INSTANCE = 32, SELF_CLASS = 33, INTERFACE = 34, 
    ENUM = 35, VEC = 36, VEC2 = 37, VEC3 = 38, VEC4 = 39, IMPLEMENTS = 40, 
    IMPORT = 41, IF = 42, ELSE = 43, FOR = 44, BREAK = 45, CONTINUE = 46, 
    RETURN = 47, VISIBILITY = 48, CONST = 49, AND = 50, OR = 51, NOT = 52, 
    IN = 53, INTEGER = 54, FLOAT = 55, BOOL = 56, NULL_ = 57, CONST_NAME = 58, 
    TYPE = 59, VARIABLE = 60, STRING = 61, LINE_COMMENT = 62, BLOCK_COMMENT = 63, 
    WS = 64
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

