
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, DOUBLE_EQUAL = 5, NOT_EQUAL = 6, 
    GE = 7, LE = 8, LPAREN = 9, RPAREN = 10, LBRACE = 11, RBRACE = 12, LBRACK = 13, 
    RBRACK = 14, ARROW = 15, LANGLE = 16, RANGLE = 17, COMMA = 18, TRIPLE_DOT = 19, 
    DOUBLE_DOT = 20, WALRUS = 21, EQUAL_PLUS = 22, EQUAL_MINUS = 23, EQUAL_STAR = 24, 
    EQUAL_SLASH = 25, EQUAL_PERCENT = 26, EQUAL_AMPERSAND = 27, EQUAL_PIPE = 28, 
    EQUAL_CARET = 29, EQUAL_DOUBLE_RANGLE = 30, EQUAL_DOUBLE_LANGLE = 31, 
    INC = 32, DEC = 33, DOT = 34, COLON = 35, EQUAL = 36, PLUS = 37, MINUS = 38, 
    STAR = 39, SLASH = 40, HASH = 41, QUEST_MARK = 42, EXCLA_MARK = 43, 
    PERCENT = 44, DOLLAR = 45, AMPERSAND = 46, PIPE = 47, CARET = 48, DOUBLE_RANGLE = 49, 
    DOUBLE_LANGLE = 50, OBJECT = 51, SINGLETON = 52, SELF_INSTANCE = 53, 
    SELF_CLASS = 54, INTERFACE = 55, EXTERN = 56, VISIBILITY = 57, IMPLEMENTS = 58, 
    CONST = 59, ENUM = 60, GO = 61, VEC2 = 62, VEC3 = 63, VEC4 = 64, IF = 65, 
    ELSE = 66, FOR = 67, BREAK = 68, CONTINUE = 69, RETURN = 70, AND = 71, 
    OR = 72, NOT = 73, IN = 74, INTEGER = 75, FLOAT = 76, BOOL = 77, NULL_ = 78, 
    IDENTIFIER = 79, STRING = 80, TAG = 81, LINE_COMMENT = 82, BLOCK_COMMENT = 83, 
    WS = 84
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

