#ifndef SMARTCALC_V2_MVCMODEL_MODEL_H_
#define SMARTCALC_V2_MVCMODEL_MODEL_H_

#include "expression_parser.h"
#include "expression_solver.h"
#include "types.h"

namespace e_calc {

#define EXPRESSION_MAX_SIZE 255

class SmartCalculator {
 public:
  SmartCalculator();
  ~SmartCalculator() = default;

  void SetCalculator(const std::string& infix_expression, double var);
  double GetResult();
  const PlotPoints& GetPlotPoints(double x_min, double x_max, double x_step);

 private:
  void CleanQueue();

  std::string str_;
  double var_;
  std::queue<Token> queue_;
  ExpressionParser parser_;
  ExpressionSolver solver_;
  PlotPoints points_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_MODEL_H_
