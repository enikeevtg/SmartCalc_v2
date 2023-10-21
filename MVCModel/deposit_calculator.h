#ifndef SMARTCALC_V2_MVCMODEL_DEPOSIT_CALCULATOR_H_
#define SMARTCALC_V2_MVCMODEL_DEPOSIT_CALCULATOR_H_

#include <cmath>

#include "types.h"

namespace e_calc {

class DepositCalculator {
 public:
  DepositCalculator() = default;
  ~DepositCalculator() = default;

  const DepositPayments& CalculateDepositPayments(int type,
                                                  DepositTerms* terms);

 private:
  void SetDepositTerms(int type, DepositTerms* terms);

  double key_rate_{0.075};
  int deposit_type_;
  DepositTerms terms_;
  DepositPayments payments_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_DEPOSIT_CALCULATOR_H_
