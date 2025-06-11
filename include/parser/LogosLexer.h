
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, DOUBLE_EQUAL = 4, NOT_EQUAL = 5, GE = 6, 
    LE = 7, LPAREN = 8, RPAREN = 9, LBRACE = 10, RBRACE = 11, LBRACK = 12, 
    RBRACK = 13, ARROW = 14, LANGLE = 15, RANGLE = 16, COMMA = 17, TRIPLE_DOT = 18, 
    DOUBLE_DOT = 19, WALRUS = 20, EQUAL_ADD = 21, EQUAL_SUB = 22, EQUAL_MUL = 23, 
    EQUAL_DIV = 24, INC = 25, DEC = 26, DOT = 27, COLON = 28, EQUAL = 29, 
    MINUS = 30, PLUS = 31, STAR = 32, SLASH = 33, HASH = 34, QUEST_MARK = 35, 
    EXCLA_MARK = 36, PERCENT = 37, DOLLAR = 38, AMPERSAND = 39, PIPE = 40, 
    CARET = 41, DOUBLE_RANGLE = 42, DOUBLE_LANGLE = 43, OBJECT = 44, SINGLETON = 45, 
    SELF_INSTANCE = 46, SELF_CLASS = 47, INTERFACE = 48, ENUM = 49, VEC2 = 50, 
    VEC3 = 51, VEC4 = 52, IMPLEMENTS = 53, EXTERN = 54, IF = 55, ELSE = 56, 
    FOR = 57, BREAK = 58, CONTINUE = 59, RETURN = 60, VISIBILITY = 61, CONST = 62, 
    AND = 63, OR = 64, NOT = 65, IN = 66, INTEGER = 67, FLOAT = 68, BOOL = 69, 
    NULL_ = 70, CONST_NAME = 71, TYPE = 72, VARIABLE = 73, STRING = 74, 
    TAG = 75, LINE_COMMENT = 76, BLOCK_COMMENT = 77, WS = 78
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

