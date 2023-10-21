#ifndef SMARTCALC_V2_MVCMODEL_EXPRESSION_SOLVER_H_
#define SMARTCALC_V2_MVCMODEL_EXPRESSION_SOLVER_H_

#include <cmath>
#include <queue>
#include <stack>
#include <vector>

#include "types.h"

namespace e_calc {

double UPlus(double value);
double UMinus(double value);
double Sum(double value_1, double value_2);
double Sub(double value_1, double value_2);
double Mult(double value_1, double value_2);
double Div(double value_1, double value_2);

class ExpressionSolver {
 public:
  ExpressionSolver() = default;
  explicit ExpressionSolver(std::queue<Token>* reverse_polish_notation);
  ~ExpressionSolver() = default;

  double GetResult(const double& var);

 private:
  using unary_func = double (*)(double);
  using binary_func = double (*)(double, double);

  void NumericalCalculation(const TokenType& function_id);
  void TranslateFromQueueToStack();

  inline static std::vector<unary_func> unary_functions_ = {
      std::cos,  std::sin, std::tan,   std::acos,     std::asin,     std::atan,
      std::sqrt, std::log, std::log10, e_calc::UPlus, e_calc::UMinus};
  inline static std::vector<binary_func> binary_functions_ = {
      e_calc::Sum, e_calc::Sub, e_calc::Mult, e_calc::Div, std::fmod, std::pow};

  std::queue<Token>* reverse_polish_notation_;
  std::stack<Token> stack_;
  std::queue<Token> queue_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_EXPRESSION_Solver_H_
