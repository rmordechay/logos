
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, DOUBLE_EQUAL = 7, 
    NOT_EQUAL = 8, GE = 9, LE = 10, LPAREN = 11, RPAREN = 12, LBRACE = 13, 
    RBRACE = 14, LBRACK = 15, RBRACK = 16, LANGLE = 17, RANGLE = 18, COMMA = 19, 
    ARROW = 20, TRIPLE_DOT = 21, DOUBLE_DOT = 22, WALRUS = 23, EQUAL_PLUS = 24, 
    EQUAL_MINUS = 25, EQUAL_STAR = 26, EQUAL_SLASH = 27, EQUAL_PERCENT = 28, 
    EQUAL_AMPERSAND = 29, EQUAL_PIPE = 30, EQUAL_CARET = 31, EQUAL_DOUBLE_RANGLE = 32, 
    EQUAL_DOUBLE_LANGLE = 33, INC = 34, DEC = 35, DOT = 36, COLON = 37, 
    EQUAL = 38, PLUS = 39, MINUS = 40, STAR = 41, SLASH = 42, HASH = 43, 
    QUEST_MARK = 44, EXCLA_MARK = 45, PERCENT = 46, DOLLAR = 47, AMPERSAND = 48, 
    PIPE = 49, CARET = 50, DOUBLE_RANGLE = 51, DOUBLE_LANGLE = 52, SLIDER = 53, 
    OBJECT = 54, SINGLETON = 55, SELF_INSTANCE = 56, SELF_CLASS = 57, INTERFACE = 58, 
    EXTERN = 59, VISIBILITY = 60, IMPLEMENTS = 61, CONST = 62, ENUM = 63, 
    GO = 64, DEFER = 65, IO = 66, FOR_IS_FIRST = 67, FOR_IS_LAST = 68, FOR_I = 69, 
    VEC2 = 70, VEC3 = 71, VEC4 = 72, IF = 73, WHILE = 74, ELSE = 75, FOR = 76, 
    BREAK = 77, CONTINUE = 78, RETURN = 79, AND = 80, OR = 81, NOT = 82, 
    IN = 83, LONG = 84, INTEGER = 85, FLOAT = 86, BOOL = 87, NULL_ = 88, 
    IDENTIFIER = 89, STRING = 90, TAG = 91, LINE_COMMENT = 92, BLOCK_COMMENT = 93, 
    WS = 94
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

