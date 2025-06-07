
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, DOUBLE_EQUAL = 4, NOT_EQUAL = 5, GE = 6, 
    LE = 7, LPAREN = 8, RPAREN = 9, LBRACE = 10, RBRACE = 11, LBRACK = 12, 
    RBRACK = 13, ARROW = 14, LANGLE = 15, RANGLE = 16, COMMA = 17, TRIPLE_DOT = 18, 
    DOUBLE_DOT = 19, DOT = 20, COLON = 21, EQUAL = 22, MINUS = 23, PLUS = 24, 
    STAR = 25, SLASH = 26, HASH = 27, QUEST_MARK = 28, EXCLA_MARK = 29, 
    PERCENT = 30, DOLLAR = 31, AMPERSAND = 32, PIPE = 33, CARET = 34, DOUBLE_RANGLE = 35, 
    DOUBLE_LANGLE = 36, OBJECT = 37, SINGLETON = 38, SELF_INSTANCE = 39, 
    SELF_CLASS = 40, INTERFACE = 41, ENUM = 42, VEC2 = 43, VEC3 = 44, VEC4 = 45, 
    IMPLEMENTS = 46, EXTERN = 47, IF = 48, ELSE = 49, FOR = 50, BREAK = 51, 
    CONTINUE = 52, RETURN = 53, VISIBILITY = 54, CONST = 55, AND = 56, OR = 57, 
    NOT = 58, IN = 59, INTEGER = 60, FLOAT = 61, BOOL = 62, NULL_ = 63, 
    CONST_NAME = 64, TYPE = 65, VARIABLE = 66, STRING = 67, TAG = 68, LINE_COMMENT = 69, 
    BLOCK_COMMENT = 70, WS = 71
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

