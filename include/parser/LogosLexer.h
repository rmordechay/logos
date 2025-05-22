
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, DOUBLE_EQUAL = 3, NOT_EQUAL = 4, GE = 5, LE = 6, 
    LPAREN = 7, RPAREN = 8, LBRACE = 9, RBRACE = 10, LBRACK = 11, RBRACK = 12, 
    CAST = 13, LANGLE = 14, RANGLE = 15, COMMA = 16, TRIPLE_DOT = 17, DOUBLE_DOT = 18, 
    DOT = 19, COLON = 20, EQUAL = 21, MINUS = 22, PLUS = 23, STAR = 24, 
    SLASH = 25, HASH = 26, QUEST_MARK = 27, EXCLA_MARK = 28, PERCENT = 29, 
    DOLLAR = 30, AMPERSAND = 31, PIPE = 32, CARET = 33, DOUBLE_RANGLE = 34, 
    DOUBLE_LANGLE = 35, OBJECT = 36, SINGLETON = 37, SELF_INSTANCE = 38, 
    SELF_CLASS = 39, INTERFACE = 40, ENUM = 41, VEC2 = 42, VEC3 = 43, VEC4 = 44, 
    IMPLEMENTS = 45, IMPORT = 46, IF = 47, ELSE = 48, FOR = 49, BREAK = 50, 
    CONTINUE = 51, RETURN = 52, VISIBILITY = 53, CONST = 54, AND = 55, OR = 56, 
    NOT = 57, IN = 58, INTEGER = 59, FLOAT = 60, BOOL = 61, NULL_ = 62, 
    CONST_NAME = 63, TYPE = 64, VARIABLE = 65, STRING = 66, LINE_COMMENT = 67, 
    BLOCK_COMMENT = 68, WS = 69
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

