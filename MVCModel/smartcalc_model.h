#ifndef SMARTCALC_V2_MVCMODEL_MODEL_H_
#define SMARTCALC_V2_MVCMODEL_MODEL_H_

#include "credit_calculator.h"
#include "expression_parser.h"
#include "expression_solver.h"
#include "token.h"

namespace e_calc {

struct PlotPoints {
  std::vector<double> x_coord;
  std::vector<double> y_coord;
};

class Model {
 public:
  Model();
  ~Model();

  void SetModel(const std::string& infix_expression, const double& var);
  double GetResult();
  PlotPoints GetPlotPoints(const double& x_min, const double& x_max,
                           const double& x_step);

  void SetModel(int& credit_type, double& total_amount, int& term,
                double& rate);

  CreditPayments& PaymentsCalculation();

 private:
  void CleanQueue();

  std::string str_;
  double var_;
  std::queue<Token> queue_;
  ExpressionParser parser_;
  ExpressionSolver solver_;
  PlotPoints points_;
  CreditCalculator credit_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_MODEL_H_
