#ifndef SMARTCALC_V2_MVCCONTROLLER_CONTROLLER_H_
#define SMARTCALC_V2_MVCCONTROLLER_CONTROLLER_H_

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "MVCModel/expression_parser.h"
#include "MVCModel/expression_solver.h"
#include "MVCModel/token.h"

namespace e_calc {

class Controller {
 public:
  Controller();
  Controller(std::string expression, double var);
  ~Controller();

  double GetResult(double var);

 private:
  std::queue<Token> reverse_polish_notation_;
  ExpressionParser parser_;
  ExpressionSolver solver_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCCONTROLLER_CONTROLLER_H_
