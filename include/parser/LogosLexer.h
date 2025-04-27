
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
    AMPERSAND = 30, OBJECT = 31, SINGLETON = 32, SELF_INSTANCE = 33, SELF_CLASS = 34, 
    INTERFACE = 35, ENUM = 36, VEC = 37, VEC2 = 38, VEC3 = 39, VEC4 = 40, 
    IMPLEMENTS = 41, IMPORT = 42, IF = 43, ELSE = 44, FOR = 45, BREAK = 46, 
    CONTINUE = 47, RETURN = 48, VISIBILITY = 49, CONST = 50, AND = 51, OR = 52, 
    NOT = 53, IN = 54, INTEGER = 55, FLOAT = 56, BOOL = 57, NULL_ = 58, 
    CONST_NAME = 59, TYPE = 60, VARIABLE = 61, STRING = 62, LINE_COMMENT = 63, 
    BLOCK_COMMENT = 64, WS = 65
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

