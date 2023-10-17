#ifndef SMARTCALC_V2_MVCCONTROLLER_CONTROLLER_H_
#define SMARTCALC_V2_MVCCONTROLLER_CONTROLLER_H_

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "../MVCModel/smartcalc_model.h"

namespace e_calc {

class Controller {
 public:
  Controller() {}
  Controller(Model* model) : model_(model) {}
  ~Controller() {}

  void SetController(const std::string& infix_expression) {
    model_->SetModel(infix_expression, 0.0);
  }

  void SetController(const std::string& infix_expression, const double& var) {
    model_->SetModel(infix_expression, var);
  }

  void SetController(int& credit_type, double& total_amount, int& term,
                     double& rate) {
    model_->SetModel(credit_type, total_amount, term, rate);
  }

  double GetResult() { return model_->GetResult(); }

  PlotPoints GetPlotPoints(const double& x_min, const double& x_max,
                           const double& x_step) {
    return model_->GetPlotPoints(x_min, x_max, x_step);
  }

  CreditPayments& PaymentsCalculation() {
    return model_->PaymentsCalculation();
  }

 private:
  Model* model_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCCONTROLLER_CONTROLLER_H_
