#include "expression_parser.h"

#include <iostream>

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

  while (!(pos_ == str_.size() && stack_.empty() == true)) {
    if (pos_ == str_.size() && last_address_ != kStack) {
      EndOfExpressionProcessing();
    } else if (pos_ == str_.size() && last_address_ == kStack) {
      throw "Error: incorrect last input token";
    } else if (str_.at(pos_) == ')') {
      CloseBracketProcessing();
    } else if (token_chars.find(str_.at(pos_)) != std::string::npos) {
      TokenProcessing();
    } else if (str_.at(pos_) == ' ') {
      ++pos_;
    } else {
      throw std::string("Error: undefined token");
    }

    ///////////////////// Debug: ///////////////////////
    // std::cout << "stack_.top(): ";
    // if (stack_.empty() == false)
    //   std::cerr << int(stack_.top().type) << ' ';
    // std::cout << "queue: ";
    // if (queue_->empty() == false)
    //   if (queue_->back().type == kNumber)
    //     std::cerr << int(queue_->back().value);
    //   else
    //     std::cerr << int(queue_->back().type);
    // std::cerr << std::endl;
    ///////////////////////////////////////////////////
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
  } else if (str_.at(pos_) == 'x') {
    VariableTokenProcessing();
  } else if (operators_chars.find(str_.at(pos_)) != std::string::npos) {
    OperatorTokenProcessing();
  } else {
    FunctionTokenProcessing();
  }
}

void ExpressionParser::ValueTokenProcessing() {
  container_.type = kNumber;
  container_.value = std::stod(str_.substr(pos_));
  queue_->push(container_);

  pos_ = str_.find_first_not_of("0123456789.", pos_);
  if (pos_ > str_.size()) pos_ = str_.size();
  last_address_ = kQueue;
}

void ExpressionParser::VariableTokenProcessing() {
  container_.type = kVar;
  queue_->push(container_);

  ++pos_;
  last_address_ = kQueue;
}

void ExpressionParser::OperatorTokenProcessing() {
  char op_char = str_.at(pos_);

  if (op_char == '+' && last_address_ == kStack) {
    container_.type = kUplus;
    container_.prior = kPrior4;
  } else if (op_char == '-' && last_address_ == kStack) {
    container_.type = kUminus;
    container_.prior = kPrior4;
  } else if (op_char == '(') {
    container_.type = kOpenBracket;
    container_.prior = kPrior1;
  } else if (op_char == '+' && last_address_ == kQueue) {
    container_.type = kPlus;
    container_.prior = kPrior2;
  } else if (op_char == '-' && last_address_ == kQueue) {
    container_.type = kMinus;
    container_.prior = kPrior2;
  } else if (op_char == '*') {
    container_.type = kMult;
    container_.prior = kPrior3;
  } else if (op_char == '/') {
    container_.type = kDiv;
    container_.prior = kPrior3;
  } else if (op_char == '%') {
    container_.type = kMod;
    container_.prior = kPrior3;
  } else if (op_char == '^') {
    container_.type = kPow;
    container_.prior = kPrior3;
  }

  if (container_.type != kOpenBracket && container_.type != kPow) {
    while (stack_.empty() == false && container_.prior <= stack_.top().prior) {
      TranslateFromStackToQueue();
    }
  }
  stack_.push(container_);

  ++pos_;
  last_address_ = kStack;
}

void ExpressionParser::FunctionTokenProcessing() {
  std::vector<std::string> math_functions_names{
      "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};

  size_t end_pos = str_.find_first_of("(0123456789x", pos_);
  std::string function_name = str_.substr(pos_, end_pos - pos_);

  int function_id = 0;
  while (function_name != math_functions_names[function_id]) {
    ++function_id;
  }

  container_.type = TokenType(function_id);
  container_.prior = kPrior4;
  stack_.push(container_);

  pos_ = end_pos;
  last_address_ = kStack;
}

void ExpressionParser::CloseBracketProcessing() {
  if (last_address_ == kStack) {
    throw "Error: incorrect input";
  }

  // stack_ -> queue_ while token != '('
  while (stack_.top().type != kOpenBracket) {
    TranslateFromStackToQueue();
  }
  stack_.pop();

  // if there is unary function before the '('
  if (stack_.empty() == false && stack_.top().type < kOpenBracket) {
    TranslateFromStackToQueue();
  }

  ++pos_;
}

void ExpressionParser::EndOfExpressionProcessing() {
  while (stack_.empty() == false) {
    if (stack_.top().type == kOpenBracket) {
      throw "Error: unbalanced brackets";
    }
    TranslateFromStackToQueue();
  }
}

void ExpressionParser::TranslateFromStackToQueue() {
  queue_->push(stack_.top());
  stack_.pop();
}

}  // namespace e_calc
