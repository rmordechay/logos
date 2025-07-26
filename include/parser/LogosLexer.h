
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, DOUBLE_EQUAL = 4, NOT_EQUAL = 5, GE = 6, 
    LE = 7, LPAREN = 8, RPAREN = 9, LBRACE = 10, RBRACE = 11, LBRACK = 12, 
    RBRACK = 13, ARROW = 14, LANGLE = 15, RANGLE = 16, COMMA = 17, TRIPLE_DOT = 18, 
    DOUBLE_DOT = 19, WALRUS = 20, EQUAL_PLUS = 21, EQUAL_MINUS = 22, EQUAL_STAR = 23, 
    EQUAL_SLASH = 24, EQUAL_PERCENT = 25, EQUAL_AMPERSAND = 26, EQUAL_PIPE = 27, 
    EQUAL_CARET = 28, EQUAL_DOUBLE_RANGLE = 29, EQUAL_DOUBLE_LANGLE = 30, 
    INC = 31, DEC = 32, DOT = 33, COLON = 34, EQUAL = 35, PLUS = 36, MINUS = 37, 
    STAR = 38, SLASH = 39, HASH = 40, QUEST_MARK = 41, EXCLA_MARK = 42, 
    PERCENT = 43, DOLLAR = 44, AMPERSAND = 45, PIPE = 46, CARET = 47, DOUBLE_RANGLE = 48, 
    DOUBLE_LANGLE = 49, OBJECT = 50, SINGLETON = 51, SELF_INSTANCE = 52, 
    SELF_CLASS = 53, INTERFACE = 54, EXTERN = 55, VISIBILITY = 56, IMPLEMENTS = 57, 
    CONST = 58, ENUM = 59, GO = 60, VEC2 = 61, VEC3 = 62, VEC4 = 63, IF = 64, 
    ELSE = 65, FOR = 66, BREAK = 67, CONTINUE = 68, RETURN = 69, AND = 70, 
    OR = 71, NOT = 72, IN = 73, INTEGER = 74, FLOAT = 75, BOOL = 76, NULL_ = 77, 
    IDENTIFIER = 78, STRING = 79, TAG = 80, LINE_COMMENT = 81, BLOCK_COMMENT = 82, 
    WS = 83
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

