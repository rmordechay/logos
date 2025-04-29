
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
    AMPERSAND = 30, PIPE = 31, CARET = 32, DOUBLE_RANGLE = 33, DOUBLE_LANGLE = 34, 
    OBJECT = 35, SINGLETON = 36, SELF_INSTANCE = 37, SELF_CLASS = 38, INTERFACE = 39, 
    ENUM = 40, VEC2 = 41, VEC3 = 42, VEC4 = 43, IMPLEMENTS = 44, IMPORT = 45, 
    IF = 46, ELSE = 47, FOR = 48, BREAK = 49, CONTINUE = 50, RETURN = 51, 
    VISIBILITY = 52, CONST = 53, AND = 54, OR = 55, NOT = 56, IN = 57, INTEGER = 58, 
    FLOAT = 59, BOOL = 60, NULL_ = 61, CONST_NAME = 62, TYPE = 63, VARIABLE = 64, 
    STRING = 65, LINE_COMMENT = 66, BLOCK_COMMENT = 67, WS = 68
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

