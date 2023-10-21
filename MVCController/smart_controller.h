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
  SmartController() {}
  SmartController(SmartCalculator* model) : model_(model) {}
  ~SmartController() {}

  void SetCalculator(const std::string& infix_expression) {
    model_->SetCalculator(infix_expression, 0.0);
  }

  void SetCalculator(const std::string& infix_expression, const double& var) {
    model_->SetCalculator(infix_expression, var);
  }

  double GetResult() { return model_->GetResult(); }

  const PlotPoints& GetPlotPoints(const double& x_min, const double& x_max,
                                  const double& x_step) {
    return model_->GetPlotPoints(x_min, x_max, x_step);
  }

 private:
  SmartCalculator* model_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCCONTROLLER_SMART_CONTROLLER_H_
