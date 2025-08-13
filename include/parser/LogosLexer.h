
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, DOUBLE_EQUAL = 6, 
    NOT_EQUAL = 7, GE = 8, LE = 9, LPAREN = 10, RPAREN = 11, LBRACE = 12, 
    RBRACE = 13, LBRACK = 14, RBRACK = 15, ARROW = 16, LANGLE = 17, RANGLE = 18, 
    COMMA = 19, TRIPLE_DOT = 20, DOUBLE_DOT = 21, WALRUS = 22, EQUAL_PLUS = 23, 
    EQUAL_MINUS = 24, EQUAL_STAR = 25, EQUAL_SLASH = 26, EQUAL_PERCENT = 27, 
    EQUAL_AMPERSAND = 28, EQUAL_PIPE = 29, EQUAL_CARET = 30, EQUAL_DOUBLE_RANGLE = 31, 
    EQUAL_DOUBLE_LANGLE = 32, INC = 33, DEC = 34, DOT = 35, COLON = 36, 
    EQUAL = 37, PLUS = 38, MINUS = 39, STAR = 40, SLASH = 41, HASH = 42, 
    QUEST_MARK = 43, EXCLA_MARK = 44, PERCENT = 45, DOLLAR = 46, AMPERSAND = 47, 
    PIPE = 48, CARET = 49, DOUBLE_RANGLE = 50, DOUBLE_LANGLE = 51, OBJECT = 52, 
    SINGLETON = 53, SELF_INSTANCE = 54, SELF_CLASS = 55, INTERFACE = 56, 
    EXTERN = 57, VISIBILITY = 58, IMPLEMENTS = 59, CONST = 60, ENUM = 61, 
    GO = 62, DEFER = 63, VEC2 = 64, VEC3 = 65, VEC4 = 66, IF = 67, ELSE = 68, 
    FOR = 69, BREAK = 70, CONTINUE = 71, RETURN = 72, AND = 73, OR = 74, 
    NOT = 75, IN = 76, LONG = 77, INTEGER = 78, FLOAT = 79, BOOL = 80, NULL_ = 81, 
    IDENTIFIER = 82, STRING = 83, TAG = 84, LINE_COMMENT = 85, BLOCK_COMMENT = 86, 
    WS = 87
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

