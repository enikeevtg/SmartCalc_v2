#ifndef SMARTCALC_V2_MVCCONTROLLER_SMART_CONTROLLER_H_
#define SMARTCALC_V2_MVCCONTROLLER_SMART_CONTROLLER_H_

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "../MVCModel/smart_calculator.h"

namespace e_calc {

class SmartController {
 public:
  SmartController() = default;
  SmartController(SmartCalculator* model);
  ~SmartController() = default;

  void SetCalculator(const std::string& infix_expression);
  void SetCalculator(const std::string& infix_expression, const double& var);
  double GetResult();
  const PlotPoints& GetPlotPoints(double x_min, double x_max, double x_step);

 private:
  SmartCalculator* model_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCCONTROLLER_SMART_CONTROLLER_H_
