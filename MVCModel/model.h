#ifndef SMARTCALC_V2_MVCMODEL_MODEL_H_
#define SMARTCALC_V2_MVCMODEL_MODEL_H_

#include "expression_parser.h"
#include "expression_solver.h"
#include "token.h"

namespace e_calc {

class Model {
 public:
  Model() : parser_(&queue_), solver_(&queue_){};
  ~Model(){};

  double GetResult(const std::string& infix_expression, const double& var) {
    CleanQueue();
    parser_.ConvertInfixToPostfix(infix_expression);
    return solver_.GetResult(var);
  }

 private:
  void CleanQueue() {
    std::queue<Token> empty_queue;
    queue_.swap(empty_queue);
  }

  std::queue<Token> queue_;
  ExpressionParser parser_;
  ExpressionSolver solver_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_MODEL_H_
