
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, DOUBLE_EQUAL = 4, NOT_EQUAL = 5, GE = 6, 
    LE = 7, LPAREN = 8, RPAREN = 9, LBRACE = 10, RBRACE = 11, LBRACK = 12, 
    RBRACK = 13, ARROW = 14, LANGLE = 15, RANGLE = 16, COMMA = 17, TRIPLE_DOT = 18, 
    DOUBLE_DOT = 19, INC = 20, DEC = 21, DOT = 22, COLON = 23, EQUAL = 24, 
    MINUS = 25, PLUS = 26, STAR = 27, SLASH = 28, HASH = 29, QUEST_MARK = 30, 
    EXCLA_MARK = 31, PERCENT = 32, DOLLAR = 33, AMPERSAND = 34, PIPE = 35, 
    CARET = 36, DOUBLE_RANGLE = 37, DOUBLE_LANGLE = 38, OBJECT = 39, SINGLETON = 40, 
    SELF_INSTANCE = 41, SELF_CLASS = 42, INTERFACE = 43, ENUM = 44, VEC2 = 45, 
    VEC3 = 46, VEC4 = 47, IMPLEMENTS = 48, EXTERN = 49, IF = 50, ELSE = 51, 
    FOR = 52, BREAK = 53, CONTINUE = 54, RETURN = 55, VISIBILITY = 56, CONST = 57, 
    AND = 58, OR = 59, NOT = 60, IN = 61, INTEGER = 62, FLOAT = 63, BOOL = 64, 
    NULL_ = 65, CONST_NAME = 66, TYPE = 67, VARIABLE = 68, STRING = 69, 
    TAG = 70, LINE_COMMENT = 71, BLOCK_COMMENT = 72, WS = 73
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

