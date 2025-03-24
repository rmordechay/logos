
// Generated from Logos.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  LogosLexer : public antlr4::Lexer {
public:
  enum {
    DOUBLE_EQUAL = 1, NOT_EQUAL = 2, GE = 3, LE = 4, LPAREN = 5, RPAREN = 6, 
    LBRACE = 7, RBRACE = 8, LBRACK = 9, RBRACK = 10, LANGLE = 11, RANGLE = 12, 
    COMMA = 13, DOUBLE_DOT = 14, DOT = 15, COLON = 16, EQUAL = 17, MINUS = 18, 
    PLUS = 19, STAR = 20, SLASH = 21, HASH = 22, QUEST_MARK = 23, EXCLA_MARK = 24, 
    PERCENT = 25, DOLLAR = 26, AMPERSAND = 27, OBJECT = 28, SELF_INSTANCE = 29, 
    SELF_CLASS = 30, INTERFACE = 31, ENUM = 32, VEC = 33, VEC2 = 34, VEC3 = 35, 
    VEC4 = 36, IMPLEMENTS = 37, IMPORT = 38, IF = 39, ELSE = 40, FOR = 41, 
    BREAK = 42, CONTINUE = 43, RETURN = 44, AND = 45, OR = 46, NOT = 47, 
    IN = 48, INTEGER = 49, FLOAT = 50, BOOL = 51, NULL_ = 52, CONST = 53, 
    TYPE = 54, VARIABLE = 55, STRING = 56, LINE_COMMENT = 57, BLOCK_COMMENT = 58, 
    WS = 59
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

