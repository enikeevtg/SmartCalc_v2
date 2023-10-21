#include "expression_parser.h"

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

ExpressionParser::ExpressionParser(std::queue<Token>* queue) : queue_(queue) {}

/*
PUBLIC METHODS
*/

void ExpressionParser::SetParser(const std::string& infix_expression) {
  str_ = infix_expression;
  pos_ = 0;
  last_address_ = kStack;
  CleanStack();
}

void ExpressionParser::ConvertInfixToPostfix() {
  while (!(pos_ == str_.size() && stack_.empty() == true)) {
    if (pos_ == str_.size() && last_address_ != kStack) {
      EndOfExpressionProcessing();
    } else if (pos_ == str_.size() && last_address_ == kStack) {
      throw "Error: incorrect last input token";
    } else if (str_.at(pos_) == ')') {
      CloseBracketProcessing();
    } else if (token_chars_.find(str_.at(pos_)) != std::string::npos) {
      TokenProcessing();
    } else if (str_.at(pos_) == ' ') {
      ++pos_;
    } else {
      throw std::string("Error: undefined token");
    }
  }
}

/*
PRIVATE METHODS
*/

void ExpressionParser::CleanStack() {
  std::stack<Token> empty_stack;
  stack_.swap(empty_stack);
}

void ExpressionParser::TokenProcessing() {
  if (numbers_chars_.find(str_.at(pos_)) != std::string::npos) {
    ValueTokenProcessing();
  } else if (str_.at(pos_) == 'x') {
    VariableTokenProcessing();
  } else if (operators_chars_.find(str_.at(pos_)) != std::string::npos) {
    OperatorTokenProcessing();
  } else {
    FunctionTokenProcessing();
  }
}

void ExpressionParser::ValueTokenProcessing() {
  container_.type = kNumber;
  container_.value = std::stod(str_.substr(pos_));
  queue_->push(container_);

  pos_ = str_.find_first_not_of(numbers_chars_, pos_);
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
  size_t end_pos = str_.find_first_of("(0123456789x", pos_);
  std::string function_name = str_.substr(pos_, end_pos - pos_);

  int function_id = 0;
  while (function_id < int(math_functions_names_.size()) &&
         function_name != math_functions_names_[function_id]) {
    ++function_id;
  }

  if (function_id == int(math_functions_names_.size())) {
    throw "Error: undefined token";
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
