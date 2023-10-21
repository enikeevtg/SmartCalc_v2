#ifndef SMARTCALC_V2_MVCMODEL_MODEL_H_
#define SMARTCALC_V2_MVCMODEL_MODEL_H_

#include "expression_parser.h"
#include "expression_solver.h"
#include "types.h"

namespace e_calc {

#define EXPRESSION_MAX_SIZE 255

struct PlotPoints {
  std::vector<double> x_coord;
  std::vector<double> y_coord;
};

class Model {
 public:
  Model();
  ~Model() = default;

  void SetModel(const std::string& infix_expression, const double& var);
  double GetResult();
  PlotPoints& GetPlotPoints(const double& x_min, const double& x_max,
                            const double& x_step);

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
