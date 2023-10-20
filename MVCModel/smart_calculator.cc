#include "smart_calculator.h"

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

Model::Model() : parser_(&queue_), solver_(&queue_) {}
Model::~Model() {}

/*
PUBLIC METHODS
*/

void Model::SetModel(const std::string& infix_expression, const double& var) {
  if (infix_expression.size() > 255) {
    throw "Error: too large expression";
  }

  str_ = infix_expression;
  var_ = var;
  CleanQueue();
  parser_.SetParser(infix_expression);
  points_.x_coord.clear();
  points_.y_coord.clear();
}

double Model::GetResult() {
  parser_.ConvertInfixToPostfix();
  return solver_.GetResult(var_);
}

PlotPoints& Model::GetPlotPoints(const double& x_min, const double& x_max,
                                 const double& x_step) {
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

// void Model::SetCreditTerms(int& credit_type, CreditTerms& terms) {
//   credit_.SetCreditTerms(credit_type, terms);
// }

// CreditPayments& Model::GetCreditPayments() {
//   return credit_.GetCreditPayments();
// }

void Model::SetDepositTerms(int& type, DepositTerms* terms) {
  deposit_.SetDepositTerms(type, terms);
}

DepositPayments& Model::GetDepositPayments() {
  return deposit_.GetDepositPayments();
}

/*
PRIVATE METHODS
*/

void Model::CleanQueue() {
  std::queue<Token> empty_queue;
  queue_.swap(empty_queue);
}

}  // namespace e_calc
