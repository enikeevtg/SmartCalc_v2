#ifndef SMARTCALC_V2_MVCMODEL_CREDIT_CALCULATOR_H_
#define SMARTCALC_V2_MVCMODEL_CREDIT_CALCULATOR_H_

#include "cmath"
#include "types.h"

namespace e_calc {

class CreditCalculator {
 public:
  CreditCalculator() = default;
  ~CreditCalculator() = default;

  const CreditPayments& CalculateCreditPayments(int credit_type,
                                                CreditTerms* terms);

 private:
  void SetCreditTerms(int credit_type, CreditTerms* terms);

  int credit_type_;
  CreditTerms terms_;
  CreditPayments payments_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_CREDIT_CALCULATOR_H_
