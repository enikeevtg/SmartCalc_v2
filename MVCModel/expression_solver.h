#ifndef SMARTCALC_V2_MVCMODEL_EXPRESSION_SOLVER_H_
#define SMARTCALC_V2_MVCMODEL_EXPRESSION_SOLVER_H_

#include <cmath>
#include <queue>
#include <stack>
#include <vector>

#include "types.h"

namespace e_calc {

class ExpressionSolver {
 public:
  ExpressionSolver();
  ExpressionSolver(std::queue<Token>* reverse_polish_notation);
  ~ExpressionSolver();

  double GetResult(const double& var);

 private:
  void NumericalCalculation(const TokenType& function_id);
  void TranslateFromQueueToStack();

  std::queue<Token>* reverse_polish_notation_;
  std::stack<Token> stack_;
  std::queue<Token> queue_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_EXPRESSION_Solver_H_
