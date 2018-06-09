/**
 * Implementation of Scanner for rational number calculator
 * CSE 374, 18sp, HP+MW
 */

#include "Scanner.h"

#include <cctype>
#include <cstdlib>
#include <string>

namespace cse374 {

void Scanner::scan() {
  if (nextTok_.kind == EOL) {
    return;
  }

  // Skip whitespace.
  while (pos_ < line_.size() && isspace(line_[pos_])) {
    pos_++;
  }

  // Skipped leading whitespace. Either past end of line, or
  // next character is not blank. Return if past end of line.
  if (pos_ >= line_.size()) {
    nextTok_.kind = EOL;
    return;
  }

  // Declared here to get rid of a g++ warning
  std::string::size_type nextPos;

  // Next character is not blank. Classify and return next token.
  switch (line_[pos_]) {
  // Single-character tokens
  case '+':
    nextTok_.kind = PLUS;
    pos_++;
    return;
  case '-':
    nextTok_.kind = MINUS;
    pos_++;
    return;
  case '*':
    nextTok_.kind = TIMES;
    pos_++;
    return;
  case '%':
    nextTok_.kind = DIV;
    pos_++;
    return;
  case '/':
    nextTok_.kind = SLASH;
    pos_++;
    return;
  case '(':
    nextTok_.kind = LPAREN;
    pos_++;
    return;
  case ')':
    nextTok_.kind = RPAREN;
    pos_++;
    return;

  // Integer tokens
  case '0': case '1': case '2': case '3': case '4':
  case '5': case '6': case '7': case '8': case '9':
    // line_[pos_] is a digit.
    // Find last digit in the integer.
    nextPos = pos_ + 1;
    while (nextPos < line_.size() && isdigit(line_[nextPos])) {
      nextPos++;
    }
    // line_[pos_..nextPos-1] holds the integer characters
    nextTok_.kind = INT;
    nextTok_.ival = atoi(line_.substr(pos_, nextPos - pos_).c_str());
    pos_ = nextPos;
    return;

  // Unknown character in input
  default:
    nextTok_.kind = UNKNOWN;
    pos_++;
    return;
  }
}

void Scanner::setInput(std::string newLine) {
  line_ = newLine;
  pos_ = 0;
  nextTok_.kind = UNKNOWN;
  scan();
}

Token Scanner::token() {
  return nextTok_;
}

}  // namespace cse374
