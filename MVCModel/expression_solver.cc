#include "expression_solver.h"

#include <iostream>

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

ExpressionSolver::ExpressionSolver() {}

ExpressionSolver::ExpressionSolver(std::queue<Token>* reverse_polish_notation)
    : queue_(reverse_polish_notation) {}

ExpressionSolver::~ExpressionSolver() {}

/*
PUBLIC METHODS
*/

double ExpressionSolver::GetResult(const double& var) {
  while (queue_->empty() == false) {
    if (queue_->front().type == kNumber) {
      TranslateFromQueueToStack();
    } else if (queue_->front().type == kVar) {
      queue_->front().value = var;
      TranslateFromQueueToStack();
    } else {
      NumericalCalculation(queue_->front().type);
      queue_->pop();
    }
  }
  return stack_.top().value;
}

/*
NON CLASS FUNCTIONS
*/

double UPlus(double value) { return value; }
double UMinus(double value) { return -value; }
double Sum(double value_1, double value_2) { return value_1 + value_2; }
double Sub(double value_1, double value_2) { return value_1 - value_2; }
double Mult(double value_1, double value_2) { return value_1 * value_2; }
double Div(double value_1, double value_2) { return value_1 / value_2; }

/*
PRIVATE METHODS
*/

void ExpressionSolver::NumericalCalculation(const TokenType& function_id) {
  double top_value = stack_.top().value;

  if (function_id == kAcos && fabs(top_value) > 1) {
    throw "Error: acos() invalid argument";
  } else if (function_id == kAsin && fabs(top_value) > 1) {
    throw "Error: asin() invalid argument";
  } else if (function_id == kLn && top_value <= 0) {
    throw "Error: ln() invalid argument";
  } else if (function_id == kLog && top_value <= 0) {
    throw "Error: log() invalid argument";
  } else if (function_id == kSqrt && top_value < 0) {
    throw "Error: sqrt() invalid argument";
  }

  if (function_id < kOpenBracket) {
    double (*unary_functions[11])(double) = {
        cos, sin, tan, acos, asin, atan, sqrt, log, log10, UPlus, UMinus};
    stack_.top().value = unary_functions[function_id](top_value);
  } else {
    double (*binary_functions[6])(double, double) = {Sum, Sub,  Mult,
                                                     Div, fmod, pow};
    stack_.pop();
    stack_.top().value = binary_functions[function_id - kOpenBracket - 1](
        stack_.top().value, top_value);
  }
}

void ExpressionSolver::TranslateFromQueueToStack() {
  stack_.push(queue_->front());
  queue_->pop();
}

}  // namespace e_calc
