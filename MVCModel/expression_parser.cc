#include "expression_parser.h"

#include <cstring>
#include <stack>
#include <string>

namespace e_calc {

ExpressionParser::ExpressionParser() {}

ExpressionParser::ExpressionParser(const std::string& infix_expression,
                                   std::queue<Token>* reverse_polish_notation)
    : str_(infix_expression), queue_(reverse_polish_notation) {}

ExpressionParser::~ExpressionParser() {}

void ExpressionParser::ShuntingYardAlgorithm() {
  // char* ptr = str_;
  Address last_address = kStack;
  std::string token_chars{"1234567890.+-*/^%(cstalx"};

  while (!(str_.at(pos_) >= str_.size() && stack_.empty())) {
    if (token_chars.find(str_.at(pos_)) != std::string::npos) {
      TokenProcessing();
    } else if (str_.at(pos_) == ')') {
      CloseBracketProcessing();
    } else if (str_.at(pos_) == ' ') {
      ++pos_;
    } else if (str_.at(pos_) == '\0' && last_address == kStack) {
      throw "Error: incorrect input";
    } else if (str_.at(pos_) == '\0') {
      EndOfExpressionProcessing();
    } else {
      throw "Error: undefined token";
    }
  }
}

/*
PRIVATE METHODS
*/

void ExpressionParser::TokenProcessing() {
  std::string numbers_chars = "1234567890.";
  std::string operators_chars = "+-*/^%()";

  if (numbers_chars.find(str_.at(pos_)) != std::string::npos) {
    container_.type = kNumber;
    std::stod(str_.substr(pos_));
      // numbers_chars.substr(pos_,
                        //  pos_ + str_.find_first_not_of(numbers_chars, pos_)));
  } else if (operators_chars.find(str_.at(pos_)) != std::string::npos) {

  }
}

void ExpressionParser::CloseBracketProcessing() {
  if (stack_.top().type == kOpenBracket) {
    throw "Error: empty brackets";
  }

  // stack_ -> queue_ while token != '('
  while (stack_.empty() == false && stack_.top().type != kOpenBracket) {
    TranslateFromStackToQueue();
  }

  // remove '(' from the stack_
  if (stack_.empty() == true) {
    throw "Error: unbalanced brackets";
  } else {
    stack_.pop();
  }

  // if there is unary function before the '('
  if (stack_.empty() == false && stack_.top().value < kOpenBracket) {
    TranslateFromStackToQueue();
  }
}

void ExpressionParser::EndOfExpressionProcessing() {
  while (stack_.empty() == false) {
    if (stack_.top().type == kOpenBracket) {
      throw "Error: unbalanced brackets";
    } else {
      queue_->push(stack_.top());
      stack_.pop();
    }
  }
}

void ExpressionParser::TranslateFromStackToQueue() {
  queue_->push(stack_.top());
  stack_.pop();
}

}  // namespace e_calc
