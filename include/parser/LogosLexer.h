
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    DOUBLE_EQUAL = 8, NOT_EQUAL = 9, GE = 10, LE = 11, LPAREN = 12, RPAREN = 13, 
    LBRACE = 14, RBRACE = 15, LBRACK = 16, RBRACK = 17, LANGLE = 18, RANGLE = 19, 
    COMMA = 20, ARROW = 21, TRIPLE_DOT = 22, DOUBLE_DOT = 23, WALRUS = 24, 
    EQUAL_PLUS = 25, EQUAL_MINUS = 26, EQUAL_STAR = 27, EQUAL_SLASH = 28, 
    EQUAL_PERCENT = 29, EQUAL_AMPERSAND = 30, EQUAL_PIPE = 31, EQUAL_CARET = 32, 
    EQUAL_DOUBLE_RANGLE = 33, EQUAL_DOUBLE_LANGLE = 34, INC = 35, DEC = 36, 
    DOT = 37, COLON = 38, EQUAL = 39, PLUS = 40, MINUS = 41, STAR = 42, 
    SLIDER = 43, SLASH = 44, HASH = 45, QUEST_MARK = 46, EXCLA_MARK = 47, 
    PERCENT = 48, DOLLAR = 49, AMPERSAND = 50, PIPE = 51, CARET = 52, DOUBLE_RANGLE = 53, 
    DOUBLE_LANGLE = 54, OBJECT = 55, SINGLETON = 56, SELF_INSTANCE = 57, 
    SELF_CLASS = 58, INTERFACE = 59, EXTERN = 60, VISIBILITY = 61, IMPLEMENTS = 62, 
    CONST = 63, ENUM = 64, GO = 65, DEFER = 66, IO = 67, OWNER = 68, AND = 69, 
    OR = 70, NOT = 71, IN = 72, IF = 73, WHILE = 74, ELSE = 75, BREAK = 76, 
    CONTINUE = 77, RETURN = 78, FOR = 79, FOREVER = 80, FOR_IS_FIRST = 81, 
    FOR_IS_LAST = 82, FOR_I = 83, VEC2 = 84, VEC3 = 85, VEC4 = 86, LONG = 87, 
    INTEGER = 88, FLOAT = 89, BOOL = 90, NULL_ = 91, IDENTIFIER = 92, STRING = 93, 
    TAG = 94, LINE_COMMENT = 95, BLOCK_COMMENT = 96, WS = 97
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

