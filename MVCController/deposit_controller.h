#ifndef SMARTCALC_V2_MVCCONTROLLER_DEPOSIT_CONTROLLER_H_
#define SMARTCALC_V2_MVCCONTROLLER_DEPOSIT_CONTROLLER_H_

#include "../MVCModel/deposit_calculator.h"

namespace e_calc {

class DepositController {
 public:
  DepositController() = default;
  DepositController(DepositCalculator* model);
  ~DepositController() = default;

  const DepositPayments& CalculateDepositPayments(int deposit_type,
                                                  DepositTerms* terms);

 private:
  DepositCalculator* model_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCCONTROLLER_DEPOSIT_CONTROLLER_H_
