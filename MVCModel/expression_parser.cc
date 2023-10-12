#include "expression_parser.h"

#include <cstring>
#include <stack>
#include <string>

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

ExpressionParser::ExpressionParser() {}

ExpressionParser::ExpressionParser(const std::string& infix_expression,
                                   std::queue<Token>* reverse_polish_notation)
    : str_(infix_expression), queue_(reverse_polish_notation) {}

ExpressionParser::~ExpressionParser() {}

/*
PUBLIC METHODS
*/

void ExpressionParser::ShuntingYardAlgorithm() {
  std::string token_chars{"1234567890.+-*/^%(cstalx"};

  while (!(str_.at(pos_) >= str_.size() && stack_.empty())) {
    if (token_chars.find(str_.at(pos_)) != std::string::npos) {
      TokenProcessing();
    } else if (str_.at(pos_) == ')') {
      CloseBracketProcessing();
    } else if (str_.at(pos_) == ' ') {
      ++pos_;
    
    // if last token is not a number or ')'. make it in mvcview
    } else if (str_.at(pos_) == '\0' && last_address_ == kStack) {
      throw std::string("Error: incorrect input");
    
    } else if (str_.at(pos_) == '\0') {
      EndOfExpressionProcessing();

    // } else {
    //   throw std::string("Error: undefined token");
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
    ValueTokenProcessing();
  } else if (operators_chars.find(str_.at(pos_)) != std::string::npos) {
    // operators
  } else {
    // functions
  }
}

void ExpressionParser::ValueTokenProcessing() {
  container_.type = kNumber;
  container_.value = std::stod(str_.substr(pos_));
  queue_->push(container_);

  pos_ = str_.find_first_not_of("0123456789.", pos_);
  last_address_ = kQueue;
}

void ExpressionParser::CloseBracketProcessing() {
  if (stack_.top().type == kOpenBracket) {
    throw std::string("Error: empty brackets");
  }

  // stack_ -> queue_ while token != '('
  while (stack_.empty() == false && stack_.top().type != kOpenBracket) {
    TranslateFromStackToQueue();
  }

  // remove '(' from the stack_ or throw exception
  if (stack_.empty() == true) {
    throw std::string("Error: unbalanced brackets");
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
      throw std::string("Error: unbalanced brackets");
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
