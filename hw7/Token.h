/**
 * Structs representing lexical tokens scanned from the input.
 * CSE 374 18sp, HP+MW
 */

#ifndef TOKEN_H
#define TOKEN_H

namespace cse374 {

/**
 * Lexical classes
 */
enum LexClass {
  UNKNOWN,          // illegal or unknown character
  INT,              // integer constant
  PLUS,             // operator +
  MINUS,            // operator -
  TIMES,            // operator *
  DIV,              // operator %
  SLASH,            // slash to separate numerator/denominator
  LPAREN,           // (
  RPAREN,           // )
  EOL               // end of input line
};

/**
 * Lexical token returned by scanner
 */
typedef struct Token {
  LexClass kind;   // Lexical class of the token
  int      ival;   // Integer value if kind == INT (undefined otherwise)
} Token;

}  // namespace cse374

#endif
