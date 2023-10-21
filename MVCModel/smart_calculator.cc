#include "smart_calculator.h"

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

SmartCalculator::SmartCalculator() : parser_(&queue_), solver_(&queue_) {}

/*
PUBLIC METHODS
*/

void SmartCalculator::SetCalculator(const std::string& infix_expression,
                                    double var) {
  if (infix_expression.size() > EXPRESSION_MAX_SIZE) {
    throw "Error: too large expression";
  }

  str_ = infix_expression;
  var_ = var;
  CleanQueue();
  parser_.SetParser(infix_expression);
  points_.x_coord.clear();
  points_.y_coord.clear();
}

double SmartCalculator::GetResult() {
  parser_.ConvertInfixToPostfix();
  return solver_.GetResult(var_);
}

const PlotPoints& SmartCalculator::GetPlotPoints(double x_min, double x_max,
                                                 double x_step) {
  if ((x_min < -1000000) || (x_max > 1000000) || (x_min >= x_max)) {
    throw "Error: incorrect plot range";
  }

  parser_.ConvertInfixToPostfix();
  double x = x_min;
  while (x <= x_max) {
    points_.x_coord.push_back(x);
    try {
      points_.y_coord.push_back(solver_.GetResult(x));
    } catch (const char* message) {
      points_.x_coord.pop_back();
    }
    x += x_step;
  }

  return points_;
}

/*
PRIVATE METHODS
*/

void SmartCalculator::CleanQueue() {
  std::queue<Token> empty_queue;
  queue_.swap(empty_queue);
}

}  // namespace e_calc
