
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
    EQUAL = 38, PLUS = 39, MINUS = 40, STAR = 41, SLIDER = 42, SLASH = 43, 
    HASH = 44, QUEST_MARK = 45, EXCLA_MARK = 46, PERCENT = 47, DOLLAR = 48, 
    AMPERSAND = 49, PIPE = 50, CARET = 51, DOUBLE_RANGLE = 52, DOUBLE_LANGLE = 53, 
    OBJECT = 54, SINGLETON = 55, SELF_INSTANCE = 56, SELF_CLASS = 57, INTERFACE = 58, 
    EXTERN = 59, VISIBILITY = 60, IMPLEMENTS = 61, CONST = 62, ENUM = 63, 
    GO = 64, DEFER = 65, IO = 66, OWNER = 67, AND = 68, OR = 69, NOT = 70, 
    IN = 71, IF = 72, WHILE = 73, ELSE = 74, BREAK = 75, CONTINUE = 76, 
    RETURN = 77, FOR = 78, FOR_I = 79, FOREVER = 80, FOR_PREV = 81, FOR_NEXT = 82, 
    FOR_IS_FIRST = 83, FOR_IS_LAST = 84, JSON = 85, SET = 86, VEC2 = 87, 
    VEC3 = 88, VEC4 = 89, LONG = 90, INTEGER = 91, FLOAT = 92, BOOL = 93, 
    NULL_ = 94, IDENTIFIER = 95, STRING = 96, TAG = 97, LINE_COMMENT = 98, 
    BLOCK_COMMENT = 99, WS = 100
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

