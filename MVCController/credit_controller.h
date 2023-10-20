#ifndef SMARTCALC_V2_MVCCONTROLLER_CREDIT_CONTROLLER_H_
#define SMARTCALC_V2_MVCCONTROLLER_CREDIT_CONTROLLER_H_

#include "../MVCModel/credit_calculator.h"

namespace e_calc {

class CreditController {
 public:
  CreditController() = default;
  CreditController(CreditCalculator* model) : model_(model) {}
  ~CreditController() = default;

  const CreditPayments& CalculateCreditPayments(int credit_type,
                                                CreditTerms* terms) {
    return model_->CalculateCreditPayments(credit_type, terms);
  }

 private:
  CreditCalculator* model_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCCONTROLLER_CREDIT_CONTROLLER_H_
