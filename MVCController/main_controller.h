#ifndef SMARTCALC_V2_MVCCONTROLLER_CONTROLLER_H_
#define SMARTCALC_V2_MVCCONTROLLER_CONTROLLER_H_

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "../MVCModel/smart_calculator.h"

namespace e_calc {

class Controller {
 public:
  Controller() {}
  Controller(Model* model) : model_(model) {}
  ~Controller() {}

  // SmartCalc
  void SetController(const std::string& infix_expression) {
    model_->SetModel(infix_expression, 0.0);
  }

  void SetController(const std::string& infix_expression, const double& var) {
    model_->SetModel(infix_expression, var);
  }

  double GetResult() { return model_->GetResult(); }

  PlotPoints GetPlotPoints(const double& x_min, const double& x_max,
                           const double& x_step) {
    return model_->GetPlotPoints(x_min, x_max, x_step);
  }

  // // Credit
  // void SetCreditController(int& credit_type, CreditTerms& terms) {
  //   model_->SetCreditTerms(credit_type, terms);
  // }

  // CreditPayments& GetCreditPayments() {  // const reference return?
  //   return model_->GetCreditPayments();
  // }

  // Deposit
  void SetDepositController(int& deposit_type, DepositTerms* terms) {
    model_->SetDepositTerms(deposit_type, terms);
  }

  DepositPayments& GetDepositPayments() {  // const reference return?
    return model_->GetDepositPayments();
  }

 private:
  Model* model_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCCONTROLLER_CONTROLLER_H_
